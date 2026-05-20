/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

rnbomatic()
{
}

~rnbomatic()
{
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number samplerate() {
    return this->sr;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);

    this->freqshift_tilde_11_perform(
        in1,
        this->freqshift_tilde_11_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_12_perform(this->signals[0], this->signals[1], n);

    this->freqshift_tilde_05_perform(
        in1,
        this->freqshift_tilde_05_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_06_perform(this->signals[0], this->signals[2], n);

    this->freqshift_tilde_01_perform(
        in1,
        this->freqshift_tilde_01_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_02_perform(this->signals[0], this->signals[3], n);

    this->freqshift_tilde_35_perform(
        in1,
        this->freqshift_tilde_35_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_36_perform(this->signals[0], this->signals[4], n);

    this->freqshift_tilde_31_perform(
        in1,
        this->freqshift_tilde_31_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_32_perform(this->signals[0], this->signals[5], n);

    this->freqshift_tilde_28_perform(
        in1,
        this->freqshift_tilde_28_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_29_perform(this->signals[0], this->signals[6], n);

    this->freqshift_tilde_24_perform(
        in1,
        this->freqshift_tilde_24_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_25_perform(this->signals[0], this->signals[7], n);

    this->freqshift_tilde_20_perform(
        in1,
        this->freqshift_tilde_20_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_21_perform(this->signals[0], this->signals[8], n);

    this->freqshift_tilde_16_perform(
        in1,
        this->freqshift_tilde_16_frequency,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_17_perform(this->signals[0], this->signals[9], n);
    this->gaintilde_01_perform(in1, this->signals[0], n);

    this->freqshift_tilde_12_perform(
        in1,
        this->freqshift_tilde_12_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_13_perform(this->signals[10], this->signals[11], n);

    this->freqshift_tilde_02_perform(
        in1,
        this->freqshift_tilde_02_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_03_perform(this->signals[10], this->signals[12], n);

    this->freqshift_tilde_06_perform(
        in1,
        this->freqshift_tilde_06_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_07_perform(this->signals[10], this->signals[13], n);

    this->freqshift_tilde_09_perform(
        in1,
        this->freqshift_tilde_09_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_10_perform(this->signals[10], this->signals[14], n);

    this->freqshift_tilde_13_perform(
        in1,
        this->freqshift_tilde_13_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_14_perform(this->signals[10], this->signals[15], n);

    this->freqshift_tilde_17_perform(
        in1,
        this->freqshift_tilde_17_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_18_perform(this->signals[10], this->signals[16], n);

    this->freqshift_tilde_21_perform(
        in1,
        this->freqshift_tilde_21_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_22_perform(this->signals[10], this->signals[17], n);

    this->freqshift_tilde_08_perform(
        in1,
        this->freqshift_tilde_08_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_09_perform(this->signals[10], this->signals[18], n);

    this->freqshift_tilde_25_perform(
        in1,
        this->freqshift_tilde_25_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_26_perform(this->signals[10], this->signals[19], n);

    this->freqshift_tilde_29_perform(
        in1,
        this->freqshift_tilde_29_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_30_perform(this->signals[10], this->signals[20], n);

    this->freqshift_tilde_33_perform(
        in1,
        this->freqshift_tilde_33_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_34_perform(this->signals[10], this->signals[21], n);

    this->freqshift_tilde_37_perform(
        in1,
        this->freqshift_tilde_37_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_38_perform(this->signals[10], this->signals[22], n);

    this->freqshift_tilde_38_perform(
        in1,
        this->freqshift_tilde_38_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_39_perform(this->signals[10], this->signals[23], n);

    this->freqshift_tilde_34_perform(
        in1,
        this->freqshift_tilde_34_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_35_perform(this->signals[10], this->signals[24], n);

    this->freqshift_tilde_30_perform(
        in1,
        this->freqshift_tilde_30_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_31_perform(this->signals[10], this->signals[25], n);

    this->freqshift_tilde_26_perform(
        in1,
        this->freqshift_tilde_26_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_27_perform(this->signals[10], this->signals[26], n);

    this->freqshift_tilde_22_perform(
        in1,
        this->freqshift_tilde_22_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_23_perform(this->signals[10], this->signals[27], n);

    this->freqshift_tilde_18_perform(
        in1,
        this->freqshift_tilde_18_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_19_perform(this->signals[10], this->signals[28], n);

    this->freqshift_tilde_14_perform(
        in1,
        this->freqshift_tilde_14_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_15_perform(this->signals[10], this->signals[29], n);

    this->freqshift_tilde_10_perform(
        in1,
        this->freqshift_tilde_10_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_11_perform(this->signals[10], this->signals[30], n);

    this->freqshift_tilde_07_perform(
        in1,
        this->freqshift_tilde_07_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_08_perform(this->signals[10], this->signals[31], n);

    this->freqshift_tilde_03_perform(
        in1,
        this->freqshift_tilde_03_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_04_perform(this->signals[10], this->signals[32], n);

    this->freqshift_tilde_39_perform(
        in1,
        this->freqshift_tilde_39_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_40_perform(this->signals[10], this->signals[33], n);

    this->freqshift_tilde_36_perform(
        in1,
        this->freqshift_tilde_36_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_37_perform(this->signals[10], this->signals[34], n);

    this->freqshift_tilde_32_perform(
        in1,
        this->freqshift_tilde_32_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_33_perform(this->signals[10], this->signals[35], n);

    this->freqshift_tilde_27_perform(
        in1,
        this->freqshift_tilde_27_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_28_perform(this->signals[10], this->signals[36], n);

    this->freqshift_tilde_23_perform(
        in1,
        this->freqshift_tilde_23_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_24_perform(this->signals[10], this->signals[37], n);

    this->freqshift_tilde_04_perform(
        in1,
        this->freqshift_tilde_04_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_05_perform(this->signals[10], this->signals[38], n);

    this->freqshift_tilde_19_perform(
        in1,
        this->freqshift_tilde_19_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_20_perform(this->signals[10], this->signals[39], n);

    this->freqshift_tilde_15_perform(
        in1,
        this->freqshift_tilde_15_frequency,
        this->signals[10],
        this->dummyBuffer,
        n
    );

    this->gaintilde_16_perform(this->signals[10], this->signals[40], n);

    this->signaladder_01_perform(
        this->signals[1],
        this->signals[2],
        this->signals[3],
        this->signals[4],
        this->signals[5],
        this->signals[6],
        this->signals[7],
        this->signals[8],
        this->signals[9],
        this->signals[0],
        this->signals[11],
        this->signals[12],
        this->signals[13],
        this->signals[18],
        this->signals[14],
        this->signals[15],
        this->signals[16],
        this->signals[17],
        this->signals[19],
        this->signals[20],
        this->signals[21],
        this->signals[22],
        this->signals[23],
        this->signals[24],
        this->signals[25],
        this->signals[26],
        this->signals[27],
        this->signals[28],
        this->signals[29],
        this->signals[30],
        this->signals[31],
        this->signals[32],
        this->signals[33],
        this->signals[34],
        this->signals[35],
        this->signals[36],
        this->signals[37],
        this->signals[39],
        this->signals[38],
        this->signals[40],
        this->signals[40],
        n
    );

    this->limi_01_perform(this->signals[40], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 41; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->freqshift_tilde_11_dspsetup(forceDSPSetup);
    this->gaintilde_12_dspsetup(forceDSPSetup);
    this->freqshift_tilde_05_dspsetup(forceDSPSetup);
    this->gaintilde_06_dspsetup(forceDSPSetup);
    this->freqshift_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_02_dspsetup(forceDSPSetup);
    this->freqshift_tilde_35_dspsetup(forceDSPSetup);
    this->gaintilde_36_dspsetup(forceDSPSetup);
    this->freqshift_tilde_31_dspsetup(forceDSPSetup);
    this->gaintilde_32_dspsetup(forceDSPSetup);
    this->freqshift_tilde_28_dspsetup(forceDSPSetup);
    this->gaintilde_29_dspsetup(forceDSPSetup);
    this->freqshift_tilde_24_dspsetup(forceDSPSetup);
    this->gaintilde_25_dspsetup(forceDSPSetup);
    this->freqshift_tilde_20_dspsetup(forceDSPSetup);
    this->gaintilde_21_dspsetup(forceDSPSetup);
    this->freqshift_tilde_16_dspsetup(forceDSPSetup);
    this->gaintilde_17_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
    this->freqshift_tilde_12_dspsetup(forceDSPSetup);
    this->gaintilde_13_dspsetup(forceDSPSetup);
    this->freqshift_tilde_02_dspsetup(forceDSPSetup);
    this->gaintilde_03_dspsetup(forceDSPSetup);
    this->freqshift_tilde_06_dspsetup(forceDSPSetup);
    this->gaintilde_07_dspsetup(forceDSPSetup);
    this->freqshift_tilde_09_dspsetup(forceDSPSetup);
    this->gaintilde_10_dspsetup(forceDSPSetup);
    this->freqshift_tilde_13_dspsetup(forceDSPSetup);
    this->gaintilde_14_dspsetup(forceDSPSetup);
    this->freqshift_tilde_17_dspsetup(forceDSPSetup);
    this->gaintilde_18_dspsetup(forceDSPSetup);
    this->freqshift_tilde_21_dspsetup(forceDSPSetup);
    this->gaintilde_22_dspsetup(forceDSPSetup);
    this->freqshift_tilde_08_dspsetup(forceDSPSetup);
    this->gaintilde_09_dspsetup(forceDSPSetup);
    this->freqshift_tilde_25_dspsetup(forceDSPSetup);
    this->gaintilde_26_dspsetup(forceDSPSetup);
    this->freqshift_tilde_29_dspsetup(forceDSPSetup);
    this->gaintilde_30_dspsetup(forceDSPSetup);
    this->freqshift_tilde_33_dspsetup(forceDSPSetup);
    this->gaintilde_34_dspsetup(forceDSPSetup);
    this->freqshift_tilde_37_dspsetup(forceDSPSetup);
    this->gaintilde_38_dspsetup(forceDSPSetup);
    this->freqshift_tilde_38_dspsetup(forceDSPSetup);
    this->gaintilde_39_dspsetup(forceDSPSetup);
    this->freqshift_tilde_34_dspsetup(forceDSPSetup);
    this->gaintilde_35_dspsetup(forceDSPSetup);
    this->freqshift_tilde_30_dspsetup(forceDSPSetup);
    this->gaintilde_31_dspsetup(forceDSPSetup);
    this->freqshift_tilde_26_dspsetup(forceDSPSetup);
    this->gaintilde_27_dspsetup(forceDSPSetup);
    this->freqshift_tilde_22_dspsetup(forceDSPSetup);
    this->gaintilde_23_dspsetup(forceDSPSetup);
    this->freqshift_tilde_18_dspsetup(forceDSPSetup);
    this->gaintilde_19_dspsetup(forceDSPSetup);
    this->freqshift_tilde_14_dspsetup(forceDSPSetup);
    this->gaintilde_15_dspsetup(forceDSPSetup);
    this->freqshift_tilde_10_dspsetup(forceDSPSetup);
    this->gaintilde_11_dspsetup(forceDSPSetup);
    this->freqshift_tilde_07_dspsetup(forceDSPSetup);
    this->gaintilde_08_dspsetup(forceDSPSetup);
    this->freqshift_tilde_03_dspsetup(forceDSPSetup);
    this->gaintilde_04_dspsetup(forceDSPSetup);
    this->freqshift_tilde_39_dspsetup(forceDSPSetup);
    this->gaintilde_40_dspsetup(forceDSPSetup);
    this->freqshift_tilde_36_dspsetup(forceDSPSetup);
    this->gaintilde_37_dspsetup(forceDSPSetup);
    this->freqshift_tilde_32_dspsetup(forceDSPSetup);
    this->gaintilde_33_dspsetup(forceDSPSetup);
    this->freqshift_tilde_27_dspsetup(forceDSPSetup);
    this->gaintilde_28_dspsetup(forceDSPSetup);
    this->freqshift_tilde_23_dspsetup(forceDSPSetup);
    this->gaintilde_24_dspsetup(forceDSPSetup);
    this->freqshift_tilde_04_dspsetup(forceDSPSetup);
    this->gaintilde_05_dspsetup(forceDSPSetup);
    this->freqshift_tilde_19_dspsetup(forceDSPSetup);
    this->gaintilde_20_dspsetup(forceDSPSetup);
    this->freqshift_tilde_15_dspsetup(forceDSPSetup);
    this->gaintilde_16_dspsetup(forceDSPSetup);
    this->limi_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}

void initialize() {
    this->assign_defaults();
    this->setState();
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "h4"));
    this->param_02_getPresetValue(getSubState(preset, "h3"));
    this->param_03_getPresetValue(getSubState(preset, "freq"));
    this->param_04_getPresetValue(getSubState(preset, "h2"));
    this->param_05_getPresetValue(getSubState(preset, "f"));
    this->param_06_getPresetValue(getSubState(preset, "h8"));
    this->param_07_getPresetValue(getSubState(preset, "h7"));
    this->param_08_getPresetValue(getSubState(preset, "h6"));
    this->param_09_getPresetValue(getSubState(preset, "h5"));
    this->param_10_getPresetValue(getSubState(preset, "h12"));
    this->param_11_getPresetValue(getSubState(preset, "h11"));
    this->param_12_getPresetValue(getSubState(preset, "h10"));
    this->param_13_getPresetValue(getSubState(preset, "h9"));
    this->param_14_getPresetValue(getSubState(preset, "h16"));
    this->param_15_getPresetValue(getSubState(preset, "h15"));
    this->param_16_getPresetValue(getSubState(preset, "h14"));
    this->param_17_getPresetValue(getSubState(preset, "h13"));
    this->param_18_getPresetValue(getSubState(preset, "h20"));
    this->param_19_getPresetValue(getSubState(preset, "h19"));
    this->param_20_getPresetValue(getSubState(preset, "h18"));
    this->param_21_getPresetValue(getSubState(preset, "h17"));
    this->param_22_getPresetValue(getSubState(preset, "h23"));
    this->param_23_getPresetValue(getSubState(preset, "h24"));
    this->param_24_getPresetValue(getSubState(preset, "h22"));
    this->param_25_getPresetValue(getSubState(preset, "h21"));
    this->param_26_getPresetValue(getSubState(preset, "h26"));
    this->param_27_getPresetValue(getSubState(preset, "h25"));
    this->param_28_getPresetValue(getSubState(preset, "h28"));
    this->param_29_getPresetValue(getSubState(preset, "h27"));
    this->param_30_getPresetValue(getSubState(preset, "h32"));
    this->param_31_getPresetValue(getSubState(preset, "h31"));
    this->param_32_getPresetValue(getSubState(preset, "h30"));
    this->param_33_getPresetValue(getSubState(preset, "h29"));
    this->param_34_getPresetValue(getSubState(preset, "h36"));
    this->param_35_getPresetValue(getSubState(preset, "h35"));
    this->param_36_getPresetValue(getSubState(preset, "h34"));
    this->param_37_getPresetValue(getSubState(preset, "h33"));
    this->param_38_getPresetValue(getSubState(preset, "h40"));
    this->param_39_getPresetValue(getSubState(preset, "h39"));
    this->param_40_getPresetValue(getSubState(preset, "h38"));
    this->param_41_getPresetValue(getSubState(preset, "h37"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "h4"));
    this->param_02_setPresetValue(getSubState(preset, "h3"));
    this->param_03_setPresetValue(getSubState(preset, "freq"));
    this->param_04_setPresetValue(getSubState(preset, "h2"));
    this->param_05_setPresetValue(getSubState(preset, "f"));
    this->param_06_setPresetValue(getSubState(preset, "h8"));
    this->param_07_setPresetValue(getSubState(preset, "h7"));
    this->param_08_setPresetValue(getSubState(preset, "h6"));
    this->param_09_setPresetValue(getSubState(preset, "h5"));
    this->param_10_setPresetValue(getSubState(preset, "h12"));
    this->param_11_setPresetValue(getSubState(preset, "h11"));
    this->param_12_setPresetValue(getSubState(preset, "h10"));
    this->param_13_setPresetValue(getSubState(preset, "h9"));
    this->param_14_setPresetValue(getSubState(preset, "h16"));
    this->param_15_setPresetValue(getSubState(preset, "h15"));
    this->param_16_setPresetValue(getSubState(preset, "h14"));
    this->param_17_setPresetValue(getSubState(preset, "h13"));
    this->param_18_setPresetValue(getSubState(preset, "h20"));
    this->param_19_setPresetValue(getSubState(preset, "h19"));
    this->param_20_setPresetValue(getSubState(preset, "h18"));
    this->param_21_setPresetValue(getSubState(preset, "h17"));
    this->param_22_setPresetValue(getSubState(preset, "h23"));
    this->param_23_setPresetValue(getSubState(preset, "h24"));
    this->param_24_setPresetValue(getSubState(preset, "h22"));
    this->param_25_setPresetValue(getSubState(preset, "h21"));
    this->param_26_setPresetValue(getSubState(preset, "h26"));
    this->param_27_setPresetValue(getSubState(preset, "h25"));
    this->param_28_setPresetValue(getSubState(preset, "h28"));
    this->param_29_setPresetValue(getSubState(preset, "h27"));
    this->param_30_setPresetValue(getSubState(preset, "h32"));
    this->param_31_setPresetValue(getSubState(preset, "h31"));
    this->param_32_setPresetValue(getSubState(preset, "h30"));
    this->param_33_setPresetValue(getSubState(preset, "h29"));
    this->param_34_setPresetValue(getSubState(preset, "h36"));
    this->param_35_setPresetValue(getSubState(preset, "h35"));
    this->param_36_setPresetValue(getSubState(preset, "h34"));
    this->param_37_setPresetValue(getSubState(preset, "h33"));
    this->param_38_setPresetValue(getSubState(preset, "h40"));
    this->param_39_setPresetValue(getSubState(preset, "h39"));
    this->param_40_setPresetValue(getSubState(preset, "h38"));
    this->param_41_setPresetValue(getSubState(preset, "h37"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false))
        {}
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false))
        {}
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false))
        {}
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false))
        {}
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_11_value_set(v);
        break;
        }
    case 11:
        {
        this->param_12_value_set(v);
        break;
        }
    case 12:
        {
        this->param_13_value_set(v);
        break;
        }
    case 13:
        {
        this->param_14_value_set(v);
        break;
        }
    case 14:
        {
        this->param_15_value_set(v);
        break;
        }
    case 15:
        {
        this->param_16_value_set(v);
        break;
        }
    case 16:
        {
        this->param_17_value_set(v);
        break;
        }
    case 17:
        {
        this->param_18_value_set(v);
        break;
        }
    case 18:
        {
        this->param_19_value_set(v);
        break;
        }
    case 19:
        {
        this->param_20_value_set(v);
        break;
        }
    case 20:
        {
        this->param_21_value_set(v);
        break;
        }
    case 21:
        {
        this->param_22_value_set(v);
        break;
        }
    case 22:
        {
        this->param_23_value_set(v);
        break;
        }
    case 23:
        {
        this->param_24_value_set(v);
        break;
        }
    case 24:
        {
        this->param_25_value_set(v);
        break;
        }
    case 25:
        {
        this->param_26_value_set(v);
        break;
        }
    case 26:
        {
        this->param_27_value_set(v);
        break;
        }
    case 27:
        {
        this->param_28_value_set(v);
        break;
        }
    case 28:
        {
        this->param_29_value_set(v);
        break;
        }
    case 29:
        {
        this->param_30_value_set(v);
        break;
        }
    case 30:
        {
        this->param_31_value_set(v);
        break;
        }
    case 31:
        {
        this->param_32_value_set(v);
        break;
        }
    case 32:
        {
        this->param_33_value_set(v);
        break;
        }
    case 33:
        {
        this->param_34_value_set(v);
        break;
        }
    case 34:
        {
        this->param_35_value_set(v);
        break;
        }
    case 35:
        {
        this->param_36_value_set(v);
        break;
        }
    case 36:
        {
        this->param_37_value_set(v);
        break;
        }
    case 37:
        {
        this->param_38_value_set(v);
        break;
        }
    case 38:
        {
        this->param_39_value_set(v);
        break;
        }
    case 39:
        {
        this->param_40_value_set(v);
        break;
        }
    case 40:
        {
        this->param_41_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_11_value;
        }
    case 11:
        {
        return this->param_12_value;
        }
    case 12:
        {
        return this->param_13_value;
        }
    case 13:
        {
        return this->param_14_value;
        }
    case 14:
        {
        return this->param_15_value;
        }
    case 15:
        {
        return this->param_16_value;
        }
    case 16:
        {
        return this->param_17_value;
        }
    case 17:
        {
        return this->param_18_value;
        }
    case 18:
        {
        return this->param_19_value;
        }
    case 19:
        {
        return this->param_20_value;
        }
    case 20:
        {
        return this->param_21_value;
        }
    case 21:
        {
        return this->param_22_value;
        }
    case 22:
        {
        return this->param_23_value;
        }
    case 23:
        {
        return this->param_24_value;
        }
    case 24:
        {
        return this->param_25_value;
        }
    case 25:
        {
        return this->param_26_value;
        }
    case 26:
        {
        return this->param_27_value;
        }
    case 27:
        {
        return this->param_28_value;
        }
    case 28:
        {
        return this->param_29_value;
        }
    case 29:
        {
        return this->param_30_value;
        }
    case 30:
        {
        return this->param_31_value;
        }
    case 31:
        {
        return this->param_32_value;
        }
    case 32:
        {
        return this->param_33_value;
        }
    case 33:
        {
        return this->param_34_value;
        }
    case 34:
        {
        return this->param_35_value;
        }
    case 35:
        {
        return this->param_36_value;
        }
    case 36:
        {
        return this->param_37_value;
        }
    case 37:
        {
        return this->param_38_value;
        }
    case 38:
        {
        return this->param_39_value;
        }
    case 39:
        {
        return this->param_40_value;
        }
    case 40:
        {
        return this->param_41_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 41;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "h4";
        }
    case 1:
        {
        return "h3";
        }
    case 2:
        {
        return "freq";
        }
    case 3:
        {
        return "h2";
        }
    case 4:
        {
        return "f";
        }
    case 5:
        {
        return "h8";
        }
    case 6:
        {
        return "h7";
        }
    case 7:
        {
        return "h6";
        }
    case 8:
        {
        return "h5";
        }
    case 9:
        {
        return "h12";
        }
    case 10:
        {
        return "h11";
        }
    case 11:
        {
        return "h10";
        }
    case 12:
        {
        return "h9";
        }
    case 13:
        {
        return "h16";
        }
    case 14:
        {
        return "h15";
        }
    case 15:
        {
        return "h14";
        }
    case 16:
        {
        return "h13";
        }
    case 17:
        {
        return "h20";
        }
    case 18:
        {
        return "h19";
        }
    case 19:
        {
        return "h18";
        }
    case 20:
        {
        return "h17";
        }
    case 21:
        {
        return "h23";
        }
    case 22:
        {
        return "h24";
        }
    case 23:
        {
        return "h22";
        }
    case 24:
        {
        return "h21";
        }
    case 25:
        {
        return "h26";
        }
    case 26:
        {
        return "h25";
        }
    case 27:
        {
        return "h28";
        }
    case 28:
        {
        return "h27";
        }
    case 29:
        {
        return "h32";
        }
    case 30:
        {
        return "h31";
        }
    case 31:
        {
        return "h30";
        }
    case 32:
        {
        return "h29";
        }
    case 33:
        {
        return "h36";
        }
    case 34:
        {
        return "h35";
        }
    case 35:
        {
        return "h34";
        }
    case 36:
        {
        return "h33";
        }
    case 37:
        {
        return "h40";
        }
    case 38:
        {
        return "h39";
        }
    case 39:
        {
        return "h38";
        }
    case 40:
        {
        return "h37";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "h4";
        }
    case 1:
        {
        return "h3";
        }
    case 2:
        {
        return "freq";
        }
    case 3:
        {
        return "h2";
        }
    case 4:
        {
        return "f";
        }
    case 5:
        {
        return "h8";
        }
    case 6:
        {
        return "h7";
        }
    case 7:
        {
        return "h6";
        }
    case 8:
        {
        return "h5";
        }
    case 9:
        {
        return "h12";
        }
    case 10:
        {
        return "h11";
        }
    case 11:
        {
        return "h10";
        }
    case 12:
        {
        return "h9";
        }
    case 13:
        {
        return "h16";
        }
    case 14:
        {
        return "h15";
        }
    case 15:
        {
        return "h14";
        }
    case 16:
        {
        return "h13";
        }
    case 17:
        {
        return "h20";
        }
    case 18:
        {
        return "h19";
        }
    case 19:
        {
        return "h18";
        }
    case 20:
        {
        return "h17";
        }
    case 21:
        {
        return "h23";
        }
    case 22:
        {
        return "h24";
        }
    case 23:
        {
        return "h22";
        }
    case 24:
        {
        return "h21";
        }
    case 25:
        {
        return "h26";
        }
    case 26:
        {
        return "h25";
        }
    case 27:
        {
        return "h28";
        }
    case 28:
        {
        return "h27";
        }
    case 29:
        {
        return "h32";
        }
    case 30:
        {
        return "h31";
        }
    case 31:
        {
        return "h30";
        }
    case 32:
        {
        return "h29";
        }
    case 33:
        {
        return "h36";
        }
    case 34:
        {
        return "h35";
        }
    case 35:
        {
        return "h34";
        }
    case 36:
        {
        return "h33";
        }
    case 37:
        {
        return "h40";
        }
    case 38:
        {
        return "h39";
        }
    case 39:
        {
        return "h38";
        }
    case 40:
        {
        return "h37";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 32.703;
            info->max = 2093;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 19:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 20:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 21:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 22:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 23:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 24:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 25:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 26:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 27:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 28:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 29:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 30:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 31:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 32:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 33:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 34:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 35:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 36:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 37:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 38:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 39:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 40:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 158;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
        {
        {
            value = (value < 0 ? 0 : (value > 158 ? 158 : value));
            ParameterValue normalizedValue = (value - 0) / (158 - 0);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 32.703 ? 32.703 : (value > 2093 ? 2093 : value));
            ParameterValue normalizedValue = (value - 32.703) / (2093 - 32.703);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (158 - 0);
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 32.703 + value * (2093 - 32.703);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_11_value_constrain(value);
        }
    case 11:
        {
        return this->param_12_value_constrain(value);
        }
    case 12:
        {
        return this->param_13_value_constrain(value);
        }
    case 13:
        {
        return this->param_14_value_constrain(value);
        }
    case 14:
        {
        return this->param_15_value_constrain(value);
        }
    case 15:
        {
        return this->param_16_value_constrain(value);
        }
    case 16:
        {
        return this->param_17_value_constrain(value);
        }
    case 17:
        {
        return this->param_18_value_constrain(value);
        }
    case 18:
        {
        return this->param_19_value_constrain(value);
        }
    case 19:
        {
        return this->param_20_value_constrain(value);
        }
    case 20:
        {
        return this->param_21_value_constrain(value);
        }
    case 21:
        {
        return this->param_22_value_constrain(value);
        }
    case 22:
        {
        return this->param_23_value_constrain(value);
        }
    case 23:
        {
        return this->param_24_value_constrain(value);
        }
    case 24:
        {
        return this->param_25_value_constrain(value);
        }
    case 25:
        {
        return this->param_26_value_constrain(value);
        }
    case 26:
        {
        return this->param_27_value_constrain(value);
        }
    case 27:
        {
        return this->param_28_value_constrain(value);
        }
    case 28:
        {
        return this->param_29_value_constrain(value);
        }
    case 29:
        {
        return this->param_30_value_constrain(value);
        }
    case 30:
        {
        return this->param_31_value_constrain(value);
        }
    case 31:
        {
        return this->param_32_value_constrain(value);
        }
    case 32:
        {
        return this->param_33_value_constrain(value);
        }
    case 33:
        {
        return this->param_34_value_constrain(value);
        }
    case 34:
        {
        return this->param_35_value_constrain(value);
        }
    case 35:
        {
        return this->param_36_value_constrain(value);
        }
    case 36:
        {
        return this->param_37_value_constrain(value);
        }
    case 37:
        {
        return this->param_38_value_constrain(value);
        }
    case 38:
        {
        return this->param_39_value_constrain(value);
        }
    case 39:
        {
        return this->param_40_value_constrain(value);
        }
    case 40:
        {
        return this->param_41_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("gain~_obj-4") == objectId)
            this->gaintilde_01_valin_set(payload);

        if (TAG("gain~_obj-84") == objectId)
            this->gaintilde_02_valin_set(payload);

        if (TAG("gain~_obj-289") == objectId)
            this->gaintilde_03_valin_set(payload);

        if (TAG("gain~_obj-172") == objectId)
            this->gaintilde_04_valin_set(payload);

        if (TAG("gain~_obj-11") == objectId)
            this->gaintilde_05_valin_set(payload);

        if (TAG("gain~_obj-91") == objectId)
            this->gaintilde_06_valin_set(payload);

        if (TAG("gain~_obj-284") == objectId)
            this->gaintilde_07_valin_set(payload);

        if (TAG("gain~_obj-177") == objectId)
            this->gaintilde_08_valin_set(payload);

        if (TAG("gain~_obj-28") == objectId)
            this->gaintilde_09_valin_set(payload);

        if (TAG("gain~_obj-279") == objectId)
            this->gaintilde_10_valin_set(payload);

        if (TAG("gain~_obj-182") == objectId)
            this->gaintilde_11_valin_set(payload);

        if (TAG("gain~_obj-98") == objectId)
            this->gaintilde_12_valin_set(payload);

        if (TAG("gain~_obj-33") == objectId)
            this->gaintilde_13_valin_set(payload);

        if (TAG("gain~_obj-274") == objectId)
            this->gaintilde_14_valin_set(payload);

        if (TAG("gain~_obj-187") == objectId)
            this->gaintilde_15_valin_set(payload);

        if (TAG("gain~_obj-105") == objectId)
            this->gaintilde_16_valin_set(payload);

        if (TAG("gain~_obj-42") == objectId)
            this->gaintilde_17_valin_set(payload);

        if (TAG("gain~_obj-269") == objectId)
            this->gaintilde_18_valin_set(payload);

        if (TAG("gain~_obj-192") == objectId)
            this->gaintilde_19_valin_set(payload);

        if (TAG("gain~_obj-112") == objectId)
            this->gaintilde_20_valin_set(payload);

        if (TAG("gain~_obj-49") == objectId)
            this->gaintilde_21_valin_set(payload);

        if (TAG("gain~_obj-264") == objectId)
            this->gaintilde_22_valin_set(payload);

        if (TAG("gain~_obj-197") == objectId)
            this->gaintilde_23_valin_set(payload);

        if (TAG("gain~_obj-127") == objectId)
            this->gaintilde_24_valin_set(payload);

        if (TAG("gain~_obj-56") == objectId)
            this->gaintilde_25_valin_set(payload);

        if (TAG("gain~_obj-259") == objectId)
            this->gaintilde_26_valin_set(payload);

        if (TAG("gain~_obj-202") == objectId)
            this->gaintilde_27_valin_set(payload);

        if (TAG("gain~_obj-132") == objectId)
            this->gaintilde_28_valin_set(payload);

        if (TAG("gain~_obj-63") == objectId)
            this->gaintilde_29_valin_set(payload);

        if (TAG("gain~_obj-254") == objectId)
            this->gaintilde_30_valin_set(payload);

        if (TAG("gain~_obj-207") == objectId)
            this->gaintilde_31_valin_set(payload);

        if (TAG("gain~_obj-70") == objectId)
            this->gaintilde_32_valin_set(payload);

        if (TAG("gain~_obj-137") == objectId)
            this->gaintilde_33_valin_set(payload);

        if (TAG("gain~_obj-249") == objectId)
            this->gaintilde_34_valin_set(payload);

        if (TAG("gain~_obj-212") == objectId)
            this->gaintilde_35_valin_set(payload);

        if (TAG("gain~_obj-77") == objectId)
            this->gaintilde_36_valin_set(payload);

        if (TAG("gain~_obj-142") == objectId)
            this->gaintilde_37_valin_set(payload);

        if (TAG("gain~_obj-244") == objectId)
            this->gaintilde_38_valin_set(payload);

        if (TAG("gain~_obj-217") == objectId)
            this->gaintilde_39_valin_set(payload);

        if (TAG("gain~_obj-147") == objectId)
            this->gaintilde_40_valin_set(payload);

        break;
        }
    }
}

void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}

void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("gain~_obj-4"):
        {
        return "gain~_obj-4";
        }
    case TAG("gain~_obj-84"):
        {
        return "gain~_obj-84";
        }
    case TAG("gain~_obj-289"):
        {
        return "gain~_obj-289";
        }
    case TAG("gain~_obj-172"):
        {
        return "gain~_obj-172";
        }
    case TAG("gain~_obj-11"):
        {
        return "gain~_obj-11";
        }
    case TAG("gain~_obj-91"):
        {
        return "gain~_obj-91";
        }
    case TAG("gain~_obj-284"):
        {
        return "gain~_obj-284";
        }
    case TAG("gain~_obj-177"):
        {
        return "gain~_obj-177";
        }
    case TAG("gain~_obj-28"):
        {
        return "gain~_obj-28";
        }
    case TAG("gain~_obj-279"):
        {
        return "gain~_obj-279";
        }
    case TAG("gain~_obj-182"):
        {
        return "gain~_obj-182";
        }
    case TAG("gain~_obj-98"):
        {
        return "gain~_obj-98";
        }
    case TAG("gain~_obj-33"):
        {
        return "gain~_obj-33";
        }
    case TAG("gain~_obj-274"):
        {
        return "gain~_obj-274";
        }
    case TAG("gain~_obj-187"):
        {
        return "gain~_obj-187";
        }
    case TAG("gain~_obj-105"):
        {
        return "gain~_obj-105";
        }
    case TAG("gain~_obj-42"):
        {
        return "gain~_obj-42";
        }
    case TAG("gain~_obj-269"):
        {
        return "gain~_obj-269";
        }
    case TAG("gain~_obj-192"):
        {
        return "gain~_obj-192";
        }
    case TAG("gain~_obj-112"):
        {
        return "gain~_obj-112";
        }
    case TAG("gain~_obj-49"):
        {
        return "gain~_obj-49";
        }
    case TAG("gain~_obj-264"):
        {
        return "gain~_obj-264";
        }
    case TAG("gain~_obj-197"):
        {
        return "gain~_obj-197";
        }
    case TAG("gain~_obj-127"):
        {
        return "gain~_obj-127";
        }
    case TAG("gain~_obj-56"):
        {
        return "gain~_obj-56";
        }
    case TAG("gain~_obj-259"):
        {
        return "gain~_obj-259";
        }
    case TAG("gain~_obj-202"):
        {
        return "gain~_obj-202";
        }
    case TAG("gain~_obj-132"):
        {
        return "gain~_obj-132";
        }
    case TAG("gain~_obj-63"):
        {
        return "gain~_obj-63";
        }
    case TAG("gain~_obj-254"):
        {
        return "gain~_obj-254";
        }
    case TAG("gain~_obj-207"):
        {
        return "gain~_obj-207";
        }
    case TAG("gain~_obj-70"):
        {
        return "gain~_obj-70";
        }
    case TAG("gain~_obj-137"):
        {
        return "gain~_obj-137";
        }
    case TAG("gain~_obj-249"):
        {
        return "gain~_obj-249";
        }
    case TAG("gain~_obj-212"):
        {
        return "gain~_obj-212";
        }
    case TAG("gain~_obj-77"):
        {
        return "gain~_obj-77";
        }
    case TAG("gain~_obj-142"):
        {
        return "gain~_obj-142";
        }
    case TAG("gain~_obj-244"):
        {
        return "gain~_obj-244";
        }
    case TAG("gain~_obj-217"):
        {
        return "gain~_obj-217";
        }
    case TAG("gain~_obj-147"):
        {
        return "gain~_obj-147";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->send_01_input_number_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->send_02_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->send_03_input_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->send_04_input_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->send_05_input_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->send_06_input_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->send_07_input_number_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->send_08_input_number_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->send_09_input_number_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->send_10_input_number_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->send_11_input_number_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->send_12_input_number_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->send_13_input_number_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->send_14_input_number_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(14, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->send_15_input_number_set(v);
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(15, false);

    if (this->param_16_value != this->param_16_lastValue) {
        this->getEngine()->presetTouched();
        this->param_16_lastValue = this->param_16_value;
    }

    this->send_16_input_number_set(v);
}

void param_17_value_set(number v) {
    v = this->param_17_value_constrain(v);
    this->param_17_value = v;
    this->sendParameter(16, false);

    if (this->param_17_value != this->param_17_lastValue) {
        this->getEngine()->presetTouched();
        this->param_17_lastValue = this->param_17_value;
    }

    this->send_17_input_number_set(v);
}

void param_18_value_set(number v) {
    v = this->param_18_value_constrain(v);
    this->param_18_value = v;
    this->sendParameter(17, false);

    if (this->param_18_value != this->param_18_lastValue) {
        this->getEngine()->presetTouched();
        this->param_18_lastValue = this->param_18_value;
    }

    this->send_18_input_number_set(v);
}

void param_19_value_set(number v) {
    v = this->param_19_value_constrain(v);
    this->param_19_value = v;
    this->sendParameter(18, false);

    if (this->param_19_value != this->param_19_lastValue) {
        this->getEngine()->presetTouched();
        this->param_19_lastValue = this->param_19_value;
    }

    this->send_19_input_number_set(v);
}

void param_20_value_set(number v) {
    v = this->param_20_value_constrain(v);
    this->param_20_value = v;
    this->sendParameter(19, false);

    if (this->param_20_value != this->param_20_lastValue) {
        this->getEngine()->presetTouched();
        this->param_20_lastValue = this->param_20_value;
    }

    this->send_20_input_number_set(v);
}

void param_21_value_set(number v) {
    v = this->param_21_value_constrain(v);
    this->param_21_value = v;
    this->sendParameter(20, false);

    if (this->param_21_value != this->param_21_lastValue) {
        this->getEngine()->presetTouched();
        this->param_21_lastValue = this->param_21_value;
    }

    this->send_21_input_number_set(v);
}

void param_22_value_set(number v) {
    v = this->param_22_value_constrain(v);
    this->param_22_value = v;
    this->sendParameter(21, false);

    if (this->param_22_value != this->param_22_lastValue) {
        this->getEngine()->presetTouched();
        this->param_22_lastValue = this->param_22_value;
    }

    this->send_22_input_number_set(v);
}

void param_23_value_set(number v) {
    v = this->param_23_value_constrain(v);
    this->param_23_value = v;
    this->sendParameter(22, false);

    if (this->param_23_value != this->param_23_lastValue) {
        this->getEngine()->presetTouched();
        this->param_23_lastValue = this->param_23_value;
    }

    this->send_23_input_number_set(v);
}

void param_24_value_set(number v) {
    v = this->param_24_value_constrain(v);
    this->param_24_value = v;
    this->sendParameter(23, false);

    if (this->param_24_value != this->param_24_lastValue) {
        this->getEngine()->presetTouched();
        this->param_24_lastValue = this->param_24_value;
    }

    this->send_24_input_number_set(v);
}

void param_25_value_set(number v) {
    v = this->param_25_value_constrain(v);
    this->param_25_value = v;
    this->sendParameter(24, false);

    if (this->param_25_value != this->param_25_lastValue) {
        this->getEngine()->presetTouched();
        this->param_25_lastValue = this->param_25_value;
    }

    this->send_25_input_number_set(v);
}

void param_26_value_set(number v) {
    v = this->param_26_value_constrain(v);
    this->param_26_value = v;
    this->sendParameter(25, false);

    if (this->param_26_value != this->param_26_lastValue) {
        this->getEngine()->presetTouched();
        this->param_26_lastValue = this->param_26_value;
    }

    this->send_26_input_number_set(v);
}

void param_27_value_set(number v) {
    v = this->param_27_value_constrain(v);
    this->param_27_value = v;
    this->sendParameter(26, false);

    if (this->param_27_value != this->param_27_lastValue) {
        this->getEngine()->presetTouched();
        this->param_27_lastValue = this->param_27_value;
    }

    this->send_27_input_number_set(v);
}

void param_28_value_set(number v) {
    v = this->param_28_value_constrain(v);
    this->param_28_value = v;
    this->sendParameter(27, false);

    if (this->param_28_value != this->param_28_lastValue) {
        this->getEngine()->presetTouched();
        this->param_28_lastValue = this->param_28_value;
    }

    this->send_28_input_number_set(v);
}

void param_29_value_set(number v) {
    v = this->param_29_value_constrain(v);
    this->param_29_value = v;
    this->sendParameter(28, false);

    if (this->param_29_value != this->param_29_lastValue) {
        this->getEngine()->presetTouched();
        this->param_29_lastValue = this->param_29_value;
    }

    this->send_29_input_number_set(v);
}

void param_30_value_set(number v) {
    v = this->param_30_value_constrain(v);
    this->param_30_value = v;
    this->sendParameter(29, false);

    if (this->param_30_value != this->param_30_lastValue) {
        this->getEngine()->presetTouched();
        this->param_30_lastValue = this->param_30_value;
    }

    this->send_30_input_number_set(v);
}

void param_31_value_set(number v) {
    v = this->param_31_value_constrain(v);
    this->param_31_value = v;
    this->sendParameter(30, false);

    if (this->param_31_value != this->param_31_lastValue) {
        this->getEngine()->presetTouched();
        this->param_31_lastValue = this->param_31_value;
    }

    this->send_31_input_number_set(v);
}

void param_32_value_set(number v) {
    v = this->param_32_value_constrain(v);
    this->param_32_value = v;
    this->sendParameter(31, false);

    if (this->param_32_value != this->param_32_lastValue) {
        this->getEngine()->presetTouched();
        this->param_32_lastValue = this->param_32_value;
    }

    this->send_32_input_number_set(v);
}

void param_33_value_set(number v) {
    v = this->param_33_value_constrain(v);
    this->param_33_value = v;
    this->sendParameter(32, false);

    if (this->param_33_value != this->param_33_lastValue) {
        this->getEngine()->presetTouched();
        this->param_33_lastValue = this->param_33_value;
    }

    this->send_33_input_number_set(v);
}

void param_34_value_set(number v) {
    v = this->param_34_value_constrain(v);
    this->param_34_value = v;
    this->sendParameter(33, false);

    if (this->param_34_value != this->param_34_lastValue) {
        this->getEngine()->presetTouched();
        this->param_34_lastValue = this->param_34_value;
    }

    this->send_34_input_number_set(v);
}

void param_35_value_set(number v) {
    v = this->param_35_value_constrain(v);
    this->param_35_value = v;
    this->sendParameter(34, false);

    if (this->param_35_value != this->param_35_lastValue) {
        this->getEngine()->presetTouched();
        this->param_35_lastValue = this->param_35_value;
    }

    this->send_35_input_number_set(v);
}

void param_36_value_set(number v) {
    v = this->param_36_value_constrain(v);
    this->param_36_value = v;
    this->sendParameter(35, false);

    if (this->param_36_value != this->param_36_lastValue) {
        this->getEngine()->presetTouched();
        this->param_36_lastValue = this->param_36_value;
    }

    this->send_36_input_number_set(v);
}

void param_37_value_set(number v) {
    v = this->param_37_value_constrain(v);
    this->param_37_value = v;
    this->sendParameter(36, false);

    if (this->param_37_value != this->param_37_lastValue) {
        this->getEngine()->presetTouched();
        this->param_37_lastValue = this->param_37_value;
    }

    this->send_37_input_number_set(v);
}

void param_38_value_set(number v) {
    v = this->param_38_value_constrain(v);
    this->param_38_value = v;
    this->sendParameter(37, false);

    if (this->param_38_value != this->param_38_lastValue) {
        this->getEngine()->presetTouched();
        this->param_38_lastValue = this->param_38_value;
    }

    this->send_38_input_number_set(v);
}

void param_39_value_set(number v) {
    v = this->param_39_value_constrain(v);
    this->param_39_value = v;
    this->sendParameter(38, false);

    if (this->param_39_value != this->param_39_lastValue) {
        this->getEngine()->presetTouched();
        this->param_39_lastValue = this->param_39_value;
    }

    this->send_39_input_number_set(v);
}

void param_40_value_set(number v) {
    v = this->param_40_value_constrain(v);
    this->param_40_value = v;
    this->sendParameter(39, false);

    if (this->param_40_value != this->param_40_lastValue) {
        this->getEngine()->presetTouched();
        this->param_40_lastValue = this->param_40_value;
    }

    this->send_40_input_number_set(v);
}

void param_41_value_set(number v) {
    v = this->param_41_value_constrain(v);
    this->param_41_value = v;
    this->sendParameter(40, false);

    if (this->param_41_value != this->param_41_lastValue) {
        this->getEngine()->presetTouched();
        this->param_41_lastValue = this->param_41_value;
    }

    this->send_41_input_number_set(v);
}

void gaintilde_01_valin_set(number v) {
    this->gaintilde_01_value_set(v);
}

void gaintilde_02_valin_set(number v) {
    this->gaintilde_02_value_set(v);
}

void gaintilde_03_valin_set(number v) {
    this->gaintilde_03_value_set(v);
}

void gaintilde_04_valin_set(number v) {
    this->gaintilde_04_value_set(v);
}

void gaintilde_05_valin_set(number v) {
    this->gaintilde_05_value_set(v);
}

void gaintilde_06_valin_set(number v) {
    this->gaintilde_06_value_set(v);
}

void gaintilde_07_valin_set(number v) {
    this->gaintilde_07_value_set(v);
}

void gaintilde_08_valin_set(number v) {
    this->gaintilde_08_value_set(v);
}

void gaintilde_09_valin_set(number v) {
    this->gaintilde_09_value_set(v);
}

void gaintilde_10_valin_set(number v) {
    this->gaintilde_10_value_set(v);
}

void gaintilde_11_valin_set(number v) {
    this->gaintilde_11_value_set(v);
}

void gaintilde_12_valin_set(number v) {
    this->gaintilde_12_value_set(v);
}

void gaintilde_13_valin_set(number v) {
    this->gaintilde_13_value_set(v);
}

void gaintilde_14_valin_set(number v) {
    this->gaintilde_14_value_set(v);
}

void gaintilde_15_valin_set(number v) {
    this->gaintilde_15_value_set(v);
}

void gaintilde_16_valin_set(number v) {
    this->gaintilde_16_value_set(v);
}

void gaintilde_17_valin_set(number v) {
    this->gaintilde_17_value_set(v);
}

void gaintilde_18_valin_set(number v) {
    this->gaintilde_18_value_set(v);
}

void gaintilde_19_valin_set(number v) {
    this->gaintilde_19_value_set(v);
}

void gaintilde_20_valin_set(number v) {
    this->gaintilde_20_value_set(v);
}

void gaintilde_21_valin_set(number v) {
    this->gaintilde_21_value_set(v);
}

void gaintilde_22_valin_set(number v) {
    this->gaintilde_22_value_set(v);
}

void gaintilde_23_valin_set(number v) {
    this->gaintilde_23_value_set(v);
}

void gaintilde_24_valin_set(number v) {
    this->gaintilde_24_value_set(v);
}

void gaintilde_25_valin_set(number v) {
    this->gaintilde_25_value_set(v);
}

void gaintilde_26_valin_set(number v) {
    this->gaintilde_26_value_set(v);
}

void gaintilde_27_valin_set(number v) {
    this->gaintilde_27_value_set(v);
}

void gaintilde_28_valin_set(number v) {
    this->gaintilde_28_value_set(v);
}

void gaintilde_29_valin_set(number v) {
    this->gaintilde_29_value_set(v);
}

void gaintilde_30_valin_set(number v) {
    this->gaintilde_30_value_set(v);
}

void gaintilde_31_valin_set(number v) {
    this->gaintilde_31_value_set(v);
}

void gaintilde_32_valin_set(number v) {
    this->gaintilde_32_value_set(v);
}

void gaintilde_33_valin_set(number v) {
    this->gaintilde_33_value_set(v);
}

void gaintilde_34_valin_set(number v) {
    this->gaintilde_34_value_set(v);
}

void gaintilde_35_valin_set(number v) {
    this->gaintilde_35_value_set(v);
}

void gaintilde_36_valin_set(number v) {
    this->gaintilde_36_value_set(v);
}

void gaintilde_37_valin_set(number v) {
    this->gaintilde_37_value_set(v);
}

void gaintilde_38_valin_set(number v) {
    this->gaintilde_38_value_set(v);
}

void gaintilde_39_valin_set(number v) {
    this->gaintilde_39_value_set(v);
}

void gaintilde_40_valin_set(number v) {
    this->gaintilde_40_value_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 1;
}

Index getNumOutputChannels() const {
    return 1;
}

void allocateDataRefs() {}

void initializeObjects() {
    this->gaintilde_01_init();
    this->gaintilde_02_init();
    this->gaintilde_03_init();
    this->gaintilde_04_init();
    this->gaintilde_05_init();
    this->gaintilde_06_init();
    this->gaintilde_07_init();
    this->gaintilde_08_init();
    this->gaintilde_09_init();
    this->gaintilde_10_init();
    this->gaintilde_11_init();
    this->gaintilde_12_init();
    this->gaintilde_13_init();
    this->gaintilde_14_init();
    this->gaintilde_15_init();
    this->gaintilde_16_init();
    this->gaintilde_17_init();
    this->gaintilde_18_init();
    this->gaintilde_19_init();
    this->gaintilde_20_init();
    this->gaintilde_21_init();
    this->gaintilde_22_init();
    this->gaintilde_23_init();
    this->gaintilde_24_init();
    this->gaintilde_25_init();
    this->gaintilde_26_init();
    this->gaintilde_27_init();
    this->gaintilde_28_init();
    this->gaintilde_29_init();
    this->gaintilde_30_init();
    this->gaintilde_31_init();
    this->gaintilde_32_init();
    this->gaintilde_33_init();
    this->gaintilde_34_init();
    this->gaintilde_35_init();
    this->gaintilde_36_init();
    this->gaintilde_37_init();
    this->gaintilde_38_init();
    this->gaintilde_39_init();
    this->gaintilde_40_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 0);
    }

    {
        this->scheduleParamInit(17, 0);
    }

    {
        this->scheduleParamInit(18, 0);
    }

    {
        this->scheduleParamInit(19, 0);
    }

    {
        this->scheduleParamInit(20, 0);
    }

    {
        this->scheduleParamInit(21, 0);
    }

    {
        this->scheduleParamInit(22, 0);
    }

    {
        this->scheduleParamInit(23, 0);
    }

    {
        this->scheduleParamInit(24, 0);
    }

    {
        this->scheduleParamInit(25, 0);
    }

    {
        this->scheduleParamInit(26, 0);
    }

    {
        this->scheduleParamInit(27, 0);
    }

    {
        this->scheduleParamInit(28, 0);
    }

    {
        this->scheduleParamInit(29, 0);
    }

    {
        this->scheduleParamInit(30, 0);
    }

    {
        this->scheduleParamInit(31, 0);
    }

    {
        this->scheduleParamInit(32, 0);
    }

    {
        this->scheduleParamInit(33, 0);
    }

    {
        this->scheduleParamInit(34, 0);
    }

    {
        this->scheduleParamInit(35, 0);
    }

    {
        this->scheduleParamInit(36, 0);
    }

    {
        this->scheduleParamInit(37, 0);
    }

    {
        this->scheduleParamInit(38, 0);
    }

    {
        this->scheduleParamInit(39, 0);
    }

    {
        this->scheduleParamInit(40, 0);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_13_outval_set(number ) {}

void gaintilde_13_value_set(number v) {
    this->gaintilde_13_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-33"), v, this->_currentTime);
    this->gaintilde_13_outval_set(value);
}

void gaintilde_13_input_number_set(number v) {
    this->gaintilde_13_input_number = v;

    this->gaintilde_13_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_21_output_number_set(number v) {
    this->receive_21_output_number = v;
    this->gaintilde_13_input_number_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_21_output_number_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_09_outval_set(number ) {}

void gaintilde_09_value_set(number v) {
    this->gaintilde_09_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-28"), v, this->_currentTime);
    this->gaintilde_09_outval_set(value);
}

void gaintilde_09_input_number_set(number v) {
    this->gaintilde_09_input_number = v;

    this->gaintilde_09_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_13_output_number_set(number v) {
    this->receive_13_output_number = v;
    this->gaintilde_09_input_number_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_13_output_number_set(v);
}

static number param_03_value_constrain(number v) {
    v = (v > 2093 ? 2093 : (v < 32.703 ? 32.703 : v));
    return v;
}

void freqshift_tilde_01_frequency_set(number v) {
    this->freqshift_tilde_01_frequency = v;
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->freqshift_tilde_01_frequency_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;
    this->expr_01_out1_set(this->expr_01_in1 * this->expr_01_in2);//#map:*_obj-81:1
}

void receive_06_output_number_set(number v) {
    this->receive_06_output_number = v;
    this->expr_01_in1_set(v);
}

void freqshift_tilde_02_frequency_set(number v) {
    this->freqshift_tilde_02_frequency = v;
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->freqshift_tilde_02_frequency_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:*_obj-286:1
}

void receive_07_output_number_set(number v) {
    this->receive_07_output_number = v;
    this->expr_02_in1_set(v);
}

void freqshift_tilde_03_frequency_set(number v) {
    this->freqshift_tilde_03_frequency = v;
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->freqshift_tilde_03_frequency_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;
    this->expr_03_out1_set(this->expr_03_in1 * this->expr_03_in2);//#map:*_obj-169:1
}

void receive_08_output_number_set(number v) {
    this->receive_08_output_number = v;
    this->expr_03_in1_set(v);
}

void freqshift_tilde_04_frequency_set(number v) {
    this->freqshift_tilde_04_frequency = v;
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->freqshift_tilde_04_frequency_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:*_obj-13:1
}

void receive_09_output_number_set(number v) {
    this->receive_09_output_number = v;
    this->expr_04_in1_set(v);
}

void freqshift_tilde_05_frequency_set(number v) {
    this->freqshift_tilde_05_frequency = v;
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->freqshift_tilde_05_frequency_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;
    this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:*_obj-88:1
}

void receive_14_output_number_set(number v) {
    this->receive_14_output_number = v;
    this->expr_05_in1_set(v);
}

void freqshift_tilde_06_frequency_set(number v) {
    this->freqshift_tilde_06_frequency = v;
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->freqshift_tilde_06_frequency_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:*_obj-281:1
}

void receive_15_output_number_set(number v) {
    this->receive_15_output_number = v;
    this->expr_06_in1_set(v);
}

void freqshift_tilde_07_frequency_set(number v) {
    this->freqshift_tilde_07_frequency = v;
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->freqshift_tilde_07_frequency_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;
    this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:*_obj-174:1
}

void receive_16_output_number_set(number v) {
    this->receive_16_output_number = v;
    this->expr_07_in1_set(v);
}

void freqshift_tilde_08_frequency_set(number v) {
    this->freqshift_tilde_08_frequency = v;
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->freqshift_tilde_08_frequency_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(this->expr_08_in1 * this->expr_08_in2);//#map:*_obj-25:1
}

void receive_18_output_number_set(number v) {
    this->receive_18_output_number = v;
    this->expr_08_in1_set(v);
}

void freqshift_tilde_09_frequency_set(number v) {
    this->freqshift_tilde_09_frequency = v;
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->freqshift_tilde_09_frequency_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:*_obj-276:1
}

void receive_22_output_number_set(number v) {
    this->receive_22_output_number = v;
    this->expr_09_in1_set(v);
}

void freqshift_tilde_10_frequency_set(number v) {
    this->freqshift_tilde_10_frequency = v;
}

void expr_10_out1_set(number v) {
    this->expr_10_out1 = v;
    this->freqshift_tilde_10_frequency_set(this->expr_10_out1);
}

void expr_10_in1_set(number in1) {
    this->expr_10_in1 = in1;
    this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:*_obj-179:1
}

void receive_23_output_number_set(number v) {
    this->receive_23_output_number = v;
    this->expr_10_in1_set(v);
}

void freqshift_tilde_11_frequency_set(number v) {
    this->freqshift_tilde_11_frequency = v;
}

void expr_11_out1_set(number v) {
    this->expr_11_out1 = v;
    this->freqshift_tilde_11_frequency_set(this->expr_11_out1);
}

void expr_11_in1_set(number in1) {
    this->expr_11_in1 = in1;
    this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:*_obj-95:1
}

void receive_24_output_number_set(number v) {
    this->receive_24_output_number = v;
    this->expr_11_in1_set(v);
}

void freqshift_tilde_12_frequency_set(number v) {
    this->freqshift_tilde_12_frequency = v;
}

void expr_12_out1_set(number v) {
    this->expr_12_out1 = v;
    this->freqshift_tilde_12_frequency_set(this->expr_12_out1);
}

void expr_12_in1_set(number in1) {
    this->expr_12_in1 = in1;
    this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:*_obj-30:1
}

void receive_26_output_number_set(number v) {
    this->receive_26_output_number = v;
    this->expr_12_in1_set(v);
}

void freqshift_tilde_13_frequency_set(number v) {
    this->freqshift_tilde_13_frequency = v;
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->freqshift_tilde_13_frequency_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:*_obj-271:1
}

void receive_30_output_number_set(number v) {
    this->receive_30_output_number = v;
    this->expr_13_in1_set(v);
}

void freqshift_tilde_14_frequency_set(number v) {
    this->freqshift_tilde_14_frequency = v;
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->freqshift_tilde_14_frequency_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:*_obj-184:1
}

void receive_31_output_number_set(number v) {
    this->receive_31_output_number = v;
    this->expr_14_in1_set(v);
}

void freqshift_tilde_15_frequency_set(number v) {
    this->freqshift_tilde_15_frequency = v;
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->freqshift_tilde_15_frequency_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 * this->expr_15_in2);//#map:*_obj-102:1
}

void receive_32_output_number_set(number v) {
    this->receive_32_output_number = v;
    this->expr_15_in1_set(v);
}

void freqshift_tilde_16_frequency_set(number v) {
    this->freqshift_tilde_16_frequency = v;
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->freqshift_tilde_16_frequency_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 * this->expr_16_in2);//#map:*_obj-39:1
}

void receive_35_output_number_set(number v) {
    this->receive_35_output_number = v;
    this->expr_16_in1_set(v);
}

void freqshift_tilde_17_frequency_set(number v) {
    this->freqshift_tilde_17_frequency = v;
}

void expr_17_out1_set(number v) {
    this->expr_17_out1 = v;
    this->freqshift_tilde_17_frequency_set(this->expr_17_out1);
}

void expr_17_in1_set(number in1) {
    this->expr_17_in1 = in1;
    this->expr_17_out1_set(this->expr_17_in1 * this->expr_17_in2);//#map:*_obj-266:1
}

void receive_38_output_number_set(number v) {
    this->receive_38_output_number = v;
    this->expr_17_in1_set(v);
}

void freqshift_tilde_18_frequency_set(number v) {
    this->freqshift_tilde_18_frequency = v;
}

void expr_18_out1_set(number v) {
    this->expr_18_out1 = v;
    this->freqshift_tilde_18_frequency_set(this->expr_18_out1);
}

void expr_18_in1_set(number in1) {
    this->expr_18_in1 = in1;
    this->expr_18_out1_set(this->expr_18_in1 * this->expr_18_in2);//#map:*_obj-189:1
}

void receive_39_output_number_set(number v) {
    this->receive_39_output_number = v;
    this->expr_18_in1_set(v);
}

void freqshift_tilde_19_frequency_set(number v) {
    this->freqshift_tilde_19_frequency = v;
}

void expr_19_out1_set(number v) {
    this->expr_19_out1 = v;
    this->freqshift_tilde_19_frequency_set(this->expr_19_out1);
}

void expr_19_in1_set(number in1) {
    this->expr_19_in1 = in1;
    this->expr_19_out1_set(this->expr_19_in1 * this->expr_19_in2);//#map:*_obj-109:1
}

void receive_42_output_number_set(number v) {
    this->receive_42_output_number = v;
    this->expr_19_in1_set(v);
}

void freqshift_tilde_20_frequency_set(number v) {
    this->freqshift_tilde_20_frequency = v;
}

void expr_20_out1_set(number v) {
    this->expr_20_out1 = v;
    this->freqshift_tilde_20_frequency_set(this->expr_20_out1);
}

void expr_20_in1_set(number in1) {
    this->expr_20_in1 = in1;
    this->expr_20_out1_set(this->expr_20_in1 * this->expr_20_in2);//#map:*_obj-46:1
}

void receive_43_output_number_set(number v) {
    this->receive_43_output_number = v;
    this->expr_20_in1_set(v);
}

void freqshift_tilde_21_frequency_set(number v) {
    this->freqshift_tilde_21_frequency = v;
}

void expr_21_out1_set(number v) {
    this->expr_21_out1 = v;
    this->freqshift_tilde_21_frequency_set(this->expr_21_out1);
}

void expr_21_in1_set(number in1) {
    this->expr_21_in1 = in1;
    this->expr_21_out1_set(this->expr_21_in1 * this->expr_21_in2);//#map:*_obj-261:1
}

void receive_46_output_number_set(number v) {
    this->receive_46_output_number = v;
    this->expr_21_in1_set(v);
}

void freqshift_tilde_22_frequency_set(number v) {
    this->freqshift_tilde_22_frequency = v;
}

void expr_22_out1_set(number v) {
    this->expr_22_out1 = v;
    this->freqshift_tilde_22_frequency_set(this->expr_22_out1);
}

void expr_22_in1_set(number in1) {
    this->expr_22_in1 = in1;
    this->expr_22_out1_set(this->expr_22_in1 * this->expr_22_in2);//#map:*_obj-194:1
}

void receive_47_output_number_set(number v) {
    this->receive_47_output_number = v;
    this->expr_22_in1_set(v);
}

void freqshift_tilde_23_frequency_set(number v) {
    this->freqshift_tilde_23_frequency = v;
}

void expr_23_out1_set(number v) {
    this->expr_23_out1 = v;
    this->freqshift_tilde_23_frequency_set(this->expr_23_out1);
}

void expr_23_in1_set(number in1) {
    this->expr_23_in1 = in1;
    this->expr_23_out1_set(this->expr_23_in1 * this->expr_23_in2);//#map:*_obj-124:1
}

void receive_50_output_number_set(number v) {
    this->receive_50_output_number = v;
    this->expr_23_in1_set(v);
}

void freqshift_tilde_24_frequency_set(number v) {
    this->freqshift_tilde_24_frequency = v;
}

void expr_24_out1_set(number v) {
    this->expr_24_out1 = v;
    this->freqshift_tilde_24_frequency_set(this->expr_24_out1);
}

void expr_24_in1_set(number in1) {
    this->expr_24_in1 = in1;
    this->expr_24_out1_set(this->expr_24_in1 * this->expr_24_in2);//#map:*_obj-53:1
}

void receive_51_output_number_set(number v) {
    this->receive_51_output_number = v;
    this->expr_24_in1_set(v);
}

void freqshift_tilde_25_frequency_set(number v) {
    this->freqshift_tilde_25_frequency = v;
}

void expr_25_out1_set(number v) {
    this->expr_25_out1 = v;
    this->freqshift_tilde_25_frequency_set(this->expr_25_out1);
}

void expr_25_in1_set(number in1) {
    this->expr_25_in1 = in1;
    this->expr_25_out1_set(this->expr_25_in1 * this->expr_25_in2);//#map:*_obj-256:1
}

void receive_54_output_number_set(number v) {
    this->receive_54_output_number = v;
    this->expr_25_in1_set(v);
}

void freqshift_tilde_26_frequency_set(number v) {
    this->freqshift_tilde_26_frequency = v;
}

void expr_26_out1_set(number v) {
    this->expr_26_out1 = v;
    this->freqshift_tilde_26_frequency_set(this->expr_26_out1);
}

void expr_26_in1_set(number in1) {
    this->expr_26_in1 = in1;
    this->expr_26_out1_set(this->expr_26_in1 * this->expr_26_in2);//#map:*_obj-199:1
}

void receive_55_output_number_set(number v) {
    this->receive_55_output_number = v;
    this->expr_26_in1_set(v);
}

void freqshift_tilde_27_frequency_set(number v) {
    this->freqshift_tilde_27_frequency = v;
}

void expr_27_out1_set(number v) {
    this->expr_27_out1 = v;
    this->freqshift_tilde_27_frequency_set(this->expr_27_out1);
}

void expr_27_in1_set(number in1) {
    this->expr_27_in1 = in1;
    this->expr_27_out1_set(this->expr_27_in1 * this->expr_27_in2);//#map:*_obj-129:1
}

void receive_58_output_number_set(number v) {
    this->receive_58_output_number = v;
    this->expr_27_in1_set(v);
}

void freqshift_tilde_28_frequency_set(number v) {
    this->freqshift_tilde_28_frequency = v;
}

void expr_28_out1_set(number v) {
    this->expr_28_out1 = v;
    this->freqshift_tilde_28_frequency_set(this->expr_28_out1);
}

void expr_28_in1_set(number in1) {
    this->expr_28_in1 = in1;
    this->expr_28_out1_set(this->expr_28_in1 * this->expr_28_in2);//#map:*_obj-60:1
}

void receive_59_output_number_set(number v) {
    this->receive_59_output_number = v;
    this->expr_28_in1_set(v);
}

void freqshift_tilde_29_frequency_set(number v) {
    this->freqshift_tilde_29_frequency = v;
}

void expr_29_out1_set(number v) {
    this->expr_29_out1 = v;
    this->freqshift_tilde_29_frequency_set(this->expr_29_out1);
}

void expr_29_in1_set(number in1) {
    this->expr_29_in1 = in1;
    this->expr_29_out1_set(this->expr_29_in1 * this->expr_29_in2);//#map:*_obj-251:1
}

void receive_62_output_number_set(number v) {
    this->receive_62_output_number = v;
    this->expr_29_in1_set(v);
}

void freqshift_tilde_30_frequency_set(number v) {
    this->freqshift_tilde_30_frequency = v;
}

void expr_30_out1_set(number v) {
    this->expr_30_out1 = v;
    this->freqshift_tilde_30_frequency_set(this->expr_30_out1);
}

void expr_30_in1_set(number in1) {
    this->expr_30_in1 = in1;
    this->expr_30_out1_set(this->expr_30_in1 * this->expr_30_in2);//#map:*_obj-204:1
}

void receive_63_output_number_set(number v) {
    this->receive_63_output_number = v;
    this->expr_30_in1_set(v);
}

void freqshift_tilde_31_frequency_set(number v) {
    this->freqshift_tilde_31_frequency = v;
}

void expr_31_out1_set(number v) {
    this->expr_31_out1 = v;
    this->freqshift_tilde_31_frequency_set(this->expr_31_out1);
}

void expr_31_in1_set(number in1) {
    this->expr_31_in1 = in1;
    this->expr_31_out1_set(this->expr_31_in1 * this->expr_31_in2);//#map:*_obj-67:1
}

void receive_66_output_number_set(number v) {
    this->receive_66_output_number = v;
    this->expr_31_in1_set(v);
}

void freqshift_tilde_32_frequency_set(number v) {
    this->freqshift_tilde_32_frequency = v;
}

void expr_32_out1_set(number v) {
    this->expr_32_out1 = v;
    this->freqshift_tilde_32_frequency_set(this->expr_32_out1);
}

void expr_32_in1_set(number in1) {
    this->expr_32_in1 = in1;
    this->expr_32_out1_set(this->expr_32_in1 * this->expr_32_in2);//#map:*_obj-134:1
}

void receive_67_output_number_set(number v) {
    this->receive_67_output_number = v;
    this->expr_32_in1_set(v);
}

void freqshift_tilde_33_frequency_set(number v) {
    this->freqshift_tilde_33_frequency = v;
}

void expr_33_out1_set(number v) {
    this->expr_33_out1 = v;
    this->freqshift_tilde_33_frequency_set(this->expr_33_out1);
}

void expr_33_in1_set(number in1) {
    this->expr_33_in1 = in1;
    this->expr_33_out1_set(this->expr_33_in1 * this->expr_33_in2);//#map:*_obj-246:1
}

void receive_69_output_number_set(number v) {
    this->receive_69_output_number = v;
    this->expr_33_in1_set(v);
}

void freqshift_tilde_34_frequency_set(number v) {
    this->freqshift_tilde_34_frequency = v;
}

void expr_34_out1_set(number v) {
    this->expr_34_out1 = v;
    this->freqshift_tilde_34_frequency_set(this->expr_34_out1);
}

void expr_34_in1_set(number in1) {
    this->expr_34_in1 = in1;
    this->expr_34_out1_set(this->expr_34_in1 * this->expr_34_in2);//#map:*_obj-209:1
}

void receive_71_output_number_set(number v) {
    this->receive_71_output_number = v;
    this->expr_34_in1_set(v);
}

void freqshift_tilde_35_frequency_set(number v) {
    this->freqshift_tilde_35_frequency = v;
}

void expr_35_out1_set(number v) {
    this->expr_35_out1 = v;
    this->freqshift_tilde_35_frequency_set(this->expr_35_out1);
}

void expr_35_in1_set(number in1) {
    this->expr_35_in1 = in1;
    this->expr_35_out1_set(this->expr_35_in1 * this->expr_35_in2);//#map:*_obj-74:1
}

void receive_74_output_number_set(number v) {
    this->receive_74_output_number = v;
    this->expr_35_in1_set(v);
}

void freqshift_tilde_36_frequency_set(number v) {
    this->freqshift_tilde_36_frequency = v;
}

void expr_36_out1_set(number v) {
    this->expr_36_out1 = v;
    this->freqshift_tilde_36_frequency_set(this->expr_36_out1);
}

void expr_36_in1_set(number in1) {
    this->expr_36_in1 = in1;
    this->expr_36_out1_set(this->expr_36_in1 * this->expr_36_in2);//#map:*_obj-139:1
}

void receive_75_output_number_set(number v) {
    this->receive_75_output_number = v;
    this->expr_36_in1_set(v);
}

void freqshift_tilde_37_frequency_set(number v) {
    this->freqshift_tilde_37_frequency = v;
}

void expr_37_out1_set(number v) {
    this->expr_37_out1 = v;
    this->freqshift_tilde_37_frequency_set(this->expr_37_out1);
}

void expr_37_in1_set(number in1) {
    this->expr_37_in1 = in1;
    this->expr_37_out1_set(this->expr_37_in1 * this->expr_37_in2);//#map:*_obj-241:1
}

void receive_76_output_number_set(number v) {
    this->receive_76_output_number = v;
    this->expr_37_in1_set(v);
}

void freqshift_tilde_38_frequency_set(number v) {
    this->freqshift_tilde_38_frequency = v;
}

void expr_38_out1_set(number v) {
    this->expr_38_out1 = v;
    this->freqshift_tilde_38_frequency_set(this->expr_38_out1);
}

void expr_38_in1_set(number in1) {
    this->expr_38_in1 = in1;
    this->expr_38_out1_set(this->expr_38_in1 * this->expr_38_in2);//#map:*_obj-214:1
}

void receive_77_output_number_set(number v) {
    this->receive_77_output_number = v;
    this->expr_38_in1_set(v);
}

void freqshift_tilde_39_frequency_set(number v) {
    this->freqshift_tilde_39_frequency = v;
}

void expr_39_out1_set(number v) {
    this->expr_39_out1 = v;
    this->freqshift_tilde_39_frequency_set(this->expr_39_out1);
}

void expr_39_in1_set(number in1) {
    this->expr_39_in1 = in1;
    this->expr_39_out1_set(this->expr_39_in1 * this->expr_39_in2);//#map:*_obj-144:1
}

void receive_79_output_number_set(number v) {
    this->receive_79_output_number = v;
    this->expr_39_in1_set(v);
}

void send_03_input_number_set(number v) {
    this->send_03_input_number = v;
    this->receive_06_output_number_set(v);
    this->receive_07_output_number_set(v);
    this->receive_08_output_number_set(v);
    this->receive_09_output_number_set(v);
    this->receive_14_output_number_set(v);
    this->receive_15_output_number_set(v);
    this->receive_16_output_number_set(v);
    this->receive_18_output_number_set(v);
    this->receive_22_output_number_set(v);
    this->receive_23_output_number_set(v);
    this->receive_24_output_number_set(v);
    this->receive_26_output_number_set(v);
    this->receive_30_output_number_set(v);
    this->receive_31_output_number_set(v);
    this->receive_32_output_number_set(v);
    this->receive_35_output_number_set(v);
    this->receive_38_output_number_set(v);
    this->receive_39_output_number_set(v);
    this->receive_42_output_number_set(v);
    this->receive_43_output_number_set(v);
    this->receive_46_output_number_set(v);
    this->receive_47_output_number_set(v);
    this->receive_50_output_number_set(v);
    this->receive_51_output_number_set(v);
    this->receive_54_output_number_set(v);
    this->receive_55_output_number_set(v);
    this->receive_58_output_number_set(v);
    this->receive_59_output_number_set(v);
    this->receive_62_output_number_set(v);
    this->receive_63_output_number_set(v);
    this->receive_66_output_number_set(v);
    this->receive_67_output_number_set(v);
    this->receive_69_output_number_set(v);
    this->receive_71_output_number_set(v);
    this->receive_74_output_number_set(v);
    this->receive_75_output_number_set(v);
    this->receive_76_output_number_set(v);
    this->receive_77_output_number_set(v);
    this->receive_79_output_number_set(v);
}

static number param_04_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_05_outval_set(number ) {}

void gaintilde_05_value_set(number v) {
    this->gaintilde_05_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-11"), v, this->_currentTime);
    this->gaintilde_05_outval_set(value);
}

void gaintilde_05_input_number_set(number v) {
    this->gaintilde_05_input_number = v;

    this->gaintilde_05_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_05_output_number_set(number v) {
    this->receive_05_output_number = v;
    this->gaintilde_05_input_number_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->receive_05_output_number_set(v);
}

static number param_05_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-4"), v, this->_currentTime);
    this->gaintilde_01_outval_set(value);
}

void gaintilde_01_input_number_set(number v) {
    this->gaintilde_01_input_number = v;

    this->gaintilde_01_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_01_output_number_set(number v) {
    this->receive_01_output_number = v;
    this->gaintilde_01_input_number_set(v);
}

void send_05_input_number_set(number v) {
    this->send_05_input_number = v;
    this->receive_01_output_number_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_29_outval_set(number ) {}

void gaintilde_29_value_set(number v) {
    this->gaintilde_29_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-63"), v, this->_currentTime);
    this->gaintilde_29_outval_set(value);
}

void gaintilde_29_input_number_set(number v) {
    this->gaintilde_29_input_number = v;

    this->gaintilde_29_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_53_output_number_set(number v) {
    this->receive_53_output_number = v;
    this->gaintilde_29_input_number_set(v);
}

void send_06_input_number_set(number v) {
    this->send_06_input_number = v;
    this->receive_53_output_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_25_outval_set(number ) {}

void gaintilde_25_value_set(number v) {
    this->gaintilde_25_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-56"), v, this->_currentTime);
    this->gaintilde_25_outval_set(value);
}

void gaintilde_25_input_number_set(number v) {
    this->gaintilde_25_input_number = v;

    this->gaintilde_25_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_45_output_number_set(number v) {
    this->receive_45_output_number = v;
    this->gaintilde_25_input_number_set(v);
}

void send_07_input_number_set(number v) {
    this->send_07_input_number = v;
    this->receive_45_output_number_set(v);
}

static number param_08_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_21_outval_set(number ) {}

void gaintilde_21_value_set(number v) {
    this->gaintilde_21_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-49"), v, this->_currentTime);
    this->gaintilde_21_outval_set(value);
}

void gaintilde_21_input_number_set(number v) {
    this->gaintilde_21_input_number = v;

    this->gaintilde_21_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_37_output_number_set(number v) {
    this->receive_37_output_number = v;
    this->gaintilde_21_input_number_set(v);
}

void send_08_input_number_set(number v) {
    this->send_08_input_number = v;
    this->receive_37_output_number_set(v);
}

static number param_09_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_17_outval_set(number ) {}

void gaintilde_17_value_set(number v) {
    this->gaintilde_17_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-42"), v, this->_currentTime);
    this->gaintilde_17_outval_set(value);
}

void gaintilde_17_input_number_set(number v) {
    this->gaintilde_17_input_number = v;

    this->gaintilde_17_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_29_output_number_set(number v) {
    this->receive_29_output_number = v;
    this->gaintilde_17_input_number_set(v);
}

void send_09_input_number_set(number v) {
    this->send_09_input_number = v;
    this->receive_29_output_number_set(v);
}

static number param_10_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_06_outval_set(number ) {}

void gaintilde_06_value_set(number v) {
    this->gaintilde_06_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-91"), v, this->_currentTime);
    this->gaintilde_06_outval_set(value);
}

void gaintilde_06_input_number_set(number v) {
    this->gaintilde_06_input_number = v;

    this->gaintilde_06_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_10_output_number_set(number v) {
    this->receive_10_output_number = v;
    this->gaintilde_06_input_number_set(v);
}

void send_10_input_number_set(number v) {
    this->send_10_input_number = v;
    this->receive_10_output_number_set(v);
}

static number param_11_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_02_outval_set(number ) {}

void gaintilde_02_value_set(number v) {
    this->gaintilde_02_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-84"), v, this->_currentTime);
    this->gaintilde_02_outval_set(value);
}

void gaintilde_02_input_number_set(number v) {
    this->gaintilde_02_input_number = v;

    this->gaintilde_02_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->gaintilde_02_input_number_set(v);
}

void send_11_input_number_set(number v) {
    this->send_11_input_number = v;
    this->receive_02_output_number_set(v);
}

static number param_12_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_36_outval_set(number ) {}

void gaintilde_36_value_set(number v) {
    this->gaintilde_36_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-77"), v, this->_currentTime);
    this->gaintilde_36_outval_set(value);
}

void gaintilde_36_input_number_set(number v) {
    this->gaintilde_36_input_number = v;

    this->gaintilde_36_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_68_output_number_set(number v) {
    this->receive_68_output_number = v;
    this->gaintilde_36_input_number_set(v);
}

void send_12_input_number_set(number v) {
    this->send_12_input_number = v;
    this->receive_68_output_number_set(v);
}

static number param_13_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_32_outval_set(number ) {}

void gaintilde_32_value_set(number v) {
    this->gaintilde_32_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-70"), v, this->_currentTime);
    this->gaintilde_32_outval_set(value);
}

void gaintilde_32_input_number_set(number v) {
    this->gaintilde_32_input_number = v;

    this->gaintilde_32_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_60_output_number_set(number v) {
    this->receive_60_output_number = v;
    this->gaintilde_32_input_number_set(v);
}

void send_13_input_number_set(number v) {
    this->send_13_input_number = v;
    this->receive_60_output_number_set(v);
}

static number param_14_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_24_outval_set(number ) {}

void gaintilde_24_value_set(number v) {
    this->gaintilde_24_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-127"), v, this->_currentTime);
    this->gaintilde_24_outval_set(value);
}

void gaintilde_24_input_number_set(number v) {
    this->gaintilde_24_input_number = v;

    this->gaintilde_24_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_44_output_number_set(number v) {
    this->receive_44_output_number = v;
    this->gaintilde_24_input_number_set(v);
}

void send_14_input_number_set(number v) {
    this->send_14_input_number = v;
    this->receive_44_output_number_set(v);
}

static number param_15_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_20_outval_set(number ) {}

void gaintilde_20_value_set(number v) {
    this->gaintilde_20_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-112"), v, this->_currentTime);
    this->gaintilde_20_outval_set(value);
}

void gaintilde_20_input_number_set(number v) {
    this->gaintilde_20_input_number = v;

    this->gaintilde_20_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_36_output_number_set(number v) {
    this->receive_36_output_number = v;
    this->gaintilde_20_input_number_set(v);
}

void send_15_input_number_set(number v) {
    this->send_15_input_number = v;
    this->receive_36_output_number_set(v);
}

static number param_16_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_16_outval_set(number ) {}

void gaintilde_16_value_set(number v) {
    this->gaintilde_16_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-105"), v, this->_currentTime);
    this->gaintilde_16_outval_set(value);
}

void gaintilde_16_input_number_set(number v) {
    this->gaintilde_16_input_number = v;

    this->gaintilde_16_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_28_output_number_set(number v) {
    this->receive_28_output_number = v;
    this->gaintilde_16_input_number_set(v);
}

void send_16_input_number_set(number v) {
    this->send_16_input_number = v;
    this->receive_28_output_number_set(v);
}

static number param_17_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_12_outval_set(number ) {}

void gaintilde_12_value_set(number v) {
    this->gaintilde_12_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-98"), v, this->_currentTime);
    this->gaintilde_12_outval_set(value);
}

void gaintilde_12_input_number_set(number v) {
    this->gaintilde_12_input_number = v;

    this->gaintilde_12_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_20_output_number_set(number v) {
    this->receive_20_output_number = v;
    this->gaintilde_12_input_number_set(v);
}

void send_17_input_number_set(number v) {
    this->send_17_input_number = v;
    this->receive_20_output_number_set(v);
}

static number param_18_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_40_outval_set(number ) {}

void gaintilde_40_value_set(number v) {
    this->gaintilde_40_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-147"), v, this->_currentTime);
    this->gaintilde_40_outval_set(value);
}

void gaintilde_40_input_number_set(number v) {
    this->gaintilde_40_input_number = v;

    this->gaintilde_40_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_78_output_number_set(number v) {
    this->receive_78_output_number = v;
    this->gaintilde_40_input_number_set(v);
}

void send_18_input_number_set(number v) {
    this->send_18_input_number = v;
    this->receive_78_output_number_set(v);
}

static number param_19_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_37_outval_set(number ) {}

void gaintilde_37_value_set(number v) {
    this->gaintilde_37_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-142"), v, this->_currentTime);
    this->gaintilde_37_outval_set(value);
}

void gaintilde_37_input_number_set(number v) {
    this->gaintilde_37_input_number = v;

    this->gaintilde_37_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_70_output_number_set(number v) {
    this->receive_70_output_number = v;
    this->gaintilde_37_input_number_set(v);
}

void send_19_input_number_set(number v) {
    this->send_19_input_number = v;
    this->receive_70_output_number_set(v);
}

static number param_20_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_33_outval_set(number ) {}

void gaintilde_33_value_set(number v) {
    this->gaintilde_33_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-137"), v, this->_currentTime);
    this->gaintilde_33_outval_set(value);
}

void gaintilde_33_input_number_set(number v) {
    this->gaintilde_33_input_number = v;

    this->gaintilde_33_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_61_output_number_set(number v) {
    this->receive_61_output_number = v;
    this->gaintilde_33_input_number_set(v);
}

void send_20_input_number_set(number v) {
    this->send_20_input_number = v;
    this->receive_61_output_number_set(v);
}

static number param_21_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_28_outval_set(number ) {}

void gaintilde_28_value_set(number v) {
    this->gaintilde_28_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-132"), v, this->_currentTime);
    this->gaintilde_28_outval_set(value);
}

void gaintilde_28_input_number_set(number v) {
    this->gaintilde_28_input_number = v;

    this->gaintilde_28_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_52_output_number_set(number v) {
    this->receive_52_output_number = v;
    this->gaintilde_28_input_number_set(v);
}

void send_21_input_number_set(number v) {
    this->send_21_input_number = v;
    this->receive_52_output_number_set(v);
}

static number param_22_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_11_outval_set(number ) {}

void gaintilde_11_value_set(number v) {
    this->gaintilde_11_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-182"), v, this->_currentTime);
    this->gaintilde_11_outval_set(value);
}

void gaintilde_11_input_number_set(number v) {
    this->gaintilde_11_input_number = v;

    this->gaintilde_11_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_19_output_number_set(number v) {
    this->receive_19_output_number = v;
    this->gaintilde_11_input_number_set(v);
}

void send_22_input_number_set(number v) {
    this->send_22_input_number = v;
    this->receive_19_output_number_set(v);
}

static number param_23_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_15_outval_set(number ) {}

void gaintilde_15_value_set(number v) {
    this->gaintilde_15_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-187"), v, this->_currentTime);
    this->gaintilde_15_outval_set(value);
}

void gaintilde_15_input_number_set(number v) {
    this->gaintilde_15_input_number = v;

    this->gaintilde_15_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_27_output_number_set(number v) {
    this->receive_27_output_number = v;
    this->gaintilde_15_input_number_set(v);
}

void send_23_input_number_set(number v) {
    this->send_23_input_number = v;
    this->receive_27_output_number_set(v);
}

static number param_24_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_08_outval_set(number ) {}

void gaintilde_08_value_set(number v) {
    this->gaintilde_08_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-177"), v, this->_currentTime);
    this->gaintilde_08_outval_set(value);
}

void gaintilde_08_input_number_set(number v) {
    this->gaintilde_08_input_number = v;

    this->gaintilde_08_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_12_output_number_set(number v) {
    this->receive_12_output_number = v;
    this->gaintilde_08_input_number_set(v);
}

void send_24_input_number_set(number v) {
    this->send_24_input_number = v;
    this->receive_12_output_number_set(v);
}

static number param_25_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_04_outval_set(number ) {}

void gaintilde_04_value_set(number v) {
    this->gaintilde_04_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-172"), v, this->_currentTime);
    this->gaintilde_04_outval_set(value);
}

void gaintilde_04_input_number_set(number v) {
    this->gaintilde_04_input_number = v;

    this->gaintilde_04_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_04_output_number_set(number v) {
    this->receive_04_output_number = v;
    this->gaintilde_04_input_number_set(v);
}

void send_25_input_number_set(number v) {
    this->send_25_input_number = v;
    this->receive_04_output_number_set(v);
}

static number param_26_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_23_outval_set(number ) {}

void gaintilde_23_value_set(number v) {
    this->gaintilde_23_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-197"), v, this->_currentTime);
    this->gaintilde_23_outval_set(value);
}

void gaintilde_23_input_number_set(number v) {
    this->gaintilde_23_input_number = v;

    this->gaintilde_23_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_41_output_number_set(number v) {
    this->receive_41_output_number = v;
    this->gaintilde_23_input_number_set(v);
}

void send_26_input_number_set(number v) {
    this->send_26_input_number = v;
    this->receive_41_output_number_set(v);
}

static number param_27_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_19_outval_set(number ) {}

void gaintilde_19_value_set(number v) {
    this->gaintilde_19_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-192"), v, this->_currentTime);
    this->gaintilde_19_outval_set(value);
}

void gaintilde_19_input_number_set(number v) {
    this->gaintilde_19_input_number = v;

    this->gaintilde_19_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_34_output_number_set(number v) {
    this->receive_34_output_number = v;
    this->gaintilde_19_input_number_set(v);
}

void send_27_input_number_set(number v) {
    this->send_27_input_number = v;
    this->receive_34_output_number_set(v);
}

static number param_28_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_31_outval_set(number ) {}

void gaintilde_31_value_set(number v) {
    this->gaintilde_31_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-207"), v, this->_currentTime);
    this->gaintilde_31_outval_set(value);
}

void gaintilde_31_input_number_set(number v) {
    this->gaintilde_31_input_number = v;

    this->gaintilde_31_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_57_output_number_set(number v) {
    this->receive_57_output_number = v;
    this->gaintilde_31_input_number_set(v);
}

void send_28_input_number_set(number v) {
    this->send_28_input_number = v;
    this->receive_57_output_number_set(v);
}

static number param_29_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_27_outval_set(number ) {}

void gaintilde_27_value_set(number v) {
    this->gaintilde_27_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-202"), v, this->_currentTime);
    this->gaintilde_27_outval_set(value);
}

void gaintilde_27_input_number_set(number v) {
    this->gaintilde_27_input_number = v;

    this->gaintilde_27_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_49_output_number_set(number v) {
    this->receive_49_output_number = v;
    this->gaintilde_27_input_number_set(v);
}

void send_29_input_number_set(number v) {
    this->send_29_input_number = v;
    this->receive_49_output_number_set(v);
}

static number param_30_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_07_outval_set(number ) {}

void gaintilde_07_value_set(number v) {
    this->gaintilde_07_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-284"), v, this->_currentTime);
    this->gaintilde_07_outval_set(value);
}

void gaintilde_07_input_number_set(number v) {
    this->gaintilde_07_input_number = v;

    this->gaintilde_07_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_11_output_number_set(number v) {
    this->receive_11_output_number = v;
    this->gaintilde_07_input_number_set(v);
}

void send_30_input_number_set(number v) {
    this->send_30_input_number = v;
    this->receive_11_output_number_set(v);
}

static number param_31_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_03_outval_set(number ) {}

void gaintilde_03_value_set(number v) {
    this->gaintilde_03_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-289"), v, this->_currentTime);
    this->gaintilde_03_outval_set(value);
}

void gaintilde_03_input_number_set(number v) {
    this->gaintilde_03_input_number = v;

    this->gaintilde_03_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_03_output_number_set(number v) {
    this->receive_03_output_number = v;
    this->gaintilde_03_input_number_set(v);
}

void send_31_input_number_set(number v) {
    this->send_31_input_number = v;
    this->receive_03_output_number_set(v);
}

static number param_32_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_39_outval_set(number ) {}

void gaintilde_39_value_set(number v) {
    this->gaintilde_39_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-217"), v, this->_currentTime);
    this->gaintilde_39_outval_set(value);
}

void gaintilde_39_input_number_set(number v) {
    this->gaintilde_39_input_number = v;

    this->gaintilde_39_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_73_output_number_set(number v) {
    this->receive_73_output_number = v;
    this->gaintilde_39_input_number_set(v);
}

void send_32_input_number_set(number v) {
    this->send_32_input_number = v;
    this->receive_73_output_number_set(v);
}

static number param_33_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_35_outval_set(number ) {}

void gaintilde_35_value_set(number v) {
    this->gaintilde_35_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-212"), v, this->_currentTime);
    this->gaintilde_35_outval_set(value);
}

void gaintilde_35_input_number_set(number v) {
    this->gaintilde_35_input_number = v;

    this->gaintilde_35_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_65_output_number_set(number v) {
    this->receive_65_output_number = v;
    this->gaintilde_35_input_number_set(v);
}

void send_33_input_number_set(number v) {
    this->send_33_input_number = v;
    this->receive_65_output_number_set(v);
}

static number param_34_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_22_outval_set(number ) {}

void gaintilde_22_value_set(number v) {
    this->gaintilde_22_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-264"), v, this->_currentTime);
    this->gaintilde_22_outval_set(value);
}

void gaintilde_22_input_number_set(number v) {
    this->gaintilde_22_input_number = v;

    this->gaintilde_22_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_40_output_number_set(number v) {
    this->receive_40_output_number = v;
    this->gaintilde_22_input_number_set(v);
}

void send_34_input_number_set(number v) {
    this->send_34_input_number = v;
    this->receive_40_output_number_set(v);
}

static number param_35_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_18_outval_set(number ) {}

void gaintilde_18_value_set(number v) {
    this->gaintilde_18_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-269"), v, this->_currentTime);
    this->gaintilde_18_outval_set(value);
}

void gaintilde_18_input_number_set(number v) {
    this->gaintilde_18_input_number = v;

    this->gaintilde_18_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_33_output_number_set(number v) {
    this->receive_33_output_number = v;
    this->gaintilde_18_input_number_set(v);
}

void send_35_input_number_set(number v) {
    this->send_35_input_number = v;
    this->receive_33_output_number_set(v);
}

static number param_36_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_14_outval_set(number ) {}

void gaintilde_14_value_set(number v) {
    this->gaintilde_14_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-274"), v, this->_currentTime);
    this->gaintilde_14_outval_set(value);
}

void gaintilde_14_input_number_set(number v) {
    this->gaintilde_14_input_number = v;

    this->gaintilde_14_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_25_output_number_set(number v) {
    this->receive_25_output_number = v;
    this->gaintilde_14_input_number_set(v);
}

void send_36_input_number_set(number v) {
    this->send_36_input_number = v;
    this->receive_25_output_number_set(v);
}

static number param_37_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_10_outval_set(number ) {}

void gaintilde_10_value_set(number v) {
    this->gaintilde_10_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-279"), v, this->_currentTime);
    this->gaintilde_10_outval_set(value);
}

void gaintilde_10_input_number_set(number v) {
    this->gaintilde_10_input_number = v;

    this->gaintilde_10_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_17_output_number_set(number v) {
    this->receive_17_output_number = v;
    this->gaintilde_10_input_number_set(v);
}

void send_37_input_number_set(number v) {
    this->send_37_input_number = v;
    this->receive_17_output_number_set(v);
}

static number param_38_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_38_outval_set(number ) {}

void gaintilde_38_value_set(number v) {
    this->gaintilde_38_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-244"), v, this->_currentTime);
    this->gaintilde_38_outval_set(value);
}

void gaintilde_38_input_number_set(number v) {
    this->gaintilde_38_input_number = v;

    this->gaintilde_38_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_72_output_number_set(number v) {
    this->receive_72_output_number = v;
    this->gaintilde_38_input_number_set(v);
}

void send_38_input_number_set(number v) {
    this->send_38_input_number = v;
    this->receive_72_output_number_set(v);
}

static number param_39_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_34_outval_set(number ) {}

void gaintilde_34_value_set(number v) {
    this->gaintilde_34_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-249"), v, this->_currentTime);
    this->gaintilde_34_outval_set(value);
}

void gaintilde_34_input_number_set(number v) {
    this->gaintilde_34_input_number = v;

    this->gaintilde_34_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_64_output_number_set(number v) {
    this->receive_64_output_number = v;
    this->gaintilde_34_input_number_set(v);
}

void send_39_input_number_set(number v) {
    this->send_39_input_number = v;
    this->receive_64_output_number_set(v);
}

static number param_40_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_30_outval_set(number ) {}

void gaintilde_30_value_set(number v) {
    this->gaintilde_30_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-254"), v, this->_currentTime);
    this->gaintilde_30_outval_set(value);
}

void gaintilde_30_input_number_set(number v) {
    this->gaintilde_30_input_number = v;

    this->gaintilde_30_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_56_output_number_set(number v) {
    this->receive_56_output_number = v;
    this->gaintilde_30_input_number_set(v);
}

void send_40_input_number_set(number v) {
    this->send_40_input_number = v;
    this->receive_56_output_number_set(v);
}

static number param_41_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_26_outval_set(number ) {}

void gaintilde_26_value_set(number v) {
    this->gaintilde_26_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-259"), v, this->_currentTime);
    this->gaintilde_26_outval_set(value);
}

void gaintilde_26_input_number_set(number v) {
    this->gaintilde_26_input_number = v;

    this->gaintilde_26_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_48_output_number_set(number v) {
    this->receive_48_output_number = v;
    this->gaintilde_26_input_number_set(v);
}

void send_41_input_number_set(number v) {
    this->send_41_input_number = v;
    this->receive_48_output_number_set(v);
}

void freqshift_tilde_11_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_11_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_11_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_12_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_12_interp = this->gaintilde_12_interp;
    auto __gaintilde_12_loginc = this->gaintilde_12_loginc;
    auto __gaintilde_12_zval = this->gaintilde_12_zval;
    auto __gaintilde_12_value = this->gaintilde_12_value;
    number mult = (__gaintilde_12_value <= 0 ? 0. : __gaintilde_12_zval * rnbo_exp(__gaintilde_12_value * __gaintilde_12_loginc));
    auto iv = this->mstosamps(__gaintilde_12_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_12_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_05_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_05_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_05_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_06_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_06_interp = this->gaintilde_06_interp;
    auto __gaintilde_06_loginc = this->gaintilde_06_loginc;
    auto __gaintilde_06_zval = this->gaintilde_06_zval;
    auto __gaintilde_06_value = this->gaintilde_06_value;
    number mult = (__gaintilde_06_value <= 0 ? 0. : __gaintilde_06_zval * rnbo_exp(__gaintilde_06_value * __gaintilde_06_loginc));
    auto iv = this->mstosamps(__gaintilde_06_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_06_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_01_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_01_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_01_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_02_interp = this->gaintilde_02_interp;
    auto __gaintilde_02_loginc = this->gaintilde_02_loginc;
    auto __gaintilde_02_zval = this->gaintilde_02_zval;
    auto __gaintilde_02_value = this->gaintilde_02_value;
    number mult = (__gaintilde_02_value <= 0 ? 0. : __gaintilde_02_zval * rnbo_exp(__gaintilde_02_value * __gaintilde_02_loginc));
    auto iv = this->mstosamps(__gaintilde_02_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_02_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_35_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_35_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_35_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_36_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_36_interp = this->gaintilde_36_interp;
    auto __gaintilde_36_loginc = this->gaintilde_36_loginc;
    auto __gaintilde_36_zval = this->gaintilde_36_zval;
    auto __gaintilde_36_value = this->gaintilde_36_value;
    number mult = (__gaintilde_36_value <= 0 ? 0. : __gaintilde_36_zval * rnbo_exp(__gaintilde_36_value * __gaintilde_36_loginc));
    auto iv = this->mstosamps(__gaintilde_36_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_36_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_31_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_31_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_31_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_32_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_32_interp = this->gaintilde_32_interp;
    auto __gaintilde_32_loginc = this->gaintilde_32_loginc;
    auto __gaintilde_32_zval = this->gaintilde_32_zval;
    auto __gaintilde_32_value = this->gaintilde_32_value;
    number mult = (__gaintilde_32_value <= 0 ? 0. : __gaintilde_32_zval * rnbo_exp(__gaintilde_32_value * __gaintilde_32_loginc));
    auto iv = this->mstosamps(__gaintilde_32_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_32_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_28_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_28_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_28_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_29_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_29_interp = this->gaintilde_29_interp;
    auto __gaintilde_29_loginc = this->gaintilde_29_loginc;
    auto __gaintilde_29_zval = this->gaintilde_29_zval;
    auto __gaintilde_29_value = this->gaintilde_29_value;
    number mult = (__gaintilde_29_value <= 0 ? 0. : __gaintilde_29_zval * rnbo_exp(__gaintilde_29_value * __gaintilde_29_loginc));
    auto iv = this->mstosamps(__gaintilde_29_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_29_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_24_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_24_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_24_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_25_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_25_interp = this->gaintilde_25_interp;
    auto __gaintilde_25_loginc = this->gaintilde_25_loginc;
    auto __gaintilde_25_zval = this->gaintilde_25_zval;
    auto __gaintilde_25_value = this->gaintilde_25_value;
    number mult = (__gaintilde_25_value <= 0 ? 0. : __gaintilde_25_zval * rnbo_exp(__gaintilde_25_value * __gaintilde_25_loginc));
    auto iv = this->mstosamps(__gaintilde_25_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_25_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_20_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_20_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_20_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_21_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_21_interp = this->gaintilde_21_interp;
    auto __gaintilde_21_loginc = this->gaintilde_21_loginc;
    auto __gaintilde_21_zval = this->gaintilde_21_zval;
    auto __gaintilde_21_value = this->gaintilde_21_value;
    number mult = (__gaintilde_21_value <= 0 ? 0. : __gaintilde_21_zval * rnbo_exp(__gaintilde_21_value * __gaintilde_21_loginc));
    auto iv = this->mstosamps(__gaintilde_21_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_21_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_16_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_16_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_16_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_17_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_17_interp = this->gaintilde_17_interp;
    auto __gaintilde_17_loginc = this->gaintilde_17_loginc;
    auto __gaintilde_17_zval = this->gaintilde_17_zval;
    auto __gaintilde_17_value = this->gaintilde_17_value;
    number mult = (__gaintilde_17_value <= 0 ? 0. : __gaintilde_17_zval * rnbo_exp(__gaintilde_17_value * __gaintilde_17_loginc));
    auto iv = this->mstosamps(__gaintilde_17_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_17_ramp_next(mult, iv, iv);
    }
}

void gaintilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_01_interp = this->gaintilde_01_interp;
    auto __gaintilde_01_loginc = this->gaintilde_01_loginc;
    auto __gaintilde_01_zval = this->gaintilde_01_zval;
    auto __gaintilde_01_value = this->gaintilde_01_value;
    number mult = (__gaintilde_01_value <= 0 ? 0. : __gaintilde_01_zval * rnbo_exp(__gaintilde_01_value * __gaintilde_01_loginc));
    auto iv = this->mstosamps(__gaintilde_01_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_01_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_12_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_12_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_12_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_13_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_13_interp = this->gaintilde_13_interp;
    auto __gaintilde_13_loginc = this->gaintilde_13_loginc;
    auto __gaintilde_13_zval = this->gaintilde_13_zval;
    auto __gaintilde_13_value = this->gaintilde_13_value;
    number mult = (__gaintilde_13_value <= 0 ? 0. : __gaintilde_13_zval * rnbo_exp(__gaintilde_13_value * __gaintilde_13_loginc));
    auto iv = this->mstosamps(__gaintilde_13_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_13_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_02_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_02_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_02_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_03_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_03_interp = this->gaintilde_03_interp;
    auto __gaintilde_03_loginc = this->gaintilde_03_loginc;
    auto __gaintilde_03_zval = this->gaintilde_03_zval;
    auto __gaintilde_03_value = this->gaintilde_03_value;
    number mult = (__gaintilde_03_value <= 0 ? 0. : __gaintilde_03_zval * rnbo_exp(__gaintilde_03_value * __gaintilde_03_loginc));
    auto iv = this->mstosamps(__gaintilde_03_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_03_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_06_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_06_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_06_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_07_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_07_interp = this->gaintilde_07_interp;
    auto __gaintilde_07_loginc = this->gaintilde_07_loginc;
    auto __gaintilde_07_zval = this->gaintilde_07_zval;
    auto __gaintilde_07_value = this->gaintilde_07_value;
    number mult = (__gaintilde_07_value <= 0 ? 0. : __gaintilde_07_zval * rnbo_exp(__gaintilde_07_value * __gaintilde_07_loginc));
    auto iv = this->mstosamps(__gaintilde_07_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_07_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_09_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_09_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_09_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_10_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_10_interp = this->gaintilde_10_interp;
    auto __gaintilde_10_loginc = this->gaintilde_10_loginc;
    auto __gaintilde_10_zval = this->gaintilde_10_zval;
    auto __gaintilde_10_value = this->gaintilde_10_value;
    number mult = (__gaintilde_10_value <= 0 ? 0. : __gaintilde_10_zval * rnbo_exp(__gaintilde_10_value * __gaintilde_10_loginc));
    auto iv = this->mstosamps(__gaintilde_10_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_10_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_13_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_13_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_13_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_14_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_14_interp = this->gaintilde_14_interp;
    auto __gaintilde_14_loginc = this->gaintilde_14_loginc;
    auto __gaintilde_14_zval = this->gaintilde_14_zval;
    auto __gaintilde_14_value = this->gaintilde_14_value;
    number mult = (__gaintilde_14_value <= 0 ? 0. : __gaintilde_14_zval * rnbo_exp(__gaintilde_14_value * __gaintilde_14_loginc));
    auto iv = this->mstosamps(__gaintilde_14_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_14_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_17_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_17_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_17_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_18_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_18_interp = this->gaintilde_18_interp;
    auto __gaintilde_18_loginc = this->gaintilde_18_loginc;
    auto __gaintilde_18_zval = this->gaintilde_18_zval;
    auto __gaintilde_18_value = this->gaintilde_18_value;
    number mult = (__gaintilde_18_value <= 0 ? 0. : __gaintilde_18_zval * rnbo_exp(__gaintilde_18_value * __gaintilde_18_loginc));
    auto iv = this->mstosamps(__gaintilde_18_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_18_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_21_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_21_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_21_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_22_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_22_interp = this->gaintilde_22_interp;
    auto __gaintilde_22_loginc = this->gaintilde_22_loginc;
    auto __gaintilde_22_zval = this->gaintilde_22_zval;
    auto __gaintilde_22_value = this->gaintilde_22_value;
    number mult = (__gaintilde_22_value <= 0 ? 0. : __gaintilde_22_zval * rnbo_exp(__gaintilde_22_value * __gaintilde_22_loginc));
    auto iv = this->mstosamps(__gaintilde_22_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_22_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_08_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_08_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_08_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_09_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_09_interp = this->gaintilde_09_interp;
    auto __gaintilde_09_loginc = this->gaintilde_09_loginc;
    auto __gaintilde_09_zval = this->gaintilde_09_zval;
    auto __gaintilde_09_value = this->gaintilde_09_value;
    number mult = (__gaintilde_09_value <= 0 ? 0. : __gaintilde_09_zval * rnbo_exp(__gaintilde_09_value * __gaintilde_09_loginc));
    auto iv = this->mstosamps(__gaintilde_09_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_09_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_25_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_25_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_25_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_26_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_26_interp = this->gaintilde_26_interp;
    auto __gaintilde_26_loginc = this->gaintilde_26_loginc;
    auto __gaintilde_26_zval = this->gaintilde_26_zval;
    auto __gaintilde_26_value = this->gaintilde_26_value;
    number mult = (__gaintilde_26_value <= 0 ? 0. : __gaintilde_26_zval * rnbo_exp(__gaintilde_26_value * __gaintilde_26_loginc));
    auto iv = this->mstosamps(__gaintilde_26_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_26_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_29_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_29_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_29_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_30_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_30_interp = this->gaintilde_30_interp;
    auto __gaintilde_30_loginc = this->gaintilde_30_loginc;
    auto __gaintilde_30_zval = this->gaintilde_30_zval;
    auto __gaintilde_30_value = this->gaintilde_30_value;
    number mult = (__gaintilde_30_value <= 0 ? 0. : __gaintilde_30_zval * rnbo_exp(__gaintilde_30_value * __gaintilde_30_loginc));
    auto iv = this->mstosamps(__gaintilde_30_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_30_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_33_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_33_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_33_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_34_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_34_interp = this->gaintilde_34_interp;
    auto __gaintilde_34_loginc = this->gaintilde_34_loginc;
    auto __gaintilde_34_zval = this->gaintilde_34_zval;
    auto __gaintilde_34_value = this->gaintilde_34_value;
    number mult = (__gaintilde_34_value <= 0 ? 0. : __gaintilde_34_zval * rnbo_exp(__gaintilde_34_value * __gaintilde_34_loginc));
    auto iv = this->mstosamps(__gaintilde_34_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_34_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_37_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_37_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_37_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_38_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_38_interp = this->gaintilde_38_interp;
    auto __gaintilde_38_loginc = this->gaintilde_38_loginc;
    auto __gaintilde_38_zval = this->gaintilde_38_zval;
    auto __gaintilde_38_value = this->gaintilde_38_value;
    number mult = (__gaintilde_38_value <= 0 ? 0. : __gaintilde_38_zval * rnbo_exp(__gaintilde_38_value * __gaintilde_38_loginc));
    auto iv = this->mstosamps(__gaintilde_38_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_38_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_38_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_38_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_38_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_39_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_39_interp = this->gaintilde_39_interp;
    auto __gaintilde_39_loginc = this->gaintilde_39_loginc;
    auto __gaintilde_39_zval = this->gaintilde_39_zval;
    auto __gaintilde_39_value = this->gaintilde_39_value;
    number mult = (__gaintilde_39_value <= 0 ? 0. : __gaintilde_39_zval * rnbo_exp(__gaintilde_39_value * __gaintilde_39_loginc));
    auto iv = this->mstosamps(__gaintilde_39_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_39_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_34_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_34_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_34_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_35_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_35_interp = this->gaintilde_35_interp;
    auto __gaintilde_35_loginc = this->gaintilde_35_loginc;
    auto __gaintilde_35_zval = this->gaintilde_35_zval;
    auto __gaintilde_35_value = this->gaintilde_35_value;
    number mult = (__gaintilde_35_value <= 0 ? 0. : __gaintilde_35_zval * rnbo_exp(__gaintilde_35_value * __gaintilde_35_loginc));
    auto iv = this->mstosamps(__gaintilde_35_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_35_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_30_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_30_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_30_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_31_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_31_interp = this->gaintilde_31_interp;
    auto __gaintilde_31_loginc = this->gaintilde_31_loginc;
    auto __gaintilde_31_zval = this->gaintilde_31_zval;
    auto __gaintilde_31_value = this->gaintilde_31_value;
    number mult = (__gaintilde_31_value <= 0 ? 0. : __gaintilde_31_zval * rnbo_exp(__gaintilde_31_value * __gaintilde_31_loginc));
    auto iv = this->mstosamps(__gaintilde_31_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_31_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_26_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_26_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_26_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_27_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_27_interp = this->gaintilde_27_interp;
    auto __gaintilde_27_loginc = this->gaintilde_27_loginc;
    auto __gaintilde_27_zval = this->gaintilde_27_zval;
    auto __gaintilde_27_value = this->gaintilde_27_value;
    number mult = (__gaintilde_27_value <= 0 ? 0. : __gaintilde_27_zval * rnbo_exp(__gaintilde_27_value * __gaintilde_27_loginc));
    auto iv = this->mstosamps(__gaintilde_27_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_27_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_22_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_22_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_22_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_23_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_23_interp = this->gaintilde_23_interp;
    auto __gaintilde_23_loginc = this->gaintilde_23_loginc;
    auto __gaintilde_23_zval = this->gaintilde_23_zval;
    auto __gaintilde_23_value = this->gaintilde_23_value;
    number mult = (__gaintilde_23_value <= 0 ? 0. : __gaintilde_23_zval * rnbo_exp(__gaintilde_23_value * __gaintilde_23_loginc));
    auto iv = this->mstosamps(__gaintilde_23_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_23_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_18_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_18_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_18_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_19_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_19_interp = this->gaintilde_19_interp;
    auto __gaintilde_19_loginc = this->gaintilde_19_loginc;
    auto __gaintilde_19_zval = this->gaintilde_19_zval;
    auto __gaintilde_19_value = this->gaintilde_19_value;
    number mult = (__gaintilde_19_value <= 0 ? 0. : __gaintilde_19_zval * rnbo_exp(__gaintilde_19_value * __gaintilde_19_loginc));
    auto iv = this->mstosamps(__gaintilde_19_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_19_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_14_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_14_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_14_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_15_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_15_interp = this->gaintilde_15_interp;
    auto __gaintilde_15_loginc = this->gaintilde_15_loginc;
    auto __gaintilde_15_zval = this->gaintilde_15_zval;
    auto __gaintilde_15_value = this->gaintilde_15_value;
    number mult = (__gaintilde_15_value <= 0 ? 0. : __gaintilde_15_zval * rnbo_exp(__gaintilde_15_value * __gaintilde_15_loginc));
    auto iv = this->mstosamps(__gaintilde_15_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_15_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_10_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_10_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_10_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_11_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_11_interp = this->gaintilde_11_interp;
    auto __gaintilde_11_loginc = this->gaintilde_11_loginc;
    auto __gaintilde_11_zval = this->gaintilde_11_zval;
    auto __gaintilde_11_value = this->gaintilde_11_value;
    number mult = (__gaintilde_11_value <= 0 ? 0. : __gaintilde_11_zval * rnbo_exp(__gaintilde_11_value * __gaintilde_11_loginc));
    auto iv = this->mstosamps(__gaintilde_11_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_11_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_07_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_07_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_07_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_08_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_08_interp = this->gaintilde_08_interp;
    auto __gaintilde_08_loginc = this->gaintilde_08_loginc;
    auto __gaintilde_08_zval = this->gaintilde_08_zval;
    auto __gaintilde_08_value = this->gaintilde_08_value;
    number mult = (__gaintilde_08_value <= 0 ? 0. : __gaintilde_08_zval * rnbo_exp(__gaintilde_08_value * __gaintilde_08_loginc));
    auto iv = this->mstosamps(__gaintilde_08_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_08_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_03_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_03_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_03_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_04_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_04_interp = this->gaintilde_04_interp;
    auto __gaintilde_04_loginc = this->gaintilde_04_loginc;
    auto __gaintilde_04_zval = this->gaintilde_04_zval;
    auto __gaintilde_04_value = this->gaintilde_04_value;
    number mult = (__gaintilde_04_value <= 0 ? 0. : __gaintilde_04_zval * rnbo_exp(__gaintilde_04_value * __gaintilde_04_loginc));
    auto iv = this->mstosamps(__gaintilde_04_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_04_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_39_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_39_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_39_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_40_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_40_interp = this->gaintilde_40_interp;
    auto __gaintilde_40_loginc = this->gaintilde_40_loginc;
    auto __gaintilde_40_zval = this->gaintilde_40_zval;
    auto __gaintilde_40_value = this->gaintilde_40_value;
    number mult = (__gaintilde_40_value <= 0 ? 0. : __gaintilde_40_zval * rnbo_exp(__gaintilde_40_value * __gaintilde_40_loginc));
    auto iv = this->mstosamps(__gaintilde_40_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_40_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_36_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_36_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_36_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_37_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_37_interp = this->gaintilde_37_interp;
    auto __gaintilde_37_loginc = this->gaintilde_37_loginc;
    auto __gaintilde_37_zval = this->gaintilde_37_zval;
    auto __gaintilde_37_value = this->gaintilde_37_value;
    number mult = (__gaintilde_37_value <= 0 ? 0. : __gaintilde_37_zval * rnbo_exp(__gaintilde_37_value * __gaintilde_37_loginc));
    auto iv = this->mstosamps(__gaintilde_37_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_37_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_32_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_32_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_32_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_33_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_33_interp = this->gaintilde_33_interp;
    auto __gaintilde_33_loginc = this->gaintilde_33_loginc;
    auto __gaintilde_33_zval = this->gaintilde_33_zval;
    auto __gaintilde_33_value = this->gaintilde_33_value;
    number mult = (__gaintilde_33_value <= 0 ? 0. : __gaintilde_33_zval * rnbo_exp(__gaintilde_33_value * __gaintilde_33_loginc));
    auto iv = this->mstosamps(__gaintilde_33_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_33_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_27_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_27_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_27_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_28_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_28_interp = this->gaintilde_28_interp;
    auto __gaintilde_28_loginc = this->gaintilde_28_loginc;
    auto __gaintilde_28_zval = this->gaintilde_28_zval;
    auto __gaintilde_28_value = this->gaintilde_28_value;
    number mult = (__gaintilde_28_value <= 0 ? 0. : __gaintilde_28_zval * rnbo_exp(__gaintilde_28_value * __gaintilde_28_loginc));
    auto iv = this->mstosamps(__gaintilde_28_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_28_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_23_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_23_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_23_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_24_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_24_interp = this->gaintilde_24_interp;
    auto __gaintilde_24_loginc = this->gaintilde_24_loginc;
    auto __gaintilde_24_zval = this->gaintilde_24_zval;
    auto __gaintilde_24_value = this->gaintilde_24_value;
    number mult = (__gaintilde_24_value <= 0 ? 0. : __gaintilde_24_zval * rnbo_exp(__gaintilde_24_value * __gaintilde_24_loginc));
    auto iv = this->mstosamps(__gaintilde_24_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_24_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_04_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_04_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_04_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_05_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_05_interp = this->gaintilde_05_interp;
    auto __gaintilde_05_loginc = this->gaintilde_05_loginc;
    auto __gaintilde_05_zval = this->gaintilde_05_zval;
    auto __gaintilde_05_value = this->gaintilde_05_value;
    number mult = (__gaintilde_05_value <= 0 ? 0. : __gaintilde_05_zval * rnbo_exp(__gaintilde_05_value * __gaintilde_05_loginc));
    auto iv = this->mstosamps(__gaintilde_05_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_05_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_19_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_19_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_19_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_20_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_20_interp = this->gaintilde_20_interp;
    auto __gaintilde_20_loginc = this->gaintilde_20_loginc;
    auto __gaintilde_20_zval = this->gaintilde_20_zval;
    auto __gaintilde_20_value = this->gaintilde_20_value;
    number mult = (__gaintilde_20_value <= 0 ? 0. : __gaintilde_20_zval * rnbo_exp(__gaintilde_20_value * __gaintilde_20_loginc));
    auto iv = this->mstosamps(__gaintilde_20_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_20_ramp_next(mult, iv, iv);
    }
}

void freqshift_tilde_15_perform(
    const Sample * x,
    number frequency,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        array<number, 2> realImag = this->freqshift_tilde_15_h_next(x[(Index)i]);
        number phasorValue = this->freqshift_tilde_15_p_next(frequency, -1);
        number complex1 = rnbo_cos((phasorValue + 0.25) * 6.28318530717958647692) * realImag[0];
        number complex2 = rnbo_cos(phasorValue * 6.28318530717958647692) * realImag[1];
        out1[(Index)i] = complex1 + complex2;
        out2[(Index)i] = complex1 - complex2;
    }
}

void gaintilde_16_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_16_interp = this->gaintilde_16_interp;
    auto __gaintilde_16_loginc = this->gaintilde_16_loginc;
    auto __gaintilde_16_zval = this->gaintilde_16_zval;
    auto __gaintilde_16_value = this->gaintilde_16_value;
    number mult = (__gaintilde_16_value <= 0 ? 0. : __gaintilde_16_zval * rnbo_exp(__gaintilde_16_value * __gaintilde_16_loginc));
    auto iv = this->mstosamps(__gaintilde_16_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_16_ramp_next(mult, iv, iv);
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    const SampleValue * in6,
    const SampleValue * in7,
    const SampleValue * in8,
    const SampleValue * in9,
    const SampleValue * in10,
    const SampleValue * in11,
    const SampleValue * in12,
    const SampleValue * in13,
    const SampleValue * in14,
    const SampleValue * in15,
    const SampleValue * in16,
    const SampleValue * in17,
    const SampleValue * in18,
    const SampleValue * in19,
    const SampleValue * in20,
    const SampleValue * in21,
    const SampleValue * in22,
    const SampleValue * in23,
    const SampleValue * in24,
    const SampleValue * in25,
    const SampleValue * in26,
    const SampleValue * in27,
    const SampleValue * in28,
    const SampleValue * in29,
    const SampleValue * in30,
    const SampleValue * in31,
    const SampleValue * in32,
    const SampleValue * in33,
    const SampleValue * in34,
    const SampleValue * in35,
    const SampleValue * in36,
    const SampleValue * in37,
    const SampleValue * in38,
    const SampleValue * in39,
    const SampleValue * in40,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i] + in4[(Index)i] + in5[(Index)i] + in6[(Index)i] + in7[(Index)i] + in8[(Index)i] + in9[(Index)i] + in10[(Index)i] + in11[(Index)i] + in12[(Index)i] + in13[(Index)i] + in14[(Index)i] + in15[(Index)i] + in16[(Index)i] + in17[(Index)i] + in18[(Index)i] + in19[(Index)i] + in20[(Index)i] + in21[(Index)i] + in22[(Index)i] + in23[(Index)i] + in24[(Index)i] + in25[(Index)i] + in26[(Index)i] + in27[(Index)i] + in28[(Index)i] + in29[(Index)i] + in30[(Index)i] + in31[(Index)i] + in32[(Index)i] + in33[(Index)i] + in34[(Index)i] + in35[(Index)i] + in36[(Index)i] + in37[(Index)i] + in38[(Index)i] + in39[(Index)i] + in40[(Index)i];
    }
}

void limi_01_perform(const SampleValue * input1, SampleValue * output1, Index n) {
    RNBO_UNUSED(output1);
    RNBO_UNUSED(input1);
    auto __limi_01_lookaheadInv = this->limi_01_lookaheadInv;
    auto __limi_01_threshold = this->limi_01_threshold;
    auto __limi_01_lookahead = this->limi_01_lookahead;
    auto __limi_01_recover = this->limi_01_recover;
    auto __limi_01_last = this->limi_01_last;
    auto __limi_01_postamp = this->limi_01_postamp;
    auto __limi_01_lookaheadIndex = this->limi_01_lookaheadIndex;
    auto __limi_01_preamp = this->limi_01_preamp;
    auto __limi_01_dcblock = this->limi_01_dcblock;
    auto __limi_01_bypass = this->limi_01_bypass;
    ConstSampleArray<1> input = {input1};
    SampleArray<1> output = {output1};

    if ((bool)(__limi_01_bypass)) {
        for (Index i = 0; i < n; i++) {
            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = input[(Index)j][(Index)i];
            }
        }
    } else {
        number v;

        for (Index i = 0; i < n; i++) {
            number hotSample = 0;

            for (Index j = 0; j < 1; j++) {
                auto smps = input[(Index)j];
                v = ((bool)(__limi_01_dcblock) ? this->limi_01_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                v *= __limi_01_preamp;
                this->limi_01_lookaheadBuffers[(Index)j][__limi_01_lookaheadIndex] = v * __limi_01_postamp;
                v = rnbo_fabs(v);

                if (v > hotSample)
                    hotSample = v;
            }

            {
                if (__limi_01_last > 0.01)
                    v = __limi_01_last + __limi_01_recover * __limi_01_last;
                else
                    v = __limi_01_last + __limi_01_recover;
            }

            if (v > 1)
                v = 1;

            this->limi_01_gainBuffer[__limi_01_lookaheadIndex] = v;
            int lookaheadPlayback = (int)(__limi_01_lookaheadIndex - (int)(__limi_01_lookahead));

            if (lookaheadPlayback < 0)
                lookaheadPlayback += (int)(__limi_01_lookahead);

            if (hotSample * v > __limi_01_threshold) {
                number newgain;
                number curgain = __limi_01_threshold / hotSample;
                number inc = __limi_01_threshold - curgain;
                number acc = 0.0;
                number flag = 0;

                for (Index j = 0; flag == 0 && j < (Index)(__limi_01_lookahead); j++) {
                    int k = (int)(__limi_01_lookaheadIndex - (int)(j));

                    if (k < 0)
                        k += (int)(__limi_01_lookahead);

                    {
                        newgain = curgain + inc * (acc * acc);
                    }

                    if (newgain < this->limi_01_gainBuffer[(Index)k])
                        this->limi_01_gainBuffer[(Index)k] = newgain;
                    else
                        flag = 1;

                    acc = acc + __limi_01_lookaheadInv;
                }
            }

            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = this->limi_01_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_01_gainBuffer[(Index)lookaheadPlayback];
            }

            __limi_01_last = this->limi_01_gainBuffer[__limi_01_lookaheadIndex];
            __limi_01_lookaheadIndex++;

            if (__limi_01_lookaheadIndex >= __limi_01_lookahead)
                __limi_01_lookaheadIndex = 0;
        }
    }

    this->limi_01_lookaheadIndex = __limi_01_lookaheadIndex;
    this->limi_01_last = __limi_01_last;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void limi_01_lookahead_setter(number v) {
    this->limi_01_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
    this->limi_01_lookaheadInv = (number)1 / this->limi_01_lookahead;
}

void limi_01_preamp_setter(number v) {
    this->limi_01_preamp = rnbo_pow(10., v * 0.05);
}

void limi_01_postamp_setter(number v) {
    this->limi_01_postamp = rnbo_pow(10., v * 0.05);
}

void limi_01_threshold_setter(number v) {
    this->limi_01_threshold = rnbo_pow(10., v * 0.05);
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

number limi_01_dc1_next(number x, number gain) {
    number y = x - this->limi_01_dc1_xm1 + this->limi_01_dc1_ym1 * gain;
    this->limi_01_dc1_xm1 = x;
    this->limi_01_dc1_ym1 = y;
    return y;
}

void limi_01_dc1_reset() {
    this->limi_01_dc1_xm1 = 0;
    this->limi_01_dc1_ym1 = 0;
}

void limi_01_dc1_dspsetup() {
    this->limi_01_dc1_reset();
}

number limi_01_dc_next(Index i, number x, number gain) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_next(x, gain);
        }
    }

    return 0;
}

void limi_01_dc_reset(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_reset();
        }
    }
}

void limi_01_dc_dspsetup(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_01_dc1_dspsetup();
        }
    }
}

void limi_01_reset() {
    this->limi_01_recover = (number)1000 / (this->limi_01_release * this->samplerate());

    {
        this->limi_01_recover *= 0.707;
    }
}

void limi_01_dspsetup(bool force) {
    if ((bool)(this->limi_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->limi_01_reset();
    this->limi_01_setupDone = true;
    this->limi_01_dc1_dspsetup();
}

number gaintilde_01_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_01_ramp_d_prev);
    this->gaintilde_01_ramp_d_prev = x;
    return temp;
}

void gaintilde_01_ramp_d_dspsetup() {
    this->gaintilde_01_ramp_d_reset();
}

void gaintilde_01_ramp_d_reset() {
    this->gaintilde_01_ramp_d_prev = 0;
}

number gaintilde_01_ramp_next(number x, number up, number down) {
    if (this->gaintilde_01_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_01_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_01_ramp_index = _up;
            this->gaintilde_01_ramp_increment = (x - this->gaintilde_01_ramp_prev) / _up;
        } else if (x < this->gaintilde_01_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_01_ramp_index = _down;
            this->gaintilde_01_ramp_increment = (x - this->gaintilde_01_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_01_ramp_index > 0) {
        this->gaintilde_01_ramp_prev += this->gaintilde_01_ramp_increment;
        this->gaintilde_01_ramp_index -= 1;
    } else {
        this->gaintilde_01_ramp_prev = x;
    }

    return this->gaintilde_01_ramp_prev;
}

void gaintilde_01_ramp_reset() {
    this->gaintilde_01_ramp_prev = 0;
    this->gaintilde_01_ramp_index = 0;
    this->gaintilde_01_ramp_increment = 0;
    this->gaintilde_01_ramp_d_reset();
}

void gaintilde_01_init() {
    this->gaintilde_01_loginc = rnbo_log(1.072);
    this->gaintilde_01_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_01_loginc));
}

void gaintilde_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_01_value;
}

void gaintilde_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_01_value_set(preset["value"]);
}

void gaintilde_01_dspsetup(bool force) {
    if ((bool)(this->gaintilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_01_setupDone = true;
    this->gaintilde_01_ramp_d_dspsetup();
}

number gaintilde_02_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_02_ramp_d_prev);
    this->gaintilde_02_ramp_d_prev = x;
    return temp;
}

void gaintilde_02_ramp_d_dspsetup() {
    this->gaintilde_02_ramp_d_reset();
}

void gaintilde_02_ramp_d_reset() {
    this->gaintilde_02_ramp_d_prev = 0;
}

number gaintilde_02_ramp_next(number x, number up, number down) {
    if (this->gaintilde_02_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_02_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_02_ramp_index = _up;
            this->gaintilde_02_ramp_increment = (x - this->gaintilde_02_ramp_prev) / _up;
        } else if (x < this->gaintilde_02_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_02_ramp_index = _down;
            this->gaintilde_02_ramp_increment = (x - this->gaintilde_02_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_02_ramp_index > 0) {
        this->gaintilde_02_ramp_prev += this->gaintilde_02_ramp_increment;
        this->gaintilde_02_ramp_index -= 1;
    } else {
        this->gaintilde_02_ramp_prev = x;
    }

    return this->gaintilde_02_ramp_prev;
}

void gaintilde_02_ramp_reset() {
    this->gaintilde_02_ramp_prev = 0;
    this->gaintilde_02_ramp_index = 0;
    this->gaintilde_02_ramp_increment = 0;
    this->gaintilde_02_ramp_d_reset();
}

void gaintilde_02_init() {
    this->gaintilde_02_loginc = rnbo_log(1.072);
    this->gaintilde_02_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_02_loginc));
}

void gaintilde_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_02_value;
}

void gaintilde_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_02_value_set(preset["value"]);
}

void gaintilde_02_dspsetup(bool force) {
    if ((bool)(this->gaintilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_02_setupDone = true;
    this->gaintilde_02_ramp_d_dspsetup();
}

number gaintilde_03_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_03_ramp_d_prev);
    this->gaintilde_03_ramp_d_prev = x;
    return temp;
}

void gaintilde_03_ramp_d_dspsetup() {
    this->gaintilde_03_ramp_d_reset();
}

void gaintilde_03_ramp_d_reset() {
    this->gaintilde_03_ramp_d_prev = 0;
}

number gaintilde_03_ramp_next(number x, number up, number down) {
    if (this->gaintilde_03_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_03_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_03_ramp_index = _up;
            this->gaintilde_03_ramp_increment = (x - this->gaintilde_03_ramp_prev) / _up;
        } else if (x < this->gaintilde_03_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_03_ramp_index = _down;
            this->gaintilde_03_ramp_increment = (x - this->gaintilde_03_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_03_ramp_index > 0) {
        this->gaintilde_03_ramp_prev += this->gaintilde_03_ramp_increment;
        this->gaintilde_03_ramp_index -= 1;
    } else {
        this->gaintilde_03_ramp_prev = x;
    }

    return this->gaintilde_03_ramp_prev;
}

void gaintilde_03_ramp_reset() {
    this->gaintilde_03_ramp_prev = 0;
    this->gaintilde_03_ramp_index = 0;
    this->gaintilde_03_ramp_increment = 0;
    this->gaintilde_03_ramp_d_reset();
}

void gaintilde_03_init() {
    this->gaintilde_03_loginc = rnbo_log(1.072);
    this->gaintilde_03_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_03_loginc));
}

void gaintilde_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_03_value;
}

void gaintilde_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_03_value_set(preset["value"]);
}

void gaintilde_03_dspsetup(bool force) {
    if ((bool)(this->gaintilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_03_setupDone = true;
    this->gaintilde_03_ramp_d_dspsetup();
}

number gaintilde_04_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_04_ramp_d_prev);
    this->gaintilde_04_ramp_d_prev = x;
    return temp;
}

void gaintilde_04_ramp_d_dspsetup() {
    this->gaintilde_04_ramp_d_reset();
}

void gaintilde_04_ramp_d_reset() {
    this->gaintilde_04_ramp_d_prev = 0;
}

number gaintilde_04_ramp_next(number x, number up, number down) {
    if (this->gaintilde_04_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_04_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_04_ramp_index = _up;
            this->gaintilde_04_ramp_increment = (x - this->gaintilde_04_ramp_prev) / _up;
        } else if (x < this->gaintilde_04_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_04_ramp_index = _down;
            this->gaintilde_04_ramp_increment = (x - this->gaintilde_04_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_04_ramp_index > 0) {
        this->gaintilde_04_ramp_prev += this->gaintilde_04_ramp_increment;
        this->gaintilde_04_ramp_index -= 1;
    } else {
        this->gaintilde_04_ramp_prev = x;
    }

    return this->gaintilde_04_ramp_prev;
}

void gaintilde_04_ramp_reset() {
    this->gaintilde_04_ramp_prev = 0;
    this->gaintilde_04_ramp_index = 0;
    this->gaintilde_04_ramp_increment = 0;
    this->gaintilde_04_ramp_d_reset();
}

void gaintilde_04_init() {
    this->gaintilde_04_loginc = rnbo_log(1.072);
    this->gaintilde_04_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_04_loginc));
}

void gaintilde_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_04_value;
}

void gaintilde_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_04_value_set(preset["value"]);
}

void gaintilde_04_dspsetup(bool force) {
    if ((bool)(this->gaintilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_04_setupDone = true;
    this->gaintilde_04_ramp_d_dspsetup();
}

number freqshift_tilde_01_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad1_x1 * a1 + this->freqshift_tilde_01_h_biquad1_x2 * 1 - (this->freqshift_tilde_01_h_biquad1_y1 * b1 + this->freqshift_tilde_01_h_biquad1_y2 * b2);
    this->freqshift_tilde_01_h_biquad1_x2 = this->freqshift_tilde_01_h_biquad1_x1;
    this->freqshift_tilde_01_h_biquad1_x1 = x;
    this->freqshift_tilde_01_h_biquad1_y2 = this->freqshift_tilde_01_h_biquad1_y1;
    this->freqshift_tilde_01_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad1_clear() {
    this->freqshift_tilde_01_h_biquad1_reset();
}

void freqshift_tilde_01_h_biquad1_reset() {
    this->freqshift_tilde_01_h_biquad1_x1 = 0;
    this->freqshift_tilde_01_h_biquad1_x2 = 0;
    this->freqshift_tilde_01_h_biquad1_y1 = 0;
    this->freqshift_tilde_01_h_biquad1_y2 = 0;
}

void freqshift_tilde_01_h_biquad1_dspsetup() {
    this->freqshift_tilde_01_h_biquad1_reset();
}

number freqshift_tilde_01_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad2_x1 * a1 + this->freqshift_tilde_01_h_biquad2_x2 * 1 - (this->freqshift_tilde_01_h_biquad2_y1 * b1 + this->freqshift_tilde_01_h_biquad2_y2 * b2);
    this->freqshift_tilde_01_h_biquad2_x2 = this->freqshift_tilde_01_h_biquad2_x1;
    this->freqshift_tilde_01_h_biquad2_x1 = x;
    this->freqshift_tilde_01_h_biquad2_y2 = this->freqshift_tilde_01_h_biquad2_y1;
    this->freqshift_tilde_01_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad2_clear() {
    this->freqshift_tilde_01_h_biquad2_reset();
}

void freqshift_tilde_01_h_biquad2_reset() {
    this->freqshift_tilde_01_h_biquad2_x1 = 0;
    this->freqshift_tilde_01_h_biquad2_x2 = 0;
    this->freqshift_tilde_01_h_biquad2_y1 = 0;
    this->freqshift_tilde_01_h_biquad2_y2 = 0;
}

void freqshift_tilde_01_h_biquad2_dspsetup() {
    this->freqshift_tilde_01_h_biquad2_reset();
}

number freqshift_tilde_01_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad3_x1 * a1 + this->freqshift_tilde_01_h_biquad3_x2 * 1 - (this->freqshift_tilde_01_h_biquad3_y1 * b1 + this->freqshift_tilde_01_h_biquad3_y2 * b2);
    this->freqshift_tilde_01_h_biquad3_x2 = this->freqshift_tilde_01_h_biquad3_x1;
    this->freqshift_tilde_01_h_biquad3_x1 = x;
    this->freqshift_tilde_01_h_biquad3_y2 = this->freqshift_tilde_01_h_biquad3_y1;
    this->freqshift_tilde_01_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad3_clear() {
    this->freqshift_tilde_01_h_biquad3_reset();
}

void freqshift_tilde_01_h_biquad3_reset() {
    this->freqshift_tilde_01_h_biquad3_x1 = 0;
    this->freqshift_tilde_01_h_biquad3_x2 = 0;
    this->freqshift_tilde_01_h_biquad3_y1 = 0;
    this->freqshift_tilde_01_h_biquad3_y2 = 0;
}

void freqshift_tilde_01_h_biquad3_dspsetup() {
    this->freqshift_tilde_01_h_biquad3_reset();
}

number freqshift_tilde_01_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad4_x1 * a1 + this->freqshift_tilde_01_h_biquad4_x2 * 1 - (this->freqshift_tilde_01_h_biquad4_y1 * b1 + this->freqshift_tilde_01_h_biquad4_y2 * b2);
    this->freqshift_tilde_01_h_biquad4_x2 = this->freqshift_tilde_01_h_biquad4_x1;
    this->freqshift_tilde_01_h_biquad4_x1 = x;
    this->freqshift_tilde_01_h_biquad4_y2 = this->freqshift_tilde_01_h_biquad4_y1;
    this->freqshift_tilde_01_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad4_clear() {
    this->freqshift_tilde_01_h_biquad4_reset();
}

void freqshift_tilde_01_h_biquad4_reset() {
    this->freqshift_tilde_01_h_biquad4_x1 = 0;
    this->freqshift_tilde_01_h_biquad4_x2 = 0;
    this->freqshift_tilde_01_h_biquad4_y1 = 0;
    this->freqshift_tilde_01_h_biquad4_y2 = 0;
}

void freqshift_tilde_01_h_biquad4_dspsetup() {
    this->freqshift_tilde_01_h_biquad4_reset();
}

number freqshift_tilde_01_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad5_x1 * a1 + this->freqshift_tilde_01_h_biquad5_x2 * 1 - (this->freqshift_tilde_01_h_biquad5_y1 * b1 + this->freqshift_tilde_01_h_biquad5_y2 * b2);
    this->freqshift_tilde_01_h_biquad5_x2 = this->freqshift_tilde_01_h_biquad5_x1;
    this->freqshift_tilde_01_h_biquad5_x1 = x;
    this->freqshift_tilde_01_h_biquad5_y2 = this->freqshift_tilde_01_h_biquad5_y1;
    this->freqshift_tilde_01_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad5_clear() {
    this->freqshift_tilde_01_h_biquad5_reset();
}

void freqshift_tilde_01_h_biquad5_reset() {
    this->freqshift_tilde_01_h_biquad5_x1 = 0;
    this->freqshift_tilde_01_h_biquad5_x2 = 0;
    this->freqshift_tilde_01_h_biquad5_y1 = 0;
    this->freqshift_tilde_01_h_biquad5_y2 = 0;
}

void freqshift_tilde_01_h_biquad5_dspsetup() {
    this->freqshift_tilde_01_h_biquad5_reset();
}

number freqshift_tilde_01_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_01_h_biquad6_x1 * a1 + this->freqshift_tilde_01_h_biquad6_x2 * 1 - (this->freqshift_tilde_01_h_biquad6_y1 * b1 + this->freqshift_tilde_01_h_biquad6_y2 * b2);
    this->freqshift_tilde_01_h_biquad6_x2 = this->freqshift_tilde_01_h_biquad6_x1;
    this->freqshift_tilde_01_h_biquad6_x1 = x;
    this->freqshift_tilde_01_h_biquad6_y2 = this->freqshift_tilde_01_h_biquad6_y1;
    this->freqshift_tilde_01_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_01_h_biquad6_clear() {
    this->freqshift_tilde_01_h_biquad6_reset();
}

void freqshift_tilde_01_h_biquad6_reset() {
    this->freqshift_tilde_01_h_biquad6_x1 = 0;
    this->freqshift_tilde_01_h_biquad6_x2 = 0;
    this->freqshift_tilde_01_h_biquad6_y1 = 0;
    this->freqshift_tilde_01_h_biquad6_y2 = 0;
}

void freqshift_tilde_01_h_biquad6_dspsetup() {
    this->freqshift_tilde_01_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_01_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_01_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_01_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_01_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_01_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_01_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_01_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_01_h_clear() {
    this->freqshift_tilde_01_h_reset();
}

void freqshift_tilde_01_h_reset() {
    this->freqshift_tilde_01_h_biquad1_reset();
    this->freqshift_tilde_01_h_biquad2_reset();
    this->freqshift_tilde_01_h_biquad3_reset();
    this->freqshift_tilde_01_h_biquad4_reset();
    this->freqshift_tilde_01_h_biquad5_reset();
    this->freqshift_tilde_01_h_biquad6_reset();
}

void freqshift_tilde_01_h_dspsetup() {
    this->freqshift_tilde_01_h_reset();
}

number freqshift_tilde_01_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_01_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_01_p_conv;

    if (this->freqshift_tilde_01_p_currentPhase < 0.)
        this->freqshift_tilde_01_p_currentPhase = 1. + this->freqshift_tilde_01_p_currentPhase;

    if (this->freqshift_tilde_01_p_currentPhase > 1.)
        this->freqshift_tilde_01_p_currentPhase = this->freqshift_tilde_01_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_01_p_currentPhase;
    this->freqshift_tilde_01_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_01_p_reset() {
    this->freqshift_tilde_01_p_currentPhase = 0;
}

void freqshift_tilde_01_p_dspsetup() {
    this->freqshift_tilde_01_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_01_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_01_setupDone = true;
    this->freqshift_tilde_01_h_biquad1_dspsetup();
    this->freqshift_tilde_01_h_biquad2_dspsetup();
    this->freqshift_tilde_01_h_biquad3_dspsetup();
    this->freqshift_tilde_01_h_biquad4_dspsetup();
    this->freqshift_tilde_01_h_biquad5_dspsetup();
    this->freqshift_tilde_01_h_biquad6_dspsetup();
    this->freqshift_tilde_01_h_dspsetup();
    this->freqshift_tilde_01_p_dspsetup();
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

number freqshift_tilde_02_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad1_x1 * a1 + this->freqshift_tilde_02_h_biquad1_x2 * 1 - (this->freqshift_tilde_02_h_biquad1_y1 * b1 + this->freqshift_tilde_02_h_biquad1_y2 * b2);
    this->freqshift_tilde_02_h_biquad1_x2 = this->freqshift_tilde_02_h_biquad1_x1;
    this->freqshift_tilde_02_h_biquad1_x1 = x;
    this->freqshift_tilde_02_h_biquad1_y2 = this->freqshift_tilde_02_h_biquad1_y1;
    this->freqshift_tilde_02_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad1_clear() {
    this->freqshift_tilde_02_h_biquad1_reset();
}

void freqshift_tilde_02_h_biquad1_reset() {
    this->freqshift_tilde_02_h_biquad1_x1 = 0;
    this->freqshift_tilde_02_h_biquad1_x2 = 0;
    this->freqshift_tilde_02_h_biquad1_y1 = 0;
    this->freqshift_tilde_02_h_biquad1_y2 = 0;
}

void freqshift_tilde_02_h_biquad1_dspsetup() {
    this->freqshift_tilde_02_h_biquad1_reset();
}

number freqshift_tilde_02_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad2_x1 * a1 + this->freqshift_tilde_02_h_biquad2_x2 * 1 - (this->freqshift_tilde_02_h_biquad2_y1 * b1 + this->freqshift_tilde_02_h_biquad2_y2 * b2);
    this->freqshift_tilde_02_h_biquad2_x2 = this->freqshift_tilde_02_h_biquad2_x1;
    this->freqshift_tilde_02_h_biquad2_x1 = x;
    this->freqshift_tilde_02_h_biquad2_y2 = this->freqshift_tilde_02_h_biquad2_y1;
    this->freqshift_tilde_02_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad2_clear() {
    this->freqshift_tilde_02_h_biquad2_reset();
}

void freqshift_tilde_02_h_biquad2_reset() {
    this->freqshift_tilde_02_h_biquad2_x1 = 0;
    this->freqshift_tilde_02_h_biquad2_x2 = 0;
    this->freqshift_tilde_02_h_biquad2_y1 = 0;
    this->freqshift_tilde_02_h_biquad2_y2 = 0;
}

void freqshift_tilde_02_h_biquad2_dspsetup() {
    this->freqshift_tilde_02_h_biquad2_reset();
}

number freqshift_tilde_02_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad3_x1 * a1 + this->freqshift_tilde_02_h_biquad3_x2 * 1 - (this->freqshift_tilde_02_h_biquad3_y1 * b1 + this->freqshift_tilde_02_h_biquad3_y2 * b2);
    this->freqshift_tilde_02_h_biquad3_x2 = this->freqshift_tilde_02_h_biquad3_x1;
    this->freqshift_tilde_02_h_biquad3_x1 = x;
    this->freqshift_tilde_02_h_biquad3_y2 = this->freqshift_tilde_02_h_biquad3_y1;
    this->freqshift_tilde_02_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad3_clear() {
    this->freqshift_tilde_02_h_biquad3_reset();
}

void freqshift_tilde_02_h_biquad3_reset() {
    this->freqshift_tilde_02_h_biquad3_x1 = 0;
    this->freqshift_tilde_02_h_biquad3_x2 = 0;
    this->freqshift_tilde_02_h_biquad3_y1 = 0;
    this->freqshift_tilde_02_h_biquad3_y2 = 0;
}

void freqshift_tilde_02_h_biquad3_dspsetup() {
    this->freqshift_tilde_02_h_biquad3_reset();
}

number freqshift_tilde_02_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad4_x1 * a1 + this->freqshift_tilde_02_h_biquad4_x2 * 1 - (this->freqshift_tilde_02_h_biquad4_y1 * b1 + this->freqshift_tilde_02_h_biquad4_y2 * b2);
    this->freqshift_tilde_02_h_biquad4_x2 = this->freqshift_tilde_02_h_biquad4_x1;
    this->freqshift_tilde_02_h_biquad4_x1 = x;
    this->freqshift_tilde_02_h_biquad4_y2 = this->freqshift_tilde_02_h_biquad4_y1;
    this->freqshift_tilde_02_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad4_clear() {
    this->freqshift_tilde_02_h_biquad4_reset();
}

void freqshift_tilde_02_h_biquad4_reset() {
    this->freqshift_tilde_02_h_biquad4_x1 = 0;
    this->freqshift_tilde_02_h_biquad4_x2 = 0;
    this->freqshift_tilde_02_h_biquad4_y1 = 0;
    this->freqshift_tilde_02_h_biquad4_y2 = 0;
}

void freqshift_tilde_02_h_biquad4_dspsetup() {
    this->freqshift_tilde_02_h_biquad4_reset();
}

number freqshift_tilde_02_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad5_x1 * a1 + this->freqshift_tilde_02_h_biquad5_x2 * 1 - (this->freqshift_tilde_02_h_biquad5_y1 * b1 + this->freqshift_tilde_02_h_biquad5_y2 * b2);
    this->freqshift_tilde_02_h_biquad5_x2 = this->freqshift_tilde_02_h_biquad5_x1;
    this->freqshift_tilde_02_h_biquad5_x1 = x;
    this->freqshift_tilde_02_h_biquad5_y2 = this->freqshift_tilde_02_h_biquad5_y1;
    this->freqshift_tilde_02_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad5_clear() {
    this->freqshift_tilde_02_h_biquad5_reset();
}

void freqshift_tilde_02_h_biquad5_reset() {
    this->freqshift_tilde_02_h_biquad5_x1 = 0;
    this->freqshift_tilde_02_h_biquad5_x2 = 0;
    this->freqshift_tilde_02_h_biquad5_y1 = 0;
    this->freqshift_tilde_02_h_biquad5_y2 = 0;
}

void freqshift_tilde_02_h_biquad5_dspsetup() {
    this->freqshift_tilde_02_h_biquad5_reset();
}

number freqshift_tilde_02_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_02_h_biquad6_x1 * a1 + this->freqshift_tilde_02_h_biquad6_x2 * 1 - (this->freqshift_tilde_02_h_biquad6_y1 * b1 + this->freqshift_tilde_02_h_biquad6_y2 * b2);
    this->freqshift_tilde_02_h_biquad6_x2 = this->freqshift_tilde_02_h_biquad6_x1;
    this->freqshift_tilde_02_h_biquad6_x1 = x;
    this->freqshift_tilde_02_h_biquad6_y2 = this->freqshift_tilde_02_h_biquad6_y1;
    this->freqshift_tilde_02_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_02_h_biquad6_clear() {
    this->freqshift_tilde_02_h_biquad6_reset();
}

void freqshift_tilde_02_h_biquad6_reset() {
    this->freqshift_tilde_02_h_biquad6_x1 = 0;
    this->freqshift_tilde_02_h_biquad6_x2 = 0;
    this->freqshift_tilde_02_h_biquad6_y1 = 0;
    this->freqshift_tilde_02_h_biquad6_y2 = 0;
}

void freqshift_tilde_02_h_biquad6_dspsetup() {
    this->freqshift_tilde_02_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_02_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_02_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_02_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_02_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_02_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_02_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_02_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_02_h_clear() {
    this->freqshift_tilde_02_h_reset();
}

void freqshift_tilde_02_h_reset() {
    this->freqshift_tilde_02_h_biquad1_reset();
    this->freqshift_tilde_02_h_biquad2_reset();
    this->freqshift_tilde_02_h_biquad3_reset();
    this->freqshift_tilde_02_h_biquad4_reset();
    this->freqshift_tilde_02_h_biquad5_reset();
    this->freqshift_tilde_02_h_biquad6_reset();
}

void freqshift_tilde_02_h_dspsetup() {
    this->freqshift_tilde_02_h_reset();
}

number freqshift_tilde_02_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_02_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_02_p_conv;

    if (this->freqshift_tilde_02_p_currentPhase < 0.)
        this->freqshift_tilde_02_p_currentPhase = 1. + this->freqshift_tilde_02_p_currentPhase;

    if (this->freqshift_tilde_02_p_currentPhase > 1.)
        this->freqshift_tilde_02_p_currentPhase = this->freqshift_tilde_02_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_02_p_currentPhase;
    this->freqshift_tilde_02_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_02_p_reset() {
    this->freqshift_tilde_02_p_currentPhase = 0;
}

void freqshift_tilde_02_p_dspsetup() {
    this->freqshift_tilde_02_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_02_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_02_setupDone = true;
    this->freqshift_tilde_02_h_biquad1_dspsetup();
    this->freqshift_tilde_02_h_biquad2_dspsetup();
    this->freqshift_tilde_02_h_biquad3_dspsetup();
    this->freqshift_tilde_02_h_biquad4_dspsetup();
    this->freqshift_tilde_02_h_biquad5_dspsetup();
    this->freqshift_tilde_02_h_biquad6_dspsetup();
    this->freqshift_tilde_02_h_dspsetup();
    this->freqshift_tilde_02_p_dspsetup();
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

number freqshift_tilde_03_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad1_x1 * a1 + this->freqshift_tilde_03_h_biquad1_x2 * 1 - (this->freqshift_tilde_03_h_biquad1_y1 * b1 + this->freqshift_tilde_03_h_biquad1_y2 * b2);
    this->freqshift_tilde_03_h_biquad1_x2 = this->freqshift_tilde_03_h_biquad1_x1;
    this->freqshift_tilde_03_h_biquad1_x1 = x;
    this->freqshift_tilde_03_h_biquad1_y2 = this->freqshift_tilde_03_h_biquad1_y1;
    this->freqshift_tilde_03_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad1_clear() {
    this->freqshift_tilde_03_h_biquad1_reset();
}

void freqshift_tilde_03_h_biquad1_reset() {
    this->freqshift_tilde_03_h_biquad1_x1 = 0;
    this->freqshift_tilde_03_h_biquad1_x2 = 0;
    this->freqshift_tilde_03_h_biquad1_y1 = 0;
    this->freqshift_tilde_03_h_biquad1_y2 = 0;
}

void freqshift_tilde_03_h_biquad1_dspsetup() {
    this->freqshift_tilde_03_h_biquad1_reset();
}

number freqshift_tilde_03_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad2_x1 * a1 + this->freqshift_tilde_03_h_biquad2_x2 * 1 - (this->freqshift_tilde_03_h_biquad2_y1 * b1 + this->freqshift_tilde_03_h_biquad2_y2 * b2);
    this->freqshift_tilde_03_h_biquad2_x2 = this->freqshift_tilde_03_h_biquad2_x1;
    this->freqshift_tilde_03_h_biquad2_x1 = x;
    this->freqshift_tilde_03_h_biquad2_y2 = this->freqshift_tilde_03_h_biquad2_y1;
    this->freqshift_tilde_03_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad2_clear() {
    this->freqshift_tilde_03_h_biquad2_reset();
}

void freqshift_tilde_03_h_biquad2_reset() {
    this->freqshift_tilde_03_h_biquad2_x1 = 0;
    this->freqshift_tilde_03_h_biquad2_x2 = 0;
    this->freqshift_tilde_03_h_biquad2_y1 = 0;
    this->freqshift_tilde_03_h_biquad2_y2 = 0;
}

void freqshift_tilde_03_h_biquad2_dspsetup() {
    this->freqshift_tilde_03_h_biquad2_reset();
}

number freqshift_tilde_03_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad3_x1 * a1 + this->freqshift_tilde_03_h_biquad3_x2 * 1 - (this->freqshift_tilde_03_h_biquad3_y1 * b1 + this->freqshift_tilde_03_h_biquad3_y2 * b2);
    this->freqshift_tilde_03_h_biquad3_x2 = this->freqshift_tilde_03_h_biquad3_x1;
    this->freqshift_tilde_03_h_biquad3_x1 = x;
    this->freqshift_tilde_03_h_biquad3_y2 = this->freqshift_tilde_03_h_biquad3_y1;
    this->freqshift_tilde_03_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad3_clear() {
    this->freqshift_tilde_03_h_biquad3_reset();
}

void freqshift_tilde_03_h_biquad3_reset() {
    this->freqshift_tilde_03_h_biquad3_x1 = 0;
    this->freqshift_tilde_03_h_biquad3_x2 = 0;
    this->freqshift_tilde_03_h_biquad3_y1 = 0;
    this->freqshift_tilde_03_h_biquad3_y2 = 0;
}

void freqshift_tilde_03_h_biquad3_dspsetup() {
    this->freqshift_tilde_03_h_biquad3_reset();
}

number freqshift_tilde_03_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad4_x1 * a1 + this->freqshift_tilde_03_h_biquad4_x2 * 1 - (this->freqshift_tilde_03_h_biquad4_y1 * b1 + this->freqshift_tilde_03_h_biquad4_y2 * b2);
    this->freqshift_tilde_03_h_biquad4_x2 = this->freqshift_tilde_03_h_biquad4_x1;
    this->freqshift_tilde_03_h_biquad4_x1 = x;
    this->freqshift_tilde_03_h_biquad4_y2 = this->freqshift_tilde_03_h_biquad4_y1;
    this->freqshift_tilde_03_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad4_clear() {
    this->freqshift_tilde_03_h_biquad4_reset();
}

void freqshift_tilde_03_h_biquad4_reset() {
    this->freqshift_tilde_03_h_biquad4_x1 = 0;
    this->freqshift_tilde_03_h_biquad4_x2 = 0;
    this->freqshift_tilde_03_h_biquad4_y1 = 0;
    this->freqshift_tilde_03_h_biquad4_y2 = 0;
}

void freqshift_tilde_03_h_biquad4_dspsetup() {
    this->freqshift_tilde_03_h_biquad4_reset();
}

number freqshift_tilde_03_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad5_x1 * a1 + this->freqshift_tilde_03_h_biquad5_x2 * 1 - (this->freqshift_tilde_03_h_biquad5_y1 * b1 + this->freqshift_tilde_03_h_biquad5_y2 * b2);
    this->freqshift_tilde_03_h_biquad5_x2 = this->freqshift_tilde_03_h_biquad5_x1;
    this->freqshift_tilde_03_h_biquad5_x1 = x;
    this->freqshift_tilde_03_h_biquad5_y2 = this->freqshift_tilde_03_h_biquad5_y1;
    this->freqshift_tilde_03_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad5_clear() {
    this->freqshift_tilde_03_h_biquad5_reset();
}

void freqshift_tilde_03_h_biquad5_reset() {
    this->freqshift_tilde_03_h_biquad5_x1 = 0;
    this->freqshift_tilde_03_h_biquad5_x2 = 0;
    this->freqshift_tilde_03_h_biquad5_y1 = 0;
    this->freqshift_tilde_03_h_biquad5_y2 = 0;
}

void freqshift_tilde_03_h_biquad5_dspsetup() {
    this->freqshift_tilde_03_h_biquad5_reset();
}

number freqshift_tilde_03_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_03_h_biquad6_x1 * a1 + this->freqshift_tilde_03_h_biquad6_x2 * 1 - (this->freqshift_tilde_03_h_biquad6_y1 * b1 + this->freqshift_tilde_03_h_biquad6_y2 * b2);
    this->freqshift_tilde_03_h_biquad6_x2 = this->freqshift_tilde_03_h_biquad6_x1;
    this->freqshift_tilde_03_h_biquad6_x1 = x;
    this->freqshift_tilde_03_h_biquad6_y2 = this->freqshift_tilde_03_h_biquad6_y1;
    this->freqshift_tilde_03_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_03_h_biquad6_clear() {
    this->freqshift_tilde_03_h_biquad6_reset();
}

void freqshift_tilde_03_h_biquad6_reset() {
    this->freqshift_tilde_03_h_biquad6_x1 = 0;
    this->freqshift_tilde_03_h_biquad6_x2 = 0;
    this->freqshift_tilde_03_h_biquad6_y1 = 0;
    this->freqshift_tilde_03_h_biquad6_y2 = 0;
}

void freqshift_tilde_03_h_biquad6_dspsetup() {
    this->freqshift_tilde_03_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_03_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_03_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_03_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_03_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_03_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_03_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_03_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_03_h_clear() {
    this->freqshift_tilde_03_h_reset();
}

void freqshift_tilde_03_h_reset() {
    this->freqshift_tilde_03_h_biquad1_reset();
    this->freqshift_tilde_03_h_biquad2_reset();
    this->freqshift_tilde_03_h_biquad3_reset();
    this->freqshift_tilde_03_h_biquad4_reset();
    this->freqshift_tilde_03_h_biquad5_reset();
    this->freqshift_tilde_03_h_biquad6_reset();
}

void freqshift_tilde_03_h_dspsetup() {
    this->freqshift_tilde_03_h_reset();
}

number freqshift_tilde_03_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_03_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_03_p_conv;

    if (this->freqshift_tilde_03_p_currentPhase < 0.)
        this->freqshift_tilde_03_p_currentPhase = 1. + this->freqshift_tilde_03_p_currentPhase;

    if (this->freqshift_tilde_03_p_currentPhase > 1.)
        this->freqshift_tilde_03_p_currentPhase = this->freqshift_tilde_03_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_03_p_currentPhase;
    this->freqshift_tilde_03_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_03_p_reset() {
    this->freqshift_tilde_03_p_currentPhase = 0;
}

void freqshift_tilde_03_p_dspsetup() {
    this->freqshift_tilde_03_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_03_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_03_setupDone = true;
    this->freqshift_tilde_03_h_biquad1_dspsetup();
    this->freqshift_tilde_03_h_biquad2_dspsetup();
    this->freqshift_tilde_03_h_biquad3_dspsetup();
    this->freqshift_tilde_03_h_biquad4_dspsetup();
    this->freqshift_tilde_03_h_biquad5_dspsetup();
    this->freqshift_tilde_03_h_biquad6_dspsetup();
    this->freqshift_tilde_03_h_dspsetup();
    this->freqshift_tilde_03_p_dspsetup();
}

number freqshift_tilde_04_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad1_x1 * a1 + this->freqshift_tilde_04_h_biquad1_x2 * 1 - (this->freqshift_tilde_04_h_biquad1_y1 * b1 + this->freqshift_tilde_04_h_biquad1_y2 * b2);
    this->freqshift_tilde_04_h_biquad1_x2 = this->freqshift_tilde_04_h_biquad1_x1;
    this->freqshift_tilde_04_h_biquad1_x1 = x;
    this->freqshift_tilde_04_h_biquad1_y2 = this->freqshift_tilde_04_h_biquad1_y1;
    this->freqshift_tilde_04_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad1_clear() {
    this->freqshift_tilde_04_h_biquad1_reset();
}

void freqshift_tilde_04_h_biquad1_reset() {
    this->freqshift_tilde_04_h_biquad1_x1 = 0;
    this->freqshift_tilde_04_h_biquad1_x2 = 0;
    this->freqshift_tilde_04_h_biquad1_y1 = 0;
    this->freqshift_tilde_04_h_biquad1_y2 = 0;
}

void freqshift_tilde_04_h_biquad1_dspsetup() {
    this->freqshift_tilde_04_h_biquad1_reset();
}

number freqshift_tilde_04_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad2_x1 * a1 + this->freqshift_tilde_04_h_biquad2_x2 * 1 - (this->freqshift_tilde_04_h_biquad2_y1 * b1 + this->freqshift_tilde_04_h_biquad2_y2 * b2);
    this->freqshift_tilde_04_h_biquad2_x2 = this->freqshift_tilde_04_h_biquad2_x1;
    this->freqshift_tilde_04_h_biquad2_x1 = x;
    this->freqshift_tilde_04_h_biquad2_y2 = this->freqshift_tilde_04_h_biquad2_y1;
    this->freqshift_tilde_04_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad2_clear() {
    this->freqshift_tilde_04_h_biquad2_reset();
}

void freqshift_tilde_04_h_biquad2_reset() {
    this->freqshift_tilde_04_h_biquad2_x1 = 0;
    this->freqshift_tilde_04_h_biquad2_x2 = 0;
    this->freqshift_tilde_04_h_biquad2_y1 = 0;
    this->freqshift_tilde_04_h_biquad2_y2 = 0;
}

void freqshift_tilde_04_h_biquad2_dspsetup() {
    this->freqshift_tilde_04_h_biquad2_reset();
}

number freqshift_tilde_04_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad3_x1 * a1 + this->freqshift_tilde_04_h_biquad3_x2 * 1 - (this->freqshift_tilde_04_h_biquad3_y1 * b1 + this->freqshift_tilde_04_h_biquad3_y2 * b2);
    this->freqshift_tilde_04_h_biquad3_x2 = this->freqshift_tilde_04_h_biquad3_x1;
    this->freqshift_tilde_04_h_biquad3_x1 = x;
    this->freqshift_tilde_04_h_biquad3_y2 = this->freqshift_tilde_04_h_biquad3_y1;
    this->freqshift_tilde_04_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad3_clear() {
    this->freqshift_tilde_04_h_biquad3_reset();
}

void freqshift_tilde_04_h_biquad3_reset() {
    this->freqshift_tilde_04_h_biquad3_x1 = 0;
    this->freqshift_tilde_04_h_biquad3_x2 = 0;
    this->freqshift_tilde_04_h_biquad3_y1 = 0;
    this->freqshift_tilde_04_h_biquad3_y2 = 0;
}

void freqshift_tilde_04_h_biquad3_dspsetup() {
    this->freqshift_tilde_04_h_biquad3_reset();
}

number freqshift_tilde_04_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad4_x1 * a1 + this->freqshift_tilde_04_h_biquad4_x2 * 1 - (this->freqshift_tilde_04_h_biquad4_y1 * b1 + this->freqshift_tilde_04_h_biquad4_y2 * b2);
    this->freqshift_tilde_04_h_biquad4_x2 = this->freqshift_tilde_04_h_biquad4_x1;
    this->freqshift_tilde_04_h_biquad4_x1 = x;
    this->freqshift_tilde_04_h_biquad4_y2 = this->freqshift_tilde_04_h_biquad4_y1;
    this->freqshift_tilde_04_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad4_clear() {
    this->freqshift_tilde_04_h_biquad4_reset();
}

void freqshift_tilde_04_h_biquad4_reset() {
    this->freqshift_tilde_04_h_biquad4_x1 = 0;
    this->freqshift_tilde_04_h_biquad4_x2 = 0;
    this->freqshift_tilde_04_h_biquad4_y1 = 0;
    this->freqshift_tilde_04_h_biquad4_y2 = 0;
}

void freqshift_tilde_04_h_biquad4_dspsetup() {
    this->freqshift_tilde_04_h_biquad4_reset();
}

number freqshift_tilde_04_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad5_x1 * a1 + this->freqshift_tilde_04_h_biquad5_x2 * 1 - (this->freqshift_tilde_04_h_biquad5_y1 * b1 + this->freqshift_tilde_04_h_biquad5_y2 * b2);
    this->freqshift_tilde_04_h_biquad5_x2 = this->freqshift_tilde_04_h_biquad5_x1;
    this->freqshift_tilde_04_h_biquad5_x1 = x;
    this->freqshift_tilde_04_h_biquad5_y2 = this->freqshift_tilde_04_h_biquad5_y1;
    this->freqshift_tilde_04_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad5_clear() {
    this->freqshift_tilde_04_h_biquad5_reset();
}

void freqshift_tilde_04_h_biquad5_reset() {
    this->freqshift_tilde_04_h_biquad5_x1 = 0;
    this->freqshift_tilde_04_h_biquad5_x2 = 0;
    this->freqshift_tilde_04_h_biquad5_y1 = 0;
    this->freqshift_tilde_04_h_biquad5_y2 = 0;
}

void freqshift_tilde_04_h_biquad5_dspsetup() {
    this->freqshift_tilde_04_h_biquad5_reset();
}

number freqshift_tilde_04_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_04_h_biquad6_x1 * a1 + this->freqshift_tilde_04_h_biquad6_x2 * 1 - (this->freqshift_tilde_04_h_biquad6_y1 * b1 + this->freqshift_tilde_04_h_biquad6_y2 * b2);
    this->freqshift_tilde_04_h_biquad6_x2 = this->freqshift_tilde_04_h_biquad6_x1;
    this->freqshift_tilde_04_h_biquad6_x1 = x;
    this->freqshift_tilde_04_h_biquad6_y2 = this->freqshift_tilde_04_h_biquad6_y1;
    this->freqshift_tilde_04_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_04_h_biquad6_clear() {
    this->freqshift_tilde_04_h_biquad6_reset();
}

void freqshift_tilde_04_h_biquad6_reset() {
    this->freqshift_tilde_04_h_biquad6_x1 = 0;
    this->freqshift_tilde_04_h_biquad6_x2 = 0;
    this->freqshift_tilde_04_h_biquad6_y1 = 0;
    this->freqshift_tilde_04_h_biquad6_y2 = 0;
}

void freqshift_tilde_04_h_biquad6_dspsetup() {
    this->freqshift_tilde_04_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_04_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_04_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_04_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_04_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_04_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_04_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_04_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_04_h_clear() {
    this->freqshift_tilde_04_h_reset();
}

void freqshift_tilde_04_h_reset() {
    this->freqshift_tilde_04_h_biquad1_reset();
    this->freqshift_tilde_04_h_biquad2_reset();
    this->freqshift_tilde_04_h_biquad3_reset();
    this->freqshift_tilde_04_h_biquad4_reset();
    this->freqshift_tilde_04_h_biquad5_reset();
    this->freqshift_tilde_04_h_biquad6_reset();
}

void freqshift_tilde_04_h_dspsetup() {
    this->freqshift_tilde_04_h_reset();
}

number freqshift_tilde_04_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_04_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_04_p_conv;

    if (this->freqshift_tilde_04_p_currentPhase < 0.)
        this->freqshift_tilde_04_p_currentPhase = 1. + this->freqshift_tilde_04_p_currentPhase;

    if (this->freqshift_tilde_04_p_currentPhase > 1.)
        this->freqshift_tilde_04_p_currentPhase = this->freqshift_tilde_04_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_04_p_currentPhase;
    this->freqshift_tilde_04_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_04_p_reset() {
    this->freqshift_tilde_04_p_currentPhase = 0;
}

void freqshift_tilde_04_p_dspsetup() {
    this->freqshift_tilde_04_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_04_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_04_setupDone = true;
    this->freqshift_tilde_04_h_biquad1_dspsetup();
    this->freqshift_tilde_04_h_biquad2_dspsetup();
    this->freqshift_tilde_04_h_biquad3_dspsetup();
    this->freqshift_tilde_04_h_biquad4_dspsetup();
    this->freqshift_tilde_04_h_biquad5_dspsetup();
    this->freqshift_tilde_04_h_biquad6_dspsetup();
    this->freqshift_tilde_04_h_dspsetup();
    this->freqshift_tilde_04_p_dspsetup();
}

number gaintilde_05_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_05_ramp_d_prev);
    this->gaintilde_05_ramp_d_prev = x;
    return temp;
}

void gaintilde_05_ramp_d_dspsetup() {
    this->gaintilde_05_ramp_d_reset();
}

void gaintilde_05_ramp_d_reset() {
    this->gaintilde_05_ramp_d_prev = 0;
}

number gaintilde_05_ramp_next(number x, number up, number down) {
    if (this->gaintilde_05_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_05_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_05_ramp_index = _up;
            this->gaintilde_05_ramp_increment = (x - this->gaintilde_05_ramp_prev) / _up;
        } else if (x < this->gaintilde_05_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_05_ramp_index = _down;
            this->gaintilde_05_ramp_increment = (x - this->gaintilde_05_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_05_ramp_index > 0) {
        this->gaintilde_05_ramp_prev += this->gaintilde_05_ramp_increment;
        this->gaintilde_05_ramp_index -= 1;
    } else {
        this->gaintilde_05_ramp_prev = x;
    }

    return this->gaintilde_05_ramp_prev;
}

void gaintilde_05_ramp_reset() {
    this->gaintilde_05_ramp_prev = 0;
    this->gaintilde_05_ramp_index = 0;
    this->gaintilde_05_ramp_increment = 0;
    this->gaintilde_05_ramp_d_reset();
}

void gaintilde_05_init() {
    this->gaintilde_05_loginc = rnbo_log(1.072);
    this->gaintilde_05_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_05_loginc));
}

void gaintilde_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_05_value;
}

void gaintilde_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_05_value_set(preset["value"]);
}

void gaintilde_05_dspsetup(bool force) {
    if ((bool)(this->gaintilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_05_setupDone = true;
    this->gaintilde_05_ramp_d_dspsetup();
}

number gaintilde_06_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_06_ramp_d_prev);
    this->gaintilde_06_ramp_d_prev = x;
    return temp;
}

void gaintilde_06_ramp_d_dspsetup() {
    this->gaintilde_06_ramp_d_reset();
}

void gaintilde_06_ramp_d_reset() {
    this->gaintilde_06_ramp_d_prev = 0;
}

number gaintilde_06_ramp_next(number x, number up, number down) {
    if (this->gaintilde_06_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_06_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_06_ramp_index = _up;
            this->gaintilde_06_ramp_increment = (x - this->gaintilde_06_ramp_prev) / _up;
        } else if (x < this->gaintilde_06_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_06_ramp_index = _down;
            this->gaintilde_06_ramp_increment = (x - this->gaintilde_06_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_06_ramp_index > 0) {
        this->gaintilde_06_ramp_prev += this->gaintilde_06_ramp_increment;
        this->gaintilde_06_ramp_index -= 1;
    } else {
        this->gaintilde_06_ramp_prev = x;
    }

    return this->gaintilde_06_ramp_prev;
}

void gaintilde_06_ramp_reset() {
    this->gaintilde_06_ramp_prev = 0;
    this->gaintilde_06_ramp_index = 0;
    this->gaintilde_06_ramp_increment = 0;
    this->gaintilde_06_ramp_d_reset();
}

void gaintilde_06_init() {
    this->gaintilde_06_loginc = rnbo_log(1.072);
    this->gaintilde_06_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_06_loginc));
}

void gaintilde_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_06_value;
}

void gaintilde_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_06_value_set(preset["value"]);
}

void gaintilde_06_dspsetup(bool force) {
    if ((bool)(this->gaintilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_06_setupDone = true;
    this->gaintilde_06_ramp_d_dspsetup();
}

number gaintilde_07_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_07_ramp_d_prev);
    this->gaintilde_07_ramp_d_prev = x;
    return temp;
}

void gaintilde_07_ramp_d_dspsetup() {
    this->gaintilde_07_ramp_d_reset();
}

void gaintilde_07_ramp_d_reset() {
    this->gaintilde_07_ramp_d_prev = 0;
}

number gaintilde_07_ramp_next(number x, number up, number down) {
    if (this->gaintilde_07_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_07_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_07_ramp_index = _up;
            this->gaintilde_07_ramp_increment = (x - this->gaintilde_07_ramp_prev) / _up;
        } else if (x < this->gaintilde_07_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_07_ramp_index = _down;
            this->gaintilde_07_ramp_increment = (x - this->gaintilde_07_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_07_ramp_index > 0) {
        this->gaintilde_07_ramp_prev += this->gaintilde_07_ramp_increment;
        this->gaintilde_07_ramp_index -= 1;
    } else {
        this->gaintilde_07_ramp_prev = x;
    }

    return this->gaintilde_07_ramp_prev;
}

void gaintilde_07_ramp_reset() {
    this->gaintilde_07_ramp_prev = 0;
    this->gaintilde_07_ramp_index = 0;
    this->gaintilde_07_ramp_increment = 0;
    this->gaintilde_07_ramp_d_reset();
}

void gaintilde_07_init() {
    this->gaintilde_07_loginc = rnbo_log(1.072);
    this->gaintilde_07_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_07_loginc));
}

void gaintilde_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_07_value;
}

void gaintilde_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_07_value_set(preset["value"]);
}

void gaintilde_07_dspsetup(bool force) {
    if ((bool)(this->gaintilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_07_setupDone = true;
    this->gaintilde_07_ramp_d_dspsetup();
}

number gaintilde_08_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_08_ramp_d_prev);
    this->gaintilde_08_ramp_d_prev = x;
    return temp;
}

void gaintilde_08_ramp_d_dspsetup() {
    this->gaintilde_08_ramp_d_reset();
}

void gaintilde_08_ramp_d_reset() {
    this->gaintilde_08_ramp_d_prev = 0;
}

number gaintilde_08_ramp_next(number x, number up, number down) {
    if (this->gaintilde_08_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_08_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_08_ramp_index = _up;
            this->gaintilde_08_ramp_increment = (x - this->gaintilde_08_ramp_prev) / _up;
        } else if (x < this->gaintilde_08_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_08_ramp_index = _down;
            this->gaintilde_08_ramp_increment = (x - this->gaintilde_08_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_08_ramp_index > 0) {
        this->gaintilde_08_ramp_prev += this->gaintilde_08_ramp_increment;
        this->gaintilde_08_ramp_index -= 1;
    } else {
        this->gaintilde_08_ramp_prev = x;
    }

    return this->gaintilde_08_ramp_prev;
}

void gaintilde_08_ramp_reset() {
    this->gaintilde_08_ramp_prev = 0;
    this->gaintilde_08_ramp_index = 0;
    this->gaintilde_08_ramp_increment = 0;
    this->gaintilde_08_ramp_d_reset();
}

void gaintilde_08_init() {
    this->gaintilde_08_loginc = rnbo_log(1.072);
    this->gaintilde_08_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_08_loginc));
}

void gaintilde_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_08_value;
}

void gaintilde_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_08_value_set(preset["value"]);
}

void gaintilde_08_dspsetup(bool force) {
    if ((bool)(this->gaintilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_08_setupDone = true;
    this->gaintilde_08_ramp_d_dspsetup();
}

number freqshift_tilde_05_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad1_x1 * a1 + this->freqshift_tilde_05_h_biquad1_x2 * 1 - (this->freqshift_tilde_05_h_biquad1_y1 * b1 + this->freqshift_tilde_05_h_biquad1_y2 * b2);
    this->freqshift_tilde_05_h_biquad1_x2 = this->freqshift_tilde_05_h_biquad1_x1;
    this->freqshift_tilde_05_h_biquad1_x1 = x;
    this->freqshift_tilde_05_h_biquad1_y2 = this->freqshift_tilde_05_h_biquad1_y1;
    this->freqshift_tilde_05_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad1_clear() {
    this->freqshift_tilde_05_h_biquad1_reset();
}

void freqshift_tilde_05_h_biquad1_reset() {
    this->freqshift_tilde_05_h_biquad1_x1 = 0;
    this->freqshift_tilde_05_h_biquad1_x2 = 0;
    this->freqshift_tilde_05_h_biquad1_y1 = 0;
    this->freqshift_tilde_05_h_biquad1_y2 = 0;
}

void freqshift_tilde_05_h_biquad1_dspsetup() {
    this->freqshift_tilde_05_h_biquad1_reset();
}

number freqshift_tilde_05_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad2_x1 * a1 + this->freqshift_tilde_05_h_biquad2_x2 * 1 - (this->freqshift_tilde_05_h_biquad2_y1 * b1 + this->freqshift_tilde_05_h_biquad2_y2 * b2);
    this->freqshift_tilde_05_h_biquad2_x2 = this->freqshift_tilde_05_h_biquad2_x1;
    this->freqshift_tilde_05_h_biquad2_x1 = x;
    this->freqshift_tilde_05_h_biquad2_y2 = this->freqshift_tilde_05_h_biquad2_y1;
    this->freqshift_tilde_05_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad2_clear() {
    this->freqshift_tilde_05_h_biquad2_reset();
}

void freqshift_tilde_05_h_biquad2_reset() {
    this->freqshift_tilde_05_h_biquad2_x1 = 0;
    this->freqshift_tilde_05_h_biquad2_x2 = 0;
    this->freqshift_tilde_05_h_biquad2_y1 = 0;
    this->freqshift_tilde_05_h_biquad2_y2 = 0;
}

void freqshift_tilde_05_h_biquad2_dspsetup() {
    this->freqshift_tilde_05_h_biquad2_reset();
}

number freqshift_tilde_05_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad3_x1 * a1 + this->freqshift_tilde_05_h_biquad3_x2 * 1 - (this->freqshift_tilde_05_h_biquad3_y1 * b1 + this->freqshift_tilde_05_h_biquad3_y2 * b2);
    this->freqshift_tilde_05_h_biquad3_x2 = this->freqshift_tilde_05_h_biquad3_x1;
    this->freqshift_tilde_05_h_biquad3_x1 = x;
    this->freqshift_tilde_05_h_biquad3_y2 = this->freqshift_tilde_05_h_biquad3_y1;
    this->freqshift_tilde_05_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad3_clear() {
    this->freqshift_tilde_05_h_biquad3_reset();
}

void freqshift_tilde_05_h_biquad3_reset() {
    this->freqshift_tilde_05_h_biquad3_x1 = 0;
    this->freqshift_tilde_05_h_biquad3_x2 = 0;
    this->freqshift_tilde_05_h_biquad3_y1 = 0;
    this->freqshift_tilde_05_h_biquad3_y2 = 0;
}

void freqshift_tilde_05_h_biquad3_dspsetup() {
    this->freqshift_tilde_05_h_biquad3_reset();
}

number freqshift_tilde_05_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad4_x1 * a1 + this->freqshift_tilde_05_h_biquad4_x2 * 1 - (this->freqshift_tilde_05_h_biquad4_y1 * b1 + this->freqshift_tilde_05_h_biquad4_y2 * b2);
    this->freqshift_tilde_05_h_biquad4_x2 = this->freqshift_tilde_05_h_biquad4_x1;
    this->freqshift_tilde_05_h_biquad4_x1 = x;
    this->freqshift_tilde_05_h_biquad4_y2 = this->freqshift_tilde_05_h_biquad4_y1;
    this->freqshift_tilde_05_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad4_clear() {
    this->freqshift_tilde_05_h_biquad4_reset();
}

void freqshift_tilde_05_h_biquad4_reset() {
    this->freqshift_tilde_05_h_biquad4_x1 = 0;
    this->freqshift_tilde_05_h_biquad4_x2 = 0;
    this->freqshift_tilde_05_h_biquad4_y1 = 0;
    this->freqshift_tilde_05_h_biquad4_y2 = 0;
}

void freqshift_tilde_05_h_biquad4_dspsetup() {
    this->freqshift_tilde_05_h_biquad4_reset();
}

number freqshift_tilde_05_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad5_x1 * a1 + this->freqshift_tilde_05_h_biquad5_x2 * 1 - (this->freqshift_tilde_05_h_biquad5_y1 * b1 + this->freqshift_tilde_05_h_biquad5_y2 * b2);
    this->freqshift_tilde_05_h_biquad5_x2 = this->freqshift_tilde_05_h_biquad5_x1;
    this->freqshift_tilde_05_h_biquad5_x1 = x;
    this->freqshift_tilde_05_h_biquad5_y2 = this->freqshift_tilde_05_h_biquad5_y1;
    this->freqshift_tilde_05_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad5_clear() {
    this->freqshift_tilde_05_h_biquad5_reset();
}

void freqshift_tilde_05_h_biquad5_reset() {
    this->freqshift_tilde_05_h_biquad5_x1 = 0;
    this->freqshift_tilde_05_h_biquad5_x2 = 0;
    this->freqshift_tilde_05_h_biquad5_y1 = 0;
    this->freqshift_tilde_05_h_biquad5_y2 = 0;
}

void freqshift_tilde_05_h_biquad5_dspsetup() {
    this->freqshift_tilde_05_h_biquad5_reset();
}

number freqshift_tilde_05_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_05_h_biquad6_x1 * a1 + this->freqshift_tilde_05_h_biquad6_x2 * 1 - (this->freqshift_tilde_05_h_biquad6_y1 * b1 + this->freqshift_tilde_05_h_biquad6_y2 * b2);
    this->freqshift_tilde_05_h_biquad6_x2 = this->freqshift_tilde_05_h_biquad6_x1;
    this->freqshift_tilde_05_h_biquad6_x1 = x;
    this->freqshift_tilde_05_h_biquad6_y2 = this->freqshift_tilde_05_h_biquad6_y1;
    this->freqshift_tilde_05_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_05_h_biquad6_clear() {
    this->freqshift_tilde_05_h_biquad6_reset();
}

void freqshift_tilde_05_h_biquad6_reset() {
    this->freqshift_tilde_05_h_biquad6_x1 = 0;
    this->freqshift_tilde_05_h_biquad6_x2 = 0;
    this->freqshift_tilde_05_h_biquad6_y1 = 0;
    this->freqshift_tilde_05_h_biquad6_y2 = 0;
}

void freqshift_tilde_05_h_biquad6_dspsetup() {
    this->freqshift_tilde_05_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_05_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_05_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_05_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_05_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_05_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_05_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_05_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_05_h_clear() {
    this->freqshift_tilde_05_h_reset();
}

void freqshift_tilde_05_h_reset() {
    this->freqshift_tilde_05_h_biquad1_reset();
    this->freqshift_tilde_05_h_biquad2_reset();
    this->freqshift_tilde_05_h_biquad3_reset();
    this->freqshift_tilde_05_h_biquad4_reset();
    this->freqshift_tilde_05_h_biquad5_reset();
    this->freqshift_tilde_05_h_biquad6_reset();
}

void freqshift_tilde_05_h_dspsetup() {
    this->freqshift_tilde_05_h_reset();
}

number freqshift_tilde_05_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_05_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_05_p_conv;

    if (this->freqshift_tilde_05_p_currentPhase < 0.)
        this->freqshift_tilde_05_p_currentPhase = 1. + this->freqshift_tilde_05_p_currentPhase;

    if (this->freqshift_tilde_05_p_currentPhase > 1.)
        this->freqshift_tilde_05_p_currentPhase = this->freqshift_tilde_05_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_05_p_currentPhase;
    this->freqshift_tilde_05_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_05_p_reset() {
    this->freqshift_tilde_05_p_currentPhase = 0;
}

void freqshift_tilde_05_p_dspsetup() {
    this->freqshift_tilde_05_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_05_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_05_setupDone = true;
    this->freqshift_tilde_05_h_biquad1_dspsetup();
    this->freqshift_tilde_05_h_biquad2_dspsetup();
    this->freqshift_tilde_05_h_biquad3_dspsetup();
    this->freqshift_tilde_05_h_biquad4_dspsetup();
    this->freqshift_tilde_05_h_biquad5_dspsetup();
    this->freqshift_tilde_05_h_biquad6_dspsetup();
    this->freqshift_tilde_05_h_dspsetup();
    this->freqshift_tilde_05_p_dspsetup();
}

number freqshift_tilde_06_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad1_x1 * a1 + this->freqshift_tilde_06_h_biquad1_x2 * 1 - (this->freqshift_tilde_06_h_biquad1_y1 * b1 + this->freqshift_tilde_06_h_biquad1_y2 * b2);
    this->freqshift_tilde_06_h_biquad1_x2 = this->freqshift_tilde_06_h_biquad1_x1;
    this->freqshift_tilde_06_h_biquad1_x1 = x;
    this->freqshift_tilde_06_h_biquad1_y2 = this->freqshift_tilde_06_h_biquad1_y1;
    this->freqshift_tilde_06_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad1_clear() {
    this->freqshift_tilde_06_h_biquad1_reset();
}

void freqshift_tilde_06_h_biquad1_reset() {
    this->freqshift_tilde_06_h_biquad1_x1 = 0;
    this->freqshift_tilde_06_h_biquad1_x2 = 0;
    this->freqshift_tilde_06_h_biquad1_y1 = 0;
    this->freqshift_tilde_06_h_biquad1_y2 = 0;
}

void freqshift_tilde_06_h_biquad1_dspsetup() {
    this->freqshift_tilde_06_h_biquad1_reset();
}

number freqshift_tilde_06_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad2_x1 * a1 + this->freqshift_tilde_06_h_biquad2_x2 * 1 - (this->freqshift_tilde_06_h_biquad2_y1 * b1 + this->freqshift_tilde_06_h_biquad2_y2 * b2);
    this->freqshift_tilde_06_h_biquad2_x2 = this->freqshift_tilde_06_h_biquad2_x1;
    this->freqshift_tilde_06_h_biquad2_x1 = x;
    this->freqshift_tilde_06_h_biquad2_y2 = this->freqshift_tilde_06_h_biquad2_y1;
    this->freqshift_tilde_06_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad2_clear() {
    this->freqshift_tilde_06_h_biquad2_reset();
}

void freqshift_tilde_06_h_biquad2_reset() {
    this->freqshift_tilde_06_h_biquad2_x1 = 0;
    this->freqshift_tilde_06_h_biquad2_x2 = 0;
    this->freqshift_tilde_06_h_biquad2_y1 = 0;
    this->freqshift_tilde_06_h_biquad2_y2 = 0;
}

void freqshift_tilde_06_h_biquad2_dspsetup() {
    this->freqshift_tilde_06_h_biquad2_reset();
}

number freqshift_tilde_06_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad3_x1 * a1 + this->freqshift_tilde_06_h_biquad3_x2 * 1 - (this->freqshift_tilde_06_h_biquad3_y1 * b1 + this->freqshift_tilde_06_h_biquad3_y2 * b2);
    this->freqshift_tilde_06_h_biquad3_x2 = this->freqshift_tilde_06_h_biquad3_x1;
    this->freqshift_tilde_06_h_biquad3_x1 = x;
    this->freqshift_tilde_06_h_biquad3_y2 = this->freqshift_tilde_06_h_biquad3_y1;
    this->freqshift_tilde_06_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad3_clear() {
    this->freqshift_tilde_06_h_biquad3_reset();
}

void freqshift_tilde_06_h_biquad3_reset() {
    this->freqshift_tilde_06_h_biquad3_x1 = 0;
    this->freqshift_tilde_06_h_biquad3_x2 = 0;
    this->freqshift_tilde_06_h_biquad3_y1 = 0;
    this->freqshift_tilde_06_h_biquad3_y2 = 0;
}

void freqshift_tilde_06_h_biquad3_dspsetup() {
    this->freqshift_tilde_06_h_biquad3_reset();
}

number freqshift_tilde_06_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad4_x1 * a1 + this->freqshift_tilde_06_h_biquad4_x2 * 1 - (this->freqshift_tilde_06_h_biquad4_y1 * b1 + this->freqshift_tilde_06_h_biquad4_y2 * b2);
    this->freqshift_tilde_06_h_biquad4_x2 = this->freqshift_tilde_06_h_biquad4_x1;
    this->freqshift_tilde_06_h_biquad4_x1 = x;
    this->freqshift_tilde_06_h_biquad4_y2 = this->freqshift_tilde_06_h_biquad4_y1;
    this->freqshift_tilde_06_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad4_clear() {
    this->freqshift_tilde_06_h_biquad4_reset();
}

void freqshift_tilde_06_h_biquad4_reset() {
    this->freqshift_tilde_06_h_biquad4_x1 = 0;
    this->freqshift_tilde_06_h_biquad4_x2 = 0;
    this->freqshift_tilde_06_h_biquad4_y1 = 0;
    this->freqshift_tilde_06_h_biquad4_y2 = 0;
}

void freqshift_tilde_06_h_biquad4_dspsetup() {
    this->freqshift_tilde_06_h_biquad4_reset();
}

number freqshift_tilde_06_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad5_x1 * a1 + this->freqshift_tilde_06_h_biquad5_x2 * 1 - (this->freqshift_tilde_06_h_biquad5_y1 * b1 + this->freqshift_tilde_06_h_biquad5_y2 * b2);
    this->freqshift_tilde_06_h_biquad5_x2 = this->freqshift_tilde_06_h_biquad5_x1;
    this->freqshift_tilde_06_h_biquad5_x1 = x;
    this->freqshift_tilde_06_h_biquad5_y2 = this->freqshift_tilde_06_h_biquad5_y1;
    this->freqshift_tilde_06_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad5_clear() {
    this->freqshift_tilde_06_h_biquad5_reset();
}

void freqshift_tilde_06_h_biquad5_reset() {
    this->freqshift_tilde_06_h_biquad5_x1 = 0;
    this->freqshift_tilde_06_h_biquad5_x2 = 0;
    this->freqshift_tilde_06_h_biquad5_y1 = 0;
    this->freqshift_tilde_06_h_biquad5_y2 = 0;
}

void freqshift_tilde_06_h_biquad5_dspsetup() {
    this->freqshift_tilde_06_h_biquad5_reset();
}

number freqshift_tilde_06_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_06_h_biquad6_x1 * a1 + this->freqshift_tilde_06_h_biquad6_x2 * 1 - (this->freqshift_tilde_06_h_biquad6_y1 * b1 + this->freqshift_tilde_06_h_biquad6_y2 * b2);
    this->freqshift_tilde_06_h_biquad6_x2 = this->freqshift_tilde_06_h_biquad6_x1;
    this->freqshift_tilde_06_h_biquad6_x1 = x;
    this->freqshift_tilde_06_h_biquad6_y2 = this->freqshift_tilde_06_h_biquad6_y1;
    this->freqshift_tilde_06_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_06_h_biquad6_clear() {
    this->freqshift_tilde_06_h_biquad6_reset();
}

void freqshift_tilde_06_h_biquad6_reset() {
    this->freqshift_tilde_06_h_biquad6_x1 = 0;
    this->freqshift_tilde_06_h_biquad6_x2 = 0;
    this->freqshift_tilde_06_h_biquad6_y1 = 0;
    this->freqshift_tilde_06_h_biquad6_y2 = 0;
}

void freqshift_tilde_06_h_biquad6_dspsetup() {
    this->freqshift_tilde_06_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_06_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_06_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_06_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_06_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_06_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_06_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_06_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_06_h_clear() {
    this->freqshift_tilde_06_h_reset();
}

void freqshift_tilde_06_h_reset() {
    this->freqshift_tilde_06_h_biquad1_reset();
    this->freqshift_tilde_06_h_biquad2_reset();
    this->freqshift_tilde_06_h_biquad3_reset();
    this->freqshift_tilde_06_h_biquad4_reset();
    this->freqshift_tilde_06_h_biquad5_reset();
    this->freqshift_tilde_06_h_biquad6_reset();
}

void freqshift_tilde_06_h_dspsetup() {
    this->freqshift_tilde_06_h_reset();
}

number freqshift_tilde_06_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_06_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_06_p_conv;

    if (this->freqshift_tilde_06_p_currentPhase < 0.)
        this->freqshift_tilde_06_p_currentPhase = 1. + this->freqshift_tilde_06_p_currentPhase;

    if (this->freqshift_tilde_06_p_currentPhase > 1.)
        this->freqshift_tilde_06_p_currentPhase = this->freqshift_tilde_06_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_06_p_currentPhase;
    this->freqshift_tilde_06_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_06_p_reset() {
    this->freqshift_tilde_06_p_currentPhase = 0;
}

void freqshift_tilde_06_p_dspsetup() {
    this->freqshift_tilde_06_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_06_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_06_setupDone = true;
    this->freqshift_tilde_06_h_biquad1_dspsetup();
    this->freqshift_tilde_06_h_biquad2_dspsetup();
    this->freqshift_tilde_06_h_biquad3_dspsetup();
    this->freqshift_tilde_06_h_biquad4_dspsetup();
    this->freqshift_tilde_06_h_biquad5_dspsetup();
    this->freqshift_tilde_06_h_biquad6_dspsetup();
    this->freqshift_tilde_06_h_dspsetup();
    this->freqshift_tilde_06_p_dspsetup();
}

number freqshift_tilde_07_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad1_x1 * a1 + this->freqshift_tilde_07_h_biquad1_x2 * 1 - (this->freqshift_tilde_07_h_biquad1_y1 * b1 + this->freqshift_tilde_07_h_biquad1_y2 * b2);
    this->freqshift_tilde_07_h_biquad1_x2 = this->freqshift_tilde_07_h_biquad1_x1;
    this->freqshift_tilde_07_h_biquad1_x1 = x;
    this->freqshift_tilde_07_h_biquad1_y2 = this->freqshift_tilde_07_h_biquad1_y1;
    this->freqshift_tilde_07_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad1_clear() {
    this->freqshift_tilde_07_h_biquad1_reset();
}

void freqshift_tilde_07_h_biquad1_reset() {
    this->freqshift_tilde_07_h_biquad1_x1 = 0;
    this->freqshift_tilde_07_h_biquad1_x2 = 0;
    this->freqshift_tilde_07_h_biquad1_y1 = 0;
    this->freqshift_tilde_07_h_biquad1_y2 = 0;
}

void freqshift_tilde_07_h_biquad1_dspsetup() {
    this->freqshift_tilde_07_h_biquad1_reset();
}

number freqshift_tilde_07_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad2_x1 * a1 + this->freqshift_tilde_07_h_biquad2_x2 * 1 - (this->freqshift_tilde_07_h_biquad2_y1 * b1 + this->freqshift_tilde_07_h_biquad2_y2 * b2);
    this->freqshift_tilde_07_h_biquad2_x2 = this->freqshift_tilde_07_h_biquad2_x1;
    this->freqshift_tilde_07_h_biquad2_x1 = x;
    this->freqshift_tilde_07_h_biquad2_y2 = this->freqshift_tilde_07_h_biquad2_y1;
    this->freqshift_tilde_07_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad2_clear() {
    this->freqshift_tilde_07_h_biquad2_reset();
}

void freqshift_tilde_07_h_biquad2_reset() {
    this->freqshift_tilde_07_h_biquad2_x1 = 0;
    this->freqshift_tilde_07_h_biquad2_x2 = 0;
    this->freqshift_tilde_07_h_biquad2_y1 = 0;
    this->freqshift_tilde_07_h_biquad2_y2 = 0;
}

void freqshift_tilde_07_h_biquad2_dspsetup() {
    this->freqshift_tilde_07_h_biquad2_reset();
}

number freqshift_tilde_07_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad3_x1 * a1 + this->freqshift_tilde_07_h_biquad3_x2 * 1 - (this->freqshift_tilde_07_h_biquad3_y1 * b1 + this->freqshift_tilde_07_h_biquad3_y2 * b2);
    this->freqshift_tilde_07_h_biquad3_x2 = this->freqshift_tilde_07_h_biquad3_x1;
    this->freqshift_tilde_07_h_biquad3_x1 = x;
    this->freqshift_tilde_07_h_biquad3_y2 = this->freqshift_tilde_07_h_biquad3_y1;
    this->freqshift_tilde_07_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad3_clear() {
    this->freqshift_tilde_07_h_biquad3_reset();
}

void freqshift_tilde_07_h_biquad3_reset() {
    this->freqshift_tilde_07_h_biquad3_x1 = 0;
    this->freqshift_tilde_07_h_biquad3_x2 = 0;
    this->freqshift_tilde_07_h_biquad3_y1 = 0;
    this->freqshift_tilde_07_h_biquad3_y2 = 0;
}

void freqshift_tilde_07_h_biquad3_dspsetup() {
    this->freqshift_tilde_07_h_biquad3_reset();
}

number freqshift_tilde_07_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad4_x1 * a1 + this->freqshift_tilde_07_h_biquad4_x2 * 1 - (this->freqshift_tilde_07_h_biquad4_y1 * b1 + this->freqshift_tilde_07_h_biquad4_y2 * b2);
    this->freqshift_tilde_07_h_biquad4_x2 = this->freqshift_tilde_07_h_biquad4_x1;
    this->freqshift_tilde_07_h_biquad4_x1 = x;
    this->freqshift_tilde_07_h_biquad4_y2 = this->freqshift_tilde_07_h_biquad4_y1;
    this->freqshift_tilde_07_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad4_clear() {
    this->freqshift_tilde_07_h_biquad4_reset();
}

void freqshift_tilde_07_h_biquad4_reset() {
    this->freqshift_tilde_07_h_biquad4_x1 = 0;
    this->freqshift_tilde_07_h_biquad4_x2 = 0;
    this->freqshift_tilde_07_h_biquad4_y1 = 0;
    this->freqshift_tilde_07_h_biquad4_y2 = 0;
}

void freqshift_tilde_07_h_biquad4_dspsetup() {
    this->freqshift_tilde_07_h_biquad4_reset();
}

number freqshift_tilde_07_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad5_x1 * a1 + this->freqshift_tilde_07_h_biquad5_x2 * 1 - (this->freqshift_tilde_07_h_biquad5_y1 * b1 + this->freqshift_tilde_07_h_biquad5_y2 * b2);
    this->freqshift_tilde_07_h_biquad5_x2 = this->freqshift_tilde_07_h_biquad5_x1;
    this->freqshift_tilde_07_h_biquad5_x1 = x;
    this->freqshift_tilde_07_h_biquad5_y2 = this->freqshift_tilde_07_h_biquad5_y1;
    this->freqshift_tilde_07_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad5_clear() {
    this->freqshift_tilde_07_h_biquad5_reset();
}

void freqshift_tilde_07_h_biquad5_reset() {
    this->freqshift_tilde_07_h_biquad5_x1 = 0;
    this->freqshift_tilde_07_h_biquad5_x2 = 0;
    this->freqshift_tilde_07_h_biquad5_y1 = 0;
    this->freqshift_tilde_07_h_biquad5_y2 = 0;
}

void freqshift_tilde_07_h_biquad5_dspsetup() {
    this->freqshift_tilde_07_h_biquad5_reset();
}

number freqshift_tilde_07_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_07_h_biquad6_x1 * a1 + this->freqshift_tilde_07_h_biquad6_x2 * 1 - (this->freqshift_tilde_07_h_biquad6_y1 * b1 + this->freqshift_tilde_07_h_biquad6_y2 * b2);
    this->freqshift_tilde_07_h_biquad6_x2 = this->freqshift_tilde_07_h_biquad6_x1;
    this->freqshift_tilde_07_h_biquad6_x1 = x;
    this->freqshift_tilde_07_h_biquad6_y2 = this->freqshift_tilde_07_h_biquad6_y1;
    this->freqshift_tilde_07_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_07_h_biquad6_clear() {
    this->freqshift_tilde_07_h_biquad6_reset();
}

void freqshift_tilde_07_h_biquad6_reset() {
    this->freqshift_tilde_07_h_biquad6_x1 = 0;
    this->freqshift_tilde_07_h_biquad6_x2 = 0;
    this->freqshift_tilde_07_h_biquad6_y1 = 0;
    this->freqshift_tilde_07_h_biquad6_y2 = 0;
}

void freqshift_tilde_07_h_biquad6_dspsetup() {
    this->freqshift_tilde_07_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_07_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_07_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_07_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_07_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_07_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_07_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_07_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_07_h_clear() {
    this->freqshift_tilde_07_h_reset();
}

void freqshift_tilde_07_h_reset() {
    this->freqshift_tilde_07_h_biquad1_reset();
    this->freqshift_tilde_07_h_biquad2_reset();
    this->freqshift_tilde_07_h_biquad3_reset();
    this->freqshift_tilde_07_h_biquad4_reset();
    this->freqshift_tilde_07_h_biquad5_reset();
    this->freqshift_tilde_07_h_biquad6_reset();
}

void freqshift_tilde_07_h_dspsetup() {
    this->freqshift_tilde_07_h_reset();
}

number freqshift_tilde_07_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_07_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_07_p_conv;

    if (this->freqshift_tilde_07_p_currentPhase < 0.)
        this->freqshift_tilde_07_p_currentPhase = 1. + this->freqshift_tilde_07_p_currentPhase;

    if (this->freqshift_tilde_07_p_currentPhase > 1.)
        this->freqshift_tilde_07_p_currentPhase = this->freqshift_tilde_07_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_07_p_currentPhase;
    this->freqshift_tilde_07_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_07_p_reset() {
    this->freqshift_tilde_07_p_currentPhase = 0;
}

void freqshift_tilde_07_p_dspsetup() {
    this->freqshift_tilde_07_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_07_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_07_setupDone = true;
    this->freqshift_tilde_07_h_biquad1_dspsetup();
    this->freqshift_tilde_07_h_biquad2_dspsetup();
    this->freqshift_tilde_07_h_biquad3_dspsetup();
    this->freqshift_tilde_07_h_biquad4_dspsetup();
    this->freqshift_tilde_07_h_biquad5_dspsetup();
    this->freqshift_tilde_07_h_biquad6_dspsetup();
    this->freqshift_tilde_07_h_dspsetup();
    this->freqshift_tilde_07_p_dspsetup();
}

number gaintilde_09_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_09_ramp_d_prev);
    this->gaintilde_09_ramp_d_prev = x;
    return temp;
}

void gaintilde_09_ramp_d_dspsetup() {
    this->gaintilde_09_ramp_d_reset();
}

void gaintilde_09_ramp_d_reset() {
    this->gaintilde_09_ramp_d_prev = 0;
}

number gaintilde_09_ramp_next(number x, number up, number down) {
    if (this->gaintilde_09_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_09_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_09_ramp_index = _up;
            this->gaintilde_09_ramp_increment = (x - this->gaintilde_09_ramp_prev) / _up;
        } else if (x < this->gaintilde_09_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_09_ramp_index = _down;
            this->gaintilde_09_ramp_increment = (x - this->gaintilde_09_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_09_ramp_index > 0) {
        this->gaintilde_09_ramp_prev += this->gaintilde_09_ramp_increment;
        this->gaintilde_09_ramp_index -= 1;
    } else {
        this->gaintilde_09_ramp_prev = x;
    }

    return this->gaintilde_09_ramp_prev;
}

void gaintilde_09_ramp_reset() {
    this->gaintilde_09_ramp_prev = 0;
    this->gaintilde_09_ramp_index = 0;
    this->gaintilde_09_ramp_increment = 0;
    this->gaintilde_09_ramp_d_reset();
}

void gaintilde_09_init() {
    this->gaintilde_09_loginc = rnbo_log(1.072);
    this->gaintilde_09_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_09_loginc));
}

void gaintilde_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_09_value;
}

void gaintilde_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_09_value_set(preset["value"]);
}

void gaintilde_09_dspsetup(bool force) {
    if ((bool)(this->gaintilde_09_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_09_setupDone = true;
    this->gaintilde_09_ramp_d_dspsetup();
}

number freqshift_tilde_08_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad1_x1 * a1 + this->freqshift_tilde_08_h_biquad1_x2 * 1 - (this->freqshift_tilde_08_h_biquad1_y1 * b1 + this->freqshift_tilde_08_h_biquad1_y2 * b2);
    this->freqshift_tilde_08_h_biquad1_x2 = this->freqshift_tilde_08_h_biquad1_x1;
    this->freqshift_tilde_08_h_biquad1_x1 = x;
    this->freqshift_tilde_08_h_biquad1_y2 = this->freqshift_tilde_08_h_biquad1_y1;
    this->freqshift_tilde_08_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad1_clear() {
    this->freqshift_tilde_08_h_biquad1_reset();
}

void freqshift_tilde_08_h_biquad1_reset() {
    this->freqshift_tilde_08_h_biquad1_x1 = 0;
    this->freqshift_tilde_08_h_biquad1_x2 = 0;
    this->freqshift_tilde_08_h_biquad1_y1 = 0;
    this->freqshift_tilde_08_h_biquad1_y2 = 0;
}

void freqshift_tilde_08_h_biquad1_dspsetup() {
    this->freqshift_tilde_08_h_biquad1_reset();
}

number freqshift_tilde_08_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad2_x1 * a1 + this->freqshift_tilde_08_h_biquad2_x2 * 1 - (this->freqshift_tilde_08_h_biquad2_y1 * b1 + this->freqshift_tilde_08_h_biquad2_y2 * b2);
    this->freqshift_tilde_08_h_biquad2_x2 = this->freqshift_tilde_08_h_biquad2_x1;
    this->freqshift_tilde_08_h_biquad2_x1 = x;
    this->freqshift_tilde_08_h_biquad2_y2 = this->freqshift_tilde_08_h_biquad2_y1;
    this->freqshift_tilde_08_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad2_clear() {
    this->freqshift_tilde_08_h_biquad2_reset();
}

void freqshift_tilde_08_h_biquad2_reset() {
    this->freqshift_tilde_08_h_biquad2_x1 = 0;
    this->freqshift_tilde_08_h_biquad2_x2 = 0;
    this->freqshift_tilde_08_h_biquad2_y1 = 0;
    this->freqshift_tilde_08_h_biquad2_y2 = 0;
}

void freqshift_tilde_08_h_biquad2_dspsetup() {
    this->freqshift_tilde_08_h_biquad2_reset();
}

number freqshift_tilde_08_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad3_x1 * a1 + this->freqshift_tilde_08_h_biquad3_x2 * 1 - (this->freqshift_tilde_08_h_biquad3_y1 * b1 + this->freqshift_tilde_08_h_biquad3_y2 * b2);
    this->freqshift_tilde_08_h_biquad3_x2 = this->freqshift_tilde_08_h_biquad3_x1;
    this->freqshift_tilde_08_h_biquad3_x1 = x;
    this->freqshift_tilde_08_h_biquad3_y2 = this->freqshift_tilde_08_h_biquad3_y1;
    this->freqshift_tilde_08_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad3_clear() {
    this->freqshift_tilde_08_h_biquad3_reset();
}

void freqshift_tilde_08_h_biquad3_reset() {
    this->freqshift_tilde_08_h_biquad3_x1 = 0;
    this->freqshift_tilde_08_h_biquad3_x2 = 0;
    this->freqshift_tilde_08_h_biquad3_y1 = 0;
    this->freqshift_tilde_08_h_biquad3_y2 = 0;
}

void freqshift_tilde_08_h_biquad3_dspsetup() {
    this->freqshift_tilde_08_h_biquad3_reset();
}

number freqshift_tilde_08_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad4_x1 * a1 + this->freqshift_tilde_08_h_biquad4_x2 * 1 - (this->freqshift_tilde_08_h_biquad4_y1 * b1 + this->freqshift_tilde_08_h_biquad4_y2 * b2);
    this->freqshift_tilde_08_h_biquad4_x2 = this->freqshift_tilde_08_h_biquad4_x1;
    this->freqshift_tilde_08_h_biquad4_x1 = x;
    this->freqshift_tilde_08_h_biquad4_y2 = this->freqshift_tilde_08_h_biquad4_y1;
    this->freqshift_tilde_08_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad4_clear() {
    this->freqshift_tilde_08_h_biquad4_reset();
}

void freqshift_tilde_08_h_biquad4_reset() {
    this->freqshift_tilde_08_h_biquad4_x1 = 0;
    this->freqshift_tilde_08_h_biquad4_x2 = 0;
    this->freqshift_tilde_08_h_biquad4_y1 = 0;
    this->freqshift_tilde_08_h_biquad4_y2 = 0;
}

void freqshift_tilde_08_h_biquad4_dspsetup() {
    this->freqshift_tilde_08_h_biquad4_reset();
}

number freqshift_tilde_08_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad5_x1 * a1 + this->freqshift_tilde_08_h_biquad5_x2 * 1 - (this->freqshift_tilde_08_h_biquad5_y1 * b1 + this->freqshift_tilde_08_h_biquad5_y2 * b2);
    this->freqshift_tilde_08_h_biquad5_x2 = this->freqshift_tilde_08_h_biquad5_x1;
    this->freqshift_tilde_08_h_biquad5_x1 = x;
    this->freqshift_tilde_08_h_biquad5_y2 = this->freqshift_tilde_08_h_biquad5_y1;
    this->freqshift_tilde_08_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad5_clear() {
    this->freqshift_tilde_08_h_biquad5_reset();
}

void freqshift_tilde_08_h_biquad5_reset() {
    this->freqshift_tilde_08_h_biquad5_x1 = 0;
    this->freqshift_tilde_08_h_biquad5_x2 = 0;
    this->freqshift_tilde_08_h_biquad5_y1 = 0;
    this->freqshift_tilde_08_h_biquad5_y2 = 0;
}

void freqshift_tilde_08_h_biquad5_dspsetup() {
    this->freqshift_tilde_08_h_biquad5_reset();
}

number freqshift_tilde_08_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_08_h_biquad6_x1 * a1 + this->freqshift_tilde_08_h_biquad6_x2 * 1 - (this->freqshift_tilde_08_h_biquad6_y1 * b1 + this->freqshift_tilde_08_h_biquad6_y2 * b2);
    this->freqshift_tilde_08_h_biquad6_x2 = this->freqshift_tilde_08_h_biquad6_x1;
    this->freqshift_tilde_08_h_biquad6_x1 = x;
    this->freqshift_tilde_08_h_biquad6_y2 = this->freqshift_tilde_08_h_biquad6_y1;
    this->freqshift_tilde_08_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_08_h_biquad6_clear() {
    this->freqshift_tilde_08_h_biquad6_reset();
}

void freqshift_tilde_08_h_biquad6_reset() {
    this->freqshift_tilde_08_h_biquad6_x1 = 0;
    this->freqshift_tilde_08_h_biquad6_x2 = 0;
    this->freqshift_tilde_08_h_biquad6_y1 = 0;
    this->freqshift_tilde_08_h_biquad6_y2 = 0;
}

void freqshift_tilde_08_h_biquad6_dspsetup() {
    this->freqshift_tilde_08_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_08_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_08_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_08_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_08_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_08_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_08_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_08_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_08_h_clear() {
    this->freqshift_tilde_08_h_reset();
}

void freqshift_tilde_08_h_reset() {
    this->freqshift_tilde_08_h_biquad1_reset();
    this->freqshift_tilde_08_h_biquad2_reset();
    this->freqshift_tilde_08_h_biquad3_reset();
    this->freqshift_tilde_08_h_biquad4_reset();
    this->freqshift_tilde_08_h_biquad5_reset();
    this->freqshift_tilde_08_h_biquad6_reset();
}

void freqshift_tilde_08_h_dspsetup() {
    this->freqshift_tilde_08_h_reset();
}

number freqshift_tilde_08_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_08_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_08_p_conv;

    if (this->freqshift_tilde_08_p_currentPhase < 0.)
        this->freqshift_tilde_08_p_currentPhase = 1. + this->freqshift_tilde_08_p_currentPhase;

    if (this->freqshift_tilde_08_p_currentPhase > 1.)
        this->freqshift_tilde_08_p_currentPhase = this->freqshift_tilde_08_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_08_p_currentPhase;
    this->freqshift_tilde_08_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_08_p_reset() {
    this->freqshift_tilde_08_p_currentPhase = 0;
}

void freqshift_tilde_08_p_dspsetup() {
    this->freqshift_tilde_08_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_08_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_08_setupDone = true;
    this->freqshift_tilde_08_h_biquad1_dspsetup();
    this->freqshift_tilde_08_h_biquad2_dspsetup();
    this->freqshift_tilde_08_h_biquad3_dspsetup();
    this->freqshift_tilde_08_h_biquad4_dspsetup();
    this->freqshift_tilde_08_h_biquad5_dspsetup();
    this->freqshift_tilde_08_h_biquad6_dspsetup();
    this->freqshift_tilde_08_h_dspsetup();
    this->freqshift_tilde_08_p_dspsetup();
}

number gaintilde_10_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_10_ramp_d_prev);
    this->gaintilde_10_ramp_d_prev = x;
    return temp;
}

void gaintilde_10_ramp_d_dspsetup() {
    this->gaintilde_10_ramp_d_reset();
}

void gaintilde_10_ramp_d_reset() {
    this->gaintilde_10_ramp_d_prev = 0;
}

number gaintilde_10_ramp_next(number x, number up, number down) {
    if (this->gaintilde_10_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_10_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_10_ramp_index = _up;
            this->gaintilde_10_ramp_increment = (x - this->gaintilde_10_ramp_prev) / _up;
        } else if (x < this->gaintilde_10_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_10_ramp_index = _down;
            this->gaintilde_10_ramp_increment = (x - this->gaintilde_10_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_10_ramp_index > 0) {
        this->gaintilde_10_ramp_prev += this->gaintilde_10_ramp_increment;
        this->gaintilde_10_ramp_index -= 1;
    } else {
        this->gaintilde_10_ramp_prev = x;
    }

    return this->gaintilde_10_ramp_prev;
}

void gaintilde_10_ramp_reset() {
    this->gaintilde_10_ramp_prev = 0;
    this->gaintilde_10_ramp_index = 0;
    this->gaintilde_10_ramp_increment = 0;
    this->gaintilde_10_ramp_d_reset();
}

void gaintilde_10_init() {
    this->gaintilde_10_loginc = rnbo_log(1.072);
    this->gaintilde_10_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_10_loginc));
}

void gaintilde_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_10_value;
}

void gaintilde_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_10_value_set(preset["value"]);
}

void gaintilde_10_dspsetup(bool force) {
    if ((bool)(this->gaintilde_10_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_10_setupDone = true;
    this->gaintilde_10_ramp_d_dspsetup();
}

number gaintilde_11_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_11_ramp_d_prev);
    this->gaintilde_11_ramp_d_prev = x;
    return temp;
}

void gaintilde_11_ramp_d_dspsetup() {
    this->gaintilde_11_ramp_d_reset();
}

void gaintilde_11_ramp_d_reset() {
    this->gaintilde_11_ramp_d_prev = 0;
}

number gaintilde_11_ramp_next(number x, number up, number down) {
    if (this->gaintilde_11_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_11_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_11_ramp_index = _up;
            this->gaintilde_11_ramp_increment = (x - this->gaintilde_11_ramp_prev) / _up;
        } else if (x < this->gaintilde_11_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_11_ramp_index = _down;
            this->gaintilde_11_ramp_increment = (x - this->gaintilde_11_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_11_ramp_index > 0) {
        this->gaintilde_11_ramp_prev += this->gaintilde_11_ramp_increment;
        this->gaintilde_11_ramp_index -= 1;
    } else {
        this->gaintilde_11_ramp_prev = x;
    }

    return this->gaintilde_11_ramp_prev;
}

void gaintilde_11_ramp_reset() {
    this->gaintilde_11_ramp_prev = 0;
    this->gaintilde_11_ramp_index = 0;
    this->gaintilde_11_ramp_increment = 0;
    this->gaintilde_11_ramp_d_reset();
}

void gaintilde_11_init() {
    this->gaintilde_11_loginc = rnbo_log(1.072);
    this->gaintilde_11_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_11_loginc));
}

void gaintilde_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_11_value;
}

void gaintilde_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_11_value_set(preset["value"]);
}

void gaintilde_11_dspsetup(bool force) {
    if ((bool)(this->gaintilde_11_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_11_setupDone = true;
    this->gaintilde_11_ramp_d_dspsetup();
}

number gaintilde_12_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_12_ramp_d_prev);
    this->gaintilde_12_ramp_d_prev = x;
    return temp;
}

void gaintilde_12_ramp_d_dspsetup() {
    this->gaintilde_12_ramp_d_reset();
}

void gaintilde_12_ramp_d_reset() {
    this->gaintilde_12_ramp_d_prev = 0;
}

number gaintilde_12_ramp_next(number x, number up, number down) {
    if (this->gaintilde_12_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_12_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_12_ramp_index = _up;
            this->gaintilde_12_ramp_increment = (x - this->gaintilde_12_ramp_prev) / _up;
        } else if (x < this->gaintilde_12_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_12_ramp_index = _down;
            this->gaintilde_12_ramp_increment = (x - this->gaintilde_12_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_12_ramp_index > 0) {
        this->gaintilde_12_ramp_prev += this->gaintilde_12_ramp_increment;
        this->gaintilde_12_ramp_index -= 1;
    } else {
        this->gaintilde_12_ramp_prev = x;
    }

    return this->gaintilde_12_ramp_prev;
}

void gaintilde_12_ramp_reset() {
    this->gaintilde_12_ramp_prev = 0;
    this->gaintilde_12_ramp_index = 0;
    this->gaintilde_12_ramp_increment = 0;
    this->gaintilde_12_ramp_d_reset();
}

void gaintilde_12_init() {
    this->gaintilde_12_loginc = rnbo_log(1.072);
    this->gaintilde_12_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_12_loginc));
}

void gaintilde_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_12_value;
}

void gaintilde_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_12_value_set(preset["value"]);
}

void gaintilde_12_dspsetup(bool force) {
    if ((bool)(this->gaintilde_12_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_12_setupDone = true;
    this->gaintilde_12_ramp_d_dspsetup();
}

number freqshift_tilde_09_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad1_x1 * a1 + this->freqshift_tilde_09_h_biquad1_x2 * 1 - (this->freqshift_tilde_09_h_biquad1_y1 * b1 + this->freqshift_tilde_09_h_biquad1_y2 * b2);
    this->freqshift_tilde_09_h_biquad1_x2 = this->freqshift_tilde_09_h_biquad1_x1;
    this->freqshift_tilde_09_h_biquad1_x1 = x;
    this->freqshift_tilde_09_h_biquad1_y2 = this->freqshift_tilde_09_h_biquad1_y1;
    this->freqshift_tilde_09_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad1_clear() {
    this->freqshift_tilde_09_h_biquad1_reset();
}

void freqshift_tilde_09_h_biquad1_reset() {
    this->freqshift_tilde_09_h_biquad1_x1 = 0;
    this->freqshift_tilde_09_h_biquad1_x2 = 0;
    this->freqshift_tilde_09_h_biquad1_y1 = 0;
    this->freqshift_tilde_09_h_biquad1_y2 = 0;
}

void freqshift_tilde_09_h_biquad1_dspsetup() {
    this->freqshift_tilde_09_h_biquad1_reset();
}

number freqshift_tilde_09_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad2_x1 * a1 + this->freqshift_tilde_09_h_biquad2_x2 * 1 - (this->freqshift_tilde_09_h_biquad2_y1 * b1 + this->freqshift_tilde_09_h_biquad2_y2 * b2);
    this->freqshift_tilde_09_h_biquad2_x2 = this->freqshift_tilde_09_h_biquad2_x1;
    this->freqshift_tilde_09_h_biquad2_x1 = x;
    this->freqshift_tilde_09_h_biquad2_y2 = this->freqshift_tilde_09_h_biquad2_y1;
    this->freqshift_tilde_09_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad2_clear() {
    this->freqshift_tilde_09_h_biquad2_reset();
}

void freqshift_tilde_09_h_biquad2_reset() {
    this->freqshift_tilde_09_h_biquad2_x1 = 0;
    this->freqshift_tilde_09_h_biquad2_x2 = 0;
    this->freqshift_tilde_09_h_biquad2_y1 = 0;
    this->freqshift_tilde_09_h_biquad2_y2 = 0;
}

void freqshift_tilde_09_h_biquad2_dspsetup() {
    this->freqshift_tilde_09_h_biquad2_reset();
}

number freqshift_tilde_09_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad3_x1 * a1 + this->freqshift_tilde_09_h_biquad3_x2 * 1 - (this->freqshift_tilde_09_h_biquad3_y1 * b1 + this->freqshift_tilde_09_h_biquad3_y2 * b2);
    this->freqshift_tilde_09_h_biquad3_x2 = this->freqshift_tilde_09_h_biquad3_x1;
    this->freqshift_tilde_09_h_biquad3_x1 = x;
    this->freqshift_tilde_09_h_biquad3_y2 = this->freqshift_tilde_09_h_biquad3_y1;
    this->freqshift_tilde_09_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad3_clear() {
    this->freqshift_tilde_09_h_biquad3_reset();
}

void freqshift_tilde_09_h_biquad3_reset() {
    this->freqshift_tilde_09_h_biquad3_x1 = 0;
    this->freqshift_tilde_09_h_biquad3_x2 = 0;
    this->freqshift_tilde_09_h_biquad3_y1 = 0;
    this->freqshift_tilde_09_h_biquad3_y2 = 0;
}

void freqshift_tilde_09_h_biquad3_dspsetup() {
    this->freqshift_tilde_09_h_biquad3_reset();
}

number freqshift_tilde_09_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad4_x1 * a1 + this->freqshift_tilde_09_h_biquad4_x2 * 1 - (this->freqshift_tilde_09_h_biquad4_y1 * b1 + this->freqshift_tilde_09_h_biquad4_y2 * b2);
    this->freqshift_tilde_09_h_biquad4_x2 = this->freqshift_tilde_09_h_biquad4_x1;
    this->freqshift_tilde_09_h_biquad4_x1 = x;
    this->freqshift_tilde_09_h_biquad4_y2 = this->freqshift_tilde_09_h_biquad4_y1;
    this->freqshift_tilde_09_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad4_clear() {
    this->freqshift_tilde_09_h_biquad4_reset();
}

void freqshift_tilde_09_h_biquad4_reset() {
    this->freqshift_tilde_09_h_biquad4_x1 = 0;
    this->freqshift_tilde_09_h_biquad4_x2 = 0;
    this->freqshift_tilde_09_h_biquad4_y1 = 0;
    this->freqshift_tilde_09_h_biquad4_y2 = 0;
}

void freqshift_tilde_09_h_biquad4_dspsetup() {
    this->freqshift_tilde_09_h_biquad4_reset();
}

number freqshift_tilde_09_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad5_x1 * a1 + this->freqshift_tilde_09_h_biquad5_x2 * 1 - (this->freqshift_tilde_09_h_biquad5_y1 * b1 + this->freqshift_tilde_09_h_biquad5_y2 * b2);
    this->freqshift_tilde_09_h_biquad5_x2 = this->freqshift_tilde_09_h_biquad5_x1;
    this->freqshift_tilde_09_h_biquad5_x1 = x;
    this->freqshift_tilde_09_h_biquad5_y2 = this->freqshift_tilde_09_h_biquad5_y1;
    this->freqshift_tilde_09_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad5_clear() {
    this->freqshift_tilde_09_h_biquad5_reset();
}

void freqshift_tilde_09_h_biquad5_reset() {
    this->freqshift_tilde_09_h_biquad5_x1 = 0;
    this->freqshift_tilde_09_h_biquad5_x2 = 0;
    this->freqshift_tilde_09_h_biquad5_y1 = 0;
    this->freqshift_tilde_09_h_biquad5_y2 = 0;
}

void freqshift_tilde_09_h_biquad5_dspsetup() {
    this->freqshift_tilde_09_h_biquad5_reset();
}

number freqshift_tilde_09_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_09_h_biquad6_x1 * a1 + this->freqshift_tilde_09_h_biquad6_x2 * 1 - (this->freqshift_tilde_09_h_biquad6_y1 * b1 + this->freqshift_tilde_09_h_biquad6_y2 * b2);
    this->freqshift_tilde_09_h_biquad6_x2 = this->freqshift_tilde_09_h_biquad6_x1;
    this->freqshift_tilde_09_h_biquad6_x1 = x;
    this->freqshift_tilde_09_h_biquad6_y2 = this->freqshift_tilde_09_h_biquad6_y1;
    this->freqshift_tilde_09_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_09_h_biquad6_clear() {
    this->freqshift_tilde_09_h_biquad6_reset();
}

void freqshift_tilde_09_h_biquad6_reset() {
    this->freqshift_tilde_09_h_biquad6_x1 = 0;
    this->freqshift_tilde_09_h_biquad6_x2 = 0;
    this->freqshift_tilde_09_h_biquad6_y1 = 0;
    this->freqshift_tilde_09_h_biquad6_y2 = 0;
}

void freqshift_tilde_09_h_biquad6_dspsetup() {
    this->freqshift_tilde_09_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_09_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_09_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_09_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_09_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_09_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_09_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_09_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_09_h_clear() {
    this->freqshift_tilde_09_h_reset();
}

void freqshift_tilde_09_h_reset() {
    this->freqshift_tilde_09_h_biquad1_reset();
    this->freqshift_tilde_09_h_biquad2_reset();
    this->freqshift_tilde_09_h_biquad3_reset();
    this->freqshift_tilde_09_h_biquad4_reset();
    this->freqshift_tilde_09_h_biquad5_reset();
    this->freqshift_tilde_09_h_biquad6_reset();
}

void freqshift_tilde_09_h_dspsetup() {
    this->freqshift_tilde_09_h_reset();
}

number freqshift_tilde_09_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_09_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_09_p_conv;

    if (this->freqshift_tilde_09_p_currentPhase < 0.)
        this->freqshift_tilde_09_p_currentPhase = 1. + this->freqshift_tilde_09_p_currentPhase;

    if (this->freqshift_tilde_09_p_currentPhase > 1.)
        this->freqshift_tilde_09_p_currentPhase = this->freqshift_tilde_09_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_09_p_currentPhase;
    this->freqshift_tilde_09_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_09_p_reset() {
    this->freqshift_tilde_09_p_currentPhase = 0;
}

void freqshift_tilde_09_p_dspsetup() {
    this->freqshift_tilde_09_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_09_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_09_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_09_setupDone = true;
    this->freqshift_tilde_09_h_biquad1_dspsetup();
    this->freqshift_tilde_09_h_biquad2_dspsetup();
    this->freqshift_tilde_09_h_biquad3_dspsetup();
    this->freqshift_tilde_09_h_biquad4_dspsetup();
    this->freqshift_tilde_09_h_biquad5_dspsetup();
    this->freqshift_tilde_09_h_biquad6_dspsetup();
    this->freqshift_tilde_09_h_dspsetup();
    this->freqshift_tilde_09_p_dspsetup();
}

number freqshift_tilde_10_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad1_x1 * a1 + this->freqshift_tilde_10_h_biquad1_x2 * 1 - (this->freqshift_tilde_10_h_biquad1_y1 * b1 + this->freqshift_tilde_10_h_biquad1_y2 * b2);
    this->freqshift_tilde_10_h_biquad1_x2 = this->freqshift_tilde_10_h_biquad1_x1;
    this->freqshift_tilde_10_h_biquad1_x1 = x;
    this->freqshift_tilde_10_h_biquad1_y2 = this->freqshift_tilde_10_h_biquad1_y1;
    this->freqshift_tilde_10_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad1_clear() {
    this->freqshift_tilde_10_h_biquad1_reset();
}

void freqshift_tilde_10_h_biquad1_reset() {
    this->freqshift_tilde_10_h_biquad1_x1 = 0;
    this->freqshift_tilde_10_h_biquad1_x2 = 0;
    this->freqshift_tilde_10_h_biquad1_y1 = 0;
    this->freqshift_tilde_10_h_biquad1_y2 = 0;
}

void freqshift_tilde_10_h_biquad1_dspsetup() {
    this->freqshift_tilde_10_h_biquad1_reset();
}

number freqshift_tilde_10_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad2_x1 * a1 + this->freqshift_tilde_10_h_biquad2_x2 * 1 - (this->freqshift_tilde_10_h_biquad2_y1 * b1 + this->freqshift_tilde_10_h_biquad2_y2 * b2);
    this->freqshift_tilde_10_h_biquad2_x2 = this->freqshift_tilde_10_h_biquad2_x1;
    this->freqshift_tilde_10_h_biquad2_x1 = x;
    this->freqshift_tilde_10_h_biquad2_y2 = this->freqshift_tilde_10_h_biquad2_y1;
    this->freqshift_tilde_10_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad2_clear() {
    this->freqshift_tilde_10_h_biquad2_reset();
}

void freqshift_tilde_10_h_biquad2_reset() {
    this->freqshift_tilde_10_h_biquad2_x1 = 0;
    this->freqshift_tilde_10_h_biquad2_x2 = 0;
    this->freqshift_tilde_10_h_biquad2_y1 = 0;
    this->freqshift_tilde_10_h_biquad2_y2 = 0;
}

void freqshift_tilde_10_h_biquad2_dspsetup() {
    this->freqshift_tilde_10_h_biquad2_reset();
}

number freqshift_tilde_10_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad3_x1 * a1 + this->freqshift_tilde_10_h_biquad3_x2 * 1 - (this->freqshift_tilde_10_h_biquad3_y1 * b1 + this->freqshift_tilde_10_h_biquad3_y2 * b2);
    this->freqshift_tilde_10_h_biquad3_x2 = this->freqshift_tilde_10_h_biquad3_x1;
    this->freqshift_tilde_10_h_biquad3_x1 = x;
    this->freqshift_tilde_10_h_biquad3_y2 = this->freqshift_tilde_10_h_biquad3_y1;
    this->freqshift_tilde_10_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad3_clear() {
    this->freqshift_tilde_10_h_biquad3_reset();
}

void freqshift_tilde_10_h_biquad3_reset() {
    this->freqshift_tilde_10_h_biquad3_x1 = 0;
    this->freqshift_tilde_10_h_biquad3_x2 = 0;
    this->freqshift_tilde_10_h_biquad3_y1 = 0;
    this->freqshift_tilde_10_h_biquad3_y2 = 0;
}

void freqshift_tilde_10_h_biquad3_dspsetup() {
    this->freqshift_tilde_10_h_biquad3_reset();
}

number freqshift_tilde_10_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad4_x1 * a1 + this->freqshift_tilde_10_h_biquad4_x2 * 1 - (this->freqshift_tilde_10_h_biquad4_y1 * b1 + this->freqshift_tilde_10_h_biquad4_y2 * b2);
    this->freqshift_tilde_10_h_biquad4_x2 = this->freqshift_tilde_10_h_biquad4_x1;
    this->freqshift_tilde_10_h_biquad4_x1 = x;
    this->freqshift_tilde_10_h_biquad4_y2 = this->freqshift_tilde_10_h_biquad4_y1;
    this->freqshift_tilde_10_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad4_clear() {
    this->freqshift_tilde_10_h_biquad4_reset();
}

void freqshift_tilde_10_h_biquad4_reset() {
    this->freqshift_tilde_10_h_biquad4_x1 = 0;
    this->freqshift_tilde_10_h_biquad4_x2 = 0;
    this->freqshift_tilde_10_h_biquad4_y1 = 0;
    this->freqshift_tilde_10_h_biquad4_y2 = 0;
}

void freqshift_tilde_10_h_biquad4_dspsetup() {
    this->freqshift_tilde_10_h_biquad4_reset();
}

number freqshift_tilde_10_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad5_x1 * a1 + this->freqshift_tilde_10_h_biquad5_x2 * 1 - (this->freqshift_tilde_10_h_biquad5_y1 * b1 + this->freqshift_tilde_10_h_biquad5_y2 * b2);
    this->freqshift_tilde_10_h_biquad5_x2 = this->freqshift_tilde_10_h_biquad5_x1;
    this->freqshift_tilde_10_h_biquad5_x1 = x;
    this->freqshift_tilde_10_h_biquad5_y2 = this->freqshift_tilde_10_h_biquad5_y1;
    this->freqshift_tilde_10_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad5_clear() {
    this->freqshift_tilde_10_h_biquad5_reset();
}

void freqshift_tilde_10_h_biquad5_reset() {
    this->freqshift_tilde_10_h_biquad5_x1 = 0;
    this->freqshift_tilde_10_h_biquad5_x2 = 0;
    this->freqshift_tilde_10_h_biquad5_y1 = 0;
    this->freqshift_tilde_10_h_biquad5_y2 = 0;
}

void freqshift_tilde_10_h_biquad5_dspsetup() {
    this->freqshift_tilde_10_h_biquad5_reset();
}

number freqshift_tilde_10_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_10_h_biquad6_x1 * a1 + this->freqshift_tilde_10_h_biquad6_x2 * 1 - (this->freqshift_tilde_10_h_biquad6_y1 * b1 + this->freqshift_tilde_10_h_biquad6_y2 * b2);
    this->freqshift_tilde_10_h_biquad6_x2 = this->freqshift_tilde_10_h_biquad6_x1;
    this->freqshift_tilde_10_h_biquad6_x1 = x;
    this->freqshift_tilde_10_h_biquad6_y2 = this->freqshift_tilde_10_h_biquad6_y1;
    this->freqshift_tilde_10_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_10_h_biquad6_clear() {
    this->freqshift_tilde_10_h_biquad6_reset();
}

void freqshift_tilde_10_h_biquad6_reset() {
    this->freqshift_tilde_10_h_biquad6_x1 = 0;
    this->freqshift_tilde_10_h_biquad6_x2 = 0;
    this->freqshift_tilde_10_h_biquad6_y1 = 0;
    this->freqshift_tilde_10_h_biquad6_y2 = 0;
}

void freqshift_tilde_10_h_biquad6_dspsetup() {
    this->freqshift_tilde_10_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_10_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_10_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_10_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_10_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_10_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_10_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_10_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_10_h_clear() {
    this->freqshift_tilde_10_h_reset();
}

void freqshift_tilde_10_h_reset() {
    this->freqshift_tilde_10_h_biquad1_reset();
    this->freqshift_tilde_10_h_biquad2_reset();
    this->freqshift_tilde_10_h_biquad3_reset();
    this->freqshift_tilde_10_h_biquad4_reset();
    this->freqshift_tilde_10_h_biquad5_reset();
    this->freqshift_tilde_10_h_biquad6_reset();
}

void freqshift_tilde_10_h_dspsetup() {
    this->freqshift_tilde_10_h_reset();
}

number freqshift_tilde_10_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_10_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_10_p_conv;

    if (this->freqshift_tilde_10_p_currentPhase < 0.)
        this->freqshift_tilde_10_p_currentPhase = 1. + this->freqshift_tilde_10_p_currentPhase;

    if (this->freqshift_tilde_10_p_currentPhase > 1.)
        this->freqshift_tilde_10_p_currentPhase = this->freqshift_tilde_10_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_10_p_currentPhase;
    this->freqshift_tilde_10_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_10_p_reset() {
    this->freqshift_tilde_10_p_currentPhase = 0;
}

void freqshift_tilde_10_p_dspsetup() {
    this->freqshift_tilde_10_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_10_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_10_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_10_setupDone = true;
    this->freqshift_tilde_10_h_biquad1_dspsetup();
    this->freqshift_tilde_10_h_biquad2_dspsetup();
    this->freqshift_tilde_10_h_biquad3_dspsetup();
    this->freqshift_tilde_10_h_biquad4_dspsetup();
    this->freqshift_tilde_10_h_biquad5_dspsetup();
    this->freqshift_tilde_10_h_biquad6_dspsetup();
    this->freqshift_tilde_10_h_dspsetup();
    this->freqshift_tilde_10_p_dspsetup();
}

number freqshift_tilde_11_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad1_x1 * a1 + this->freqshift_tilde_11_h_biquad1_x2 * 1 - (this->freqshift_tilde_11_h_biquad1_y1 * b1 + this->freqshift_tilde_11_h_biquad1_y2 * b2);
    this->freqshift_tilde_11_h_biquad1_x2 = this->freqshift_tilde_11_h_biquad1_x1;
    this->freqshift_tilde_11_h_biquad1_x1 = x;
    this->freqshift_tilde_11_h_biquad1_y2 = this->freqshift_tilde_11_h_biquad1_y1;
    this->freqshift_tilde_11_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad1_clear() {
    this->freqshift_tilde_11_h_biquad1_reset();
}

void freqshift_tilde_11_h_biquad1_reset() {
    this->freqshift_tilde_11_h_biquad1_x1 = 0;
    this->freqshift_tilde_11_h_biquad1_x2 = 0;
    this->freqshift_tilde_11_h_biquad1_y1 = 0;
    this->freqshift_tilde_11_h_biquad1_y2 = 0;
}

void freqshift_tilde_11_h_biquad1_dspsetup() {
    this->freqshift_tilde_11_h_biquad1_reset();
}

number freqshift_tilde_11_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad2_x1 * a1 + this->freqshift_tilde_11_h_biquad2_x2 * 1 - (this->freqshift_tilde_11_h_biquad2_y1 * b1 + this->freqshift_tilde_11_h_biquad2_y2 * b2);
    this->freqshift_tilde_11_h_biquad2_x2 = this->freqshift_tilde_11_h_biquad2_x1;
    this->freqshift_tilde_11_h_biquad2_x1 = x;
    this->freqshift_tilde_11_h_biquad2_y2 = this->freqshift_tilde_11_h_biquad2_y1;
    this->freqshift_tilde_11_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad2_clear() {
    this->freqshift_tilde_11_h_biquad2_reset();
}

void freqshift_tilde_11_h_biquad2_reset() {
    this->freqshift_tilde_11_h_biquad2_x1 = 0;
    this->freqshift_tilde_11_h_biquad2_x2 = 0;
    this->freqshift_tilde_11_h_biquad2_y1 = 0;
    this->freqshift_tilde_11_h_biquad2_y2 = 0;
}

void freqshift_tilde_11_h_biquad2_dspsetup() {
    this->freqshift_tilde_11_h_biquad2_reset();
}

number freqshift_tilde_11_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad3_x1 * a1 + this->freqshift_tilde_11_h_biquad3_x2 * 1 - (this->freqshift_tilde_11_h_biquad3_y1 * b1 + this->freqshift_tilde_11_h_biquad3_y2 * b2);
    this->freqshift_tilde_11_h_biquad3_x2 = this->freqshift_tilde_11_h_biquad3_x1;
    this->freqshift_tilde_11_h_biquad3_x1 = x;
    this->freqshift_tilde_11_h_biquad3_y2 = this->freqshift_tilde_11_h_biquad3_y1;
    this->freqshift_tilde_11_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad3_clear() {
    this->freqshift_tilde_11_h_biquad3_reset();
}

void freqshift_tilde_11_h_biquad3_reset() {
    this->freqshift_tilde_11_h_biquad3_x1 = 0;
    this->freqshift_tilde_11_h_biquad3_x2 = 0;
    this->freqshift_tilde_11_h_biquad3_y1 = 0;
    this->freqshift_tilde_11_h_biquad3_y2 = 0;
}

void freqshift_tilde_11_h_biquad3_dspsetup() {
    this->freqshift_tilde_11_h_biquad3_reset();
}

number freqshift_tilde_11_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad4_x1 * a1 + this->freqshift_tilde_11_h_biquad4_x2 * 1 - (this->freqshift_tilde_11_h_biquad4_y1 * b1 + this->freqshift_tilde_11_h_biquad4_y2 * b2);
    this->freqshift_tilde_11_h_biquad4_x2 = this->freqshift_tilde_11_h_biquad4_x1;
    this->freqshift_tilde_11_h_biquad4_x1 = x;
    this->freqshift_tilde_11_h_biquad4_y2 = this->freqshift_tilde_11_h_biquad4_y1;
    this->freqshift_tilde_11_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad4_clear() {
    this->freqshift_tilde_11_h_biquad4_reset();
}

void freqshift_tilde_11_h_biquad4_reset() {
    this->freqshift_tilde_11_h_biquad4_x1 = 0;
    this->freqshift_tilde_11_h_biquad4_x2 = 0;
    this->freqshift_tilde_11_h_biquad4_y1 = 0;
    this->freqshift_tilde_11_h_biquad4_y2 = 0;
}

void freqshift_tilde_11_h_biquad4_dspsetup() {
    this->freqshift_tilde_11_h_biquad4_reset();
}

number freqshift_tilde_11_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad5_x1 * a1 + this->freqshift_tilde_11_h_biquad5_x2 * 1 - (this->freqshift_tilde_11_h_biquad5_y1 * b1 + this->freqshift_tilde_11_h_biquad5_y2 * b2);
    this->freqshift_tilde_11_h_biquad5_x2 = this->freqshift_tilde_11_h_biquad5_x1;
    this->freqshift_tilde_11_h_biquad5_x1 = x;
    this->freqshift_tilde_11_h_biquad5_y2 = this->freqshift_tilde_11_h_biquad5_y1;
    this->freqshift_tilde_11_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad5_clear() {
    this->freqshift_tilde_11_h_biquad5_reset();
}

void freqshift_tilde_11_h_biquad5_reset() {
    this->freqshift_tilde_11_h_biquad5_x1 = 0;
    this->freqshift_tilde_11_h_biquad5_x2 = 0;
    this->freqshift_tilde_11_h_biquad5_y1 = 0;
    this->freqshift_tilde_11_h_biquad5_y2 = 0;
}

void freqshift_tilde_11_h_biquad5_dspsetup() {
    this->freqshift_tilde_11_h_biquad5_reset();
}

number freqshift_tilde_11_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_11_h_biquad6_x1 * a1 + this->freqshift_tilde_11_h_biquad6_x2 * 1 - (this->freqshift_tilde_11_h_biquad6_y1 * b1 + this->freqshift_tilde_11_h_biquad6_y2 * b2);
    this->freqshift_tilde_11_h_biquad6_x2 = this->freqshift_tilde_11_h_biquad6_x1;
    this->freqshift_tilde_11_h_biquad6_x1 = x;
    this->freqshift_tilde_11_h_biquad6_y2 = this->freqshift_tilde_11_h_biquad6_y1;
    this->freqshift_tilde_11_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_11_h_biquad6_clear() {
    this->freqshift_tilde_11_h_biquad6_reset();
}

void freqshift_tilde_11_h_biquad6_reset() {
    this->freqshift_tilde_11_h_biquad6_x1 = 0;
    this->freqshift_tilde_11_h_biquad6_x2 = 0;
    this->freqshift_tilde_11_h_biquad6_y1 = 0;
    this->freqshift_tilde_11_h_biquad6_y2 = 0;
}

void freqshift_tilde_11_h_biquad6_dspsetup() {
    this->freqshift_tilde_11_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_11_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_11_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_11_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_11_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_11_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_11_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_11_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_11_h_clear() {
    this->freqshift_tilde_11_h_reset();
}

void freqshift_tilde_11_h_reset() {
    this->freqshift_tilde_11_h_biquad1_reset();
    this->freqshift_tilde_11_h_biquad2_reset();
    this->freqshift_tilde_11_h_biquad3_reset();
    this->freqshift_tilde_11_h_biquad4_reset();
    this->freqshift_tilde_11_h_biquad5_reset();
    this->freqshift_tilde_11_h_biquad6_reset();
}

void freqshift_tilde_11_h_dspsetup() {
    this->freqshift_tilde_11_h_reset();
}

number freqshift_tilde_11_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_11_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_11_p_conv;

    if (this->freqshift_tilde_11_p_currentPhase < 0.)
        this->freqshift_tilde_11_p_currentPhase = 1. + this->freqshift_tilde_11_p_currentPhase;

    if (this->freqshift_tilde_11_p_currentPhase > 1.)
        this->freqshift_tilde_11_p_currentPhase = this->freqshift_tilde_11_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_11_p_currentPhase;
    this->freqshift_tilde_11_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_11_p_reset() {
    this->freqshift_tilde_11_p_currentPhase = 0;
}

void freqshift_tilde_11_p_dspsetup() {
    this->freqshift_tilde_11_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_11_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_11_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_11_setupDone = true;
    this->freqshift_tilde_11_h_biquad1_dspsetup();
    this->freqshift_tilde_11_h_biquad2_dspsetup();
    this->freqshift_tilde_11_h_biquad3_dspsetup();
    this->freqshift_tilde_11_h_biquad4_dspsetup();
    this->freqshift_tilde_11_h_biquad5_dspsetup();
    this->freqshift_tilde_11_h_biquad6_dspsetup();
    this->freqshift_tilde_11_h_dspsetup();
    this->freqshift_tilde_11_p_dspsetup();
}

number gaintilde_13_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_13_ramp_d_prev);
    this->gaintilde_13_ramp_d_prev = x;
    return temp;
}

void gaintilde_13_ramp_d_dspsetup() {
    this->gaintilde_13_ramp_d_reset();
}

void gaintilde_13_ramp_d_reset() {
    this->gaintilde_13_ramp_d_prev = 0;
}

number gaintilde_13_ramp_next(number x, number up, number down) {
    if (this->gaintilde_13_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_13_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_13_ramp_index = _up;
            this->gaintilde_13_ramp_increment = (x - this->gaintilde_13_ramp_prev) / _up;
        } else if (x < this->gaintilde_13_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_13_ramp_index = _down;
            this->gaintilde_13_ramp_increment = (x - this->gaintilde_13_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_13_ramp_index > 0) {
        this->gaintilde_13_ramp_prev += this->gaintilde_13_ramp_increment;
        this->gaintilde_13_ramp_index -= 1;
    } else {
        this->gaintilde_13_ramp_prev = x;
    }

    return this->gaintilde_13_ramp_prev;
}

void gaintilde_13_ramp_reset() {
    this->gaintilde_13_ramp_prev = 0;
    this->gaintilde_13_ramp_index = 0;
    this->gaintilde_13_ramp_increment = 0;
    this->gaintilde_13_ramp_d_reset();
}

void gaintilde_13_init() {
    this->gaintilde_13_loginc = rnbo_log(1.072);
    this->gaintilde_13_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_13_loginc));
}

void gaintilde_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_13_value;
}

void gaintilde_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_13_value_set(preset["value"]);
}

void gaintilde_13_dspsetup(bool force) {
    if ((bool)(this->gaintilde_13_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_13_setupDone = true;
    this->gaintilde_13_ramp_d_dspsetup();
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

number freqshift_tilde_12_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad1_x1 * a1 + this->freqshift_tilde_12_h_biquad1_x2 * 1 - (this->freqshift_tilde_12_h_biquad1_y1 * b1 + this->freqshift_tilde_12_h_biquad1_y2 * b2);
    this->freqshift_tilde_12_h_biquad1_x2 = this->freqshift_tilde_12_h_biquad1_x1;
    this->freqshift_tilde_12_h_biquad1_x1 = x;
    this->freqshift_tilde_12_h_biquad1_y2 = this->freqshift_tilde_12_h_biquad1_y1;
    this->freqshift_tilde_12_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad1_clear() {
    this->freqshift_tilde_12_h_biquad1_reset();
}

void freqshift_tilde_12_h_biquad1_reset() {
    this->freqshift_tilde_12_h_biquad1_x1 = 0;
    this->freqshift_tilde_12_h_biquad1_x2 = 0;
    this->freqshift_tilde_12_h_biquad1_y1 = 0;
    this->freqshift_tilde_12_h_biquad1_y2 = 0;
}

void freqshift_tilde_12_h_biquad1_dspsetup() {
    this->freqshift_tilde_12_h_biquad1_reset();
}

number freqshift_tilde_12_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad2_x1 * a1 + this->freqshift_tilde_12_h_biquad2_x2 * 1 - (this->freqshift_tilde_12_h_biquad2_y1 * b1 + this->freqshift_tilde_12_h_biquad2_y2 * b2);
    this->freqshift_tilde_12_h_biquad2_x2 = this->freqshift_tilde_12_h_biquad2_x1;
    this->freqshift_tilde_12_h_biquad2_x1 = x;
    this->freqshift_tilde_12_h_biquad2_y2 = this->freqshift_tilde_12_h_biquad2_y1;
    this->freqshift_tilde_12_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad2_clear() {
    this->freqshift_tilde_12_h_biquad2_reset();
}

void freqshift_tilde_12_h_biquad2_reset() {
    this->freqshift_tilde_12_h_biquad2_x1 = 0;
    this->freqshift_tilde_12_h_biquad2_x2 = 0;
    this->freqshift_tilde_12_h_biquad2_y1 = 0;
    this->freqshift_tilde_12_h_biquad2_y2 = 0;
}

void freqshift_tilde_12_h_biquad2_dspsetup() {
    this->freqshift_tilde_12_h_biquad2_reset();
}

number freqshift_tilde_12_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad3_x1 * a1 + this->freqshift_tilde_12_h_biquad3_x2 * 1 - (this->freqshift_tilde_12_h_biquad3_y1 * b1 + this->freqshift_tilde_12_h_biquad3_y2 * b2);
    this->freqshift_tilde_12_h_biquad3_x2 = this->freqshift_tilde_12_h_biquad3_x1;
    this->freqshift_tilde_12_h_biquad3_x1 = x;
    this->freqshift_tilde_12_h_biquad3_y2 = this->freqshift_tilde_12_h_biquad3_y1;
    this->freqshift_tilde_12_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad3_clear() {
    this->freqshift_tilde_12_h_biquad3_reset();
}

void freqshift_tilde_12_h_biquad3_reset() {
    this->freqshift_tilde_12_h_biquad3_x1 = 0;
    this->freqshift_tilde_12_h_biquad3_x2 = 0;
    this->freqshift_tilde_12_h_biquad3_y1 = 0;
    this->freqshift_tilde_12_h_biquad3_y2 = 0;
}

void freqshift_tilde_12_h_biquad3_dspsetup() {
    this->freqshift_tilde_12_h_biquad3_reset();
}

number freqshift_tilde_12_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad4_x1 * a1 + this->freqshift_tilde_12_h_biquad4_x2 * 1 - (this->freqshift_tilde_12_h_biquad4_y1 * b1 + this->freqshift_tilde_12_h_biquad4_y2 * b2);
    this->freqshift_tilde_12_h_biquad4_x2 = this->freqshift_tilde_12_h_biquad4_x1;
    this->freqshift_tilde_12_h_biquad4_x1 = x;
    this->freqshift_tilde_12_h_biquad4_y2 = this->freqshift_tilde_12_h_biquad4_y1;
    this->freqshift_tilde_12_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad4_clear() {
    this->freqshift_tilde_12_h_biquad4_reset();
}

void freqshift_tilde_12_h_biquad4_reset() {
    this->freqshift_tilde_12_h_biquad4_x1 = 0;
    this->freqshift_tilde_12_h_biquad4_x2 = 0;
    this->freqshift_tilde_12_h_biquad4_y1 = 0;
    this->freqshift_tilde_12_h_biquad4_y2 = 0;
}

void freqshift_tilde_12_h_biquad4_dspsetup() {
    this->freqshift_tilde_12_h_biquad4_reset();
}

number freqshift_tilde_12_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad5_x1 * a1 + this->freqshift_tilde_12_h_biquad5_x2 * 1 - (this->freqshift_tilde_12_h_biquad5_y1 * b1 + this->freqshift_tilde_12_h_biquad5_y2 * b2);
    this->freqshift_tilde_12_h_biquad5_x2 = this->freqshift_tilde_12_h_biquad5_x1;
    this->freqshift_tilde_12_h_biquad5_x1 = x;
    this->freqshift_tilde_12_h_biquad5_y2 = this->freqshift_tilde_12_h_biquad5_y1;
    this->freqshift_tilde_12_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad5_clear() {
    this->freqshift_tilde_12_h_biquad5_reset();
}

void freqshift_tilde_12_h_biquad5_reset() {
    this->freqshift_tilde_12_h_biquad5_x1 = 0;
    this->freqshift_tilde_12_h_biquad5_x2 = 0;
    this->freqshift_tilde_12_h_biquad5_y1 = 0;
    this->freqshift_tilde_12_h_biquad5_y2 = 0;
}

void freqshift_tilde_12_h_biquad5_dspsetup() {
    this->freqshift_tilde_12_h_biquad5_reset();
}

number freqshift_tilde_12_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_12_h_biquad6_x1 * a1 + this->freqshift_tilde_12_h_biquad6_x2 * 1 - (this->freqshift_tilde_12_h_biquad6_y1 * b1 + this->freqshift_tilde_12_h_biquad6_y2 * b2);
    this->freqshift_tilde_12_h_biquad6_x2 = this->freqshift_tilde_12_h_biquad6_x1;
    this->freqshift_tilde_12_h_biquad6_x1 = x;
    this->freqshift_tilde_12_h_biquad6_y2 = this->freqshift_tilde_12_h_biquad6_y1;
    this->freqshift_tilde_12_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_12_h_biquad6_clear() {
    this->freqshift_tilde_12_h_biquad6_reset();
}

void freqshift_tilde_12_h_biquad6_reset() {
    this->freqshift_tilde_12_h_biquad6_x1 = 0;
    this->freqshift_tilde_12_h_biquad6_x2 = 0;
    this->freqshift_tilde_12_h_biquad6_y1 = 0;
    this->freqshift_tilde_12_h_biquad6_y2 = 0;
}

void freqshift_tilde_12_h_biquad6_dspsetup() {
    this->freqshift_tilde_12_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_12_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_12_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_12_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_12_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_12_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_12_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_12_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_12_h_clear() {
    this->freqshift_tilde_12_h_reset();
}

void freqshift_tilde_12_h_reset() {
    this->freqshift_tilde_12_h_biquad1_reset();
    this->freqshift_tilde_12_h_biquad2_reset();
    this->freqshift_tilde_12_h_biquad3_reset();
    this->freqshift_tilde_12_h_biquad4_reset();
    this->freqshift_tilde_12_h_biquad5_reset();
    this->freqshift_tilde_12_h_biquad6_reset();
}

void freqshift_tilde_12_h_dspsetup() {
    this->freqshift_tilde_12_h_reset();
}

number freqshift_tilde_12_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_12_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_12_p_conv;

    if (this->freqshift_tilde_12_p_currentPhase < 0.)
        this->freqshift_tilde_12_p_currentPhase = 1. + this->freqshift_tilde_12_p_currentPhase;

    if (this->freqshift_tilde_12_p_currentPhase > 1.)
        this->freqshift_tilde_12_p_currentPhase = this->freqshift_tilde_12_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_12_p_currentPhase;
    this->freqshift_tilde_12_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_12_p_reset() {
    this->freqshift_tilde_12_p_currentPhase = 0;
}

void freqshift_tilde_12_p_dspsetup() {
    this->freqshift_tilde_12_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_12_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_12_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_12_setupDone = true;
    this->freqshift_tilde_12_h_biquad1_dspsetup();
    this->freqshift_tilde_12_h_biquad2_dspsetup();
    this->freqshift_tilde_12_h_biquad3_dspsetup();
    this->freqshift_tilde_12_h_biquad4_dspsetup();
    this->freqshift_tilde_12_h_biquad5_dspsetup();
    this->freqshift_tilde_12_h_biquad6_dspsetup();
    this->freqshift_tilde_12_h_dspsetup();
    this->freqshift_tilde_12_p_dspsetup();
}

void param_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_16_value;
}

void param_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_16_value_set(preset["value"]);
}

void param_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_17_value;
}

void param_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_17_value_set(preset["value"]);
}

number gaintilde_14_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_14_ramp_d_prev);
    this->gaintilde_14_ramp_d_prev = x;
    return temp;
}

void gaintilde_14_ramp_d_dspsetup() {
    this->gaintilde_14_ramp_d_reset();
}

void gaintilde_14_ramp_d_reset() {
    this->gaintilde_14_ramp_d_prev = 0;
}

number gaintilde_14_ramp_next(number x, number up, number down) {
    if (this->gaintilde_14_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_14_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_14_ramp_index = _up;
            this->gaintilde_14_ramp_increment = (x - this->gaintilde_14_ramp_prev) / _up;
        } else if (x < this->gaintilde_14_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_14_ramp_index = _down;
            this->gaintilde_14_ramp_increment = (x - this->gaintilde_14_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_14_ramp_index > 0) {
        this->gaintilde_14_ramp_prev += this->gaintilde_14_ramp_increment;
        this->gaintilde_14_ramp_index -= 1;
    } else {
        this->gaintilde_14_ramp_prev = x;
    }

    return this->gaintilde_14_ramp_prev;
}

void gaintilde_14_ramp_reset() {
    this->gaintilde_14_ramp_prev = 0;
    this->gaintilde_14_ramp_index = 0;
    this->gaintilde_14_ramp_increment = 0;
    this->gaintilde_14_ramp_d_reset();
}

void gaintilde_14_init() {
    this->gaintilde_14_loginc = rnbo_log(1.072);
    this->gaintilde_14_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_14_loginc));
}

void gaintilde_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_14_value;
}

void gaintilde_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_14_value_set(preset["value"]);
}

void gaintilde_14_dspsetup(bool force) {
    if ((bool)(this->gaintilde_14_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_14_setupDone = true;
    this->gaintilde_14_ramp_d_dspsetup();
}

number gaintilde_15_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_15_ramp_d_prev);
    this->gaintilde_15_ramp_d_prev = x;
    return temp;
}

void gaintilde_15_ramp_d_dspsetup() {
    this->gaintilde_15_ramp_d_reset();
}

void gaintilde_15_ramp_d_reset() {
    this->gaintilde_15_ramp_d_prev = 0;
}

number gaintilde_15_ramp_next(number x, number up, number down) {
    if (this->gaintilde_15_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_15_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_15_ramp_index = _up;
            this->gaintilde_15_ramp_increment = (x - this->gaintilde_15_ramp_prev) / _up;
        } else if (x < this->gaintilde_15_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_15_ramp_index = _down;
            this->gaintilde_15_ramp_increment = (x - this->gaintilde_15_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_15_ramp_index > 0) {
        this->gaintilde_15_ramp_prev += this->gaintilde_15_ramp_increment;
        this->gaintilde_15_ramp_index -= 1;
    } else {
        this->gaintilde_15_ramp_prev = x;
    }

    return this->gaintilde_15_ramp_prev;
}

void gaintilde_15_ramp_reset() {
    this->gaintilde_15_ramp_prev = 0;
    this->gaintilde_15_ramp_index = 0;
    this->gaintilde_15_ramp_increment = 0;
    this->gaintilde_15_ramp_d_reset();
}

void gaintilde_15_init() {
    this->gaintilde_15_loginc = rnbo_log(1.072);
    this->gaintilde_15_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_15_loginc));
}

void gaintilde_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_15_value;
}

void gaintilde_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_15_value_set(preset["value"]);
}

void gaintilde_15_dspsetup(bool force) {
    if ((bool)(this->gaintilde_15_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_15_setupDone = true;
    this->gaintilde_15_ramp_d_dspsetup();
}

number gaintilde_16_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_16_ramp_d_prev);
    this->gaintilde_16_ramp_d_prev = x;
    return temp;
}

void gaintilde_16_ramp_d_dspsetup() {
    this->gaintilde_16_ramp_d_reset();
}

void gaintilde_16_ramp_d_reset() {
    this->gaintilde_16_ramp_d_prev = 0;
}

number gaintilde_16_ramp_next(number x, number up, number down) {
    if (this->gaintilde_16_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_16_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_16_ramp_index = _up;
            this->gaintilde_16_ramp_increment = (x - this->gaintilde_16_ramp_prev) / _up;
        } else if (x < this->gaintilde_16_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_16_ramp_index = _down;
            this->gaintilde_16_ramp_increment = (x - this->gaintilde_16_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_16_ramp_index > 0) {
        this->gaintilde_16_ramp_prev += this->gaintilde_16_ramp_increment;
        this->gaintilde_16_ramp_index -= 1;
    } else {
        this->gaintilde_16_ramp_prev = x;
    }

    return this->gaintilde_16_ramp_prev;
}

void gaintilde_16_ramp_reset() {
    this->gaintilde_16_ramp_prev = 0;
    this->gaintilde_16_ramp_index = 0;
    this->gaintilde_16_ramp_increment = 0;
    this->gaintilde_16_ramp_d_reset();
}

void gaintilde_16_init() {
    this->gaintilde_16_loginc = rnbo_log(1.072);
    this->gaintilde_16_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_16_loginc));
}

void gaintilde_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_16_value;
}

void gaintilde_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_16_value_set(preset["value"]);
}

void gaintilde_16_dspsetup(bool force) {
    if ((bool)(this->gaintilde_16_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_16_setupDone = true;
    this->gaintilde_16_ramp_d_dspsetup();
}

number freqshift_tilde_13_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad1_x1 * a1 + this->freqshift_tilde_13_h_biquad1_x2 * 1 - (this->freqshift_tilde_13_h_biquad1_y1 * b1 + this->freqshift_tilde_13_h_biquad1_y2 * b2);
    this->freqshift_tilde_13_h_biquad1_x2 = this->freqshift_tilde_13_h_biquad1_x1;
    this->freqshift_tilde_13_h_biquad1_x1 = x;
    this->freqshift_tilde_13_h_biquad1_y2 = this->freqshift_tilde_13_h_biquad1_y1;
    this->freqshift_tilde_13_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad1_clear() {
    this->freqshift_tilde_13_h_biquad1_reset();
}

void freqshift_tilde_13_h_biquad1_reset() {
    this->freqshift_tilde_13_h_biquad1_x1 = 0;
    this->freqshift_tilde_13_h_biquad1_x2 = 0;
    this->freqshift_tilde_13_h_biquad1_y1 = 0;
    this->freqshift_tilde_13_h_biquad1_y2 = 0;
}

void freqshift_tilde_13_h_biquad1_dspsetup() {
    this->freqshift_tilde_13_h_biquad1_reset();
}

number freqshift_tilde_13_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad2_x1 * a1 + this->freqshift_tilde_13_h_biquad2_x2 * 1 - (this->freqshift_tilde_13_h_biquad2_y1 * b1 + this->freqshift_tilde_13_h_biquad2_y2 * b2);
    this->freqshift_tilde_13_h_biquad2_x2 = this->freqshift_tilde_13_h_biquad2_x1;
    this->freqshift_tilde_13_h_biquad2_x1 = x;
    this->freqshift_tilde_13_h_biquad2_y2 = this->freqshift_tilde_13_h_biquad2_y1;
    this->freqshift_tilde_13_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad2_clear() {
    this->freqshift_tilde_13_h_biquad2_reset();
}

void freqshift_tilde_13_h_biquad2_reset() {
    this->freqshift_tilde_13_h_biquad2_x1 = 0;
    this->freqshift_tilde_13_h_biquad2_x2 = 0;
    this->freqshift_tilde_13_h_biquad2_y1 = 0;
    this->freqshift_tilde_13_h_biquad2_y2 = 0;
}

void freqshift_tilde_13_h_biquad2_dspsetup() {
    this->freqshift_tilde_13_h_biquad2_reset();
}

number freqshift_tilde_13_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad3_x1 * a1 + this->freqshift_tilde_13_h_biquad3_x2 * 1 - (this->freqshift_tilde_13_h_biquad3_y1 * b1 + this->freqshift_tilde_13_h_biquad3_y2 * b2);
    this->freqshift_tilde_13_h_biquad3_x2 = this->freqshift_tilde_13_h_biquad3_x1;
    this->freqshift_tilde_13_h_biquad3_x1 = x;
    this->freqshift_tilde_13_h_biquad3_y2 = this->freqshift_tilde_13_h_biquad3_y1;
    this->freqshift_tilde_13_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad3_clear() {
    this->freqshift_tilde_13_h_biquad3_reset();
}

void freqshift_tilde_13_h_biquad3_reset() {
    this->freqshift_tilde_13_h_biquad3_x1 = 0;
    this->freqshift_tilde_13_h_biquad3_x2 = 0;
    this->freqshift_tilde_13_h_biquad3_y1 = 0;
    this->freqshift_tilde_13_h_biquad3_y2 = 0;
}

void freqshift_tilde_13_h_biquad3_dspsetup() {
    this->freqshift_tilde_13_h_biquad3_reset();
}

number freqshift_tilde_13_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad4_x1 * a1 + this->freqshift_tilde_13_h_biquad4_x2 * 1 - (this->freqshift_tilde_13_h_biquad4_y1 * b1 + this->freqshift_tilde_13_h_biquad4_y2 * b2);
    this->freqshift_tilde_13_h_biquad4_x2 = this->freqshift_tilde_13_h_biquad4_x1;
    this->freqshift_tilde_13_h_biquad4_x1 = x;
    this->freqshift_tilde_13_h_biquad4_y2 = this->freqshift_tilde_13_h_biquad4_y1;
    this->freqshift_tilde_13_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad4_clear() {
    this->freqshift_tilde_13_h_biquad4_reset();
}

void freqshift_tilde_13_h_biquad4_reset() {
    this->freqshift_tilde_13_h_biquad4_x1 = 0;
    this->freqshift_tilde_13_h_biquad4_x2 = 0;
    this->freqshift_tilde_13_h_biquad4_y1 = 0;
    this->freqshift_tilde_13_h_biquad4_y2 = 0;
}

void freqshift_tilde_13_h_biquad4_dspsetup() {
    this->freqshift_tilde_13_h_biquad4_reset();
}

number freqshift_tilde_13_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad5_x1 * a1 + this->freqshift_tilde_13_h_biquad5_x2 * 1 - (this->freqshift_tilde_13_h_biquad5_y1 * b1 + this->freqshift_tilde_13_h_biquad5_y2 * b2);
    this->freqshift_tilde_13_h_biquad5_x2 = this->freqshift_tilde_13_h_biquad5_x1;
    this->freqshift_tilde_13_h_biquad5_x1 = x;
    this->freqshift_tilde_13_h_biquad5_y2 = this->freqshift_tilde_13_h_biquad5_y1;
    this->freqshift_tilde_13_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad5_clear() {
    this->freqshift_tilde_13_h_biquad5_reset();
}

void freqshift_tilde_13_h_biquad5_reset() {
    this->freqshift_tilde_13_h_biquad5_x1 = 0;
    this->freqshift_tilde_13_h_biquad5_x2 = 0;
    this->freqshift_tilde_13_h_biquad5_y1 = 0;
    this->freqshift_tilde_13_h_biquad5_y2 = 0;
}

void freqshift_tilde_13_h_biquad5_dspsetup() {
    this->freqshift_tilde_13_h_biquad5_reset();
}

number freqshift_tilde_13_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_13_h_biquad6_x1 * a1 + this->freqshift_tilde_13_h_biquad6_x2 * 1 - (this->freqshift_tilde_13_h_biquad6_y1 * b1 + this->freqshift_tilde_13_h_biquad6_y2 * b2);
    this->freqshift_tilde_13_h_biquad6_x2 = this->freqshift_tilde_13_h_biquad6_x1;
    this->freqshift_tilde_13_h_biquad6_x1 = x;
    this->freqshift_tilde_13_h_biquad6_y2 = this->freqshift_tilde_13_h_biquad6_y1;
    this->freqshift_tilde_13_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_13_h_biquad6_clear() {
    this->freqshift_tilde_13_h_biquad6_reset();
}

void freqshift_tilde_13_h_biquad6_reset() {
    this->freqshift_tilde_13_h_biquad6_x1 = 0;
    this->freqshift_tilde_13_h_biquad6_x2 = 0;
    this->freqshift_tilde_13_h_biquad6_y1 = 0;
    this->freqshift_tilde_13_h_biquad6_y2 = 0;
}

void freqshift_tilde_13_h_biquad6_dspsetup() {
    this->freqshift_tilde_13_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_13_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_13_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_13_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_13_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_13_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_13_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_13_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_13_h_clear() {
    this->freqshift_tilde_13_h_reset();
}

void freqshift_tilde_13_h_reset() {
    this->freqshift_tilde_13_h_biquad1_reset();
    this->freqshift_tilde_13_h_biquad2_reset();
    this->freqshift_tilde_13_h_biquad3_reset();
    this->freqshift_tilde_13_h_biquad4_reset();
    this->freqshift_tilde_13_h_biquad5_reset();
    this->freqshift_tilde_13_h_biquad6_reset();
}

void freqshift_tilde_13_h_dspsetup() {
    this->freqshift_tilde_13_h_reset();
}

number freqshift_tilde_13_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_13_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_13_p_conv;

    if (this->freqshift_tilde_13_p_currentPhase < 0.)
        this->freqshift_tilde_13_p_currentPhase = 1. + this->freqshift_tilde_13_p_currentPhase;

    if (this->freqshift_tilde_13_p_currentPhase > 1.)
        this->freqshift_tilde_13_p_currentPhase = this->freqshift_tilde_13_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_13_p_currentPhase;
    this->freqshift_tilde_13_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_13_p_reset() {
    this->freqshift_tilde_13_p_currentPhase = 0;
}

void freqshift_tilde_13_p_dspsetup() {
    this->freqshift_tilde_13_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_13_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_13_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_13_setupDone = true;
    this->freqshift_tilde_13_h_biquad1_dspsetup();
    this->freqshift_tilde_13_h_biquad2_dspsetup();
    this->freqshift_tilde_13_h_biquad3_dspsetup();
    this->freqshift_tilde_13_h_biquad4_dspsetup();
    this->freqshift_tilde_13_h_biquad5_dspsetup();
    this->freqshift_tilde_13_h_biquad6_dspsetup();
    this->freqshift_tilde_13_h_dspsetup();
    this->freqshift_tilde_13_p_dspsetup();
}

number freqshift_tilde_14_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad1_x1 * a1 + this->freqshift_tilde_14_h_biquad1_x2 * 1 - (this->freqshift_tilde_14_h_biquad1_y1 * b1 + this->freqshift_tilde_14_h_biquad1_y2 * b2);
    this->freqshift_tilde_14_h_biquad1_x2 = this->freqshift_tilde_14_h_biquad1_x1;
    this->freqshift_tilde_14_h_biquad1_x1 = x;
    this->freqshift_tilde_14_h_biquad1_y2 = this->freqshift_tilde_14_h_biquad1_y1;
    this->freqshift_tilde_14_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad1_clear() {
    this->freqshift_tilde_14_h_biquad1_reset();
}

void freqshift_tilde_14_h_biquad1_reset() {
    this->freqshift_tilde_14_h_biquad1_x1 = 0;
    this->freqshift_tilde_14_h_biquad1_x2 = 0;
    this->freqshift_tilde_14_h_biquad1_y1 = 0;
    this->freqshift_tilde_14_h_biquad1_y2 = 0;
}

void freqshift_tilde_14_h_biquad1_dspsetup() {
    this->freqshift_tilde_14_h_biquad1_reset();
}

number freqshift_tilde_14_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad2_x1 * a1 + this->freqshift_tilde_14_h_biquad2_x2 * 1 - (this->freqshift_tilde_14_h_biquad2_y1 * b1 + this->freqshift_tilde_14_h_biquad2_y2 * b2);
    this->freqshift_tilde_14_h_biquad2_x2 = this->freqshift_tilde_14_h_biquad2_x1;
    this->freqshift_tilde_14_h_biquad2_x1 = x;
    this->freqshift_tilde_14_h_biquad2_y2 = this->freqshift_tilde_14_h_biquad2_y1;
    this->freqshift_tilde_14_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad2_clear() {
    this->freqshift_tilde_14_h_biquad2_reset();
}

void freqshift_tilde_14_h_biquad2_reset() {
    this->freqshift_tilde_14_h_biquad2_x1 = 0;
    this->freqshift_tilde_14_h_biquad2_x2 = 0;
    this->freqshift_tilde_14_h_biquad2_y1 = 0;
    this->freqshift_tilde_14_h_biquad2_y2 = 0;
}

void freqshift_tilde_14_h_biquad2_dspsetup() {
    this->freqshift_tilde_14_h_biquad2_reset();
}

number freqshift_tilde_14_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad3_x1 * a1 + this->freqshift_tilde_14_h_biquad3_x2 * 1 - (this->freqshift_tilde_14_h_biquad3_y1 * b1 + this->freqshift_tilde_14_h_biquad3_y2 * b2);
    this->freqshift_tilde_14_h_biquad3_x2 = this->freqshift_tilde_14_h_biquad3_x1;
    this->freqshift_tilde_14_h_biquad3_x1 = x;
    this->freqshift_tilde_14_h_biquad3_y2 = this->freqshift_tilde_14_h_biquad3_y1;
    this->freqshift_tilde_14_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad3_clear() {
    this->freqshift_tilde_14_h_biquad3_reset();
}

void freqshift_tilde_14_h_biquad3_reset() {
    this->freqshift_tilde_14_h_biquad3_x1 = 0;
    this->freqshift_tilde_14_h_biquad3_x2 = 0;
    this->freqshift_tilde_14_h_biquad3_y1 = 0;
    this->freqshift_tilde_14_h_biquad3_y2 = 0;
}

void freqshift_tilde_14_h_biquad3_dspsetup() {
    this->freqshift_tilde_14_h_biquad3_reset();
}

number freqshift_tilde_14_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad4_x1 * a1 + this->freqshift_tilde_14_h_biquad4_x2 * 1 - (this->freqshift_tilde_14_h_biquad4_y1 * b1 + this->freqshift_tilde_14_h_biquad4_y2 * b2);
    this->freqshift_tilde_14_h_biquad4_x2 = this->freqshift_tilde_14_h_biquad4_x1;
    this->freqshift_tilde_14_h_biquad4_x1 = x;
    this->freqshift_tilde_14_h_biquad4_y2 = this->freqshift_tilde_14_h_biquad4_y1;
    this->freqshift_tilde_14_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad4_clear() {
    this->freqshift_tilde_14_h_biquad4_reset();
}

void freqshift_tilde_14_h_biquad4_reset() {
    this->freqshift_tilde_14_h_biquad4_x1 = 0;
    this->freqshift_tilde_14_h_biquad4_x2 = 0;
    this->freqshift_tilde_14_h_biquad4_y1 = 0;
    this->freqshift_tilde_14_h_biquad4_y2 = 0;
}

void freqshift_tilde_14_h_biquad4_dspsetup() {
    this->freqshift_tilde_14_h_biquad4_reset();
}

number freqshift_tilde_14_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad5_x1 * a1 + this->freqshift_tilde_14_h_biquad5_x2 * 1 - (this->freqshift_tilde_14_h_biquad5_y1 * b1 + this->freqshift_tilde_14_h_biquad5_y2 * b2);
    this->freqshift_tilde_14_h_biquad5_x2 = this->freqshift_tilde_14_h_biquad5_x1;
    this->freqshift_tilde_14_h_biquad5_x1 = x;
    this->freqshift_tilde_14_h_biquad5_y2 = this->freqshift_tilde_14_h_biquad5_y1;
    this->freqshift_tilde_14_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad5_clear() {
    this->freqshift_tilde_14_h_biquad5_reset();
}

void freqshift_tilde_14_h_biquad5_reset() {
    this->freqshift_tilde_14_h_biquad5_x1 = 0;
    this->freqshift_tilde_14_h_biquad5_x2 = 0;
    this->freqshift_tilde_14_h_biquad5_y1 = 0;
    this->freqshift_tilde_14_h_biquad5_y2 = 0;
}

void freqshift_tilde_14_h_biquad5_dspsetup() {
    this->freqshift_tilde_14_h_biquad5_reset();
}

number freqshift_tilde_14_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_14_h_biquad6_x1 * a1 + this->freqshift_tilde_14_h_biquad6_x2 * 1 - (this->freqshift_tilde_14_h_biquad6_y1 * b1 + this->freqshift_tilde_14_h_biquad6_y2 * b2);
    this->freqshift_tilde_14_h_biquad6_x2 = this->freqshift_tilde_14_h_biquad6_x1;
    this->freqshift_tilde_14_h_biquad6_x1 = x;
    this->freqshift_tilde_14_h_biquad6_y2 = this->freqshift_tilde_14_h_biquad6_y1;
    this->freqshift_tilde_14_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_14_h_biquad6_clear() {
    this->freqshift_tilde_14_h_biquad6_reset();
}

void freqshift_tilde_14_h_biquad6_reset() {
    this->freqshift_tilde_14_h_biquad6_x1 = 0;
    this->freqshift_tilde_14_h_biquad6_x2 = 0;
    this->freqshift_tilde_14_h_biquad6_y1 = 0;
    this->freqshift_tilde_14_h_biquad6_y2 = 0;
}

void freqshift_tilde_14_h_biquad6_dspsetup() {
    this->freqshift_tilde_14_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_14_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_14_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_14_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_14_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_14_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_14_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_14_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_14_h_clear() {
    this->freqshift_tilde_14_h_reset();
}

void freqshift_tilde_14_h_reset() {
    this->freqshift_tilde_14_h_biquad1_reset();
    this->freqshift_tilde_14_h_biquad2_reset();
    this->freqshift_tilde_14_h_biquad3_reset();
    this->freqshift_tilde_14_h_biquad4_reset();
    this->freqshift_tilde_14_h_biquad5_reset();
    this->freqshift_tilde_14_h_biquad6_reset();
}

void freqshift_tilde_14_h_dspsetup() {
    this->freqshift_tilde_14_h_reset();
}

number freqshift_tilde_14_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_14_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_14_p_conv;

    if (this->freqshift_tilde_14_p_currentPhase < 0.)
        this->freqshift_tilde_14_p_currentPhase = 1. + this->freqshift_tilde_14_p_currentPhase;

    if (this->freqshift_tilde_14_p_currentPhase > 1.)
        this->freqshift_tilde_14_p_currentPhase = this->freqshift_tilde_14_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_14_p_currentPhase;
    this->freqshift_tilde_14_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_14_p_reset() {
    this->freqshift_tilde_14_p_currentPhase = 0;
}

void freqshift_tilde_14_p_dspsetup() {
    this->freqshift_tilde_14_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_14_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_14_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_14_setupDone = true;
    this->freqshift_tilde_14_h_biquad1_dspsetup();
    this->freqshift_tilde_14_h_biquad2_dspsetup();
    this->freqshift_tilde_14_h_biquad3_dspsetup();
    this->freqshift_tilde_14_h_biquad4_dspsetup();
    this->freqshift_tilde_14_h_biquad5_dspsetup();
    this->freqshift_tilde_14_h_biquad6_dspsetup();
    this->freqshift_tilde_14_h_dspsetup();
    this->freqshift_tilde_14_p_dspsetup();
}

number gaintilde_17_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_17_ramp_d_prev);
    this->gaintilde_17_ramp_d_prev = x;
    return temp;
}

void gaintilde_17_ramp_d_dspsetup() {
    this->gaintilde_17_ramp_d_reset();
}

void gaintilde_17_ramp_d_reset() {
    this->gaintilde_17_ramp_d_prev = 0;
}

number gaintilde_17_ramp_next(number x, number up, number down) {
    if (this->gaintilde_17_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_17_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_17_ramp_index = _up;
            this->gaintilde_17_ramp_increment = (x - this->gaintilde_17_ramp_prev) / _up;
        } else if (x < this->gaintilde_17_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_17_ramp_index = _down;
            this->gaintilde_17_ramp_increment = (x - this->gaintilde_17_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_17_ramp_index > 0) {
        this->gaintilde_17_ramp_prev += this->gaintilde_17_ramp_increment;
        this->gaintilde_17_ramp_index -= 1;
    } else {
        this->gaintilde_17_ramp_prev = x;
    }

    return this->gaintilde_17_ramp_prev;
}

void gaintilde_17_ramp_reset() {
    this->gaintilde_17_ramp_prev = 0;
    this->gaintilde_17_ramp_index = 0;
    this->gaintilde_17_ramp_increment = 0;
    this->gaintilde_17_ramp_d_reset();
}

void gaintilde_17_init() {
    this->gaintilde_17_loginc = rnbo_log(1.072);
    this->gaintilde_17_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_17_loginc));
}

void gaintilde_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_17_value;
}

void gaintilde_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_17_value_set(preset["value"]);
}

void gaintilde_17_dspsetup(bool force) {
    if ((bool)(this->gaintilde_17_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_17_setupDone = true;
    this->gaintilde_17_ramp_d_dspsetup();
}

number freqshift_tilde_15_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad1_x1 * a1 + this->freqshift_tilde_15_h_biquad1_x2 * 1 - (this->freqshift_tilde_15_h_biquad1_y1 * b1 + this->freqshift_tilde_15_h_biquad1_y2 * b2);
    this->freqshift_tilde_15_h_biquad1_x2 = this->freqshift_tilde_15_h_biquad1_x1;
    this->freqshift_tilde_15_h_biquad1_x1 = x;
    this->freqshift_tilde_15_h_biquad1_y2 = this->freqshift_tilde_15_h_biquad1_y1;
    this->freqshift_tilde_15_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad1_clear() {
    this->freqshift_tilde_15_h_biquad1_reset();
}

void freqshift_tilde_15_h_biquad1_reset() {
    this->freqshift_tilde_15_h_biquad1_x1 = 0;
    this->freqshift_tilde_15_h_biquad1_x2 = 0;
    this->freqshift_tilde_15_h_biquad1_y1 = 0;
    this->freqshift_tilde_15_h_biquad1_y2 = 0;
}

void freqshift_tilde_15_h_biquad1_dspsetup() {
    this->freqshift_tilde_15_h_biquad1_reset();
}

number freqshift_tilde_15_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad2_x1 * a1 + this->freqshift_tilde_15_h_biquad2_x2 * 1 - (this->freqshift_tilde_15_h_biquad2_y1 * b1 + this->freqshift_tilde_15_h_biquad2_y2 * b2);
    this->freqshift_tilde_15_h_biquad2_x2 = this->freqshift_tilde_15_h_biquad2_x1;
    this->freqshift_tilde_15_h_biquad2_x1 = x;
    this->freqshift_tilde_15_h_biquad2_y2 = this->freqshift_tilde_15_h_biquad2_y1;
    this->freqshift_tilde_15_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad2_clear() {
    this->freqshift_tilde_15_h_biquad2_reset();
}

void freqshift_tilde_15_h_biquad2_reset() {
    this->freqshift_tilde_15_h_biquad2_x1 = 0;
    this->freqshift_tilde_15_h_biquad2_x2 = 0;
    this->freqshift_tilde_15_h_biquad2_y1 = 0;
    this->freqshift_tilde_15_h_biquad2_y2 = 0;
}

void freqshift_tilde_15_h_biquad2_dspsetup() {
    this->freqshift_tilde_15_h_biquad2_reset();
}

number freqshift_tilde_15_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad3_x1 * a1 + this->freqshift_tilde_15_h_biquad3_x2 * 1 - (this->freqshift_tilde_15_h_biquad3_y1 * b1 + this->freqshift_tilde_15_h_biquad3_y2 * b2);
    this->freqshift_tilde_15_h_biquad3_x2 = this->freqshift_tilde_15_h_biquad3_x1;
    this->freqshift_tilde_15_h_biquad3_x1 = x;
    this->freqshift_tilde_15_h_biquad3_y2 = this->freqshift_tilde_15_h_biquad3_y1;
    this->freqshift_tilde_15_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad3_clear() {
    this->freqshift_tilde_15_h_biquad3_reset();
}

void freqshift_tilde_15_h_biquad3_reset() {
    this->freqshift_tilde_15_h_biquad3_x1 = 0;
    this->freqshift_tilde_15_h_biquad3_x2 = 0;
    this->freqshift_tilde_15_h_biquad3_y1 = 0;
    this->freqshift_tilde_15_h_biquad3_y2 = 0;
}

void freqshift_tilde_15_h_biquad3_dspsetup() {
    this->freqshift_tilde_15_h_biquad3_reset();
}

number freqshift_tilde_15_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad4_x1 * a1 + this->freqshift_tilde_15_h_biquad4_x2 * 1 - (this->freqshift_tilde_15_h_biquad4_y1 * b1 + this->freqshift_tilde_15_h_biquad4_y2 * b2);
    this->freqshift_tilde_15_h_biquad4_x2 = this->freqshift_tilde_15_h_biquad4_x1;
    this->freqshift_tilde_15_h_biquad4_x1 = x;
    this->freqshift_tilde_15_h_biquad4_y2 = this->freqshift_tilde_15_h_biquad4_y1;
    this->freqshift_tilde_15_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad4_clear() {
    this->freqshift_tilde_15_h_biquad4_reset();
}

void freqshift_tilde_15_h_biquad4_reset() {
    this->freqshift_tilde_15_h_biquad4_x1 = 0;
    this->freqshift_tilde_15_h_biquad4_x2 = 0;
    this->freqshift_tilde_15_h_biquad4_y1 = 0;
    this->freqshift_tilde_15_h_biquad4_y2 = 0;
}

void freqshift_tilde_15_h_biquad4_dspsetup() {
    this->freqshift_tilde_15_h_biquad4_reset();
}

number freqshift_tilde_15_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad5_x1 * a1 + this->freqshift_tilde_15_h_biquad5_x2 * 1 - (this->freqshift_tilde_15_h_biquad5_y1 * b1 + this->freqshift_tilde_15_h_biquad5_y2 * b2);
    this->freqshift_tilde_15_h_biquad5_x2 = this->freqshift_tilde_15_h_biquad5_x1;
    this->freqshift_tilde_15_h_biquad5_x1 = x;
    this->freqshift_tilde_15_h_biquad5_y2 = this->freqshift_tilde_15_h_biquad5_y1;
    this->freqshift_tilde_15_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad5_clear() {
    this->freqshift_tilde_15_h_biquad5_reset();
}

void freqshift_tilde_15_h_biquad5_reset() {
    this->freqshift_tilde_15_h_biquad5_x1 = 0;
    this->freqshift_tilde_15_h_biquad5_x2 = 0;
    this->freqshift_tilde_15_h_biquad5_y1 = 0;
    this->freqshift_tilde_15_h_biquad5_y2 = 0;
}

void freqshift_tilde_15_h_biquad5_dspsetup() {
    this->freqshift_tilde_15_h_biquad5_reset();
}

number freqshift_tilde_15_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_15_h_biquad6_x1 * a1 + this->freqshift_tilde_15_h_biquad6_x2 * 1 - (this->freqshift_tilde_15_h_biquad6_y1 * b1 + this->freqshift_tilde_15_h_biquad6_y2 * b2);
    this->freqshift_tilde_15_h_biquad6_x2 = this->freqshift_tilde_15_h_biquad6_x1;
    this->freqshift_tilde_15_h_biquad6_x1 = x;
    this->freqshift_tilde_15_h_biquad6_y2 = this->freqshift_tilde_15_h_biquad6_y1;
    this->freqshift_tilde_15_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_15_h_biquad6_clear() {
    this->freqshift_tilde_15_h_biquad6_reset();
}

void freqshift_tilde_15_h_biquad6_reset() {
    this->freqshift_tilde_15_h_biquad6_x1 = 0;
    this->freqshift_tilde_15_h_biquad6_x2 = 0;
    this->freqshift_tilde_15_h_biquad6_y1 = 0;
    this->freqshift_tilde_15_h_biquad6_y2 = 0;
}

void freqshift_tilde_15_h_biquad6_dspsetup() {
    this->freqshift_tilde_15_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_15_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_15_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_15_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_15_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_15_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_15_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_15_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_15_h_clear() {
    this->freqshift_tilde_15_h_reset();
}

void freqshift_tilde_15_h_reset() {
    this->freqshift_tilde_15_h_biquad1_reset();
    this->freqshift_tilde_15_h_biquad2_reset();
    this->freqshift_tilde_15_h_biquad3_reset();
    this->freqshift_tilde_15_h_biquad4_reset();
    this->freqshift_tilde_15_h_biquad5_reset();
    this->freqshift_tilde_15_h_biquad6_reset();
}

void freqshift_tilde_15_h_dspsetup() {
    this->freqshift_tilde_15_h_reset();
}

number freqshift_tilde_15_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_15_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_15_p_conv;

    if (this->freqshift_tilde_15_p_currentPhase < 0.)
        this->freqshift_tilde_15_p_currentPhase = 1. + this->freqshift_tilde_15_p_currentPhase;

    if (this->freqshift_tilde_15_p_currentPhase > 1.)
        this->freqshift_tilde_15_p_currentPhase = this->freqshift_tilde_15_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_15_p_currentPhase;
    this->freqshift_tilde_15_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_15_p_reset() {
    this->freqshift_tilde_15_p_currentPhase = 0;
}

void freqshift_tilde_15_p_dspsetup() {
    this->freqshift_tilde_15_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_15_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_15_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_15_setupDone = true;
    this->freqshift_tilde_15_h_biquad1_dspsetup();
    this->freqshift_tilde_15_h_biquad2_dspsetup();
    this->freqshift_tilde_15_h_biquad3_dspsetup();
    this->freqshift_tilde_15_h_biquad4_dspsetup();
    this->freqshift_tilde_15_h_biquad5_dspsetup();
    this->freqshift_tilde_15_h_biquad6_dspsetup();
    this->freqshift_tilde_15_h_dspsetup();
    this->freqshift_tilde_15_p_dspsetup();
}

number freqshift_tilde_16_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad1_x1 * a1 + this->freqshift_tilde_16_h_biquad1_x2 * 1 - (this->freqshift_tilde_16_h_biquad1_y1 * b1 + this->freqshift_tilde_16_h_biquad1_y2 * b2);
    this->freqshift_tilde_16_h_biquad1_x2 = this->freqshift_tilde_16_h_biquad1_x1;
    this->freqshift_tilde_16_h_biquad1_x1 = x;
    this->freqshift_tilde_16_h_biquad1_y2 = this->freqshift_tilde_16_h_biquad1_y1;
    this->freqshift_tilde_16_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad1_clear() {
    this->freqshift_tilde_16_h_biquad1_reset();
}

void freqshift_tilde_16_h_biquad1_reset() {
    this->freqshift_tilde_16_h_biquad1_x1 = 0;
    this->freqshift_tilde_16_h_biquad1_x2 = 0;
    this->freqshift_tilde_16_h_biquad1_y1 = 0;
    this->freqshift_tilde_16_h_biquad1_y2 = 0;
}

void freqshift_tilde_16_h_biquad1_dspsetup() {
    this->freqshift_tilde_16_h_biquad1_reset();
}

number freqshift_tilde_16_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad2_x1 * a1 + this->freqshift_tilde_16_h_biquad2_x2 * 1 - (this->freqshift_tilde_16_h_biquad2_y1 * b1 + this->freqshift_tilde_16_h_biquad2_y2 * b2);
    this->freqshift_tilde_16_h_biquad2_x2 = this->freqshift_tilde_16_h_biquad2_x1;
    this->freqshift_tilde_16_h_biquad2_x1 = x;
    this->freqshift_tilde_16_h_biquad2_y2 = this->freqshift_tilde_16_h_biquad2_y1;
    this->freqshift_tilde_16_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad2_clear() {
    this->freqshift_tilde_16_h_biquad2_reset();
}

void freqshift_tilde_16_h_biquad2_reset() {
    this->freqshift_tilde_16_h_biquad2_x1 = 0;
    this->freqshift_tilde_16_h_biquad2_x2 = 0;
    this->freqshift_tilde_16_h_biquad2_y1 = 0;
    this->freqshift_tilde_16_h_biquad2_y2 = 0;
}

void freqshift_tilde_16_h_biquad2_dspsetup() {
    this->freqshift_tilde_16_h_biquad2_reset();
}

number freqshift_tilde_16_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad3_x1 * a1 + this->freqshift_tilde_16_h_biquad3_x2 * 1 - (this->freqshift_tilde_16_h_biquad3_y1 * b1 + this->freqshift_tilde_16_h_biquad3_y2 * b2);
    this->freqshift_tilde_16_h_biquad3_x2 = this->freqshift_tilde_16_h_biquad3_x1;
    this->freqshift_tilde_16_h_biquad3_x1 = x;
    this->freqshift_tilde_16_h_biquad3_y2 = this->freqshift_tilde_16_h_biquad3_y1;
    this->freqshift_tilde_16_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad3_clear() {
    this->freqshift_tilde_16_h_biquad3_reset();
}

void freqshift_tilde_16_h_biquad3_reset() {
    this->freqshift_tilde_16_h_biquad3_x1 = 0;
    this->freqshift_tilde_16_h_biquad3_x2 = 0;
    this->freqshift_tilde_16_h_biquad3_y1 = 0;
    this->freqshift_tilde_16_h_biquad3_y2 = 0;
}

void freqshift_tilde_16_h_biquad3_dspsetup() {
    this->freqshift_tilde_16_h_biquad3_reset();
}

number freqshift_tilde_16_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad4_x1 * a1 + this->freqshift_tilde_16_h_biquad4_x2 * 1 - (this->freqshift_tilde_16_h_biquad4_y1 * b1 + this->freqshift_tilde_16_h_biquad4_y2 * b2);
    this->freqshift_tilde_16_h_biquad4_x2 = this->freqshift_tilde_16_h_biquad4_x1;
    this->freqshift_tilde_16_h_biquad4_x1 = x;
    this->freqshift_tilde_16_h_biquad4_y2 = this->freqshift_tilde_16_h_biquad4_y1;
    this->freqshift_tilde_16_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad4_clear() {
    this->freqshift_tilde_16_h_biquad4_reset();
}

void freqshift_tilde_16_h_biquad4_reset() {
    this->freqshift_tilde_16_h_biquad4_x1 = 0;
    this->freqshift_tilde_16_h_biquad4_x2 = 0;
    this->freqshift_tilde_16_h_biquad4_y1 = 0;
    this->freqshift_tilde_16_h_biquad4_y2 = 0;
}

void freqshift_tilde_16_h_biquad4_dspsetup() {
    this->freqshift_tilde_16_h_biquad4_reset();
}

number freqshift_tilde_16_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad5_x1 * a1 + this->freqshift_tilde_16_h_biquad5_x2 * 1 - (this->freqshift_tilde_16_h_biquad5_y1 * b1 + this->freqshift_tilde_16_h_biquad5_y2 * b2);
    this->freqshift_tilde_16_h_biquad5_x2 = this->freqshift_tilde_16_h_biquad5_x1;
    this->freqshift_tilde_16_h_biquad5_x1 = x;
    this->freqshift_tilde_16_h_biquad5_y2 = this->freqshift_tilde_16_h_biquad5_y1;
    this->freqshift_tilde_16_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad5_clear() {
    this->freqshift_tilde_16_h_biquad5_reset();
}

void freqshift_tilde_16_h_biquad5_reset() {
    this->freqshift_tilde_16_h_biquad5_x1 = 0;
    this->freqshift_tilde_16_h_biquad5_x2 = 0;
    this->freqshift_tilde_16_h_biquad5_y1 = 0;
    this->freqshift_tilde_16_h_biquad5_y2 = 0;
}

void freqshift_tilde_16_h_biquad5_dspsetup() {
    this->freqshift_tilde_16_h_biquad5_reset();
}

number freqshift_tilde_16_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_16_h_biquad6_x1 * a1 + this->freqshift_tilde_16_h_biquad6_x2 * 1 - (this->freqshift_tilde_16_h_biquad6_y1 * b1 + this->freqshift_tilde_16_h_biquad6_y2 * b2);
    this->freqshift_tilde_16_h_biquad6_x2 = this->freqshift_tilde_16_h_biquad6_x1;
    this->freqshift_tilde_16_h_biquad6_x1 = x;
    this->freqshift_tilde_16_h_biquad6_y2 = this->freqshift_tilde_16_h_biquad6_y1;
    this->freqshift_tilde_16_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_16_h_biquad6_clear() {
    this->freqshift_tilde_16_h_biquad6_reset();
}

void freqshift_tilde_16_h_biquad6_reset() {
    this->freqshift_tilde_16_h_biquad6_x1 = 0;
    this->freqshift_tilde_16_h_biquad6_x2 = 0;
    this->freqshift_tilde_16_h_biquad6_y1 = 0;
    this->freqshift_tilde_16_h_biquad6_y2 = 0;
}

void freqshift_tilde_16_h_biquad6_dspsetup() {
    this->freqshift_tilde_16_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_16_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_16_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_16_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_16_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_16_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_16_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_16_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_16_h_clear() {
    this->freqshift_tilde_16_h_reset();
}

void freqshift_tilde_16_h_reset() {
    this->freqshift_tilde_16_h_biquad1_reset();
    this->freqshift_tilde_16_h_biquad2_reset();
    this->freqshift_tilde_16_h_biquad3_reset();
    this->freqshift_tilde_16_h_biquad4_reset();
    this->freqshift_tilde_16_h_biquad5_reset();
    this->freqshift_tilde_16_h_biquad6_reset();
}

void freqshift_tilde_16_h_dspsetup() {
    this->freqshift_tilde_16_h_reset();
}

number freqshift_tilde_16_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_16_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_16_p_conv;

    if (this->freqshift_tilde_16_p_currentPhase < 0.)
        this->freqshift_tilde_16_p_currentPhase = 1. + this->freqshift_tilde_16_p_currentPhase;

    if (this->freqshift_tilde_16_p_currentPhase > 1.)
        this->freqshift_tilde_16_p_currentPhase = this->freqshift_tilde_16_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_16_p_currentPhase;
    this->freqshift_tilde_16_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_16_p_reset() {
    this->freqshift_tilde_16_p_currentPhase = 0;
}

void freqshift_tilde_16_p_dspsetup() {
    this->freqshift_tilde_16_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_16_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_16_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_16_setupDone = true;
    this->freqshift_tilde_16_h_biquad1_dspsetup();
    this->freqshift_tilde_16_h_biquad2_dspsetup();
    this->freqshift_tilde_16_h_biquad3_dspsetup();
    this->freqshift_tilde_16_h_biquad4_dspsetup();
    this->freqshift_tilde_16_h_biquad5_dspsetup();
    this->freqshift_tilde_16_h_biquad6_dspsetup();
    this->freqshift_tilde_16_h_dspsetup();
    this->freqshift_tilde_16_p_dspsetup();
}

number gaintilde_18_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_18_ramp_d_prev);
    this->gaintilde_18_ramp_d_prev = x;
    return temp;
}

void gaintilde_18_ramp_d_dspsetup() {
    this->gaintilde_18_ramp_d_reset();
}

void gaintilde_18_ramp_d_reset() {
    this->gaintilde_18_ramp_d_prev = 0;
}

number gaintilde_18_ramp_next(number x, number up, number down) {
    if (this->gaintilde_18_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_18_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_18_ramp_index = _up;
            this->gaintilde_18_ramp_increment = (x - this->gaintilde_18_ramp_prev) / _up;
        } else if (x < this->gaintilde_18_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_18_ramp_index = _down;
            this->gaintilde_18_ramp_increment = (x - this->gaintilde_18_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_18_ramp_index > 0) {
        this->gaintilde_18_ramp_prev += this->gaintilde_18_ramp_increment;
        this->gaintilde_18_ramp_index -= 1;
    } else {
        this->gaintilde_18_ramp_prev = x;
    }

    return this->gaintilde_18_ramp_prev;
}

void gaintilde_18_ramp_reset() {
    this->gaintilde_18_ramp_prev = 0;
    this->gaintilde_18_ramp_index = 0;
    this->gaintilde_18_ramp_increment = 0;
    this->gaintilde_18_ramp_d_reset();
}

void gaintilde_18_init() {
    this->gaintilde_18_loginc = rnbo_log(1.072);
    this->gaintilde_18_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_18_loginc));
}

void gaintilde_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_18_value;
}

void gaintilde_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_18_value_set(preset["value"]);
}

void gaintilde_18_dspsetup(bool force) {
    if ((bool)(this->gaintilde_18_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_18_setupDone = true;
    this->gaintilde_18_ramp_d_dspsetup();
}

number gaintilde_19_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_19_ramp_d_prev);
    this->gaintilde_19_ramp_d_prev = x;
    return temp;
}

void gaintilde_19_ramp_d_dspsetup() {
    this->gaintilde_19_ramp_d_reset();
}

void gaintilde_19_ramp_d_reset() {
    this->gaintilde_19_ramp_d_prev = 0;
}

number gaintilde_19_ramp_next(number x, number up, number down) {
    if (this->gaintilde_19_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_19_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_19_ramp_index = _up;
            this->gaintilde_19_ramp_increment = (x - this->gaintilde_19_ramp_prev) / _up;
        } else if (x < this->gaintilde_19_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_19_ramp_index = _down;
            this->gaintilde_19_ramp_increment = (x - this->gaintilde_19_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_19_ramp_index > 0) {
        this->gaintilde_19_ramp_prev += this->gaintilde_19_ramp_increment;
        this->gaintilde_19_ramp_index -= 1;
    } else {
        this->gaintilde_19_ramp_prev = x;
    }

    return this->gaintilde_19_ramp_prev;
}

void gaintilde_19_ramp_reset() {
    this->gaintilde_19_ramp_prev = 0;
    this->gaintilde_19_ramp_index = 0;
    this->gaintilde_19_ramp_increment = 0;
    this->gaintilde_19_ramp_d_reset();
}

void gaintilde_19_init() {
    this->gaintilde_19_loginc = rnbo_log(1.072);
    this->gaintilde_19_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_19_loginc));
}

void gaintilde_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_19_value;
}

void gaintilde_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_19_value_set(preset["value"]);
}

void gaintilde_19_dspsetup(bool force) {
    if ((bool)(this->gaintilde_19_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_19_setupDone = true;
    this->gaintilde_19_ramp_d_dspsetup();
}

number freqshift_tilde_17_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad1_x1 * a1 + this->freqshift_tilde_17_h_biquad1_x2 * 1 - (this->freqshift_tilde_17_h_biquad1_y1 * b1 + this->freqshift_tilde_17_h_biquad1_y2 * b2);
    this->freqshift_tilde_17_h_biquad1_x2 = this->freqshift_tilde_17_h_biquad1_x1;
    this->freqshift_tilde_17_h_biquad1_x1 = x;
    this->freqshift_tilde_17_h_biquad1_y2 = this->freqshift_tilde_17_h_biquad1_y1;
    this->freqshift_tilde_17_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad1_clear() {
    this->freqshift_tilde_17_h_biquad1_reset();
}

void freqshift_tilde_17_h_biquad1_reset() {
    this->freqshift_tilde_17_h_biquad1_x1 = 0;
    this->freqshift_tilde_17_h_biquad1_x2 = 0;
    this->freqshift_tilde_17_h_biquad1_y1 = 0;
    this->freqshift_tilde_17_h_biquad1_y2 = 0;
}

void freqshift_tilde_17_h_biquad1_dspsetup() {
    this->freqshift_tilde_17_h_biquad1_reset();
}

number freqshift_tilde_17_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad2_x1 * a1 + this->freqshift_tilde_17_h_biquad2_x2 * 1 - (this->freqshift_tilde_17_h_biquad2_y1 * b1 + this->freqshift_tilde_17_h_biquad2_y2 * b2);
    this->freqshift_tilde_17_h_biquad2_x2 = this->freqshift_tilde_17_h_biquad2_x1;
    this->freqshift_tilde_17_h_biquad2_x1 = x;
    this->freqshift_tilde_17_h_biquad2_y2 = this->freqshift_tilde_17_h_biquad2_y1;
    this->freqshift_tilde_17_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad2_clear() {
    this->freqshift_tilde_17_h_biquad2_reset();
}

void freqshift_tilde_17_h_biquad2_reset() {
    this->freqshift_tilde_17_h_biquad2_x1 = 0;
    this->freqshift_tilde_17_h_biquad2_x2 = 0;
    this->freqshift_tilde_17_h_biquad2_y1 = 0;
    this->freqshift_tilde_17_h_biquad2_y2 = 0;
}

void freqshift_tilde_17_h_biquad2_dspsetup() {
    this->freqshift_tilde_17_h_biquad2_reset();
}

number freqshift_tilde_17_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad3_x1 * a1 + this->freqshift_tilde_17_h_biquad3_x2 * 1 - (this->freqshift_tilde_17_h_biquad3_y1 * b1 + this->freqshift_tilde_17_h_biquad3_y2 * b2);
    this->freqshift_tilde_17_h_biquad3_x2 = this->freqshift_tilde_17_h_biquad3_x1;
    this->freqshift_tilde_17_h_biquad3_x1 = x;
    this->freqshift_tilde_17_h_biquad3_y2 = this->freqshift_tilde_17_h_biquad3_y1;
    this->freqshift_tilde_17_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad3_clear() {
    this->freqshift_tilde_17_h_biquad3_reset();
}

void freqshift_tilde_17_h_biquad3_reset() {
    this->freqshift_tilde_17_h_biquad3_x1 = 0;
    this->freqshift_tilde_17_h_biquad3_x2 = 0;
    this->freqshift_tilde_17_h_biquad3_y1 = 0;
    this->freqshift_tilde_17_h_biquad3_y2 = 0;
}

void freqshift_tilde_17_h_biquad3_dspsetup() {
    this->freqshift_tilde_17_h_biquad3_reset();
}

number freqshift_tilde_17_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad4_x1 * a1 + this->freqshift_tilde_17_h_biquad4_x2 * 1 - (this->freqshift_tilde_17_h_biquad4_y1 * b1 + this->freqshift_tilde_17_h_biquad4_y2 * b2);
    this->freqshift_tilde_17_h_biquad4_x2 = this->freqshift_tilde_17_h_biquad4_x1;
    this->freqshift_tilde_17_h_biquad4_x1 = x;
    this->freqshift_tilde_17_h_biquad4_y2 = this->freqshift_tilde_17_h_biquad4_y1;
    this->freqshift_tilde_17_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad4_clear() {
    this->freqshift_tilde_17_h_biquad4_reset();
}

void freqshift_tilde_17_h_biquad4_reset() {
    this->freqshift_tilde_17_h_biquad4_x1 = 0;
    this->freqshift_tilde_17_h_biquad4_x2 = 0;
    this->freqshift_tilde_17_h_biquad4_y1 = 0;
    this->freqshift_tilde_17_h_biquad4_y2 = 0;
}

void freqshift_tilde_17_h_biquad4_dspsetup() {
    this->freqshift_tilde_17_h_biquad4_reset();
}

number freqshift_tilde_17_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad5_x1 * a1 + this->freqshift_tilde_17_h_biquad5_x2 * 1 - (this->freqshift_tilde_17_h_biquad5_y1 * b1 + this->freqshift_tilde_17_h_biquad5_y2 * b2);
    this->freqshift_tilde_17_h_biquad5_x2 = this->freqshift_tilde_17_h_biquad5_x1;
    this->freqshift_tilde_17_h_biquad5_x1 = x;
    this->freqshift_tilde_17_h_biquad5_y2 = this->freqshift_tilde_17_h_biquad5_y1;
    this->freqshift_tilde_17_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad5_clear() {
    this->freqshift_tilde_17_h_biquad5_reset();
}

void freqshift_tilde_17_h_biquad5_reset() {
    this->freqshift_tilde_17_h_biquad5_x1 = 0;
    this->freqshift_tilde_17_h_biquad5_x2 = 0;
    this->freqshift_tilde_17_h_biquad5_y1 = 0;
    this->freqshift_tilde_17_h_biquad5_y2 = 0;
}

void freqshift_tilde_17_h_biquad5_dspsetup() {
    this->freqshift_tilde_17_h_biquad5_reset();
}

number freqshift_tilde_17_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_17_h_biquad6_x1 * a1 + this->freqshift_tilde_17_h_biquad6_x2 * 1 - (this->freqshift_tilde_17_h_biquad6_y1 * b1 + this->freqshift_tilde_17_h_biquad6_y2 * b2);
    this->freqshift_tilde_17_h_biquad6_x2 = this->freqshift_tilde_17_h_biquad6_x1;
    this->freqshift_tilde_17_h_biquad6_x1 = x;
    this->freqshift_tilde_17_h_biquad6_y2 = this->freqshift_tilde_17_h_biquad6_y1;
    this->freqshift_tilde_17_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_17_h_biquad6_clear() {
    this->freqshift_tilde_17_h_biquad6_reset();
}

void freqshift_tilde_17_h_biquad6_reset() {
    this->freqshift_tilde_17_h_biquad6_x1 = 0;
    this->freqshift_tilde_17_h_biquad6_x2 = 0;
    this->freqshift_tilde_17_h_biquad6_y1 = 0;
    this->freqshift_tilde_17_h_biquad6_y2 = 0;
}

void freqshift_tilde_17_h_biquad6_dspsetup() {
    this->freqshift_tilde_17_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_17_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_17_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_17_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_17_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_17_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_17_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_17_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_17_h_clear() {
    this->freqshift_tilde_17_h_reset();
}

void freqshift_tilde_17_h_reset() {
    this->freqshift_tilde_17_h_biquad1_reset();
    this->freqshift_tilde_17_h_biquad2_reset();
    this->freqshift_tilde_17_h_biquad3_reset();
    this->freqshift_tilde_17_h_biquad4_reset();
    this->freqshift_tilde_17_h_biquad5_reset();
    this->freqshift_tilde_17_h_biquad6_reset();
}

void freqshift_tilde_17_h_dspsetup() {
    this->freqshift_tilde_17_h_reset();
}

number freqshift_tilde_17_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_17_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_17_p_conv;

    if (this->freqshift_tilde_17_p_currentPhase < 0.)
        this->freqshift_tilde_17_p_currentPhase = 1. + this->freqshift_tilde_17_p_currentPhase;

    if (this->freqshift_tilde_17_p_currentPhase > 1.)
        this->freqshift_tilde_17_p_currentPhase = this->freqshift_tilde_17_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_17_p_currentPhase;
    this->freqshift_tilde_17_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_17_p_reset() {
    this->freqshift_tilde_17_p_currentPhase = 0;
}

void freqshift_tilde_17_p_dspsetup() {
    this->freqshift_tilde_17_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_17_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_17_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_17_setupDone = true;
    this->freqshift_tilde_17_h_biquad1_dspsetup();
    this->freqshift_tilde_17_h_biquad2_dspsetup();
    this->freqshift_tilde_17_h_biquad3_dspsetup();
    this->freqshift_tilde_17_h_biquad4_dspsetup();
    this->freqshift_tilde_17_h_biquad5_dspsetup();
    this->freqshift_tilde_17_h_biquad6_dspsetup();
    this->freqshift_tilde_17_h_dspsetup();
    this->freqshift_tilde_17_p_dspsetup();
}

number freqshift_tilde_18_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad1_x1 * a1 + this->freqshift_tilde_18_h_biquad1_x2 * 1 - (this->freqshift_tilde_18_h_biquad1_y1 * b1 + this->freqshift_tilde_18_h_biquad1_y2 * b2);
    this->freqshift_tilde_18_h_biquad1_x2 = this->freqshift_tilde_18_h_biquad1_x1;
    this->freqshift_tilde_18_h_biquad1_x1 = x;
    this->freqshift_tilde_18_h_biquad1_y2 = this->freqshift_tilde_18_h_biquad1_y1;
    this->freqshift_tilde_18_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad1_clear() {
    this->freqshift_tilde_18_h_biquad1_reset();
}

void freqshift_tilde_18_h_biquad1_reset() {
    this->freqshift_tilde_18_h_biquad1_x1 = 0;
    this->freqshift_tilde_18_h_biquad1_x2 = 0;
    this->freqshift_tilde_18_h_biquad1_y1 = 0;
    this->freqshift_tilde_18_h_biquad1_y2 = 0;
}

void freqshift_tilde_18_h_biquad1_dspsetup() {
    this->freqshift_tilde_18_h_biquad1_reset();
}

number freqshift_tilde_18_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad2_x1 * a1 + this->freqshift_tilde_18_h_biquad2_x2 * 1 - (this->freqshift_tilde_18_h_biquad2_y1 * b1 + this->freqshift_tilde_18_h_biquad2_y2 * b2);
    this->freqshift_tilde_18_h_biquad2_x2 = this->freqshift_tilde_18_h_biquad2_x1;
    this->freqshift_tilde_18_h_biquad2_x1 = x;
    this->freqshift_tilde_18_h_biquad2_y2 = this->freqshift_tilde_18_h_biquad2_y1;
    this->freqshift_tilde_18_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad2_clear() {
    this->freqshift_tilde_18_h_biquad2_reset();
}

void freqshift_tilde_18_h_biquad2_reset() {
    this->freqshift_tilde_18_h_biquad2_x1 = 0;
    this->freqshift_tilde_18_h_biquad2_x2 = 0;
    this->freqshift_tilde_18_h_biquad2_y1 = 0;
    this->freqshift_tilde_18_h_biquad2_y2 = 0;
}

void freqshift_tilde_18_h_biquad2_dspsetup() {
    this->freqshift_tilde_18_h_biquad2_reset();
}

number freqshift_tilde_18_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad3_x1 * a1 + this->freqshift_tilde_18_h_biquad3_x2 * 1 - (this->freqshift_tilde_18_h_biquad3_y1 * b1 + this->freqshift_tilde_18_h_biquad3_y2 * b2);
    this->freqshift_tilde_18_h_biquad3_x2 = this->freqshift_tilde_18_h_biquad3_x1;
    this->freqshift_tilde_18_h_biquad3_x1 = x;
    this->freqshift_tilde_18_h_biquad3_y2 = this->freqshift_tilde_18_h_biquad3_y1;
    this->freqshift_tilde_18_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad3_clear() {
    this->freqshift_tilde_18_h_biquad3_reset();
}

void freqshift_tilde_18_h_biquad3_reset() {
    this->freqshift_tilde_18_h_biquad3_x1 = 0;
    this->freqshift_tilde_18_h_biquad3_x2 = 0;
    this->freqshift_tilde_18_h_biquad3_y1 = 0;
    this->freqshift_tilde_18_h_biquad3_y2 = 0;
}

void freqshift_tilde_18_h_biquad3_dspsetup() {
    this->freqshift_tilde_18_h_biquad3_reset();
}

number freqshift_tilde_18_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad4_x1 * a1 + this->freqshift_tilde_18_h_biquad4_x2 * 1 - (this->freqshift_tilde_18_h_biquad4_y1 * b1 + this->freqshift_tilde_18_h_biquad4_y2 * b2);
    this->freqshift_tilde_18_h_biquad4_x2 = this->freqshift_tilde_18_h_biquad4_x1;
    this->freqshift_tilde_18_h_biquad4_x1 = x;
    this->freqshift_tilde_18_h_biquad4_y2 = this->freqshift_tilde_18_h_biquad4_y1;
    this->freqshift_tilde_18_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad4_clear() {
    this->freqshift_tilde_18_h_biquad4_reset();
}

void freqshift_tilde_18_h_biquad4_reset() {
    this->freqshift_tilde_18_h_biquad4_x1 = 0;
    this->freqshift_tilde_18_h_biquad4_x2 = 0;
    this->freqshift_tilde_18_h_biquad4_y1 = 0;
    this->freqshift_tilde_18_h_biquad4_y2 = 0;
}

void freqshift_tilde_18_h_biquad4_dspsetup() {
    this->freqshift_tilde_18_h_biquad4_reset();
}

number freqshift_tilde_18_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad5_x1 * a1 + this->freqshift_tilde_18_h_biquad5_x2 * 1 - (this->freqshift_tilde_18_h_biquad5_y1 * b1 + this->freqshift_tilde_18_h_biquad5_y2 * b2);
    this->freqshift_tilde_18_h_biquad5_x2 = this->freqshift_tilde_18_h_biquad5_x1;
    this->freqshift_tilde_18_h_biquad5_x1 = x;
    this->freqshift_tilde_18_h_biquad5_y2 = this->freqshift_tilde_18_h_biquad5_y1;
    this->freqshift_tilde_18_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad5_clear() {
    this->freqshift_tilde_18_h_biquad5_reset();
}

void freqshift_tilde_18_h_biquad5_reset() {
    this->freqshift_tilde_18_h_biquad5_x1 = 0;
    this->freqshift_tilde_18_h_biquad5_x2 = 0;
    this->freqshift_tilde_18_h_biquad5_y1 = 0;
    this->freqshift_tilde_18_h_biquad5_y2 = 0;
}

void freqshift_tilde_18_h_biquad5_dspsetup() {
    this->freqshift_tilde_18_h_biquad5_reset();
}

number freqshift_tilde_18_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_18_h_biquad6_x1 * a1 + this->freqshift_tilde_18_h_biquad6_x2 * 1 - (this->freqshift_tilde_18_h_biquad6_y1 * b1 + this->freqshift_tilde_18_h_biquad6_y2 * b2);
    this->freqshift_tilde_18_h_biquad6_x2 = this->freqshift_tilde_18_h_biquad6_x1;
    this->freqshift_tilde_18_h_biquad6_x1 = x;
    this->freqshift_tilde_18_h_biquad6_y2 = this->freqshift_tilde_18_h_biquad6_y1;
    this->freqshift_tilde_18_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_18_h_biquad6_clear() {
    this->freqshift_tilde_18_h_biquad6_reset();
}

void freqshift_tilde_18_h_biquad6_reset() {
    this->freqshift_tilde_18_h_biquad6_x1 = 0;
    this->freqshift_tilde_18_h_biquad6_x2 = 0;
    this->freqshift_tilde_18_h_biquad6_y1 = 0;
    this->freqshift_tilde_18_h_biquad6_y2 = 0;
}

void freqshift_tilde_18_h_biquad6_dspsetup() {
    this->freqshift_tilde_18_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_18_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_18_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_18_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_18_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_18_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_18_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_18_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_18_h_clear() {
    this->freqshift_tilde_18_h_reset();
}

void freqshift_tilde_18_h_reset() {
    this->freqshift_tilde_18_h_biquad1_reset();
    this->freqshift_tilde_18_h_biquad2_reset();
    this->freqshift_tilde_18_h_biquad3_reset();
    this->freqshift_tilde_18_h_biquad4_reset();
    this->freqshift_tilde_18_h_biquad5_reset();
    this->freqshift_tilde_18_h_biquad6_reset();
}

void freqshift_tilde_18_h_dspsetup() {
    this->freqshift_tilde_18_h_reset();
}

number freqshift_tilde_18_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_18_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_18_p_conv;

    if (this->freqshift_tilde_18_p_currentPhase < 0.)
        this->freqshift_tilde_18_p_currentPhase = 1. + this->freqshift_tilde_18_p_currentPhase;

    if (this->freqshift_tilde_18_p_currentPhase > 1.)
        this->freqshift_tilde_18_p_currentPhase = this->freqshift_tilde_18_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_18_p_currentPhase;
    this->freqshift_tilde_18_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_18_p_reset() {
    this->freqshift_tilde_18_p_currentPhase = 0;
}

void freqshift_tilde_18_p_dspsetup() {
    this->freqshift_tilde_18_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_18_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_18_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_18_setupDone = true;
    this->freqshift_tilde_18_h_biquad1_dspsetup();
    this->freqshift_tilde_18_h_biquad2_dspsetup();
    this->freqshift_tilde_18_h_biquad3_dspsetup();
    this->freqshift_tilde_18_h_biquad4_dspsetup();
    this->freqshift_tilde_18_h_biquad5_dspsetup();
    this->freqshift_tilde_18_h_biquad6_dspsetup();
    this->freqshift_tilde_18_h_dspsetup();
    this->freqshift_tilde_18_p_dspsetup();
}

number gaintilde_20_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_20_ramp_d_prev);
    this->gaintilde_20_ramp_d_prev = x;
    return temp;
}

void gaintilde_20_ramp_d_dspsetup() {
    this->gaintilde_20_ramp_d_reset();
}

void gaintilde_20_ramp_d_reset() {
    this->gaintilde_20_ramp_d_prev = 0;
}

number gaintilde_20_ramp_next(number x, number up, number down) {
    if (this->gaintilde_20_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_20_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_20_ramp_index = _up;
            this->gaintilde_20_ramp_increment = (x - this->gaintilde_20_ramp_prev) / _up;
        } else if (x < this->gaintilde_20_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_20_ramp_index = _down;
            this->gaintilde_20_ramp_increment = (x - this->gaintilde_20_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_20_ramp_index > 0) {
        this->gaintilde_20_ramp_prev += this->gaintilde_20_ramp_increment;
        this->gaintilde_20_ramp_index -= 1;
    } else {
        this->gaintilde_20_ramp_prev = x;
    }

    return this->gaintilde_20_ramp_prev;
}

void gaintilde_20_ramp_reset() {
    this->gaintilde_20_ramp_prev = 0;
    this->gaintilde_20_ramp_index = 0;
    this->gaintilde_20_ramp_increment = 0;
    this->gaintilde_20_ramp_d_reset();
}

void gaintilde_20_init() {
    this->gaintilde_20_loginc = rnbo_log(1.072);
    this->gaintilde_20_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_20_loginc));
}

void gaintilde_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_20_value;
}

void gaintilde_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_20_value_set(preset["value"]);
}

void gaintilde_20_dspsetup(bool force) {
    if ((bool)(this->gaintilde_20_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_20_setupDone = true;
    this->gaintilde_20_ramp_d_dspsetup();
}

number gaintilde_21_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_21_ramp_d_prev);
    this->gaintilde_21_ramp_d_prev = x;
    return temp;
}

void gaintilde_21_ramp_d_dspsetup() {
    this->gaintilde_21_ramp_d_reset();
}

void gaintilde_21_ramp_d_reset() {
    this->gaintilde_21_ramp_d_prev = 0;
}

number gaintilde_21_ramp_next(number x, number up, number down) {
    if (this->gaintilde_21_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_21_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_21_ramp_index = _up;
            this->gaintilde_21_ramp_increment = (x - this->gaintilde_21_ramp_prev) / _up;
        } else if (x < this->gaintilde_21_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_21_ramp_index = _down;
            this->gaintilde_21_ramp_increment = (x - this->gaintilde_21_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_21_ramp_index > 0) {
        this->gaintilde_21_ramp_prev += this->gaintilde_21_ramp_increment;
        this->gaintilde_21_ramp_index -= 1;
    } else {
        this->gaintilde_21_ramp_prev = x;
    }

    return this->gaintilde_21_ramp_prev;
}

void gaintilde_21_ramp_reset() {
    this->gaintilde_21_ramp_prev = 0;
    this->gaintilde_21_ramp_index = 0;
    this->gaintilde_21_ramp_increment = 0;
    this->gaintilde_21_ramp_d_reset();
}

void gaintilde_21_init() {
    this->gaintilde_21_loginc = rnbo_log(1.072);
    this->gaintilde_21_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_21_loginc));
}

void gaintilde_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_21_value;
}

void gaintilde_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_21_value_set(preset["value"]);
}

void gaintilde_21_dspsetup(bool force) {
    if ((bool)(this->gaintilde_21_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_21_setupDone = true;
    this->gaintilde_21_ramp_d_dspsetup();
}

number freqshift_tilde_19_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad1_x1 * a1 + this->freqshift_tilde_19_h_biquad1_x2 * 1 - (this->freqshift_tilde_19_h_biquad1_y1 * b1 + this->freqshift_tilde_19_h_biquad1_y2 * b2);
    this->freqshift_tilde_19_h_biquad1_x2 = this->freqshift_tilde_19_h_biquad1_x1;
    this->freqshift_tilde_19_h_biquad1_x1 = x;
    this->freqshift_tilde_19_h_biquad1_y2 = this->freqshift_tilde_19_h_biquad1_y1;
    this->freqshift_tilde_19_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad1_clear() {
    this->freqshift_tilde_19_h_biquad1_reset();
}

void freqshift_tilde_19_h_biquad1_reset() {
    this->freqshift_tilde_19_h_biquad1_x1 = 0;
    this->freqshift_tilde_19_h_biquad1_x2 = 0;
    this->freqshift_tilde_19_h_biquad1_y1 = 0;
    this->freqshift_tilde_19_h_biquad1_y2 = 0;
}

void freqshift_tilde_19_h_biquad1_dspsetup() {
    this->freqshift_tilde_19_h_biquad1_reset();
}

number freqshift_tilde_19_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad2_x1 * a1 + this->freqshift_tilde_19_h_biquad2_x2 * 1 - (this->freqshift_tilde_19_h_biquad2_y1 * b1 + this->freqshift_tilde_19_h_biquad2_y2 * b2);
    this->freqshift_tilde_19_h_biquad2_x2 = this->freqshift_tilde_19_h_biquad2_x1;
    this->freqshift_tilde_19_h_biquad2_x1 = x;
    this->freqshift_tilde_19_h_biquad2_y2 = this->freqshift_tilde_19_h_biquad2_y1;
    this->freqshift_tilde_19_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad2_clear() {
    this->freqshift_tilde_19_h_biquad2_reset();
}

void freqshift_tilde_19_h_biquad2_reset() {
    this->freqshift_tilde_19_h_biquad2_x1 = 0;
    this->freqshift_tilde_19_h_biquad2_x2 = 0;
    this->freqshift_tilde_19_h_biquad2_y1 = 0;
    this->freqshift_tilde_19_h_biquad2_y2 = 0;
}

void freqshift_tilde_19_h_biquad2_dspsetup() {
    this->freqshift_tilde_19_h_biquad2_reset();
}

number freqshift_tilde_19_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad3_x1 * a1 + this->freqshift_tilde_19_h_biquad3_x2 * 1 - (this->freqshift_tilde_19_h_biquad3_y1 * b1 + this->freqshift_tilde_19_h_biquad3_y2 * b2);
    this->freqshift_tilde_19_h_biquad3_x2 = this->freqshift_tilde_19_h_biquad3_x1;
    this->freqshift_tilde_19_h_biquad3_x1 = x;
    this->freqshift_tilde_19_h_biquad3_y2 = this->freqshift_tilde_19_h_biquad3_y1;
    this->freqshift_tilde_19_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad3_clear() {
    this->freqshift_tilde_19_h_biquad3_reset();
}

void freqshift_tilde_19_h_biquad3_reset() {
    this->freqshift_tilde_19_h_biquad3_x1 = 0;
    this->freqshift_tilde_19_h_biquad3_x2 = 0;
    this->freqshift_tilde_19_h_biquad3_y1 = 0;
    this->freqshift_tilde_19_h_biquad3_y2 = 0;
}

void freqshift_tilde_19_h_biquad3_dspsetup() {
    this->freqshift_tilde_19_h_biquad3_reset();
}

number freqshift_tilde_19_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad4_x1 * a1 + this->freqshift_tilde_19_h_biquad4_x2 * 1 - (this->freqshift_tilde_19_h_biquad4_y1 * b1 + this->freqshift_tilde_19_h_biquad4_y2 * b2);
    this->freqshift_tilde_19_h_biquad4_x2 = this->freqshift_tilde_19_h_biquad4_x1;
    this->freqshift_tilde_19_h_biquad4_x1 = x;
    this->freqshift_tilde_19_h_biquad4_y2 = this->freqshift_tilde_19_h_biquad4_y1;
    this->freqshift_tilde_19_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad4_clear() {
    this->freqshift_tilde_19_h_biquad4_reset();
}

void freqshift_tilde_19_h_biquad4_reset() {
    this->freqshift_tilde_19_h_biquad4_x1 = 0;
    this->freqshift_tilde_19_h_biquad4_x2 = 0;
    this->freqshift_tilde_19_h_biquad4_y1 = 0;
    this->freqshift_tilde_19_h_biquad4_y2 = 0;
}

void freqshift_tilde_19_h_biquad4_dspsetup() {
    this->freqshift_tilde_19_h_biquad4_reset();
}

number freqshift_tilde_19_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad5_x1 * a1 + this->freqshift_tilde_19_h_biquad5_x2 * 1 - (this->freqshift_tilde_19_h_biquad5_y1 * b1 + this->freqshift_tilde_19_h_biquad5_y2 * b2);
    this->freqshift_tilde_19_h_biquad5_x2 = this->freqshift_tilde_19_h_biquad5_x1;
    this->freqshift_tilde_19_h_biquad5_x1 = x;
    this->freqshift_tilde_19_h_biquad5_y2 = this->freqshift_tilde_19_h_biquad5_y1;
    this->freqshift_tilde_19_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad5_clear() {
    this->freqshift_tilde_19_h_biquad5_reset();
}

void freqshift_tilde_19_h_biquad5_reset() {
    this->freqshift_tilde_19_h_biquad5_x1 = 0;
    this->freqshift_tilde_19_h_biquad5_x2 = 0;
    this->freqshift_tilde_19_h_biquad5_y1 = 0;
    this->freqshift_tilde_19_h_biquad5_y2 = 0;
}

void freqshift_tilde_19_h_biquad5_dspsetup() {
    this->freqshift_tilde_19_h_biquad5_reset();
}

number freqshift_tilde_19_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_19_h_biquad6_x1 * a1 + this->freqshift_tilde_19_h_biquad6_x2 * 1 - (this->freqshift_tilde_19_h_biquad6_y1 * b1 + this->freqshift_tilde_19_h_biquad6_y2 * b2);
    this->freqshift_tilde_19_h_biquad6_x2 = this->freqshift_tilde_19_h_biquad6_x1;
    this->freqshift_tilde_19_h_biquad6_x1 = x;
    this->freqshift_tilde_19_h_biquad6_y2 = this->freqshift_tilde_19_h_biquad6_y1;
    this->freqshift_tilde_19_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_19_h_biquad6_clear() {
    this->freqshift_tilde_19_h_biquad6_reset();
}

void freqshift_tilde_19_h_biquad6_reset() {
    this->freqshift_tilde_19_h_biquad6_x1 = 0;
    this->freqshift_tilde_19_h_biquad6_x2 = 0;
    this->freqshift_tilde_19_h_biquad6_y1 = 0;
    this->freqshift_tilde_19_h_biquad6_y2 = 0;
}

void freqshift_tilde_19_h_biquad6_dspsetup() {
    this->freqshift_tilde_19_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_19_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_19_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_19_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_19_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_19_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_19_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_19_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_19_h_clear() {
    this->freqshift_tilde_19_h_reset();
}

void freqshift_tilde_19_h_reset() {
    this->freqshift_tilde_19_h_biquad1_reset();
    this->freqshift_tilde_19_h_biquad2_reset();
    this->freqshift_tilde_19_h_biquad3_reset();
    this->freqshift_tilde_19_h_biquad4_reset();
    this->freqshift_tilde_19_h_biquad5_reset();
    this->freqshift_tilde_19_h_biquad6_reset();
}

void freqshift_tilde_19_h_dspsetup() {
    this->freqshift_tilde_19_h_reset();
}

number freqshift_tilde_19_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_19_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_19_p_conv;

    if (this->freqshift_tilde_19_p_currentPhase < 0.)
        this->freqshift_tilde_19_p_currentPhase = 1. + this->freqshift_tilde_19_p_currentPhase;

    if (this->freqshift_tilde_19_p_currentPhase > 1.)
        this->freqshift_tilde_19_p_currentPhase = this->freqshift_tilde_19_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_19_p_currentPhase;
    this->freqshift_tilde_19_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_19_p_reset() {
    this->freqshift_tilde_19_p_currentPhase = 0;
}

void freqshift_tilde_19_p_dspsetup() {
    this->freqshift_tilde_19_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_19_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_19_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_19_setupDone = true;
    this->freqshift_tilde_19_h_biquad1_dspsetup();
    this->freqshift_tilde_19_h_biquad2_dspsetup();
    this->freqshift_tilde_19_h_biquad3_dspsetup();
    this->freqshift_tilde_19_h_biquad4_dspsetup();
    this->freqshift_tilde_19_h_biquad5_dspsetup();
    this->freqshift_tilde_19_h_biquad6_dspsetup();
    this->freqshift_tilde_19_h_dspsetup();
    this->freqshift_tilde_19_p_dspsetup();
}

number freqshift_tilde_20_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad1_x1 * a1 + this->freqshift_tilde_20_h_biquad1_x2 * 1 - (this->freqshift_tilde_20_h_biquad1_y1 * b1 + this->freqshift_tilde_20_h_biquad1_y2 * b2);
    this->freqshift_tilde_20_h_biquad1_x2 = this->freqshift_tilde_20_h_biquad1_x1;
    this->freqshift_tilde_20_h_biquad1_x1 = x;
    this->freqshift_tilde_20_h_biquad1_y2 = this->freqshift_tilde_20_h_biquad1_y1;
    this->freqshift_tilde_20_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad1_clear() {
    this->freqshift_tilde_20_h_biquad1_reset();
}

void freqshift_tilde_20_h_biquad1_reset() {
    this->freqshift_tilde_20_h_biquad1_x1 = 0;
    this->freqshift_tilde_20_h_biquad1_x2 = 0;
    this->freqshift_tilde_20_h_biquad1_y1 = 0;
    this->freqshift_tilde_20_h_biquad1_y2 = 0;
}

void freqshift_tilde_20_h_biquad1_dspsetup() {
    this->freqshift_tilde_20_h_biquad1_reset();
}

number freqshift_tilde_20_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad2_x1 * a1 + this->freqshift_tilde_20_h_biquad2_x2 * 1 - (this->freqshift_tilde_20_h_biquad2_y1 * b1 + this->freqshift_tilde_20_h_biquad2_y2 * b2);
    this->freqshift_tilde_20_h_biquad2_x2 = this->freqshift_tilde_20_h_biquad2_x1;
    this->freqshift_tilde_20_h_biquad2_x1 = x;
    this->freqshift_tilde_20_h_biquad2_y2 = this->freqshift_tilde_20_h_biquad2_y1;
    this->freqshift_tilde_20_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad2_clear() {
    this->freqshift_tilde_20_h_biquad2_reset();
}

void freqshift_tilde_20_h_biquad2_reset() {
    this->freqshift_tilde_20_h_biquad2_x1 = 0;
    this->freqshift_tilde_20_h_biquad2_x2 = 0;
    this->freqshift_tilde_20_h_biquad2_y1 = 0;
    this->freqshift_tilde_20_h_biquad2_y2 = 0;
}

void freqshift_tilde_20_h_biquad2_dspsetup() {
    this->freqshift_tilde_20_h_biquad2_reset();
}

number freqshift_tilde_20_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad3_x1 * a1 + this->freqshift_tilde_20_h_biquad3_x2 * 1 - (this->freqshift_tilde_20_h_biquad3_y1 * b1 + this->freqshift_tilde_20_h_biquad3_y2 * b2);
    this->freqshift_tilde_20_h_biquad3_x2 = this->freqshift_tilde_20_h_biquad3_x1;
    this->freqshift_tilde_20_h_biquad3_x1 = x;
    this->freqshift_tilde_20_h_biquad3_y2 = this->freqshift_tilde_20_h_biquad3_y1;
    this->freqshift_tilde_20_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad3_clear() {
    this->freqshift_tilde_20_h_biquad3_reset();
}

void freqshift_tilde_20_h_biquad3_reset() {
    this->freqshift_tilde_20_h_biquad3_x1 = 0;
    this->freqshift_tilde_20_h_biquad3_x2 = 0;
    this->freqshift_tilde_20_h_biquad3_y1 = 0;
    this->freqshift_tilde_20_h_biquad3_y2 = 0;
}

void freqshift_tilde_20_h_biquad3_dspsetup() {
    this->freqshift_tilde_20_h_biquad3_reset();
}

number freqshift_tilde_20_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad4_x1 * a1 + this->freqshift_tilde_20_h_biquad4_x2 * 1 - (this->freqshift_tilde_20_h_biquad4_y1 * b1 + this->freqshift_tilde_20_h_biquad4_y2 * b2);
    this->freqshift_tilde_20_h_biquad4_x2 = this->freqshift_tilde_20_h_biquad4_x1;
    this->freqshift_tilde_20_h_biquad4_x1 = x;
    this->freqshift_tilde_20_h_biquad4_y2 = this->freqshift_tilde_20_h_biquad4_y1;
    this->freqshift_tilde_20_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad4_clear() {
    this->freqshift_tilde_20_h_biquad4_reset();
}

void freqshift_tilde_20_h_biquad4_reset() {
    this->freqshift_tilde_20_h_biquad4_x1 = 0;
    this->freqshift_tilde_20_h_biquad4_x2 = 0;
    this->freqshift_tilde_20_h_biquad4_y1 = 0;
    this->freqshift_tilde_20_h_biquad4_y2 = 0;
}

void freqshift_tilde_20_h_biquad4_dspsetup() {
    this->freqshift_tilde_20_h_biquad4_reset();
}

number freqshift_tilde_20_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad5_x1 * a1 + this->freqshift_tilde_20_h_biquad5_x2 * 1 - (this->freqshift_tilde_20_h_biquad5_y1 * b1 + this->freqshift_tilde_20_h_biquad5_y2 * b2);
    this->freqshift_tilde_20_h_biquad5_x2 = this->freqshift_tilde_20_h_biquad5_x1;
    this->freqshift_tilde_20_h_biquad5_x1 = x;
    this->freqshift_tilde_20_h_biquad5_y2 = this->freqshift_tilde_20_h_biquad5_y1;
    this->freqshift_tilde_20_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad5_clear() {
    this->freqshift_tilde_20_h_biquad5_reset();
}

void freqshift_tilde_20_h_biquad5_reset() {
    this->freqshift_tilde_20_h_biquad5_x1 = 0;
    this->freqshift_tilde_20_h_biquad5_x2 = 0;
    this->freqshift_tilde_20_h_biquad5_y1 = 0;
    this->freqshift_tilde_20_h_biquad5_y2 = 0;
}

void freqshift_tilde_20_h_biquad5_dspsetup() {
    this->freqshift_tilde_20_h_biquad5_reset();
}

number freqshift_tilde_20_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_20_h_biquad6_x1 * a1 + this->freqshift_tilde_20_h_biquad6_x2 * 1 - (this->freqshift_tilde_20_h_biquad6_y1 * b1 + this->freqshift_tilde_20_h_biquad6_y2 * b2);
    this->freqshift_tilde_20_h_biquad6_x2 = this->freqshift_tilde_20_h_biquad6_x1;
    this->freqshift_tilde_20_h_biquad6_x1 = x;
    this->freqshift_tilde_20_h_biquad6_y2 = this->freqshift_tilde_20_h_biquad6_y1;
    this->freqshift_tilde_20_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_20_h_biquad6_clear() {
    this->freqshift_tilde_20_h_biquad6_reset();
}

void freqshift_tilde_20_h_biquad6_reset() {
    this->freqshift_tilde_20_h_biquad6_x1 = 0;
    this->freqshift_tilde_20_h_biquad6_x2 = 0;
    this->freqshift_tilde_20_h_biquad6_y1 = 0;
    this->freqshift_tilde_20_h_biquad6_y2 = 0;
}

void freqshift_tilde_20_h_biquad6_dspsetup() {
    this->freqshift_tilde_20_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_20_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_20_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_20_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_20_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_20_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_20_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_20_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_20_h_clear() {
    this->freqshift_tilde_20_h_reset();
}

void freqshift_tilde_20_h_reset() {
    this->freqshift_tilde_20_h_biquad1_reset();
    this->freqshift_tilde_20_h_biquad2_reset();
    this->freqshift_tilde_20_h_biquad3_reset();
    this->freqshift_tilde_20_h_biquad4_reset();
    this->freqshift_tilde_20_h_biquad5_reset();
    this->freqshift_tilde_20_h_biquad6_reset();
}

void freqshift_tilde_20_h_dspsetup() {
    this->freqshift_tilde_20_h_reset();
}

number freqshift_tilde_20_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_20_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_20_p_conv;

    if (this->freqshift_tilde_20_p_currentPhase < 0.)
        this->freqshift_tilde_20_p_currentPhase = 1. + this->freqshift_tilde_20_p_currentPhase;

    if (this->freqshift_tilde_20_p_currentPhase > 1.)
        this->freqshift_tilde_20_p_currentPhase = this->freqshift_tilde_20_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_20_p_currentPhase;
    this->freqshift_tilde_20_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_20_p_reset() {
    this->freqshift_tilde_20_p_currentPhase = 0;
}

void freqshift_tilde_20_p_dspsetup() {
    this->freqshift_tilde_20_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_20_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_20_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_20_setupDone = true;
    this->freqshift_tilde_20_h_biquad1_dspsetup();
    this->freqshift_tilde_20_h_biquad2_dspsetup();
    this->freqshift_tilde_20_h_biquad3_dspsetup();
    this->freqshift_tilde_20_h_biquad4_dspsetup();
    this->freqshift_tilde_20_h_biquad5_dspsetup();
    this->freqshift_tilde_20_h_biquad6_dspsetup();
    this->freqshift_tilde_20_h_dspsetup();
    this->freqshift_tilde_20_p_dspsetup();
}

number gaintilde_22_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_22_ramp_d_prev);
    this->gaintilde_22_ramp_d_prev = x;
    return temp;
}

void gaintilde_22_ramp_d_dspsetup() {
    this->gaintilde_22_ramp_d_reset();
}

void gaintilde_22_ramp_d_reset() {
    this->gaintilde_22_ramp_d_prev = 0;
}

number gaintilde_22_ramp_next(number x, number up, number down) {
    if (this->gaintilde_22_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_22_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_22_ramp_index = _up;
            this->gaintilde_22_ramp_increment = (x - this->gaintilde_22_ramp_prev) / _up;
        } else if (x < this->gaintilde_22_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_22_ramp_index = _down;
            this->gaintilde_22_ramp_increment = (x - this->gaintilde_22_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_22_ramp_index > 0) {
        this->gaintilde_22_ramp_prev += this->gaintilde_22_ramp_increment;
        this->gaintilde_22_ramp_index -= 1;
    } else {
        this->gaintilde_22_ramp_prev = x;
    }

    return this->gaintilde_22_ramp_prev;
}

void gaintilde_22_ramp_reset() {
    this->gaintilde_22_ramp_prev = 0;
    this->gaintilde_22_ramp_index = 0;
    this->gaintilde_22_ramp_increment = 0;
    this->gaintilde_22_ramp_d_reset();
}

void gaintilde_22_init() {
    this->gaintilde_22_loginc = rnbo_log(1.072);
    this->gaintilde_22_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_22_loginc));
}

void gaintilde_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_22_value;
}

void gaintilde_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_22_value_set(preset["value"]);
}

void gaintilde_22_dspsetup(bool force) {
    if ((bool)(this->gaintilde_22_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_22_setupDone = true;
    this->gaintilde_22_ramp_d_dspsetup();
}

number gaintilde_23_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_23_ramp_d_prev);
    this->gaintilde_23_ramp_d_prev = x;
    return temp;
}

void gaintilde_23_ramp_d_dspsetup() {
    this->gaintilde_23_ramp_d_reset();
}

void gaintilde_23_ramp_d_reset() {
    this->gaintilde_23_ramp_d_prev = 0;
}

number gaintilde_23_ramp_next(number x, number up, number down) {
    if (this->gaintilde_23_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_23_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_23_ramp_index = _up;
            this->gaintilde_23_ramp_increment = (x - this->gaintilde_23_ramp_prev) / _up;
        } else if (x < this->gaintilde_23_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_23_ramp_index = _down;
            this->gaintilde_23_ramp_increment = (x - this->gaintilde_23_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_23_ramp_index > 0) {
        this->gaintilde_23_ramp_prev += this->gaintilde_23_ramp_increment;
        this->gaintilde_23_ramp_index -= 1;
    } else {
        this->gaintilde_23_ramp_prev = x;
    }

    return this->gaintilde_23_ramp_prev;
}

void gaintilde_23_ramp_reset() {
    this->gaintilde_23_ramp_prev = 0;
    this->gaintilde_23_ramp_index = 0;
    this->gaintilde_23_ramp_increment = 0;
    this->gaintilde_23_ramp_d_reset();
}

void gaintilde_23_init() {
    this->gaintilde_23_loginc = rnbo_log(1.072);
    this->gaintilde_23_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_23_loginc));
}

void gaintilde_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_23_value;
}

void gaintilde_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_23_value_set(preset["value"]);
}

void gaintilde_23_dspsetup(bool force) {
    if ((bool)(this->gaintilde_23_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_23_setupDone = true;
    this->gaintilde_23_ramp_d_dspsetup();
}

void param_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_18_value;
}

void param_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_18_value_set(preset["value"]);
}

void param_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_19_value;
}

void param_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_19_value_set(preset["value"]);
}

number freqshift_tilde_21_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad1_x1 * a1 + this->freqshift_tilde_21_h_biquad1_x2 * 1 - (this->freqshift_tilde_21_h_biquad1_y1 * b1 + this->freqshift_tilde_21_h_biquad1_y2 * b2);
    this->freqshift_tilde_21_h_biquad1_x2 = this->freqshift_tilde_21_h_biquad1_x1;
    this->freqshift_tilde_21_h_biquad1_x1 = x;
    this->freqshift_tilde_21_h_biquad1_y2 = this->freqshift_tilde_21_h_biquad1_y1;
    this->freqshift_tilde_21_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad1_clear() {
    this->freqshift_tilde_21_h_biquad1_reset();
}

void freqshift_tilde_21_h_biquad1_reset() {
    this->freqshift_tilde_21_h_biquad1_x1 = 0;
    this->freqshift_tilde_21_h_biquad1_x2 = 0;
    this->freqshift_tilde_21_h_biquad1_y1 = 0;
    this->freqshift_tilde_21_h_biquad1_y2 = 0;
}

void freqshift_tilde_21_h_biquad1_dspsetup() {
    this->freqshift_tilde_21_h_biquad1_reset();
}

number freqshift_tilde_21_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad2_x1 * a1 + this->freqshift_tilde_21_h_biquad2_x2 * 1 - (this->freqshift_tilde_21_h_biquad2_y1 * b1 + this->freqshift_tilde_21_h_biquad2_y2 * b2);
    this->freqshift_tilde_21_h_biquad2_x2 = this->freqshift_tilde_21_h_biquad2_x1;
    this->freqshift_tilde_21_h_biquad2_x1 = x;
    this->freqshift_tilde_21_h_biquad2_y2 = this->freqshift_tilde_21_h_biquad2_y1;
    this->freqshift_tilde_21_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad2_clear() {
    this->freqshift_tilde_21_h_biquad2_reset();
}

void freqshift_tilde_21_h_biquad2_reset() {
    this->freqshift_tilde_21_h_biquad2_x1 = 0;
    this->freqshift_tilde_21_h_biquad2_x2 = 0;
    this->freqshift_tilde_21_h_biquad2_y1 = 0;
    this->freqshift_tilde_21_h_biquad2_y2 = 0;
}

void freqshift_tilde_21_h_biquad2_dspsetup() {
    this->freqshift_tilde_21_h_biquad2_reset();
}

number freqshift_tilde_21_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad3_x1 * a1 + this->freqshift_tilde_21_h_biquad3_x2 * 1 - (this->freqshift_tilde_21_h_biquad3_y1 * b1 + this->freqshift_tilde_21_h_biquad3_y2 * b2);
    this->freqshift_tilde_21_h_biquad3_x2 = this->freqshift_tilde_21_h_biquad3_x1;
    this->freqshift_tilde_21_h_biquad3_x1 = x;
    this->freqshift_tilde_21_h_biquad3_y2 = this->freqshift_tilde_21_h_biquad3_y1;
    this->freqshift_tilde_21_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad3_clear() {
    this->freqshift_tilde_21_h_biquad3_reset();
}

void freqshift_tilde_21_h_biquad3_reset() {
    this->freqshift_tilde_21_h_biquad3_x1 = 0;
    this->freqshift_tilde_21_h_biquad3_x2 = 0;
    this->freqshift_tilde_21_h_biquad3_y1 = 0;
    this->freqshift_tilde_21_h_biquad3_y2 = 0;
}

void freqshift_tilde_21_h_biquad3_dspsetup() {
    this->freqshift_tilde_21_h_biquad3_reset();
}

number freqshift_tilde_21_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad4_x1 * a1 + this->freqshift_tilde_21_h_biquad4_x2 * 1 - (this->freqshift_tilde_21_h_biquad4_y1 * b1 + this->freqshift_tilde_21_h_biquad4_y2 * b2);
    this->freqshift_tilde_21_h_biquad4_x2 = this->freqshift_tilde_21_h_biquad4_x1;
    this->freqshift_tilde_21_h_biquad4_x1 = x;
    this->freqshift_tilde_21_h_biquad4_y2 = this->freqshift_tilde_21_h_biquad4_y1;
    this->freqshift_tilde_21_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad4_clear() {
    this->freqshift_tilde_21_h_biquad4_reset();
}

void freqshift_tilde_21_h_biquad4_reset() {
    this->freqshift_tilde_21_h_biquad4_x1 = 0;
    this->freqshift_tilde_21_h_biquad4_x2 = 0;
    this->freqshift_tilde_21_h_biquad4_y1 = 0;
    this->freqshift_tilde_21_h_biquad4_y2 = 0;
}

void freqshift_tilde_21_h_biquad4_dspsetup() {
    this->freqshift_tilde_21_h_biquad4_reset();
}

number freqshift_tilde_21_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad5_x1 * a1 + this->freqshift_tilde_21_h_biquad5_x2 * 1 - (this->freqshift_tilde_21_h_biquad5_y1 * b1 + this->freqshift_tilde_21_h_biquad5_y2 * b2);
    this->freqshift_tilde_21_h_biquad5_x2 = this->freqshift_tilde_21_h_biquad5_x1;
    this->freqshift_tilde_21_h_biquad5_x1 = x;
    this->freqshift_tilde_21_h_biquad5_y2 = this->freqshift_tilde_21_h_biquad5_y1;
    this->freqshift_tilde_21_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad5_clear() {
    this->freqshift_tilde_21_h_biquad5_reset();
}

void freqshift_tilde_21_h_biquad5_reset() {
    this->freqshift_tilde_21_h_biquad5_x1 = 0;
    this->freqshift_tilde_21_h_biquad5_x2 = 0;
    this->freqshift_tilde_21_h_biquad5_y1 = 0;
    this->freqshift_tilde_21_h_biquad5_y2 = 0;
}

void freqshift_tilde_21_h_biquad5_dspsetup() {
    this->freqshift_tilde_21_h_biquad5_reset();
}

number freqshift_tilde_21_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_21_h_biquad6_x1 * a1 + this->freqshift_tilde_21_h_biquad6_x2 * 1 - (this->freqshift_tilde_21_h_biquad6_y1 * b1 + this->freqshift_tilde_21_h_biquad6_y2 * b2);
    this->freqshift_tilde_21_h_biquad6_x2 = this->freqshift_tilde_21_h_biquad6_x1;
    this->freqshift_tilde_21_h_biquad6_x1 = x;
    this->freqshift_tilde_21_h_biquad6_y2 = this->freqshift_tilde_21_h_biquad6_y1;
    this->freqshift_tilde_21_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_21_h_biquad6_clear() {
    this->freqshift_tilde_21_h_biquad6_reset();
}

void freqshift_tilde_21_h_biquad6_reset() {
    this->freqshift_tilde_21_h_biquad6_x1 = 0;
    this->freqshift_tilde_21_h_biquad6_x2 = 0;
    this->freqshift_tilde_21_h_biquad6_y1 = 0;
    this->freqshift_tilde_21_h_biquad6_y2 = 0;
}

void freqshift_tilde_21_h_biquad6_dspsetup() {
    this->freqshift_tilde_21_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_21_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_21_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_21_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_21_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_21_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_21_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_21_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_21_h_clear() {
    this->freqshift_tilde_21_h_reset();
}

void freqshift_tilde_21_h_reset() {
    this->freqshift_tilde_21_h_biquad1_reset();
    this->freqshift_tilde_21_h_biquad2_reset();
    this->freqshift_tilde_21_h_biquad3_reset();
    this->freqshift_tilde_21_h_biquad4_reset();
    this->freqshift_tilde_21_h_biquad5_reset();
    this->freqshift_tilde_21_h_biquad6_reset();
}

void freqshift_tilde_21_h_dspsetup() {
    this->freqshift_tilde_21_h_reset();
}

number freqshift_tilde_21_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_21_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_21_p_conv;

    if (this->freqshift_tilde_21_p_currentPhase < 0.)
        this->freqshift_tilde_21_p_currentPhase = 1. + this->freqshift_tilde_21_p_currentPhase;

    if (this->freqshift_tilde_21_p_currentPhase > 1.)
        this->freqshift_tilde_21_p_currentPhase = this->freqshift_tilde_21_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_21_p_currentPhase;
    this->freqshift_tilde_21_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_21_p_reset() {
    this->freqshift_tilde_21_p_currentPhase = 0;
}

void freqshift_tilde_21_p_dspsetup() {
    this->freqshift_tilde_21_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_21_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_21_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_21_setupDone = true;
    this->freqshift_tilde_21_h_biquad1_dspsetup();
    this->freqshift_tilde_21_h_biquad2_dspsetup();
    this->freqshift_tilde_21_h_biquad3_dspsetup();
    this->freqshift_tilde_21_h_biquad4_dspsetup();
    this->freqshift_tilde_21_h_biquad5_dspsetup();
    this->freqshift_tilde_21_h_biquad6_dspsetup();
    this->freqshift_tilde_21_h_dspsetup();
    this->freqshift_tilde_21_p_dspsetup();
}

void param_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_20_value;
}

void param_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_20_value_set(preset["value"]);
}

number freqshift_tilde_22_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad1_x1 * a1 + this->freqshift_tilde_22_h_biquad1_x2 * 1 - (this->freqshift_tilde_22_h_biquad1_y1 * b1 + this->freqshift_tilde_22_h_biquad1_y2 * b2);
    this->freqshift_tilde_22_h_biquad1_x2 = this->freqshift_tilde_22_h_biquad1_x1;
    this->freqshift_tilde_22_h_biquad1_x1 = x;
    this->freqshift_tilde_22_h_biquad1_y2 = this->freqshift_tilde_22_h_biquad1_y1;
    this->freqshift_tilde_22_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad1_clear() {
    this->freqshift_tilde_22_h_biquad1_reset();
}

void freqshift_tilde_22_h_biquad1_reset() {
    this->freqshift_tilde_22_h_biquad1_x1 = 0;
    this->freqshift_tilde_22_h_biquad1_x2 = 0;
    this->freqshift_tilde_22_h_biquad1_y1 = 0;
    this->freqshift_tilde_22_h_biquad1_y2 = 0;
}

void freqshift_tilde_22_h_biquad1_dspsetup() {
    this->freqshift_tilde_22_h_biquad1_reset();
}

number freqshift_tilde_22_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad2_x1 * a1 + this->freqshift_tilde_22_h_biquad2_x2 * 1 - (this->freqshift_tilde_22_h_biquad2_y1 * b1 + this->freqshift_tilde_22_h_biquad2_y2 * b2);
    this->freqshift_tilde_22_h_biquad2_x2 = this->freqshift_tilde_22_h_biquad2_x1;
    this->freqshift_tilde_22_h_biquad2_x1 = x;
    this->freqshift_tilde_22_h_biquad2_y2 = this->freqshift_tilde_22_h_biquad2_y1;
    this->freqshift_tilde_22_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad2_clear() {
    this->freqshift_tilde_22_h_biquad2_reset();
}

void freqshift_tilde_22_h_biquad2_reset() {
    this->freqshift_tilde_22_h_biquad2_x1 = 0;
    this->freqshift_tilde_22_h_biquad2_x2 = 0;
    this->freqshift_tilde_22_h_biquad2_y1 = 0;
    this->freqshift_tilde_22_h_biquad2_y2 = 0;
}

void freqshift_tilde_22_h_biquad2_dspsetup() {
    this->freqshift_tilde_22_h_biquad2_reset();
}

number freqshift_tilde_22_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad3_x1 * a1 + this->freqshift_tilde_22_h_biquad3_x2 * 1 - (this->freqshift_tilde_22_h_biquad3_y1 * b1 + this->freqshift_tilde_22_h_biquad3_y2 * b2);
    this->freqshift_tilde_22_h_biquad3_x2 = this->freqshift_tilde_22_h_biquad3_x1;
    this->freqshift_tilde_22_h_biquad3_x1 = x;
    this->freqshift_tilde_22_h_biquad3_y2 = this->freqshift_tilde_22_h_biquad3_y1;
    this->freqshift_tilde_22_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad3_clear() {
    this->freqshift_tilde_22_h_biquad3_reset();
}

void freqshift_tilde_22_h_biquad3_reset() {
    this->freqshift_tilde_22_h_biquad3_x1 = 0;
    this->freqshift_tilde_22_h_biquad3_x2 = 0;
    this->freqshift_tilde_22_h_biquad3_y1 = 0;
    this->freqshift_tilde_22_h_biquad3_y2 = 0;
}

void freqshift_tilde_22_h_biquad3_dspsetup() {
    this->freqshift_tilde_22_h_biquad3_reset();
}

number freqshift_tilde_22_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad4_x1 * a1 + this->freqshift_tilde_22_h_biquad4_x2 * 1 - (this->freqshift_tilde_22_h_biquad4_y1 * b1 + this->freqshift_tilde_22_h_biquad4_y2 * b2);
    this->freqshift_tilde_22_h_biquad4_x2 = this->freqshift_tilde_22_h_biquad4_x1;
    this->freqshift_tilde_22_h_biquad4_x1 = x;
    this->freqshift_tilde_22_h_biquad4_y2 = this->freqshift_tilde_22_h_biquad4_y1;
    this->freqshift_tilde_22_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad4_clear() {
    this->freqshift_tilde_22_h_biquad4_reset();
}

void freqshift_tilde_22_h_biquad4_reset() {
    this->freqshift_tilde_22_h_biquad4_x1 = 0;
    this->freqshift_tilde_22_h_biquad4_x2 = 0;
    this->freqshift_tilde_22_h_biquad4_y1 = 0;
    this->freqshift_tilde_22_h_biquad4_y2 = 0;
}

void freqshift_tilde_22_h_biquad4_dspsetup() {
    this->freqshift_tilde_22_h_biquad4_reset();
}

number freqshift_tilde_22_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad5_x1 * a1 + this->freqshift_tilde_22_h_biquad5_x2 * 1 - (this->freqshift_tilde_22_h_biquad5_y1 * b1 + this->freqshift_tilde_22_h_biquad5_y2 * b2);
    this->freqshift_tilde_22_h_biquad5_x2 = this->freqshift_tilde_22_h_biquad5_x1;
    this->freqshift_tilde_22_h_biquad5_x1 = x;
    this->freqshift_tilde_22_h_biquad5_y2 = this->freqshift_tilde_22_h_biquad5_y1;
    this->freqshift_tilde_22_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad5_clear() {
    this->freqshift_tilde_22_h_biquad5_reset();
}

void freqshift_tilde_22_h_biquad5_reset() {
    this->freqshift_tilde_22_h_biquad5_x1 = 0;
    this->freqshift_tilde_22_h_biquad5_x2 = 0;
    this->freqshift_tilde_22_h_biquad5_y1 = 0;
    this->freqshift_tilde_22_h_biquad5_y2 = 0;
}

void freqshift_tilde_22_h_biquad5_dspsetup() {
    this->freqshift_tilde_22_h_biquad5_reset();
}

number freqshift_tilde_22_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_22_h_biquad6_x1 * a1 + this->freqshift_tilde_22_h_biquad6_x2 * 1 - (this->freqshift_tilde_22_h_biquad6_y1 * b1 + this->freqshift_tilde_22_h_biquad6_y2 * b2);
    this->freqshift_tilde_22_h_biquad6_x2 = this->freqshift_tilde_22_h_biquad6_x1;
    this->freqshift_tilde_22_h_biquad6_x1 = x;
    this->freqshift_tilde_22_h_biquad6_y2 = this->freqshift_tilde_22_h_biquad6_y1;
    this->freqshift_tilde_22_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_22_h_biquad6_clear() {
    this->freqshift_tilde_22_h_biquad6_reset();
}

void freqshift_tilde_22_h_biquad6_reset() {
    this->freqshift_tilde_22_h_biquad6_x1 = 0;
    this->freqshift_tilde_22_h_biquad6_x2 = 0;
    this->freqshift_tilde_22_h_biquad6_y1 = 0;
    this->freqshift_tilde_22_h_biquad6_y2 = 0;
}

void freqshift_tilde_22_h_biquad6_dspsetup() {
    this->freqshift_tilde_22_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_22_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_22_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_22_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_22_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_22_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_22_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_22_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_22_h_clear() {
    this->freqshift_tilde_22_h_reset();
}

void freqshift_tilde_22_h_reset() {
    this->freqshift_tilde_22_h_biquad1_reset();
    this->freqshift_tilde_22_h_biquad2_reset();
    this->freqshift_tilde_22_h_biquad3_reset();
    this->freqshift_tilde_22_h_biquad4_reset();
    this->freqshift_tilde_22_h_biquad5_reset();
    this->freqshift_tilde_22_h_biquad6_reset();
}

void freqshift_tilde_22_h_dspsetup() {
    this->freqshift_tilde_22_h_reset();
}

number freqshift_tilde_22_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_22_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_22_p_conv;

    if (this->freqshift_tilde_22_p_currentPhase < 0.)
        this->freqshift_tilde_22_p_currentPhase = 1. + this->freqshift_tilde_22_p_currentPhase;

    if (this->freqshift_tilde_22_p_currentPhase > 1.)
        this->freqshift_tilde_22_p_currentPhase = this->freqshift_tilde_22_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_22_p_currentPhase;
    this->freqshift_tilde_22_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_22_p_reset() {
    this->freqshift_tilde_22_p_currentPhase = 0;
}

void freqshift_tilde_22_p_dspsetup() {
    this->freqshift_tilde_22_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_22_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_22_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_22_setupDone = true;
    this->freqshift_tilde_22_h_biquad1_dspsetup();
    this->freqshift_tilde_22_h_biquad2_dspsetup();
    this->freqshift_tilde_22_h_biquad3_dspsetup();
    this->freqshift_tilde_22_h_biquad4_dspsetup();
    this->freqshift_tilde_22_h_biquad5_dspsetup();
    this->freqshift_tilde_22_h_biquad6_dspsetup();
    this->freqshift_tilde_22_h_dspsetup();
    this->freqshift_tilde_22_p_dspsetup();
}

void param_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_21_value;
}

void param_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_21_value_set(preset["value"]);
}

number gaintilde_24_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_24_ramp_d_prev);
    this->gaintilde_24_ramp_d_prev = x;
    return temp;
}

void gaintilde_24_ramp_d_dspsetup() {
    this->gaintilde_24_ramp_d_reset();
}

void gaintilde_24_ramp_d_reset() {
    this->gaintilde_24_ramp_d_prev = 0;
}

number gaintilde_24_ramp_next(number x, number up, number down) {
    if (this->gaintilde_24_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_24_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_24_ramp_index = _up;
            this->gaintilde_24_ramp_increment = (x - this->gaintilde_24_ramp_prev) / _up;
        } else if (x < this->gaintilde_24_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_24_ramp_index = _down;
            this->gaintilde_24_ramp_increment = (x - this->gaintilde_24_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_24_ramp_index > 0) {
        this->gaintilde_24_ramp_prev += this->gaintilde_24_ramp_increment;
        this->gaintilde_24_ramp_index -= 1;
    } else {
        this->gaintilde_24_ramp_prev = x;
    }

    return this->gaintilde_24_ramp_prev;
}

void gaintilde_24_ramp_reset() {
    this->gaintilde_24_ramp_prev = 0;
    this->gaintilde_24_ramp_index = 0;
    this->gaintilde_24_ramp_increment = 0;
    this->gaintilde_24_ramp_d_reset();
}

void gaintilde_24_init() {
    this->gaintilde_24_loginc = rnbo_log(1.072);
    this->gaintilde_24_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_24_loginc));
}

void gaintilde_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_24_value;
}

void gaintilde_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_24_value_set(preset["value"]);
}

void gaintilde_24_dspsetup(bool force) {
    if ((bool)(this->gaintilde_24_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_24_setupDone = true;
    this->gaintilde_24_ramp_d_dspsetup();
}

number gaintilde_25_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_25_ramp_d_prev);
    this->gaintilde_25_ramp_d_prev = x;
    return temp;
}

void gaintilde_25_ramp_d_dspsetup() {
    this->gaintilde_25_ramp_d_reset();
}

void gaintilde_25_ramp_d_reset() {
    this->gaintilde_25_ramp_d_prev = 0;
}

number gaintilde_25_ramp_next(number x, number up, number down) {
    if (this->gaintilde_25_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_25_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_25_ramp_index = _up;
            this->gaintilde_25_ramp_increment = (x - this->gaintilde_25_ramp_prev) / _up;
        } else if (x < this->gaintilde_25_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_25_ramp_index = _down;
            this->gaintilde_25_ramp_increment = (x - this->gaintilde_25_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_25_ramp_index > 0) {
        this->gaintilde_25_ramp_prev += this->gaintilde_25_ramp_increment;
        this->gaintilde_25_ramp_index -= 1;
    } else {
        this->gaintilde_25_ramp_prev = x;
    }

    return this->gaintilde_25_ramp_prev;
}

void gaintilde_25_ramp_reset() {
    this->gaintilde_25_ramp_prev = 0;
    this->gaintilde_25_ramp_index = 0;
    this->gaintilde_25_ramp_increment = 0;
    this->gaintilde_25_ramp_d_reset();
}

void gaintilde_25_init() {
    this->gaintilde_25_loginc = rnbo_log(1.072);
    this->gaintilde_25_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_25_loginc));
}

void gaintilde_25_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_25_value;
}

void gaintilde_25_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_25_value_set(preset["value"]);
}

void gaintilde_25_dspsetup(bool force) {
    if ((bool)(this->gaintilde_25_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_25_setupDone = true;
    this->gaintilde_25_ramp_d_dspsetup();
}

number freqshift_tilde_23_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad1_x1 * a1 + this->freqshift_tilde_23_h_biquad1_x2 * 1 - (this->freqshift_tilde_23_h_biquad1_y1 * b1 + this->freqshift_tilde_23_h_biquad1_y2 * b2);
    this->freqshift_tilde_23_h_biquad1_x2 = this->freqshift_tilde_23_h_biquad1_x1;
    this->freqshift_tilde_23_h_biquad1_x1 = x;
    this->freqshift_tilde_23_h_biquad1_y2 = this->freqshift_tilde_23_h_biquad1_y1;
    this->freqshift_tilde_23_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad1_clear() {
    this->freqshift_tilde_23_h_biquad1_reset();
}

void freqshift_tilde_23_h_biquad1_reset() {
    this->freqshift_tilde_23_h_biquad1_x1 = 0;
    this->freqshift_tilde_23_h_biquad1_x2 = 0;
    this->freqshift_tilde_23_h_biquad1_y1 = 0;
    this->freqshift_tilde_23_h_biquad1_y2 = 0;
}

void freqshift_tilde_23_h_biquad1_dspsetup() {
    this->freqshift_tilde_23_h_biquad1_reset();
}

number freqshift_tilde_23_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad2_x1 * a1 + this->freqshift_tilde_23_h_biquad2_x2 * 1 - (this->freqshift_tilde_23_h_biquad2_y1 * b1 + this->freqshift_tilde_23_h_biquad2_y2 * b2);
    this->freqshift_tilde_23_h_biquad2_x2 = this->freqshift_tilde_23_h_biquad2_x1;
    this->freqshift_tilde_23_h_biquad2_x1 = x;
    this->freqshift_tilde_23_h_biquad2_y2 = this->freqshift_tilde_23_h_biquad2_y1;
    this->freqshift_tilde_23_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad2_clear() {
    this->freqshift_tilde_23_h_biquad2_reset();
}

void freqshift_tilde_23_h_biquad2_reset() {
    this->freqshift_tilde_23_h_biquad2_x1 = 0;
    this->freqshift_tilde_23_h_biquad2_x2 = 0;
    this->freqshift_tilde_23_h_biquad2_y1 = 0;
    this->freqshift_tilde_23_h_biquad2_y2 = 0;
}

void freqshift_tilde_23_h_biquad2_dspsetup() {
    this->freqshift_tilde_23_h_biquad2_reset();
}

number freqshift_tilde_23_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad3_x1 * a1 + this->freqshift_tilde_23_h_biquad3_x2 * 1 - (this->freqshift_tilde_23_h_biquad3_y1 * b1 + this->freqshift_tilde_23_h_biquad3_y2 * b2);
    this->freqshift_tilde_23_h_biquad3_x2 = this->freqshift_tilde_23_h_biquad3_x1;
    this->freqshift_tilde_23_h_biquad3_x1 = x;
    this->freqshift_tilde_23_h_biquad3_y2 = this->freqshift_tilde_23_h_biquad3_y1;
    this->freqshift_tilde_23_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad3_clear() {
    this->freqshift_tilde_23_h_biquad3_reset();
}

void freqshift_tilde_23_h_biquad3_reset() {
    this->freqshift_tilde_23_h_biquad3_x1 = 0;
    this->freqshift_tilde_23_h_biquad3_x2 = 0;
    this->freqshift_tilde_23_h_biquad3_y1 = 0;
    this->freqshift_tilde_23_h_biquad3_y2 = 0;
}

void freqshift_tilde_23_h_biquad3_dspsetup() {
    this->freqshift_tilde_23_h_biquad3_reset();
}

number freqshift_tilde_23_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad4_x1 * a1 + this->freqshift_tilde_23_h_biquad4_x2 * 1 - (this->freqshift_tilde_23_h_biquad4_y1 * b1 + this->freqshift_tilde_23_h_biquad4_y2 * b2);
    this->freqshift_tilde_23_h_biquad4_x2 = this->freqshift_tilde_23_h_biquad4_x1;
    this->freqshift_tilde_23_h_biquad4_x1 = x;
    this->freqshift_tilde_23_h_biquad4_y2 = this->freqshift_tilde_23_h_biquad4_y1;
    this->freqshift_tilde_23_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad4_clear() {
    this->freqshift_tilde_23_h_biquad4_reset();
}

void freqshift_tilde_23_h_biquad4_reset() {
    this->freqshift_tilde_23_h_biquad4_x1 = 0;
    this->freqshift_tilde_23_h_biquad4_x2 = 0;
    this->freqshift_tilde_23_h_biquad4_y1 = 0;
    this->freqshift_tilde_23_h_biquad4_y2 = 0;
}

void freqshift_tilde_23_h_biquad4_dspsetup() {
    this->freqshift_tilde_23_h_biquad4_reset();
}

number freqshift_tilde_23_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad5_x1 * a1 + this->freqshift_tilde_23_h_biquad5_x2 * 1 - (this->freqshift_tilde_23_h_biquad5_y1 * b1 + this->freqshift_tilde_23_h_biquad5_y2 * b2);
    this->freqshift_tilde_23_h_biquad5_x2 = this->freqshift_tilde_23_h_biquad5_x1;
    this->freqshift_tilde_23_h_biquad5_x1 = x;
    this->freqshift_tilde_23_h_biquad5_y2 = this->freqshift_tilde_23_h_biquad5_y1;
    this->freqshift_tilde_23_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad5_clear() {
    this->freqshift_tilde_23_h_biquad5_reset();
}

void freqshift_tilde_23_h_biquad5_reset() {
    this->freqshift_tilde_23_h_biquad5_x1 = 0;
    this->freqshift_tilde_23_h_biquad5_x2 = 0;
    this->freqshift_tilde_23_h_biquad5_y1 = 0;
    this->freqshift_tilde_23_h_biquad5_y2 = 0;
}

void freqshift_tilde_23_h_biquad5_dspsetup() {
    this->freqshift_tilde_23_h_biquad5_reset();
}

number freqshift_tilde_23_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_23_h_biquad6_x1 * a1 + this->freqshift_tilde_23_h_biquad6_x2 * 1 - (this->freqshift_tilde_23_h_biquad6_y1 * b1 + this->freqshift_tilde_23_h_biquad6_y2 * b2);
    this->freqshift_tilde_23_h_biquad6_x2 = this->freqshift_tilde_23_h_biquad6_x1;
    this->freqshift_tilde_23_h_biquad6_x1 = x;
    this->freqshift_tilde_23_h_biquad6_y2 = this->freqshift_tilde_23_h_biquad6_y1;
    this->freqshift_tilde_23_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_23_h_biquad6_clear() {
    this->freqshift_tilde_23_h_biquad6_reset();
}

void freqshift_tilde_23_h_biquad6_reset() {
    this->freqshift_tilde_23_h_biquad6_x1 = 0;
    this->freqshift_tilde_23_h_biquad6_x2 = 0;
    this->freqshift_tilde_23_h_biquad6_y1 = 0;
    this->freqshift_tilde_23_h_biquad6_y2 = 0;
}

void freqshift_tilde_23_h_biquad6_dspsetup() {
    this->freqshift_tilde_23_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_23_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_23_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_23_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_23_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_23_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_23_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_23_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_23_h_clear() {
    this->freqshift_tilde_23_h_reset();
}

void freqshift_tilde_23_h_reset() {
    this->freqshift_tilde_23_h_biquad1_reset();
    this->freqshift_tilde_23_h_biquad2_reset();
    this->freqshift_tilde_23_h_biquad3_reset();
    this->freqshift_tilde_23_h_biquad4_reset();
    this->freqshift_tilde_23_h_biquad5_reset();
    this->freqshift_tilde_23_h_biquad6_reset();
}

void freqshift_tilde_23_h_dspsetup() {
    this->freqshift_tilde_23_h_reset();
}

number freqshift_tilde_23_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_23_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_23_p_conv;

    if (this->freqshift_tilde_23_p_currentPhase < 0.)
        this->freqshift_tilde_23_p_currentPhase = 1. + this->freqshift_tilde_23_p_currentPhase;

    if (this->freqshift_tilde_23_p_currentPhase > 1.)
        this->freqshift_tilde_23_p_currentPhase = this->freqshift_tilde_23_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_23_p_currentPhase;
    this->freqshift_tilde_23_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_23_p_reset() {
    this->freqshift_tilde_23_p_currentPhase = 0;
}

void freqshift_tilde_23_p_dspsetup() {
    this->freqshift_tilde_23_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_23_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_23_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_23_setupDone = true;
    this->freqshift_tilde_23_h_biquad1_dspsetup();
    this->freqshift_tilde_23_h_biquad2_dspsetup();
    this->freqshift_tilde_23_h_biquad3_dspsetup();
    this->freqshift_tilde_23_h_biquad4_dspsetup();
    this->freqshift_tilde_23_h_biquad5_dspsetup();
    this->freqshift_tilde_23_h_biquad6_dspsetup();
    this->freqshift_tilde_23_h_dspsetup();
    this->freqshift_tilde_23_p_dspsetup();
}

number freqshift_tilde_24_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad1_x1 * a1 + this->freqshift_tilde_24_h_biquad1_x2 * 1 - (this->freqshift_tilde_24_h_biquad1_y1 * b1 + this->freqshift_tilde_24_h_biquad1_y2 * b2);
    this->freqshift_tilde_24_h_biquad1_x2 = this->freqshift_tilde_24_h_biquad1_x1;
    this->freqshift_tilde_24_h_biquad1_x1 = x;
    this->freqshift_tilde_24_h_biquad1_y2 = this->freqshift_tilde_24_h_biquad1_y1;
    this->freqshift_tilde_24_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad1_clear() {
    this->freqshift_tilde_24_h_biquad1_reset();
}

void freqshift_tilde_24_h_biquad1_reset() {
    this->freqshift_tilde_24_h_biquad1_x1 = 0;
    this->freqshift_tilde_24_h_biquad1_x2 = 0;
    this->freqshift_tilde_24_h_biquad1_y1 = 0;
    this->freqshift_tilde_24_h_biquad1_y2 = 0;
}

void freqshift_tilde_24_h_biquad1_dspsetup() {
    this->freqshift_tilde_24_h_biquad1_reset();
}

number freqshift_tilde_24_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad2_x1 * a1 + this->freqshift_tilde_24_h_biquad2_x2 * 1 - (this->freqshift_tilde_24_h_biquad2_y1 * b1 + this->freqshift_tilde_24_h_biquad2_y2 * b2);
    this->freqshift_tilde_24_h_biquad2_x2 = this->freqshift_tilde_24_h_biquad2_x1;
    this->freqshift_tilde_24_h_biquad2_x1 = x;
    this->freqshift_tilde_24_h_biquad2_y2 = this->freqshift_tilde_24_h_biquad2_y1;
    this->freqshift_tilde_24_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad2_clear() {
    this->freqshift_tilde_24_h_biquad2_reset();
}

void freqshift_tilde_24_h_biquad2_reset() {
    this->freqshift_tilde_24_h_biquad2_x1 = 0;
    this->freqshift_tilde_24_h_biquad2_x2 = 0;
    this->freqshift_tilde_24_h_biquad2_y1 = 0;
    this->freqshift_tilde_24_h_biquad2_y2 = 0;
}

void freqshift_tilde_24_h_biquad2_dspsetup() {
    this->freqshift_tilde_24_h_biquad2_reset();
}

number freqshift_tilde_24_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad3_x1 * a1 + this->freqshift_tilde_24_h_biquad3_x2 * 1 - (this->freqshift_tilde_24_h_biquad3_y1 * b1 + this->freqshift_tilde_24_h_biquad3_y2 * b2);
    this->freqshift_tilde_24_h_biquad3_x2 = this->freqshift_tilde_24_h_biquad3_x1;
    this->freqshift_tilde_24_h_biquad3_x1 = x;
    this->freqshift_tilde_24_h_biquad3_y2 = this->freqshift_tilde_24_h_biquad3_y1;
    this->freqshift_tilde_24_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad3_clear() {
    this->freqshift_tilde_24_h_biquad3_reset();
}

void freqshift_tilde_24_h_biquad3_reset() {
    this->freqshift_tilde_24_h_biquad3_x1 = 0;
    this->freqshift_tilde_24_h_biquad3_x2 = 0;
    this->freqshift_tilde_24_h_biquad3_y1 = 0;
    this->freqshift_tilde_24_h_biquad3_y2 = 0;
}

void freqshift_tilde_24_h_biquad3_dspsetup() {
    this->freqshift_tilde_24_h_biquad3_reset();
}

number freqshift_tilde_24_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad4_x1 * a1 + this->freqshift_tilde_24_h_biquad4_x2 * 1 - (this->freqshift_tilde_24_h_biquad4_y1 * b1 + this->freqshift_tilde_24_h_biquad4_y2 * b2);
    this->freqshift_tilde_24_h_biquad4_x2 = this->freqshift_tilde_24_h_biquad4_x1;
    this->freqshift_tilde_24_h_biquad4_x1 = x;
    this->freqshift_tilde_24_h_biquad4_y2 = this->freqshift_tilde_24_h_biquad4_y1;
    this->freqshift_tilde_24_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad4_clear() {
    this->freqshift_tilde_24_h_biquad4_reset();
}

void freqshift_tilde_24_h_biquad4_reset() {
    this->freqshift_tilde_24_h_biquad4_x1 = 0;
    this->freqshift_tilde_24_h_biquad4_x2 = 0;
    this->freqshift_tilde_24_h_biquad4_y1 = 0;
    this->freqshift_tilde_24_h_biquad4_y2 = 0;
}

void freqshift_tilde_24_h_biquad4_dspsetup() {
    this->freqshift_tilde_24_h_biquad4_reset();
}

number freqshift_tilde_24_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad5_x1 * a1 + this->freqshift_tilde_24_h_biquad5_x2 * 1 - (this->freqshift_tilde_24_h_biquad5_y1 * b1 + this->freqshift_tilde_24_h_biquad5_y2 * b2);
    this->freqshift_tilde_24_h_biquad5_x2 = this->freqshift_tilde_24_h_biquad5_x1;
    this->freqshift_tilde_24_h_biquad5_x1 = x;
    this->freqshift_tilde_24_h_biquad5_y2 = this->freqshift_tilde_24_h_biquad5_y1;
    this->freqshift_tilde_24_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad5_clear() {
    this->freqshift_tilde_24_h_biquad5_reset();
}

void freqshift_tilde_24_h_biquad5_reset() {
    this->freqshift_tilde_24_h_biquad5_x1 = 0;
    this->freqshift_tilde_24_h_biquad5_x2 = 0;
    this->freqshift_tilde_24_h_biquad5_y1 = 0;
    this->freqshift_tilde_24_h_biquad5_y2 = 0;
}

void freqshift_tilde_24_h_biquad5_dspsetup() {
    this->freqshift_tilde_24_h_biquad5_reset();
}

number freqshift_tilde_24_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_24_h_biquad6_x1 * a1 + this->freqshift_tilde_24_h_biquad6_x2 * 1 - (this->freqshift_tilde_24_h_biquad6_y1 * b1 + this->freqshift_tilde_24_h_biquad6_y2 * b2);
    this->freqshift_tilde_24_h_biquad6_x2 = this->freqshift_tilde_24_h_biquad6_x1;
    this->freqshift_tilde_24_h_biquad6_x1 = x;
    this->freqshift_tilde_24_h_biquad6_y2 = this->freqshift_tilde_24_h_biquad6_y1;
    this->freqshift_tilde_24_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_24_h_biquad6_clear() {
    this->freqshift_tilde_24_h_biquad6_reset();
}

void freqshift_tilde_24_h_biquad6_reset() {
    this->freqshift_tilde_24_h_biquad6_x1 = 0;
    this->freqshift_tilde_24_h_biquad6_x2 = 0;
    this->freqshift_tilde_24_h_biquad6_y1 = 0;
    this->freqshift_tilde_24_h_biquad6_y2 = 0;
}

void freqshift_tilde_24_h_biquad6_dspsetup() {
    this->freqshift_tilde_24_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_24_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_24_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_24_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_24_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_24_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_24_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_24_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_24_h_clear() {
    this->freqshift_tilde_24_h_reset();
}

void freqshift_tilde_24_h_reset() {
    this->freqshift_tilde_24_h_biquad1_reset();
    this->freqshift_tilde_24_h_biquad2_reset();
    this->freqshift_tilde_24_h_biquad3_reset();
    this->freqshift_tilde_24_h_biquad4_reset();
    this->freqshift_tilde_24_h_biquad5_reset();
    this->freqshift_tilde_24_h_biquad6_reset();
}

void freqshift_tilde_24_h_dspsetup() {
    this->freqshift_tilde_24_h_reset();
}

number freqshift_tilde_24_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_24_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_24_p_conv;

    if (this->freqshift_tilde_24_p_currentPhase < 0.)
        this->freqshift_tilde_24_p_currentPhase = 1. + this->freqshift_tilde_24_p_currentPhase;

    if (this->freqshift_tilde_24_p_currentPhase > 1.)
        this->freqshift_tilde_24_p_currentPhase = this->freqshift_tilde_24_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_24_p_currentPhase;
    this->freqshift_tilde_24_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_24_p_reset() {
    this->freqshift_tilde_24_p_currentPhase = 0;
}

void freqshift_tilde_24_p_dspsetup() {
    this->freqshift_tilde_24_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_24_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_24_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_24_setupDone = true;
    this->freqshift_tilde_24_h_biquad1_dspsetup();
    this->freqshift_tilde_24_h_biquad2_dspsetup();
    this->freqshift_tilde_24_h_biquad3_dspsetup();
    this->freqshift_tilde_24_h_biquad4_dspsetup();
    this->freqshift_tilde_24_h_biquad5_dspsetup();
    this->freqshift_tilde_24_h_biquad6_dspsetup();
    this->freqshift_tilde_24_h_dspsetup();
    this->freqshift_tilde_24_p_dspsetup();
}

number gaintilde_26_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_26_ramp_d_prev);
    this->gaintilde_26_ramp_d_prev = x;
    return temp;
}

void gaintilde_26_ramp_d_dspsetup() {
    this->gaintilde_26_ramp_d_reset();
}

void gaintilde_26_ramp_d_reset() {
    this->gaintilde_26_ramp_d_prev = 0;
}

number gaintilde_26_ramp_next(number x, number up, number down) {
    if (this->gaintilde_26_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_26_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_26_ramp_index = _up;
            this->gaintilde_26_ramp_increment = (x - this->gaintilde_26_ramp_prev) / _up;
        } else if (x < this->gaintilde_26_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_26_ramp_index = _down;
            this->gaintilde_26_ramp_increment = (x - this->gaintilde_26_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_26_ramp_index > 0) {
        this->gaintilde_26_ramp_prev += this->gaintilde_26_ramp_increment;
        this->gaintilde_26_ramp_index -= 1;
    } else {
        this->gaintilde_26_ramp_prev = x;
    }

    return this->gaintilde_26_ramp_prev;
}

void gaintilde_26_ramp_reset() {
    this->gaintilde_26_ramp_prev = 0;
    this->gaintilde_26_ramp_index = 0;
    this->gaintilde_26_ramp_increment = 0;
    this->gaintilde_26_ramp_d_reset();
}

void gaintilde_26_init() {
    this->gaintilde_26_loginc = rnbo_log(1.072);
    this->gaintilde_26_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_26_loginc));
}

void gaintilde_26_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_26_value;
}

void gaintilde_26_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_26_value_set(preset["value"]);
}

void gaintilde_26_dspsetup(bool force) {
    if ((bool)(this->gaintilde_26_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_26_setupDone = true;
    this->gaintilde_26_ramp_d_dspsetup();
}

number gaintilde_27_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_27_ramp_d_prev);
    this->gaintilde_27_ramp_d_prev = x;
    return temp;
}

void gaintilde_27_ramp_d_dspsetup() {
    this->gaintilde_27_ramp_d_reset();
}

void gaintilde_27_ramp_d_reset() {
    this->gaintilde_27_ramp_d_prev = 0;
}

number gaintilde_27_ramp_next(number x, number up, number down) {
    if (this->gaintilde_27_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_27_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_27_ramp_index = _up;
            this->gaintilde_27_ramp_increment = (x - this->gaintilde_27_ramp_prev) / _up;
        } else if (x < this->gaintilde_27_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_27_ramp_index = _down;
            this->gaintilde_27_ramp_increment = (x - this->gaintilde_27_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_27_ramp_index > 0) {
        this->gaintilde_27_ramp_prev += this->gaintilde_27_ramp_increment;
        this->gaintilde_27_ramp_index -= 1;
    } else {
        this->gaintilde_27_ramp_prev = x;
    }

    return this->gaintilde_27_ramp_prev;
}

void gaintilde_27_ramp_reset() {
    this->gaintilde_27_ramp_prev = 0;
    this->gaintilde_27_ramp_index = 0;
    this->gaintilde_27_ramp_increment = 0;
    this->gaintilde_27_ramp_d_reset();
}

void gaintilde_27_init() {
    this->gaintilde_27_loginc = rnbo_log(1.072);
    this->gaintilde_27_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_27_loginc));
}

void gaintilde_27_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_27_value;
}

void gaintilde_27_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_27_value_set(preset["value"]);
}

void gaintilde_27_dspsetup(bool force) {
    if ((bool)(this->gaintilde_27_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_27_setupDone = true;
    this->gaintilde_27_ramp_d_dspsetup();
}

number freqshift_tilde_25_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad1_x1 * a1 + this->freqshift_tilde_25_h_biquad1_x2 * 1 - (this->freqshift_tilde_25_h_biquad1_y1 * b1 + this->freqshift_tilde_25_h_biquad1_y2 * b2);
    this->freqshift_tilde_25_h_biquad1_x2 = this->freqshift_tilde_25_h_biquad1_x1;
    this->freqshift_tilde_25_h_biquad1_x1 = x;
    this->freqshift_tilde_25_h_biquad1_y2 = this->freqshift_tilde_25_h_biquad1_y1;
    this->freqshift_tilde_25_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad1_clear() {
    this->freqshift_tilde_25_h_biquad1_reset();
}

void freqshift_tilde_25_h_biquad1_reset() {
    this->freqshift_tilde_25_h_biquad1_x1 = 0;
    this->freqshift_tilde_25_h_biquad1_x2 = 0;
    this->freqshift_tilde_25_h_biquad1_y1 = 0;
    this->freqshift_tilde_25_h_biquad1_y2 = 0;
}

void freqshift_tilde_25_h_biquad1_dspsetup() {
    this->freqshift_tilde_25_h_biquad1_reset();
}

number freqshift_tilde_25_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad2_x1 * a1 + this->freqshift_tilde_25_h_biquad2_x2 * 1 - (this->freqshift_tilde_25_h_biquad2_y1 * b1 + this->freqshift_tilde_25_h_biquad2_y2 * b2);
    this->freqshift_tilde_25_h_biquad2_x2 = this->freqshift_tilde_25_h_biquad2_x1;
    this->freqshift_tilde_25_h_biquad2_x1 = x;
    this->freqshift_tilde_25_h_biquad2_y2 = this->freqshift_tilde_25_h_biquad2_y1;
    this->freqshift_tilde_25_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad2_clear() {
    this->freqshift_tilde_25_h_biquad2_reset();
}

void freqshift_tilde_25_h_biquad2_reset() {
    this->freqshift_tilde_25_h_biquad2_x1 = 0;
    this->freqshift_tilde_25_h_biquad2_x2 = 0;
    this->freqshift_tilde_25_h_biquad2_y1 = 0;
    this->freqshift_tilde_25_h_biquad2_y2 = 0;
}

void freqshift_tilde_25_h_biquad2_dspsetup() {
    this->freqshift_tilde_25_h_biquad2_reset();
}

number freqshift_tilde_25_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad3_x1 * a1 + this->freqshift_tilde_25_h_biquad3_x2 * 1 - (this->freqshift_tilde_25_h_biquad3_y1 * b1 + this->freqshift_tilde_25_h_biquad3_y2 * b2);
    this->freqshift_tilde_25_h_biquad3_x2 = this->freqshift_tilde_25_h_biquad3_x1;
    this->freqshift_tilde_25_h_biquad3_x1 = x;
    this->freqshift_tilde_25_h_biquad3_y2 = this->freqshift_tilde_25_h_biquad3_y1;
    this->freqshift_tilde_25_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad3_clear() {
    this->freqshift_tilde_25_h_biquad3_reset();
}

void freqshift_tilde_25_h_biquad3_reset() {
    this->freqshift_tilde_25_h_biquad3_x1 = 0;
    this->freqshift_tilde_25_h_biquad3_x2 = 0;
    this->freqshift_tilde_25_h_biquad3_y1 = 0;
    this->freqshift_tilde_25_h_biquad3_y2 = 0;
}

void freqshift_tilde_25_h_biquad3_dspsetup() {
    this->freqshift_tilde_25_h_biquad3_reset();
}

number freqshift_tilde_25_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad4_x1 * a1 + this->freqshift_tilde_25_h_biquad4_x2 * 1 - (this->freqshift_tilde_25_h_biquad4_y1 * b1 + this->freqshift_tilde_25_h_biquad4_y2 * b2);
    this->freqshift_tilde_25_h_biquad4_x2 = this->freqshift_tilde_25_h_biquad4_x1;
    this->freqshift_tilde_25_h_biquad4_x1 = x;
    this->freqshift_tilde_25_h_biquad4_y2 = this->freqshift_tilde_25_h_biquad4_y1;
    this->freqshift_tilde_25_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad4_clear() {
    this->freqshift_tilde_25_h_biquad4_reset();
}

void freqshift_tilde_25_h_biquad4_reset() {
    this->freqshift_tilde_25_h_biquad4_x1 = 0;
    this->freqshift_tilde_25_h_biquad4_x2 = 0;
    this->freqshift_tilde_25_h_biquad4_y1 = 0;
    this->freqshift_tilde_25_h_biquad4_y2 = 0;
}

void freqshift_tilde_25_h_biquad4_dspsetup() {
    this->freqshift_tilde_25_h_biquad4_reset();
}

number freqshift_tilde_25_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad5_x1 * a1 + this->freqshift_tilde_25_h_biquad5_x2 * 1 - (this->freqshift_tilde_25_h_biquad5_y1 * b1 + this->freqshift_tilde_25_h_biquad5_y2 * b2);
    this->freqshift_tilde_25_h_biquad5_x2 = this->freqshift_tilde_25_h_biquad5_x1;
    this->freqshift_tilde_25_h_biquad5_x1 = x;
    this->freqshift_tilde_25_h_biquad5_y2 = this->freqshift_tilde_25_h_biquad5_y1;
    this->freqshift_tilde_25_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad5_clear() {
    this->freqshift_tilde_25_h_biquad5_reset();
}

void freqshift_tilde_25_h_biquad5_reset() {
    this->freqshift_tilde_25_h_biquad5_x1 = 0;
    this->freqshift_tilde_25_h_biquad5_x2 = 0;
    this->freqshift_tilde_25_h_biquad5_y1 = 0;
    this->freqshift_tilde_25_h_biquad5_y2 = 0;
}

void freqshift_tilde_25_h_biquad5_dspsetup() {
    this->freqshift_tilde_25_h_biquad5_reset();
}

number freqshift_tilde_25_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_25_h_biquad6_x1 * a1 + this->freqshift_tilde_25_h_biquad6_x2 * 1 - (this->freqshift_tilde_25_h_biquad6_y1 * b1 + this->freqshift_tilde_25_h_biquad6_y2 * b2);
    this->freqshift_tilde_25_h_biquad6_x2 = this->freqshift_tilde_25_h_biquad6_x1;
    this->freqshift_tilde_25_h_biquad6_x1 = x;
    this->freqshift_tilde_25_h_biquad6_y2 = this->freqshift_tilde_25_h_biquad6_y1;
    this->freqshift_tilde_25_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_25_h_biquad6_clear() {
    this->freqshift_tilde_25_h_biquad6_reset();
}

void freqshift_tilde_25_h_biquad6_reset() {
    this->freqshift_tilde_25_h_biquad6_x1 = 0;
    this->freqshift_tilde_25_h_biquad6_x2 = 0;
    this->freqshift_tilde_25_h_biquad6_y1 = 0;
    this->freqshift_tilde_25_h_biquad6_y2 = 0;
}

void freqshift_tilde_25_h_biquad6_dspsetup() {
    this->freqshift_tilde_25_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_25_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_25_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_25_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_25_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_25_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_25_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_25_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_25_h_clear() {
    this->freqshift_tilde_25_h_reset();
}

void freqshift_tilde_25_h_reset() {
    this->freqshift_tilde_25_h_biquad1_reset();
    this->freqshift_tilde_25_h_biquad2_reset();
    this->freqshift_tilde_25_h_biquad3_reset();
    this->freqshift_tilde_25_h_biquad4_reset();
    this->freqshift_tilde_25_h_biquad5_reset();
    this->freqshift_tilde_25_h_biquad6_reset();
}

void freqshift_tilde_25_h_dspsetup() {
    this->freqshift_tilde_25_h_reset();
}

number freqshift_tilde_25_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_25_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_25_p_conv;

    if (this->freqshift_tilde_25_p_currentPhase < 0.)
        this->freqshift_tilde_25_p_currentPhase = 1. + this->freqshift_tilde_25_p_currentPhase;

    if (this->freqshift_tilde_25_p_currentPhase > 1.)
        this->freqshift_tilde_25_p_currentPhase = this->freqshift_tilde_25_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_25_p_currentPhase;
    this->freqshift_tilde_25_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_25_p_reset() {
    this->freqshift_tilde_25_p_currentPhase = 0;
}

void freqshift_tilde_25_p_dspsetup() {
    this->freqshift_tilde_25_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_25_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_25_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_25_setupDone = true;
    this->freqshift_tilde_25_h_biquad1_dspsetup();
    this->freqshift_tilde_25_h_biquad2_dspsetup();
    this->freqshift_tilde_25_h_biquad3_dspsetup();
    this->freqshift_tilde_25_h_biquad4_dspsetup();
    this->freqshift_tilde_25_h_biquad5_dspsetup();
    this->freqshift_tilde_25_h_biquad6_dspsetup();
    this->freqshift_tilde_25_h_dspsetup();
    this->freqshift_tilde_25_p_dspsetup();
}

number freqshift_tilde_26_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad1_x1 * a1 + this->freqshift_tilde_26_h_biquad1_x2 * 1 - (this->freqshift_tilde_26_h_biquad1_y1 * b1 + this->freqshift_tilde_26_h_biquad1_y2 * b2);
    this->freqshift_tilde_26_h_biquad1_x2 = this->freqshift_tilde_26_h_biquad1_x1;
    this->freqshift_tilde_26_h_biquad1_x1 = x;
    this->freqshift_tilde_26_h_biquad1_y2 = this->freqshift_tilde_26_h_biquad1_y1;
    this->freqshift_tilde_26_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad1_clear() {
    this->freqshift_tilde_26_h_biquad1_reset();
}

void freqshift_tilde_26_h_biquad1_reset() {
    this->freqshift_tilde_26_h_biquad1_x1 = 0;
    this->freqshift_tilde_26_h_biquad1_x2 = 0;
    this->freqshift_tilde_26_h_biquad1_y1 = 0;
    this->freqshift_tilde_26_h_biquad1_y2 = 0;
}

void freqshift_tilde_26_h_biquad1_dspsetup() {
    this->freqshift_tilde_26_h_biquad1_reset();
}

number freqshift_tilde_26_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad2_x1 * a1 + this->freqshift_tilde_26_h_biquad2_x2 * 1 - (this->freqshift_tilde_26_h_biquad2_y1 * b1 + this->freqshift_tilde_26_h_biquad2_y2 * b2);
    this->freqshift_tilde_26_h_biquad2_x2 = this->freqshift_tilde_26_h_biquad2_x1;
    this->freqshift_tilde_26_h_biquad2_x1 = x;
    this->freqshift_tilde_26_h_biquad2_y2 = this->freqshift_tilde_26_h_biquad2_y1;
    this->freqshift_tilde_26_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad2_clear() {
    this->freqshift_tilde_26_h_biquad2_reset();
}

void freqshift_tilde_26_h_biquad2_reset() {
    this->freqshift_tilde_26_h_biquad2_x1 = 0;
    this->freqshift_tilde_26_h_biquad2_x2 = 0;
    this->freqshift_tilde_26_h_biquad2_y1 = 0;
    this->freqshift_tilde_26_h_biquad2_y2 = 0;
}

void freqshift_tilde_26_h_biquad2_dspsetup() {
    this->freqshift_tilde_26_h_biquad2_reset();
}

number freqshift_tilde_26_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad3_x1 * a1 + this->freqshift_tilde_26_h_biquad3_x2 * 1 - (this->freqshift_tilde_26_h_biquad3_y1 * b1 + this->freqshift_tilde_26_h_biquad3_y2 * b2);
    this->freqshift_tilde_26_h_biquad3_x2 = this->freqshift_tilde_26_h_biquad3_x1;
    this->freqshift_tilde_26_h_biquad3_x1 = x;
    this->freqshift_tilde_26_h_biquad3_y2 = this->freqshift_tilde_26_h_biquad3_y1;
    this->freqshift_tilde_26_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad3_clear() {
    this->freqshift_tilde_26_h_biquad3_reset();
}

void freqshift_tilde_26_h_biquad3_reset() {
    this->freqshift_tilde_26_h_biquad3_x1 = 0;
    this->freqshift_tilde_26_h_biquad3_x2 = 0;
    this->freqshift_tilde_26_h_biquad3_y1 = 0;
    this->freqshift_tilde_26_h_biquad3_y2 = 0;
}

void freqshift_tilde_26_h_biquad3_dspsetup() {
    this->freqshift_tilde_26_h_biquad3_reset();
}

number freqshift_tilde_26_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad4_x1 * a1 + this->freqshift_tilde_26_h_biquad4_x2 * 1 - (this->freqshift_tilde_26_h_biquad4_y1 * b1 + this->freqshift_tilde_26_h_biquad4_y2 * b2);
    this->freqshift_tilde_26_h_biquad4_x2 = this->freqshift_tilde_26_h_biquad4_x1;
    this->freqshift_tilde_26_h_biquad4_x1 = x;
    this->freqshift_tilde_26_h_biquad4_y2 = this->freqshift_tilde_26_h_biquad4_y1;
    this->freqshift_tilde_26_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad4_clear() {
    this->freqshift_tilde_26_h_biquad4_reset();
}

void freqshift_tilde_26_h_biquad4_reset() {
    this->freqshift_tilde_26_h_biquad4_x1 = 0;
    this->freqshift_tilde_26_h_biquad4_x2 = 0;
    this->freqshift_tilde_26_h_biquad4_y1 = 0;
    this->freqshift_tilde_26_h_biquad4_y2 = 0;
}

void freqshift_tilde_26_h_biquad4_dspsetup() {
    this->freqshift_tilde_26_h_biquad4_reset();
}

number freqshift_tilde_26_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad5_x1 * a1 + this->freqshift_tilde_26_h_biquad5_x2 * 1 - (this->freqshift_tilde_26_h_biquad5_y1 * b1 + this->freqshift_tilde_26_h_biquad5_y2 * b2);
    this->freqshift_tilde_26_h_biquad5_x2 = this->freqshift_tilde_26_h_biquad5_x1;
    this->freqshift_tilde_26_h_biquad5_x1 = x;
    this->freqshift_tilde_26_h_biquad5_y2 = this->freqshift_tilde_26_h_biquad5_y1;
    this->freqshift_tilde_26_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad5_clear() {
    this->freqshift_tilde_26_h_biquad5_reset();
}

void freqshift_tilde_26_h_biquad5_reset() {
    this->freqshift_tilde_26_h_biquad5_x1 = 0;
    this->freqshift_tilde_26_h_biquad5_x2 = 0;
    this->freqshift_tilde_26_h_biquad5_y1 = 0;
    this->freqshift_tilde_26_h_biquad5_y2 = 0;
}

void freqshift_tilde_26_h_biquad5_dspsetup() {
    this->freqshift_tilde_26_h_biquad5_reset();
}

number freqshift_tilde_26_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_26_h_biquad6_x1 * a1 + this->freqshift_tilde_26_h_biquad6_x2 * 1 - (this->freqshift_tilde_26_h_biquad6_y1 * b1 + this->freqshift_tilde_26_h_biquad6_y2 * b2);
    this->freqshift_tilde_26_h_biquad6_x2 = this->freqshift_tilde_26_h_biquad6_x1;
    this->freqshift_tilde_26_h_biquad6_x1 = x;
    this->freqshift_tilde_26_h_biquad6_y2 = this->freqshift_tilde_26_h_biquad6_y1;
    this->freqshift_tilde_26_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_26_h_biquad6_clear() {
    this->freqshift_tilde_26_h_biquad6_reset();
}

void freqshift_tilde_26_h_biquad6_reset() {
    this->freqshift_tilde_26_h_biquad6_x1 = 0;
    this->freqshift_tilde_26_h_biquad6_x2 = 0;
    this->freqshift_tilde_26_h_biquad6_y1 = 0;
    this->freqshift_tilde_26_h_biquad6_y2 = 0;
}

void freqshift_tilde_26_h_biquad6_dspsetup() {
    this->freqshift_tilde_26_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_26_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_26_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_26_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_26_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_26_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_26_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_26_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_26_h_clear() {
    this->freqshift_tilde_26_h_reset();
}

void freqshift_tilde_26_h_reset() {
    this->freqshift_tilde_26_h_biquad1_reset();
    this->freqshift_tilde_26_h_biquad2_reset();
    this->freqshift_tilde_26_h_biquad3_reset();
    this->freqshift_tilde_26_h_biquad4_reset();
    this->freqshift_tilde_26_h_biquad5_reset();
    this->freqshift_tilde_26_h_biquad6_reset();
}

void freqshift_tilde_26_h_dspsetup() {
    this->freqshift_tilde_26_h_reset();
}

number freqshift_tilde_26_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_26_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_26_p_conv;

    if (this->freqshift_tilde_26_p_currentPhase < 0.)
        this->freqshift_tilde_26_p_currentPhase = 1. + this->freqshift_tilde_26_p_currentPhase;

    if (this->freqshift_tilde_26_p_currentPhase > 1.)
        this->freqshift_tilde_26_p_currentPhase = this->freqshift_tilde_26_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_26_p_currentPhase;
    this->freqshift_tilde_26_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_26_p_reset() {
    this->freqshift_tilde_26_p_currentPhase = 0;
}

void freqshift_tilde_26_p_dspsetup() {
    this->freqshift_tilde_26_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_26_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_26_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_26_setupDone = true;
    this->freqshift_tilde_26_h_biquad1_dspsetup();
    this->freqshift_tilde_26_h_biquad2_dspsetup();
    this->freqshift_tilde_26_h_biquad3_dspsetup();
    this->freqshift_tilde_26_h_biquad4_dspsetup();
    this->freqshift_tilde_26_h_biquad5_dspsetup();
    this->freqshift_tilde_26_h_biquad6_dspsetup();
    this->freqshift_tilde_26_h_dspsetup();
    this->freqshift_tilde_26_p_dspsetup();
}

number gaintilde_28_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_28_ramp_d_prev);
    this->gaintilde_28_ramp_d_prev = x;
    return temp;
}

void gaintilde_28_ramp_d_dspsetup() {
    this->gaintilde_28_ramp_d_reset();
}

void gaintilde_28_ramp_d_reset() {
    this->gaintilde_28_ramp_d_prev = 0;
}

number gaintilde_28_ramp_next(number x, number up, number down) {
    if (this->gaintilde_28_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_28_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_28_ramp_index = _up;
            this->gaintilde_28_ramp_increment = (x - this->gaintilde_28_ramp_prev) / _up;
        } else if (x < this->gaintilde_28_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_28_ramp_index = _down;
            this->gaintilde_28_ramp_increment = (x - this->gaintilde_28_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_28_ramp_index > 0) {
        this->gaintilde_28_ramp_prev += this->gaintilde_28_ramp_increment;
        this->gaintilde_28_ramp_index -= 1;
    } else {
        this->gaintilde_28_ramp_prev = x;
    }

    return this->gaintilde_28_ramp_prev;
}

void gaintilde_28_ramp_reset() {
    this->gaintilde_28_ramp_prev = 0;
    this->gaintilde_28_ramp_index = 0;
    this->gaintilde_28_ramp_increment = 0;
    this->gaintilde_28_ramp_d_reset();
}

void gaintilde_28_init() {
    this->gaintilde_28_loginc = rnbo_log(1.072);
    this->gaintilde_28_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_28_loginc));
}

void gaintilde_28_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_28_value;
}

void gaintilde_28_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_28_value_set(preset["value"]);
}

void gaintilde_28_dspsetup(bool force) {
    if ((bool)(this->gaintilde_28_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_28_setupDone = true;
    this->gaintilde_28_ramp_d_dspsetup();
}

number gaintilde_29_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_29_ramp_d_prev);
    this->gaintilde_29_ramp_d_prev = x;
    return temp;
}

void gaintilde_29_ramp_d_dspsetup() {
    this->gaintilde_29_ramp_d_reset();
}

void gaintilde_29_ramp_d_reset() {
    this->gaintilde_29_ramp_d_prev = 0;
}

number gaintilde_29_ramp_next(number x, number up, number down) {
    if (this->gaintilde_29_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_29_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_29_ramp_index = _up;
            this->gaintilde_29_ramp_increment = (x - this->gaintilde_29_ramp_prev) / _up;
        } else if (x < this->gaintilde_29_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_29_ramp_index = _down;
            this->gaintilde_29_ramp_increment = (x - this->gaintilde_29_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_29_ramp_index > 0) {
        this->gaintilde_29_ramp_prev += this->gaintilde_29_ramp_increment;
        this->gaintilde_29_ramp_index -= 1;
    } else {
        this->gaintilde_29_ramp_prev = x;
    }

    return this->gaintilde_29_ramp_prev;
}

void gaintilde_29_ramp_reset() {
    this->gaintilde_29_ramp_prev = 0;
    this->gaintilde_29_ramp_index = 0;
    this->gaintilde_29_ramp_increment = 0;
    this->gaintilde_29_ramp_d_reset();
}

void gaintilde_29_init() {
    this->gaintilde_29_loginc = rnbo_log(1.072);
    this->gaintilde_29_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_29_loginc));
}

void gaintilde_29_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_29_value;
}

void gaintilde_29_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_29_value_set(preset["value"]);
}

void gaintilde_29_dspsetup(bool force) {
    if ((bool)(this->gaintilde_29_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_29_setupDone = true;
    this->gaintilde_29_ramp_d_dspsetup();
}

number freqshift_tilde_27_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad1_x1 * a1 + this->freqshift_tilde_27_h_biquad1_x2 * 1 - (this->freqshift_tilde_27_h_biquad1_y1 * b1 + this->freqshift_tilde_27_h_biquad1_y2 * b2);
    this->freqshift_tilde_27_h_biquad1_x2 = this->freqshift_tilde_27_h_biquad1_x1;
    this->freqshift_tilde_27_h_biquad1_x1 = x;
    this->freqshift_tilde_27_h_biquad1_y2 = this->freqshift_tilde_27_h_biquad1_y1;
    this->freqshift_tilde_27_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad1_clear() {
    this->freqshift_tilde_27_h_biquad1_reset();
}

void freqshift_tilde_27_h_biquad1_reset() {
    this->freqshift_tilde_27_h_biquad1_x1 = 0;
    this->freqshift_tilde_27_h_biquad1_x2 = 0;
    this->freqshift_tilde_27_h_biquad1_y1 = 0;
    this->freqshift_tilde_27_h_biquad1_y2 = 0;
}

void freqshift_tilde_27_h_biquad1_dspsetup() {
    this->freqshift_tilde_27_h_biquad1_reset();
}

number freqshift_tilde_27_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad2_x1 * a1 + this->freqshift_tilde_27_h_biquad2_x2 * 1 - (this->freqshift_tilde_27_h_biquad2_y1 * b1 + this->freqshift_tilde_27_h_biquad2_y2 * b2);
    this->freqshift_tilde_27_h_biquad2_x2 = this->freqshift_tilde_27_h_biquad2_x1;
    this->freqshift_tilde_27_h_biquad2_x1 = x;
    this->freqshift_tilde_27_h_biquad2_y2 = this->freqshift_tilde_27_h_biquad2_y1;
    this->freqshift_tilde_27_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad2_clear() {
    this->freqshift_tilde_27_h_biquad2_reset();
}

void freqshift_tilde_27_h_biquad2_reset() {
    this->freqshift_tilde_27_h_biquad2_x1 = 0;
    this->freqshift_tilde_27_h_biquad2_x2 = 0;
    this->freqshift_tilde_27_h_biquad2_y1 = 0;
    this->freqshift_tilde_27_h_biquad2_y2 = 0;
}

void freqshift_tilde_27_h_biquad2_dspsetup() {
    this->freqshift_tilde_27_h_biquad2_reset();
}

number freqshift_tilde_27_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad3_x1 * a1 + this->freqshift_tilde_27_h_biquad3_x2 * 1 - (this->freqshift_tilde_27_h_biquad3_y1 * b1 + this->freqshift_tilde_27_h_biquad3_y2 * b2);
    this->freqshift_tilde_27_h_biquad3_x2 = this->freqshift_tilde_27_h_biquad3_x1;
    this->freqshift_tilde_27_h_biquad3_x1 = x;
    this->freqshift_tilde_27_h_biquad3_y2 = this->freqshift_tilde_27_h_biquad3_y1;
    this->freqshift_tilde_27_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad3_clear() {
    this->freqshift_tilde_27_h_biquad3_reset();
}

void freqshift_tilde_27_h_biquad3_reset() {
    this->freqshift_tilde_27_h_biquad3_x1 = 0;
    this->freqshift_tilde_27_h_biquad3_x2 = 0;
    this->freqshift_tilde_27_h_biquad3_y1 = 0;
    this->freqshift_tilde_27_h_biquad3_y2 = 0;
}

void freqshift_tilde_27_h_biquad3_dspsetup() {
    this->freqshift_tilde_27_h_biquad3_reset();
}

number freqshift_tilde_27_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad4_x1 * a1 + this->freqshift_tilde_27_h_biquad4_x2 * 1 - (this->freqshift_tilde_27_h_biquad4_y1 * b1 + this->freqshift_tilde_27_h_biquad4_y2 * b2);
    this->freqshift_tilde_27_h_biquad4_x2 = this->freqshift_tilde_27_h_biquad4_x1;
    this->freqshift_tilde_27_h_biquad4_x1 = x;
    this->freqshift_tilde_27_h_biquad4_y2 = this->freqshift_tilde_27_h_biquad4_y1;
    this->freqshift_tilde_27_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad4_clear() {
    this->freqshift_tilde_27_h_biquad4_reset();
}

void freqshift_tilde_27_h_biquad4_reset() {
    this->freqshift_tilde_27_h_biquad4_x1 = 0;
    this->freqshift_tilde_27_h_biquad4_x2 = 0;
    this->freqshift_tilde_27_h_biquad4_y1 = 0;
    this->freqshift_tilde_27_h_biquad4_y2 = 0;
}

void freqshift_tilde_27_h_biquad4_dspsetup() {
    this->freqshift_tilde_27_h_biquad4_reset();
}

number freqshift_tilde_27_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad5_x1 * a1 + this->freqshift_tilde_27_h_biquad5_x2 * 1 - (this->freqshift_tilde_27_h_biquad5_y1 * b1 + this->freqshift_tilde_27_h_biquad5_y2 * b2);
    this->freqshift_tilde_27_h_biquad5_x2 = this->freqshift_tilde_27_h_biquad5_x1;
    this->freqshift_tilde_27_h_biquad5_x1 = x;
    this->freqshift_tilde_27_h_biquad5_y2 = this->freqshift_tilde_27_h_biquad5_y1;
    this->freqshift_tilde_27_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad5_clear() {
    this->freqshift_tilde_27_h_biquad5_reset();
}

void freqshift_tilde_27_h_biquad5_reset() {
    this->freqshift_tilde_27_h_biquad5_x1 = 0;
    this->freqshift_tilde_27_h_biquad5_x2 = 0;
    this->freqshift_tilde_27_h_biquad5_y1 = 0;
    this->freqshift_tilde_27_h_biquad5_y2 = 0;
}

void freqshift_tilde_27_h_biquad5_dspsetup() {
    this->freqshift_tilde_27_h_biquad5_reset();
}

number freqshift_tilde_27_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_27_h_biquad6_x1 * a1 + this->freqshift_tilde_27_h_biquad6_x2 * 1 - (this->freqshift_tilde_27_h_biquad6_y1 * b1 + this->freqshift_tilde_27_h_biquad6_y2 * b2);
    this->freqshift_tilde_27_h_biquad6_x2 = this->freqshift_tilde_27_h_biquad6_x1;
    this->freqshift_tilde_27_h_biquad6_x1 = x;
    this->freqshift_tilde_27_h_biquad6_y2 = this->freqshift_tilde_27_h_biquad6_y1;
    this->freqshift_tilde_27_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_27_h_biquad6_clear() {
    this->freqshift_tilde_27_h_biquad6_reset();
}

void freqshift_tilde_27_h_biquad6_reset() {
    this->freqshift_tilde_27_h_biquad6_x1 = 0;
    this->freqshift_tilde_27_h_biquad6_x2 = 0;
    this->freqshift_tilde_27_h_biquad6_y1 = 0;
    this->freqshift_tilde_27_h_biquad6_y2 = 0;
}

void freqshift_tilde_27_h_biquad6_dspsetup() {
    this->freqshift_tilde_27_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_27_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_27_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_27_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_27_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_27_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_27_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_27_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_27_h_clear() {
    this->freqshift_tilde_27_h_reset();
}

void freqshift_tilde_27_h_reset() {
    this->freqshift_tilde_27_h_biquad1_reset();
    this->freqshift_tilde_27_h_biquad2_reset();
    this->freqshift_tilde_27_h_biquad3_reset();
    this->freqshift_tilde_27_h_biquad4_reset();
    this->freqshift_tilde_27_h_biquad5_reset();
    this->freqshift_tilde_27_h_biquad6_reset();
}

void freqshift_tilde_27_h_dspsetup() {
    this->freqshift_tilde_27_h_reset();
}

number freqshift_tilde_27_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_27_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_27_p_conv;

    if (this->freqshift_tilde_27_p_currentPhase < 0.)
        this->freqshift_tilde_27_p_currentPhase = 1. + this->freqshift_tilde_27_p_currentPhase;

    if (this->freqshift_tilde_27_p_currentPhase > 1.)
        this->freqshift_tilde_27_p_currentPhase = this->freqshift_tilde_27_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_27_p_currentPhase;
    this->freqshift_tilde_27_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_27_p_reset() {
    this->freqshift_tilde_27_p_currentPhase = 0;
}

void freqshift_tilde_27_p_dspsetup() {
    this->freqshift_tilde_27_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_27_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_27_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_27_setupDone = true;
    this->freqshift_tilde_27_h_biquad1_dspsetup();
    this->freqshift_tilde_27_h_biquad2_dspsetup();
    this->freqshift_tilde_27_h_biquad3_dspsetup();
    this->freqshift_tilde_27_h_biquad4_dspsetup();
    this->freqshift_tilde_27_h_biquad5_dspsetup();
    this->freqshift_tilde_27_h_biquad6_dspsetup();
    this->freqshift_tilde_27_h_dspsetup();
    this->freqshift_tilde_27_p_dspsetup();
}

number freqshift_tilde_28_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad1_x1 * a1 + this->freqshift_tilde_28_h_biquad1_x2 * 1 - (this->freqshift_tilde_28_h_biquad1_y1 * b1 + this->freqshift_tilde_28_h_biquad1_y2 * b2);
    this->freqshift_tilde_28_h_biquad1_x2 = this->freqshift_tilde_28_h_biquad1_x1;
    this->freqshift_tilde_28_h_biquad1_x1 = x;
    this->freqshift_tilde_28_h_biquad1_y2 = this->freqshift_tilde_28_h_biquad1_y1;
    this->freqshift_tilde_28_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad1_clear() {
    this->freqshift_tilde_28_h_biquad1_reset();
}

void freqshift_tilde_28_h_biquad1_reset() {
    this->freqshift_tilde_28_h_biquad1_x1 = 0;
    this->freqshift_tilde_28_h_biquad1_x2 = 0;
    this->freqshift_tilde_28_h_biquad1_y1 = 0;
    this->freqshift_tilde_28_h_biquad1_y2 = 0;
}

void freqshift_tilde_28_h_biquad1_dspsetup() {
    this->freqshift_tilde_28_h_biquad1_reset();
}

number freqshift_tilde_28_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad2_x1 * a1 + this->freqshift_tilde_28_h_biquad2_x2 * 1 - (this->freqshift_tilde_28_h_biquad2_y1 * b1 + this->freqshift_tilde_28_h_biquad2_y2 * b2);
    this->freqshift_tilde_28_h_biquad2_x2 = this->freqshift_tilde_28_h_biquad2_x1;
    this->freqshift_tilde_28_h_biquad2_x1 = x;
    this->freqshift_tilde_28_h_biquad2_y2 = this->freqshift_tilde_28_h_biquad2_y1;
    this->freqshift_tilde_28_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad2_clear() {
    this->freqshift_tilde_28_h_biquad2_reset();
}

void freqshift_tilde_28_h_biquad2_reset() {
    this->freqshift_tilde_28_h_biquad2_x1 = 0;
    this->freqshift_tilde_28_h_biquad2_x2 = 0;
    this->freqshift_tilde_28_h_biquad2_y1 = 0;
    this->freqshift_tilde_28_h_biquad2_y2 = 0;
}

void freqshift_tilde_28_h_biquad2_dspsetup() {
    this->freqshift_tilde_28_h_biquad2_reset();
}

number freqshift_tilde_28_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad3_x1 * a1 + this->freqshift_tilde_28_h_biquad3_x2 * 1 - (this->freqshift_tilde_28_h_biquad3_y1 * b1 + this->freqshift_tilde_28_h_biquad3_y2 * b2);
    this->freqshift_tilde_28_h_biquad3_x2 = this->freqshift_tilde_28_h_biquad3_x1;
    this->freqshift_tilde_28_h_biquad3_x1 = x;
    this->freqshift_tilde_28_h_biquad3_y2 = this->freqshift_tilde_28_h_biquad3_y1;
    this->freqshift_tilde_28_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad3_clear() {
    this->freqshift_tilde_28_h_biquad3_reset();
}

void freqshift_tilde_28_h_biquad3_reset() {
    this->freqshift_tilde_28_h_biquad3_x1 = 0;
    this->freqshift_tilde_28_h_biquad3_x2 = 0;
    this->freqshift_tilde_28_h_biquad3_y1 = 0;
    this->freqshift_tilde_28_h_biquad3_y2 = 0;
}

void freqshift_tilde_28_h_biquad3_dspsetup() {
    this->freqshift_tilde_28_h_biquad3_reset();
}

number freqshift_tilde_28_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad4_x1 * a1 + this->freqshift_tilde_28_h_biquad4_x2 * 1 - (this->freqshift_tilde_28_h_biquad4_y1 * b1 + this->freqshift_tilde_28_h_biquad4_y2 * b2);
    this->freqshift_tilde_28_h_biquad4_x2 = this->freqshift_tilde_28_h_biquad4_x1;
    this->freqshift_tilde_28_h_biquad4_x1 = x;
    this->freqshift_tilde_28_h_biquad4_y2 = this->freqshift_tilde_28_h_biquad4_y1;
    this->freqshift_tilde_28_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad4_clear() {
    this->freqshift_tilde_28_h_biquad4_reset();
}

void freqshift_tilde_28_h_biquad4_reset() {
    this->freqshift_tilde_28_h_biquad4_x1 = 0;
    this->freqshift_tilde_28_h_biquad4_x2 = 0;
    this->freqshift_tilde_28_h_biquad4_y1 = 0;
    this->freqshift_tilde_28_h_biquad4_y2 = 0;
}

void freqshift_tilde_28_h_biquad4_dspsetup() {
    this->freqshift_tilde_28_h_biquad4_reset();
}

number freqshift_tilde_28_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad5_x1 * a1 + this->freqshift_tilde_28_h_biquad5_x2 * 1 - (this->freqshift_tilde_28_h_biquad5_y1 * b1 + this->freqshift_tilde_28_h_biquad5_y2 * b2);
    this->freqshift_tilde_28_h_biquad5_x2 = this->freqshift_tilde_28_h_biquad5_x1;
    this->freqshift_tilde_28_h_biquad5_x1 = x;
    this->freqshift_tilde_28_h_biquad5_y2 = this->freqshift_tilde_28_h_biquad5_y1;
    this->freqshift_tilde_28_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad5_clear() {
    this->freqshift_tilde_28_h_biquad5_reset();
}

void freqshift_tilde_28_h_biquad5_reset() {
    this->freqshift_tilde_28_h_biquad5_x1 = 0;
    this->freqshift_tilde_28_h_biquad5_x2 = 0;
    this->freqshift_tilde_28_h_biquad5_y1 = 0;
    this->freqshift_tilde_28_h_biquad5_y2 = 0;
}

void freqshift_tilde_28_h_biquad5_dspsetup() {
    this->freqshift_tilde_28_h_biquad5_reset();
}

number freqshift_tilde_28_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_28_h_biquad6_x1 * a1 + this->freqshift_tilde_28_h_biquad6_x2 * 1 - (this->freqshift_tilde_28_h_biquad6_y1 * b1 + this->freqshift_tilde_28_h_biquad6_y2 * b2);
    this->freqshift_tilde_28_h_biquad6_x2 = this->freqshift_tilde_28_h_biquad6_x1;
    this->freqshift_tilde_28_h_biquad6_x1 = x;
    this->freqshift_tilde_28_h_biquad6_y2 = this->freqshift_tilde_28_h_biquad6_y1;
    this->freqshift_tilde_28_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_28_h_biquad6_clear() {
    this->freqshift_tilde_28_h_biquad6_reset();
}

void freqshift_tilde_28_h_biquad6_reset() {
    this->freqshift_tilde_28_h_biquad6_x1 = 0;
    this->freqshift_tilde_28_h_biquad6_x2 = 0;
    this->freqshift_tilde_28_h_biquad6_y1 = 0;
    this->freqshift_tilde_28_h_biquad6_y2 = 0;
}

void freqshift_tilde_28_h_biquad6_dspsetup() {
    this->freqshift_tilde_28_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_28_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_28_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_28_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_28_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_28_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_28_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_28_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_28_h_clear() {
    this->freqshift_tilde_28_h_reset();
}

void freqshift_tilde_28_h_reset() {
    this->freqshift_tilde_28_h_biquad1_reset();
    this->freqshift_tilde_28_h_biquad2_reset();
    this->freqshift_tilde_28_h_biquad3_reset();
    this->freqshift_tilde_28_h_biquad4_reset();
    this->freqshift_tilde_28_h_biquad5_reset();
    this->freqshift_tilde_28_h_biquad6_reset();
}

void freqshift_tilde_28_h_dspsetup() {
    this->freqshift_tilde_28_h_reset();
}

number freqshift_tilde_28_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_28_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_28_p_conv;

    if (this->freqshift_tilde_28_p_currentPhase < 0.)
        this->freqshift_tilde_28_p_currentPhase = 1. + this->freqshift_tilde_28_p_currentPhase;

    if (this->freqshift_tilde_28_p_currentPhase > 1.)
        this->freqshift_tilde_28_p_currentPhase = this->freqshift_tilde_28_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_28_p_currentPhase;
    this->freqshift_tilde_28_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_28_p_reset() {
    this->freqshift_tilde_28_p_currentPhase = 0;
}

void freqshift_tilde_28_p_dspsetup() {
    this->freqshift_tilde_28_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_28_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_28_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_28_setupDone = true;
    this->freqshift_tilde_28_h_biquad1_dspsetup();
    this->freqshift_tilde_28_h_biquad2_dspsetup();
    this->freqshift_tilde_28_h_biquad3_dspsetup();
    this->freqshift_tilde_28_h_biquad4_dspsetup();
    this->freqshift_tilde_28_h_biquad5_dspsetup();
    this->freqshift_tilde_28_h_biquad6_dspsetup();
    this->freqshift_tilde_28_h_dspsetup();
    this->freqshift_tilde_28_p_dspsetup();
}

number gaintilde_30_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_30_ramp_d_prev);
    this->gaintilde_30_ramp_d_prev = x;
    return temp;
}

void gaintilde_30_ramp_d_dspsetup() {
    this->gaintilde_30_ramp_d_reset();
}

void gaintilde_30_ramp_d_reset() {
    this->gaintilde_30_ramp_d_prev = 0;
}

number gaintilde_30_ramp_next(number x, number up, number down) {
    if (this->gaintilde_30_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_30_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_30_ramp_index = _up;
            this->gaintilde_30_ramp_increment = (x - this->gaintilde_30_ramp_prev) / _up;
        } else if (x < this->gaintilde_30_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_30_ramp_index = _down;
            this->gaintilde_30_ramp_increment = (x - this->gaintilde_30_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_30_ramp_index > 0) {
        this->gaintilde_30_ramp_prev += this->gaintilde_30_ramp_increment;
        this->gaintilde_30_ramp_index -= 1;
    } else {
        this->gaintilde_30_ramp_prev = x;
    }

    return this->gaintilde_30_ramp_prev;
}

void gaintilde_30_ramp_reset() {
    this->gaintilde_30_ramp_prev = 0;
    this->gaintilde_30_ramp_index = 0;
    this->gaintilde_30_ramp_increment = 0;
    this->gaintilde_30_ramp_d_reset();
}

void gaintilde_30_init() {
    this->gaintilde_30_loginc = rnbo_log(1.072);
    this->gaintilde_30_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_30_loginc));
}

void gaintilde_30_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_30_value;
}

void gaintilde_30_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_30_value_set(preset["value"]);
}

void gaintilde_30_dspsetup(bool force) {
    if ((bool)(this->gaintilde_30_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_30_setupDone = true;
    this->gaintilde_30_ramp_d_dspsetup();
}

number gaintilde_31_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_31_ramp_d_prev);
    this->gaintilde_31_ramp_d_prev = x;
    return temp;
}

void gaintilde_31_ramp_d_dspsetup() {
    this->gaintilde_31_ramp_d_reset();
}

void gaintilde_31_ramp_d_reset() {
    this->gaintilde_31_ramp_d_prev = 0;
}

number gaintilde_31_ramp_next(number x, number up, number down) {
    if (this->gaintilde_31_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_31_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_31_ramp_index = _up;
            this->gaintilde_31_ramp_increment = (x - this->gaintilde_31_ramp_prev) / _up;
        } else if (x < this->gaintilde_31_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_31_ramp_index = _down;
            this->gaintilde_31_ramp_increment = (x - this->gaintilde_31_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_31_ramp_index > 0) {
        this->gaintilde_31_ramp_prev += this->gaintilde_31_ramp_increment;
        this->gaintilde_31_ramp_index -= 1;
    } else {
        this->gaintilde_31_ramp_prev = x;
    }

    return this->gaintilde_31_ramp_prev;
}

void gaintilde_31_ramp_reset() {
    this->gaintilde_31_ramp_prev = 0;
    this->gaintilde_31_ramp_index = 0;
    this->gaintilde_31_ramp_increment = 0;
    this->gaintilde_31_ramp_d_reset();
}

void gaintilde_31_init() {
    this->gaintilde_31_loginc = rnbo_log(1.072);
    this->gaintilde_31_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_31_loginc));
}

void gaintilde_31_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_31_value;
}

void gaintilde_31_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_31_value_set(preset["value"]);
}

void gaintilde_31_dspsetup(bool force) {
    if ((bool)(this->gaintilde_31_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_31_setupDone = true;
    this->gaintilde_31_ramp_d_dspsetup();
}

number freqshift_tilde_29_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad1_x1 * a1 + this->freqshift_tilde_29_h_biquad1_x2 * 1 - (this->freqshift_tilde_29_h_biquad1_y1 * b1 + this->freqshift_tilde_29_h_biquad1_y2 * b2);
    this->freqshift_tilde_29_h_biquad1_x2 = this->freqshift_tilde_29_h_biquad1_x1;
    this->freqshift_tilde_29_h_biquad1_x1 = x;
    this->freqshift_tilde_29_h_biquad1_y2 = this->freqshift_tilde_29_h_biquad1_y1;
    this->freqshift_tilde_29_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad1_clear() {
    this->freqshift_tilde_29_h_biquad1_reset();
}

void freqshift_tilde_29_h_biquad1_reset() {
    this->freqshift_tilde_29_h_biquad1_x1 = 0;
    this->freqshift_tilde_29_h_biquad1_x2 = 0;
    this->freqshift_tilde_29_h_biquad1_y1 = 0;
    this->freqshift_tilde_29_h_biquad1_y2 = 0;
}

void freqshift_tilde_29_h_biquad1_dspsetup() {
    this->freqshift_tilde_29_h_biquad1_reset();
}

number freqshift_tilde_29_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad2_x1 * a1 + this->freqshift_tilde_29_h_biquad2_x2 * 1 - (this->freqshift_tilde_29_h_biquad2_y1 * b1 + this->freqshift_tilde_29_h_biquad2_y2 * b2);
    this->freqshift_tilde_29_h_biquad2_x2 = this->freqshift_tilde_29_h_biquad2_x1;
    this->freqshift_tilde_29_h_biquad2_x1 = x;
    this->freqshift_tilde_29_h_biquad2_y2 = this->freqshift_tilde_29_h_biquad2_y1;
    this->freqshift_tilde_29_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad2_clear() {
    this->freqshift_tilde_29_h_biquad2_reset();
}

void freqshift_tilde_29_h_biquad2_reset() {
    this->freqshift_tilde_29_h_biquad2_x1 = 0;
    this->freqshift_tilde_29_h_biquad2_x2 = 0;
    this->freqshift_tilde_29_h_biquad2_y1 = 0;
    this->freqshift_tilde_29_h_biquad2_y2 = 0;
}

void freqshift_tilde_29_h_biquad2_dspsetup() {
    this->freqshift_tilde_29_h_biquad2_reset();
}

number freqshift_tilde_29_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad3_x1 * a1 + this->freqshift_tilde_29_h_biquad3_x2 * 1 - (this->freqshift_tilde_29_h_biquad3_y1 * b1 + this->freqshift_tilde_29_h_biquad3_y2 * b2);
    this->freqshift_tilde_29_h_biquad3_x2 = this->freqshift_tilde_29_h_biquad3_x1;
    this->freqshift_tilde_29_h_biquad3_x1 = x;
    this->freqshift_tilde_29_h_biquad3_y2 = this->freqshift_tilde_29_h_biquad3_y1;
    this->freqshift_tilde_29_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad3_clear() {
    this->freqshift_tilde_29_h_biquad3_reset();
}

void freqshift_tilde_29_h_biquad3_reset() {
    this->freqshift_tilde_29_h_biquad3_x1 = 0;
    this->freqshift_tilde_29_h_biquad3_x2 = 0;
    this->freqshift_tilde_29_h_biquad3_y1 = 0;
    this->freqshift_tilde_29_h_biquad3_y2 = 0;
}

void freqshift_tilde_29_h_biquad3_dspsetup() {
    this->freqshift_tilde_29_h_biquad3_reset();
}

number freqshift_tilde_29_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad4_x1 * a1 + this->freqshift_tilde_29_h_biquad4_x2 * 1 - (this->freqshift_tilde_29_h_biquad4_y1 * b1 + this->freqshift_tilde_29_h_biquad4_y2 * b2);
    this->freqshift_tilde_29_h_biquad4_x2 = this->freqshift_tilde_29_h_biquad4_x1;
    this->freqshift_tilde_29_h_biquad4_x1 = x;
    this->freqshift_tilde_29_h_biquad4_y2 = this->freqshift_tilde_29_h_biquad4_y1;
    this->freqshift_tilde_29_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad4_clear() {
    this->freqshift_tilde_29_h_biquad4_reset();
}

void freqshift_tilde_29_h_biquad4_reset() {
    this->freqshift_tilde_29_h_biquad4_x1 = 0;
    this->freqshift_tilde_29_h_biquad4_x2 = 0;
    this->freqshift_tilde_29_h_biquad4_y1 = 0;
    this->freqshift_tilde_29_h_biquad4_y2 = 0;
}

void freqshift_tilde_29_h_biquad4_dspsetup() {
    this->freqshift_tilde_29_h_biquad4_reset();
}

number freqshift_tilde_29_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad5_x1 * a1 + this->freqshift_tilde_29_h_biquad5_x2 * 1 - (this->freqshift_tilde_29_h_biquad5_y1 * b1 + this->freqshift_tilde_29_h_biquad5_y2 * b2);
    this->freqshift_tilde_29_h_biquad5_x2 = this->freqshift_tilde_29_h_biquad5_x1;
    this->freqshift_tilde_29_h_biquad5_x1 = x;
    this->freqshift_tilde_29_h_biquad5_y2 = this->freqshift_tilde_29_h_biquad5_y1;
    this->freqshift_tilde_29_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad5_clear() {
    this->freqshift_tilde_29_h_biquad5_reset();
}

void freqshift_tilde_29_h_biquad5_reset() {
    this->freqshift_tilde_29_h_biquad5_x1 = 0;
    this->freqshift_tilde_29_h_biquad5_x2 = 0;
    this->freqshift_tilde_29_h_biquad5_y1 = 0;
    this->freqshift_tilde_29_h_biquad5_y2 = 0;
}

void freqshift_tilde_29_h_biquad5_dspsetup() {
    this->freqshift_tilde_29_h_biquad5_reset();
}

number freqshift_tilde_29_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_29_h_biquad6_x1 * a1 + this->freqshift_tilde_29_h_biquad6_x2 * 1 - (this->freqshift_tilde_29_h_biquad6_y1 * b1 + this->freqshift_tilde_29_h_biquad6_y2 * b2);
    this->freqshift_tilde_29_h_biquad6_x2 = this->freqshift_tilde_29_h_biquad6_x1;
    this->freqshift_tilde_29_h_biquad6_x1 = x;
    this->freqshift_tilde_29_h_biquad6_y2 = this->freqshift_tilde_29_h_biquad6_y1;
    this->freqshift_tilde_29_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_29_h_biquad6_clear() {
    this->freqshift_tilde_29_h_biquad6_reset();
}

void freqshift_tilde_29_h_biquad6_reset() {
    this->freqshift_tilde_29_h_biquad6_x1 = 0;
    this->freqshift_tilde_29_h_biquad6_x2 = 0;
    this->freqshift_tilde_29_h_biquad6_y1 = 0;
    this->freqshift_tilde_29_h_biquad6_y2 = 0;
}

void freqshift_tilde_29_h_biquad6_dspsetup() {
    this->freqshift_tilde_29_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_29_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_29_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_29_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_29_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_29_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_29_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_29_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_29_h_clear() {
    this->freqshift_tilde_29_h_reset();
}

void freqshift_tilde_29_h_reset() {
    this->freqshift_tilde_29_h_biquad1_reset();
    this->freqshift_tilde_29_h_biquad2_reset();
    this->freqshift_tilde_29_h_biquad3_reset();
    this->freqshift_tilde_29_h_biquad4_reset();
    this->freqshift_tilde_29_h_biquad5_reset();
    this->freqshift_tilde_29_h_biquad6_reset();
}

void freqshift_tilde_29_h_dspsetup() {
    this->freqshift_tilde_29_h_reset();
}

number freqshift_tilde_29_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_29_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_29_p_conv;

    if (this->freqshift_tilde_29_p_currentPhase < 0.)
        this->freqshift_tilde_29_p_currentPhase = 1. + this->freqshift_tilde_29_p_currentPhase;

    if (this->freqshift_tilde_29_p_currentPhase > 1.)
        this->freqshift_tilde_29_p_currentPhase = this->freqshift_tilde_29_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_29_p_currentPhase;
    this->freqshift_tilde_29_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_29_p_reset() {
    this->freqshift_tilde_29_p_currentPhase = 0;
}

void freqshift_tilde_29_p_dspsetup() {
    this->freqshift_tilde_29_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_29_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_29_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_29_setupDone = true;
    this->freqshift_tilde_29_h_biquad1_dspsetup();
    this->freqshift_tilde_29_h_biquad2_dspsetup();
    this->freqshift_tilde_29_h_biquad3_dspsetup();
    this->freqshift_tilde_29_h_biquad4_dspsetup();
    this->freqshift_tilde_29_h_biquad5_dspsetup();
    this->freqshift_tilde_29_h_biquad6_dspsetup();
    this->freqshift_tilde_29_h_dspsetup();
    this->freqshift_tilde_29_p_dspsetup();
}

number freqshift_tilde_30_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad1_x1 * a1 + this->freqshift_tilde_30_h_biquad1_x2 * 1 - (this->freqshift_tilde_30_h_biquad1_y1 * b1 + this->freqshift_tilde_30_h_biquad1_y2 * b2);
    this->freqshift_tilde_30_h_biquad1_x2 = this->freqshift_tilde_30_h_biquad1_x1;
    this->freqshift_tilde_30_h_biquad1_x1 = x;
    this->freqshift_tilde_30_h_biquad1_y2 = this->freqshift_tilde_30_h_biquad1_y1;
    this->freqshift_tilde_30_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad1_clear() {
    this->freqshift_tilde_30_h_biquad1_reset();
}

void freqshift_tilde_30_h_biquad1_reset() {
    this->freqshift_tilde_30_h_biquad1_x1 = 0;
    this->freqshift_tilde_30_h_biquad1_x2 = 0;
    this->freqshift_tilde_30_h_biquad1_y1 = 0;
    this->freqshift_tilde_30_h_biquad1_y2 = 0;
}

void freqshift_tilde_30_h_biquad1_dspsetup() {
    this->freqshift_tilde_30_h_biquad1_reset();
}

number freqshift_tilde_30_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad2_x1 * a1 + this->freqshift_tilde_30_h_biquad2_x2 * 1 - (this->freqshift_tilde_30_h_biquad2_y1 * b1 + this->freqshift_tilde_30_h_biquad2_y2 * b2);
    this->freqshift_tilde_30_h_biquad2_x2 = this->freqshift_tilde_30_h_biquad2_x1;
    this->freqshift_tilde_30_h_biquad2_x1 = x;
    this->freqshift_tilde_30_h_biquad2_y2 = this->freqshift_tilde_30_h_biquad2_y1;
    this->freqshift_tilde_30_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad2_clear() {
    this->freqshift_tilde_30_h_biquad2_reset();
}

void freqshift_tilde_30_h_biquad2_reset() {
    this->freqshift_tilde_30_h_biquad2_x1 = 0;
    this->freqshift_tilde_30_h_biquad2_x2 = 0;
    this->freqshift_tilde_30_h_biquad2_y1 = 0;
    this->freqshift_tilde_30_h_biquad2_y2 = 0;
}

void freqshift_tilde_30_h_biquad2_dspsetup() {
    this->freqshift_tilde_30_h_biquad2_reset();
}

number freqshift_tilde_30_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad3_x1 * a1 + this->freqshift_tilde_30_h_biquad3_x2 * 1 - (this->freqshift_tilde_30_h_biquad3_y1 * b1 + this->freqshift_tilde_30_h_biquad3_y2 * b2);
    this->freqshift_tilde_30_h_biquad3_x2 = this->freqshift_tilde_30_h_biquad3_x1;
    this->freqshift_tilde_30_h_biquad3_x1 = x;
    this->freqshift_tilde_30_h_biquad3_y2 = this->freqshift_tilde_30_h_biquad3_y1;
    this->freqshift_tilde_30_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad3_clear() {
    this->freqshift_tilde_30_h_biquad3_reset();
}

void freqshift_tilde_30_h_biquad3_reset() {
    this->freqshift_tilde_30_h_biquad3_x1 = 0;
    this->freqshift_tilde_30_h_biquad3_x2 = 0;
    this->freqshift_tilde_30_h_biquad3_y1 = 0;
    this->freqshift_tilde_30_h_biquad3_y2 = 0;
}

void freqshift_tilde_30_h_biquad3_dspsetup() {
    this->freqshift_tilde_30_h_biquad3_reset();
}

number freqshift_tilde_30_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad4_x1 * a1 + this->freqshift_tilde_30_h_biquad4_x2 * 1 - (this->freqshift_tilde_30_h_biquad4_y1 * b1 + this->freqshift_tilde_30_h_biquad4_y2 * b2);
    this->freqshift_tilde_30_h_biquad4_x2 = this->freqshift_tilde_30_h_biquad4_x1;
    this->freqshift_tilde_30_h_biquad4_x1 = x;
    this->freqshift_tilde_30_h_biquad4_y2 = this->freqshift_tilde_30_h_biquad4_y1;
    this->freqshift_tilde_30_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad4_clear() {
    this->freqshift_tilde_30_h_biquad4_reset();
}

void freqshift_tilde_30_h_biquad4_reset() {
    this->freqshift_tilde_30_h_biquad4_x1 = 0;
    this->freqshift_tilde_30_h_biquad4_x2 = 0;
    this->freqshift_tilde_30_h_biquad4_y1 = 0;
    this->freqshift_tilde_30_h_biquad4_y2 = 0;
}

void freqshift_tilde_30_h_biquad4_dspsetup() {
    this->freqshift_tilde_30_h_biquad4_reset();
}

number freqshift_tilde_30_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad5_x1 * a1 + this->freqshift_tilde_30_h_biquad5_x2 * 1 - (this->freqshift_tilde_30_h_biquad5_y1 * b1 + this->freqshift_tilde_30_h_biquad5_y2 * b2);
    this->freqshift_tilde_30_h_biquad5_x2 = this->freqshift_tilde_30_h_biquad5_x1;
    this->freqshift_tilde_30_h_biquad5_x1 = x;
    this->freqshift_tilde_30_h_biquad5_y2 = this->freqshift_tilde_30_h_biquad5_y1;
    this->freqshift_tilde_30_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad5_clear() {
    this->freqshift_tilde_30_h_biquad5_reset();
}

void freqshift_tilde_30_h_biquad5_reset() {
    this->freqshift_tilde_30_h_biquad5_x1 = 0;
    this->freqshift_tilde_30_h_biquad5_x2 = 0;
    this->freqshift_tilde_30_h_biquad5_y1 = 0;
    this->freqshift_tilde_30_h_biquad5_y2 = 0;
}

void freqshift_tilde_30_h_biquad5_dspsetup() {
    this->freqshift_tilde_30_h_biquad5_reset();
}

number freqshift_tilde_30_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_30_h_biquad6_x1 * a1 + this->freqshift_tilde_30_h_biquad6_x2 * 1 - (this->freqshift_tilde_30_h_biquad6_y1 * b1 + this->freqshift_tilde_30_h_biquad6_y2 * b2);
    this->freqshift_tilde_30_h_biquad6_x2 = this->freqshift_tilde_30_h_biquad6_x1;
    this->freqshift_tilde_30_h_biquad6_x1 = x;
    this->freqshift_tilde_30_h_biquad6_y2 = this->freqshift_tilde_30_h_biquad6_y1;
    this->freqshift_tilde_30_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_30_h_biquad6_clear() {
    this->freqshift_tilde_30_h_biquad6_reset();
}

void freqshift_tilde_30_h_biquad6_reset() {
    this->freqshift_tilde_30_h_biquad6_x1 = 0;
    this->freqshift_tilde_30_h_biquad6_x2 = 0;
    this->freqshift_tilde_30_h_biquad6_y1 = 0;
    this->freqshift_tilde_30_h_biquad6_y2 = 0;
}

void freqshift_tilde_30_h_biquad6_dspsetup() {
    this->freqshift_tilde_30_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_30_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_30_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_30_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_30_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_30_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_30_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_30_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_30_h_clear() {
    this->freqshift_tilde_30_h_reset();
}

void freqshift_tilde_30_h_reset() {
    this->freqshift_tilde_30_h_biquad1_reset();
    this->freqshift_tilde_30_h_biquad2_reset();
    this->freqshift_tilde_30_h_biquad3_reset();
    this->freqshift_tilde_30_h_biquad4_reset();
    this->freqshift_tilde_30_h_biquad5_reset();
    this->freqshift_tilde_30_h_biquad6_reset();
}

void freqshift_tilde_30_h_dspsetup() {
    this->freqshift_tilde_30_h_reset();
}

number freqshift_tilde_30_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_30_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_30_p_conv;

    if (this->freqshift_tilde_30_p_currentPhase < 0.)
        this->freqshift_tilde_30_p_currentPhase = 1. + this->freqshift_tilde_30_p_currentPhase;

    if (this->freqshift_tilde_30_p_currentPhase > 1.)
        this->freqshift_tilde_30_p_currentPhase = this->freqshift_tilde_30_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_30_p_currentPhase;
    this->freqshift_tilde_30_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_30_p_reset() {
    this->freqshift_tilde_30_p_currentPhase = 0;
}

void freqshift_tilde_30_p_dspsetup() {
    this->freqshift_tilde_30_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_30_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_30_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_30_setupDone = true;
    this->freqshift_tilde_30_h_biquad1_dspsetup();
    this->freqshift_tilde_30_h_biquad2_dspsetup();
    this->freqshift_tilde_30_h_biquad3_dspsetup();
    this->freqshift_tilde_30_h_biquad4_dspsetup();
    this->freqshift_tilde_30_h_biquad5_dspsetup();
    this->freqshift_tilde_30_h_biquad6_dspsetup();
    this->freqshift_tilde_30_h_dspsetup();
    this->freqshift_tilde_30_p_dspsetup();
}

void param_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_22_value;
}

void param_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_22_value_set(preset["value"]);
}

number gaintilde_32_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_32_ramp_d_prev);
    this->gaintilde_32_ramp_d_prev = x;
    return temp;
}

void gaintilde_32_ramp_d_dspsetup() {
    this->gaintilde_32_ramp_d_reset();
}

void gaintilde_32_ramp_d_reset() {
    this->gaintilde_32_ramp_d_prev = 0;
}

number gaintilde_32_ramp_next(number x, number up, number down) {
    if (this->gaintilde_32_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_32_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_32_ramp_index = _up;
            this->gaintilde_32_ramp_increment = (x - this->gaintilde_32_ramp_prev) / _up;
        } else if (x < this->gaintilde_32_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_32_ramp_index = _down;
            this->gaintilde_32_ramp_increment = (x - this->gaintilde_32_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_32_ramp_index > 0) {
        this->gaintilde_32_ramp_prev += this->gaintilde_32_ramp_increment;
        this->gaintilde_32_ramp_index -= 1;
    } else {
        this->gaintilde_32_ramp_prev = x;
    }

    return this->gaintilde_32_ramp_prev;
}

void gaintilde_32_ramp_reset() {
    this->gaintilde_32_ramp_prev = 0;
    this->gaintilde_32_ramp_index = 0;
    this->gaintilde_32_ramp_increment = 0;
    this->gaintilde_32_ramp_d_reset();
}

void gaintilde_32_init() {
    this->gaintilde_32_loginc = rnbo_log(1.072);
    this->gaintilde_32_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_32_loginc));
}

void gaintilde_32_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_32_value;
}

void gaintilde_32_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_32_value_set(preset["value"]);
}

void gaintilde_32_dspsetup(bool force) {
    if ((bool)(this->gaintilde_32_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_32_setupDone = true;
    this->gaintilde_32_ramp_d_dspsetup();
}

number gaintilde_33_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_33_ramp_d_prev);
    this->gaintilde_33_ramp_d_prev = x;
    return temp;
}

void gaintilde_33_ramp_d_dspsetup() {
    this->gaintilde_33_ramp_d_reset();
}

void gaintilde_33_ramp_d_reset() {
    this->gaintilde_33_ramp_d_prev = 0;
}

number gaintilde_33_ramp_next(number x, number up, number down) {
    if (this->gaintilde_33_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_33_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_33_ramp_index = _up;
            this->gaintilde_33_ramp_increment = (x - this->gaintilde_33_ramp_prev) / _up;
        } else if (x < this->gaintilde_33_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_33_ramp_index = _down;
            this->gaintilde_33_ramp_increment = (x - this->gaintilde_33_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_33_ramp_index > 0) {
        this->gaintilde_33_ramp_prev += this->gaintilde_33_ramp_increment;
        this->gaintilde_33_ramp_index -= 1;
    } else {
        this->gaintilde_33_ramp_prev = x;
    }

    return this->gaintilde_33_ramp_prev;
}

void gaintilde_33_ramp_reset() {
    this->gaintilde_33_ramp_prev = 0;
    this->gaintilde_33_ramp_index = 0;
    this->gaintilde_33_ramp_increment = 0;
    this->gaintilde_33_ramp_d_reset();
}

void gaintilde_33_init() {
    this->gaintilde_33_loginc = rnbo_log(1.072);
    this->gaintilde_33_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_33_loginc));
}

void gaintilde_33_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_33_value;
}

void gaintilde_33_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_33_value_set(preset["value"]);
}

void gaintilde_33_dspsetup(bool force) {
    if ((bool)(this->gaintilde_33_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_33_setupDone = true;
    this->gaintilde_33_ramp_d_dspsetup();
}

void param_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_23_value;
}

void param_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_23_value_set(preset["value"]);
}

void param_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_24_value;
}

void param_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_24_value_set(preset["value"]);
}

void param_25_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_25_value;
}

void param_25_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_25_value_set(preset["value"]);
}

number freqshift_tilde_31_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad1_x1 * a1 + this->freqshift_tilde_31_h_biquad1_x2 * 1 - (this->freqshift_tilde_31_h_biquad1_y1 * b1 + this->freqshift_tilde_31_h_biquad1_y2 * b2);
    this->freqshift_tilde_31_h_biquad1_x2 = this->freqshift_tilde_31_h_biquad1_x1;
    this->freqshift_tilde_31_h_biquad1_x1 = x;
    this->freqshift_tilde_31_h_biquad1_y2 = this->freqshift_tilde_31_h_biquad1_y1;
    this->freqshift_tilde_31_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad1_clear() {
    this->freqshift_tilde_31_h_biquad1_reset();
}

void freqshift_tilde_31_h_biquad1_reset() {
    this->freqshift_tilde_31_h_biquad1_x1 = 0;
    this->freqshift_tilde_31_h_biquad1_x2 = 0;
    this->freqshift_tilde_31_h_biquad1_y1 = 0;
    this->freqshift_tilde_31_h_biquad1_y2 = 0;
}

void freqshift_tilde_31_h_biquad1_dspsetup() {
    this->freqshift_tilde_31_h_biquad1_reset();
}

number freqshift_tilde_31_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad2_x1 * a1 + this->freqshift_tilde_31_h_biquad2_x2 * 1 - (this->freqshift_tilde_31_h_biquad2_y1 * b1 + this->freqshift_tilde_31_h_biquad2_y2 * b2);
    this->freqshift_tilde_31_h_biquad2_x2 = this->freqshift_tilde_31_h_biquad2_x1;
    this->freqshift_tilde_31_h_biquad2_x1 = x;
    this->freqshift_tilde_31_h_biquad2_y2 = this->freqshift_tilde_31_h_biquad2_y1;
    this->freqshift_tilde_31_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad2_clear() {
    this->freqshift_tilde_31_h_biquad2_reset();
}

void freqshift_tilde_31_h_biquad2_reset() {
    this->freqshift_tilde_31_h_biquad2_x1 = 0;
    this->freqshift_tilde_31_h_biquad2_x2 = 0;
    this->freqshift_tilde_31_h_biquad2_y1 = 0;
    this->freqshift_tilde_31_h_biquad2_y2 = 0;
}

void freqshift_tilde_31_h_biquad2_dspsetup() {
    this->freqshift_tilde_31_h_biquad2_reset();
}

number freqshift_tilde_31_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad3_x1 * a1 + this->freqshift_tilde_31_h_biquad3_x2 * 1 - (this->freqshift_tilde_31_h_biquad3_y1 * b1 + this->freqshift_tilde_31_h_biquad3_y2 * b2);
    this->freqshift_tilde_31_h_biquad3_x2 = this->freqshift_tilde_31_h_biquad3_x1;
    this->freqshift_tilde_31_h_biquad3_x1 = x;
    this->freqshift_tilde_31_h_biquad3_y2 = this->freqshift_tilde_31_h_biquad3_y1;
    this->freqshift_tilde_31_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad3_clear() {
    this->freqshift_tilde_31_h_biquad3_reset();
}

void freqshift_tilde_31_h_biquad3_reset() {
    this->freqshift_tilde_31_h_biquad3_x1 = 0;
    this->freqshift_tilde_31_h_biquad3_x2 = 0;
    this->freqshift_tilde_31_h_biquad3_y1 = 0;
    this->freqshift_tilde_31_h_biquad3_y2 = 0;
}

void freqshift_tilde_31_h_biquad3_dspsetup() {
    this->freqshift_tilde_31_h_biquad3_reset();
}

number freqshift_tilde_31_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad4_x1 * a1 + this->freqshift_tilde_31_h_biquad4_x2 * 1 - (this->freqshift_tilde_31_h_biquad4_y1 * b1 + this->freqshift_tilde_31_h_biquad4_y2 * b2);
    this->freqshift_tilde_31_h_biquad4_x2 = this->freqshift_tilde_31_h_biquad4_x1;
    this->freqshift_tilde_31_h_biquad4_x1 = x;
    this->freqshift_tilde_31_h_biquad4_y2 = this->freqshift_tilde_31_h_biquad4_y1;
    this->freqshift_tilde_31_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad4_clear() {
    this->freqshift_tilde_31_h_biquad4_reset();
}

void freqshift_tilde_31_h_biquad4_reset() {
    this->freqshift_tilde_31_h_biquad4_x1 = 0;
    this->freqshift_tilde_31_h_biquad4_x2 = 0;
    this->freqshift_tilde_31_h_biquad4_y1 = 0;
    this->freqshift_tilde_31_h_biquad4_y2 = 0;
}

void freqshift_tilde_31_h_biquad4_dspsetup() {
    this->freqshift_tilde_31_h_biquad4_reset();
}

number freqshift_tilde_31_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad5_x1 * a1 + this->freqshift_tilde_31_h_biquad5_x2 * 1 - (this->freqshift_tilde_31_h_biquad5_y1 * b1 + this->freqshift_tilde_31_h_biquad5_y2 * b2);
    this->freqshift_tilde_31_h_biquad5_x2 = this->freqshift_tilde_31_h_biquad5_x1;
    this->freqshift_tilde_31_h_biquad5_x1 = x;
    this->freqshift_tilde_31_h_biquad5_y2 = this->freqshift_tilde_31_h_biquad5_y1;
    this->freqshift_tilde_31_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad5_clear() {
    this->freqshift_tilde_31_h_biquad5_reset();
}

void freqshift_tilde_31_h_biquad5_reset() {
    this->freqshift_tilde_31_h_biquad5_x1 = 0;
    this->freqshift_tilde_31_h_biquad5_x2 = 0;
    this->freqshift_tilde_31_h_biquad5_y1 = 0;
    this->freqshift_tilde_31_h_biquad5_y2 = 0;
}

void freqshift_tilde_31_h_biquad5_dspsetup() {
    this->freqshift_tilde_31_h_biquad5_reset();
}

number freqshift_tilde_31_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_31_h_biquad6_x1 * a1 + this->freqshift_tilde_31_h_biquad6_x2 * 1 - (this->freqshift_tilde_31_h_biquad6_y1 * b1 + this->freqshift_tilde_31_h_biquad6_y2 * b2);
    this->freqshift_tilde_31_h_biquad6_x2 = this->freqshift_tilde_31_h_biquad6_x1;
    this->freqshift_tilde_31_h_biquad6_x1 = x;
    this->freqshift_tilde_31_h_biquad6_y2 = this->freqshift_tilde_31_h_biquad6_y1;
    this->freqshift_tilde_31_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_31_h_biquad6_clear() {
    this->freqshift_tilde_31_h_biquad6_reset();
}

void freqshift_tilde_31_h_biquad6_reset() {
    this->freqshift_tilde_31_h_biquad6_x1 = 0;
    this->freqshift_tilde_31_h_biquad6_x2 = 0;
    this->freqshift_tilde_31_h_biquad6_y1 = 0;
    this->freqshift_tilde_31_h_biquad6_y2 = 0;
}

void freqshift_tilde_31_h_biquad6_dspsetup() {
    this->freqshift_tilde_31_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_31_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_31_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_31_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_31_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_31_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_31_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_31_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_31_h_clear() {
    this->freqshift_tilde_31_h_reset();
}

void freqshift_tilde_31_h_reset() {
    this->freqshift_tilde_31_h_biquad1_reset();
    this->freqshift_tilde_31_h_biquad2_reset();
    this->freqshift_tilde_31_h_biquad3_reset();
    this->freqshift_tilde_31_h_biquad4_reset();
    this->freqshift_tilde_31_h_biquad5_reset();
    this->freqshift_tilde_31_h_biquad6_reset();
}

void freqshift_tilde_31_h_dspsetup() {
    this->freqshift_tilde_31_h_reset();
}

number freqshift_tilde_31_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_31_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_31_p_conv;

    if (this->freqshift_tilde_31_p_currentPhase < 0.)
        this->freqshift_tilde_31_p_currentPhase = 1. + this->freqshift_tilde_31_p_currentPhase;

    if (this->freqshift_tilde_31_p_currentPhase > 1.)
        this->freqshift_tilde_31_p_currentPhase = this->freqshift_tilde_31_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_31_p_currentPhase;
    this->freqshift_tilde_31_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_31_p_reset() {
    this->freqshift_tilde_31_p_currentPhase = 0;
}

void freqshift_tilde_31_p_dspsetup() {
    this->freqshift_tilde_31_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_31_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_31_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_31_setupDone = true;
    this->freqshift_tilde_31_h_biquad1_dspsetup();
    this->freqshift_tilde_31_h_biquad2_dspsetup();
    this->freqshift_tilde_31_h_biquad3_dspsetup();
    this->freqshift_tilde_31_h_biquad4_dspsetup();
    this->freqshift_tilde_31_h_biquad5_dspsetup();
    this->freqshift_tilde_31_h_biquad6_dspsetup();
    this->freqshift_tilde_31_h_dspsetup();
    this->freqshift_tilde_31_p_dspsetup();
}

number freqshift_tilde_32_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad1_x1 * a1 + this->freqshift_tilde_32_h_biquad1_x2 * 1 - (this->freqshift_tilde_32_h_biquad1_y1 * b1 + this->freqshift_tilde_32_h_biquad1_y2 * b2);
    this->freqshift_tilde_32_h_biquad1_x2 = this->freqshift_tilde_32_h_biquad1_x1;
    this->freqshift_tilde_32_h_biquad1_x1 = x;
    this->freqshift_tilde_32_h_biquad1_y2 = this->freqshift_tilde_32_h_biquad1_y1;
    this->freqshift_tilde_32_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad1_clear() {
    this->freqshift_tilde_32_h_biquad1_reset();
}

void freqshift_tilde_32_h_biquad1_reset() {
    this->freqshift_tilde_32_h_biquad1_x1 = 0;
    this->freqshift_tilde_32_h_biquad1_x2 = 0;
    this->freqshift_tilde_32_h_biquad1_y1 = 0;
    this->freqshift_tilde_32_h_biquad1_y2 = 0;
}

void freqshift_tilde_32_h_biquad1_dspsetup() {
    this->freqshift_tilde_32_h_biquad1_reset();
}

number freqshift_tilde_32_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad2_x1 * a1 + this->freqshift_tilde_32_h_biquad2_x2 * 1 - (this->freqshift_tilde_32_h_biquad2_y1 * b1 + this->freqshift_tilde_32_h_biquad2_y2 * b2);
    this->freqshift_tilde_32_h_biquad2_x2 = this->freqshift_tilde_32_h_biquad2_x1;
    this->freqshift_tilde_32_h_biquad2_x1 = x;
    this->freqshift_tilde_32_h_biquad2_y2 = this->freqshift_tilde_32_h_biquad2_y1;
    this->freqshift_tilde_32_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad2_clear() {
    this->freqshift_tilde_32_h_biquad2_reset();
}

void freqshift_tilde_32_h_biquad2_reset() {
    this->freqshift_tilde_32_h_biquad2_x1 = 0;
    this->freqshift_tilde_32_h_biquad2_x2 = 0;
    this->freqshift_tilde_32_h_biquad2_y1 = 0;
    this->freqshift_tilde_32_h_biquad2_y2 = 0;
}

void freqshift_tilde_32_h_biquad2_dspsetup() {
    this->freqshift_tilde_32_h_biquad2_reset();
}

number freqshift_tilde_32_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad3_x1 * a1 + this->freqshift_tilde_32_h_biquad3_x2 * 1 - (this->freqshift_tilde_32_h_biquad3_y1 * b1 + this->freqshift_tilde_32_h_biquad3_y2 * b2);
    this->freqshift_tilde_32_h_biquad3_x2 = this->freqshift_tilde_32_h_biquad3_x1;
    this->freqshift_tilde_32_h_biquad3_x1 = x;
    this->freqshift_tilde_32_h_biquad3_y2 = this->freqshift_tilde_32_h_biquad3_y1;
    this->freqshift_tilde_32_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad3_clear() {
    this->freqshift_tilde_32_h_biquad3_reset();
}

void freqshift_tilde_32_h_biquad3_reset() {
    this->freqshift_tilde_32_h_biquad3_x1 = 0;
    this->freqshift_tilde_32_h_biquad3_x2 = 0;
    this->freqshift_tilde_32_h_biquad3_y1 = 0;
    this->freqshift_tilde_32_h_biquad3_y2 = 0;
}

void freqshift_tilde_32_h_biquad3_dspsetup() {
    this->freqshift_tilde_32_h_biquad3_reset();
}

number freqshift_tilde_32_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad4_x1 * a1 + this->freqshift_tilde_32_h_biquad4_x2 * 1 - (this->freqshift_tilde_32_h_biquad4_y1 * b1 + this->freqshift_tilde_32_h_biquad4_y2 * b2);
    this->freqshift_tilde_32_h_biquad4_x2 = this->freqshift_tilde_32_h_biquad4_x1;
    this->freqshift_tilde_32_h_biquad4_x1 = x;
    this->freqshift_tilde_32_h_biquad4_y2 = this->freqshift_tilde_32_h_biquad4_y1;
    this->freqshift_tilde_32_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad4_clear() {
    this->freqshift_tilde_32_h_biquad4_reset();
}

void freqshift_tilde_32_h_biquad4_reset() {
    this->freqshift_tilde_32_h_biquad4_x1 = 0;
    this->freqshift_tilde_32_h_biquad4_x2 = 0;
    this->freqshift_tilde_32_h_biquad4_y1 = 0;
    this->freqshift_tilde_32_h_biquad4_y2 = 0;
}

void freqshift_tilde_32_h_biquad4_dspsetup() {
    this->freqshift_tilde_32_h_biquad4_reset();
}

number freqshift_tilde_32_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad5_x1 * a1 + this->freqshift_tilde_32_h_biquad5_x2 * 1 - (this->freqshift_tilde_32_h_biquad5_y1 * b1 + this->freqshift_tilde_32_h_biquad5_y2 * b2);
    this->freqshift_tilde_32_h_biquad5_x2 = this->freqshift_tilde_32_h_biquad5_x1;
    this->freqshift_tilde_32_h_biquad5_x1 = x;
    this->freqshift_tilde_32_h_biquad5_y2 = this->freqshift_tilde_32_h_biquad5_y1;
    this->freqshift_tilde_32_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad5_clear() {
    this->freqshift_tilde_32_h_biquad5_reset();
}

void freqshift_tilde_32_h_biquad5_reset() {
    this->freqshift_tilde_32_h_biquad5_x1 = 0;
    this->freqshift_tilde_32_h_biquad5_x2 = 0;
    this->freqshift_tilde_32_h_biquad5_y1 = 0;
    this->freqshift_tilde_32_h_biquad5_y2 = 0;
}

void freqshift_tilde_32_h_biquad5_dspsetup() {
    this->freqshift_tilde_32_h_biquad5_reset();
}

number freqshift_tilde_32_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_32_h_biquad6_x1 * a1 + this->freqshift_tilde_32_h_biquad6_x2 * 1 - (this->freqshift_tilde_32_h_biquad6_y1 * b1 + this->freqshift_tilde_32_h_biquad6_y2 * b2);
    this->freqshift_tilde_32_h_biquad6_x2 = this->freqshift_tilde_32_h_biquad6_x1;
    this->freqshift_tilde_32_h_biquad6_x1 = x;
    this->freqshift_tilde_32_h_biquad6_y2 = this->freqshift_tilde_32_h_biquad6_y1;
    this->freqshift_tilde_32_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_32_h_biquad6_clear() {
    this->freqshift_tilde_32_h_biquad6_reset();
}

void freqshift_tilde_32_h_biquad6_reset() {
    this->freqshift_tilde_32_h_biquad6_x1 = 0;
    this->freqshift_tilde_32_h_biquad6_x2 = 0;
    this->freqshift_tilde_32_h_biquad6_y1 = 0;
    this->freqshift_tilde_32_h_biquad6_y2 = 0;
}

void freqshift_tilde_32_h_biquad6_dspsetup() {
    this->freqshift_tilde_32_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_32_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_32_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_32_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_32_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_32_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_32_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_32_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_32_h_clear() {
    this->freqshift_tilde_32_h_reset();
}

void freqshift_tilde_32_h_reset() {
    this->freqshift_tilde_32_h_biquad1_reset();
    this->freqshift_tilde_32_h_biquad2_reset();
    this->freqshift_tilde_32_h_biquad3_reset();
    this->freqshift_tilde_32_h_biquad4_reset();
    this->freqshift_tilde_32_h_biquad5_reset();
    this->freqshift_tilde_32_h_biquad6_reset();
}

void freqshift_tilde_32_h_dspsetup() {
    this->freqshift_tilde_32_h_reset();
}

number freqshift_tilde_32_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_32_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_32_p_conv;

    if (this->freqshift_tilde_32_p_currentPhase < 0.)
        this->freqshift_tilde_32_p_currentPhase = 1. + this->freqshift_tilde_32_p_currentPhase;

    if (this->freqshift_tilde_32_p_currentPhase > 1.)
        this->freqshift_tilde_32_p_currentPhase = this->freqshift_tilde_32_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_32_p_currentPhase;
    this->freqshift_tilde_32_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_32_p_reset() {
    this->freqshift_tilde_32_p_currentPhase = 0;
}

void freqshift_tilde_32_p_dspsetup() {
    this->freqshift_tilde_32_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_32_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_32_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_32_setupDone = true;
    this->freqshift_tilde_32_h_biquad1_dspsetup();
    this->freqshift_tilde_32_h_biquad2_dspsetup();
    this->freqshift_tilde_32_h_biquad3_dspsetup();
    this->freqshift_tilde_32_h_biquad4_dspsetup();
    this->freqshift_tilde_32_h_biquad5_dspsetup();
    this->freqshift_tilde_32_h_biquad6_dspsetup();
    this->freqshift_tilde_32_h_dspsetup();
    this->freqshift_tilde_32_p_dspsetup();
}

number gaintilde_34_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_34_ramp_d_prev);
    this->gaintilde_34_ramp_d_prev = x;
    return temp;
}

void gaintilde_34_ramp_d_dspsetup() {
    this->gaintilde_34_ramp_d_reset();
}

void gaintilde_34_ramp_d_reset() {
    this->gaintilde_34_ramp_d_prev = 0;
}

number gaintilde_34_ramp_next(number x, number up, number down) {
    if (this->gaintilde_34_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_34_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_34_ramp_index = _up;
            this->gaintilde_34_ramp_increment = (x - this->gaintilde_34_ramp_prev) / _up;
        } else if (x < this->gaintilde_34_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_34_ramp_index = _down;
            this->gaintilde_34_ramp_increment = (x - this->gaintilde_34_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_34_ramp_index > 0) {
        this->gaintilde_34_ramp_prev += this->gaintilde_34_ramp_increment;
        this->gaintilde_34_ramp_index -= 1;
    } else {
        this->gaintilde_34_ramp_prev = x;
    }

    return this->gaintilde_34_ramp_prev;
}

void gaintilde_34_ramp_reset() {
    this->gaintilde_34_ramp_prev = 0;
    this->gaintilde_34_ramp_index = 0;
    this->gaintilde_34_ramp_increment = 0;
    this->gaintilde_34_ramp_d_reset();
}

void gaintilde_34_init() {
    this->gaintilde_34_loginc = rnbo_log(1.072);
    this->gaintilde_34_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_34_loginc));
}

void gaintilde_34_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_34_value;
}

void gaintilde_34_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_34_value_set(preset["value"]);
}

void gaintilde_34_dspsetup(bool force) {
    if ((bool)(this->gaintilde_34_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_34_setupDone = true;
    this->gaintilde_34_ramp_d_dspsetup();
}

number gaintilde_35_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_35_ramp_d_prev);
    this->gaintilde_35_ramp_d_prev = x;
    return temp;
}

void gaintilde_35_ramp_d_dspsetup() {
    this->gaintilde_35_ramp_d_reset();
}

void gaintilde_35_ramp_d_reset() {
    this->gaintilde_35_ramp_d_prev = 0;
}

number gaintilde_35_ramp_next(number x, number up, number down) {
    if (this->gaintilde_35_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_35_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_35_ramp_index = _up;
            this->gaintilde_35_ramp_increment = (x - this->gaintilde_35_ramp_prev) / _up;
        } else if (x < this->gaintilde_35_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_35_ramp_index = _down;
            this->gaintilde_35_ramp_increment = (x - this->gaintilde_35_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_35_ramp_index > 0) {
        this->gaintilde_35_ramp_prev += this->gaintilde_35_ramp_increment;
        this->gaintilde_35_ramp_index -= 1;
    } else {
        this->gaintilde_35_ramp_prev = x;
    }

    return this->gaintilde_35_ramp_prev;
}

void gaintilde_35_ramp_reset() {
    this->gaintilde_35_ramp_prev = 0;
    this->gaintilde_35_ramp_index = 0;
    this->gaintilde_35_ramp_increment = 0;
    this->gaintilde_35_ramp_d_reset();
}

void gaintilde_35_init() {
    this->gaintilde_35_loginc = rnbo_log(1.072);
    this->gaintilde_35_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_35_loginc));
}

void gaintilde_35_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_35_value;
}

void gaintilde_35_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_35_value_set(preset["value"]);
}

void gaintilde_35_dspsetup(bool force) {
    if ((bool)(this->gaintilde_35_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_35_setupDone = true;
    this->gaintilde_35_ramp_d_dspsetup();
}

number freqshift_tilde_33_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad1_x1 * a1 + this->freqshift_tilde_33_h_biquad1_x2 * 1 - (this->freqshift_tilde_33_h_biquad1_y1 * b1 + this->freqshift_tilde_33_h_biquad1_y2 * b2);
    this->freqshift_tilde_33_h_biquad1_x2 = this->freqshift_tilde_33_h_biquad1_x1;
    this->freqshift_tilde_33_h_biquad1_x1 = x;
    this->freqshift_tilde_33_h_biquad1_y2 = this->freqshift_tilde_33_h_biquad1_y1;
    this->freqshift_tilde_33_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad1_clear() {
    this->freqshift_tilde_33_h_biquad1_reset();
}

void freqshift_tilde_33_h_biquad1_reset() {
    this->freqshift_tilde_33_h_biquad1_x1 = 0;
    this->freqshift_tilde_33_h_biquad1_x2 = 0;
    this->freqshift_tilde_33_h_biquad1_y1 = 0;
    this->freqshift_tilde_33_h_biquad1_y2 = 0;
}

void freqshift_tilde_33_h_biquad1_dspsetup() {
    this->freqshift_tilde_33_h_biquad1_reset();
}

number freqshift_tilde_33_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad2_x1 * a1 + this->freqshift_tilde_33_h_biquad2_x2 * 1 - (this->freqshift_tilde_33_h_biquad2_y1 * b1 + this->freqshift_tilde_33_h_biquad2_y2 * b2);
    this->freqshift_tilde_33_h_biquad2_x2 = this->freqshift_tilde_33_h_biquad2_x1;
    this->freqshift_tilde_33_h_biquad2_x1 = x;
    this->freqshift_tilde_33_h_biquad2_y2 = this->freqshift_tilde_33_h_biquad2_y1;
    this->freqshift_tilde_33_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad2_clear() {
    this->freqshift_tilde_33_h_biquad2_reset();
}

void freqshift_tilde_33_h_biquad2_reset() {
    this->freqshift_tilde_33_h_biquad2_x1 = 0;
    this->freqshift_tilde_33_h_biquad2_x2 = 0;
    this->freqshift_tilde_33_h_biquad2_y1 = 0;
    this->freqshift_tilde_33_h_biquad2_y2 = 0;
}

void freqshift_tilde_33_h_biquad2_dspsetup() {
    this->freqshift_tilde_33_h_biquad2_reset();
}

number freqshift_tilde_33_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad3_x1 * a1 + this->freqshift_tilde_33_h_biquad3_x2 * 1 - (this->freqshift_tilde_33_h_biquad3_y1 * b1 + this->freqshift_tilde_33_h_biquad3_y2 * b2);
    this->freqshift_tilde_33_h_biquad3_x2 = this->freqshift_tilde_33_h_biquad3_x1;
    this->freqshift_tilde_33_h_biquad3_x1 = x;
    this->freqshift_tilde_33_h_biquad3_y2 = this->freqshift_tilde_33_h_biquad3_y1;
    this->freqshift_tilde_33_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad3_clear() {
    this->freqshift_tilde_33_h_biquad3_reset();
}

void freqshift_tilde_33_h_biquad3_reset() {
    this->freqshift_tilde_33_h_biquad3_x1 = 0;
    this->freqshift_tilde_33_h_biquad3_x2 = 0;
    this->freqshift_tilde_33_h_biquad3_y1 = 0;
    this->freqshift_tilde_33_h_biquad3_y2 = 0;
}

void freqshift_tilde_33_h_biquad3_dspsetup() {
    this->freqshift_tilde_33_h_biquad3_reset();
}

number freqshift_tilde_33_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad4_x1 * a1 + this->freqshift_tilde_33_h_biquad4_x2 * 1 - (this->freqshift_tilde_33_h_biquad4_y1 * b1 + this->freqshift_tilde_33_h_biquad4_y2 * b2);
    this->freqshift_tilde_33_h_biquad4_x2 = this->freqshift_tilde_33_h_biquad4_x1;
    this->freqshift_tilde_33_h_biquad4_x1 = x;
    this->freqshift_tilde_33_h_biquad4_y2 = this->freqshift_tilde_33_h_biquad4_y1;
    this->freqshift_tilde_33_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad4_clear() {
    this->freqshift_tilde_33_h_biquad4_reset();
}

void freqshift_tilde_33_h_biquad4_reset() {
    this->freqshift_tilde_33_h_biquad4_x1 = 0;
    this->freqshift_tilde_33_h_biquad4_x2 = 0;
    this->freqshift_tilde_33_h_biquad4_y1 = 0;
    this->freqshift_tilde_33_h_biquad4_y2 = 0;
}

void freqshift_tilde_33_h_biquad4_dspsetup() {
    this->freqshift_tilde_33_h_biquad4_reset();
}

number freqshift_tilde_33_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad5_x1 * a1 + this->freqshift_tilde_33_h_biquad5_x2 * 1 - (this->freqshift_tilde_33_h_biquad5_y1 * b1 + this->freqshift_tilde_33_h_biquad5_y2 * b2);
    this->freqshift_tilde_33_h_biquad5_x2 = this->freqshift_tilde_33_h_biquad5_x1;
    this->freqshift_tilde_33_h_biquad5_x1 = x;
    this->freqshift_tilde_33_h_biquad5_y2 = this->freqshift_tilde_33_h_biquad5_y1;
    this->freqshift_tilde_33_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad5_clear() {
    this->freqshift_tilde_33_h_biquad5_reset();
}

void freqshift_tilde_33_h_biquad5_reset() {
    this->freqshift_tilde_33_h_biquad5_x1 = 0;
    this->freqshift_tilde_33_h_biquad5_x2 = 0;
    this->freqshift_tilde_33_h_biquad5_y1 = 0;
    this->freqshift_tilde_33_h_biquad5_y2 = 0;
}

void freqshift_tilde_33_h_biquad5_dspsetup() {
    this->freqshift_tilde_33_h_biquad5_reset();
}

number freqshift_tilde_33_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_33_h_biquad6_x1 * a1 + this->freqshift_tilde_33_h_biquad6_x2 * 1 - (this->freqshift_tilde_33_h_biquad6_y1 * b1 + this->freqshift_tilde_33_h_biquad6_y2 * b2);
    this->freqshift_tilde_33_h_biquad6_x2 = this->freqshift_tilde_33_h_biquad6_x1;
    this->freqshift_tilde_33_h_biquad6_x1 = x;
    this->freqshift_tilde_33_h_biquad6_y2 = this->freqshift_tilde_33_h_biquad6_y1;
    this->freqshift_tilde_33_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_33_h_biquad6_clear() {
    this->freqshift_tilde_33_h_biquad6_reset();
}

void freqshift_tilde_33_h_biquad6_reset() {
    this->freqshift_tilde_33_h_biquad6_x1 = 0;
    this->freqshift_tilde_33_h_biquad6_x2 = 0;
    this->freqshift_tilde_33_h_biquad6_y1 = 0;
    this->freqshift_tilde_33_h_biquad6_y2 = 0;
}

void freqshift_tilde_33_h_biquad6_dspsetup() {
    this->freqshift_tilde_33_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_33_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_33_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_33_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_33_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_33_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_33_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_33_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_33_h_clear() {
    this->freqshift_tilde_33_h_reset();
}

void freqshift_tilde_33_h_reset() {
    this->freqshift_tilde_33_h_biquad1_reset();
    this->freqshift_tilde_33_h_biquad2_reset();
    this->freqshift_tilde_33_h_biquad3_reset();
    this->freqshift_tilde_33_h_biquad4_reset();
    this->freqshift_tilde_33_h_biquad5_reset();
    this->freqshift_tilde_33_h_biquad6_reset();
}

void freqshift_tilde_33_h_dspsetup() {
    this->freqshift_tilde_33_h_reset();
}

number freqshift_tilde_33_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_33_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_33_p_conv;

    if (this->freqshift_tilde_33_p_currentPhase < 0.)
        this->freqshift_tilde_33_p_currentPhase = 1. + this->freqshift_tilde_33_p_currentPhase;

    if (this->freqshift_tilde_33_p_currentPhase > 1.)
        this->freqshift_tilde_33_p_currentPhase = this->freqshift_tilde_33_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_33_p_currentPhase;
    this->freqshift_tilde_33_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_33_p_reset() {
    this->freqshift_tilde_33_p_currentPhase = 0;
}

void freqshift_tilde_33_p_dspsetup() {
    this->freqshift_tilde_33_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_33_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_33_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_33_setupDone = true;
    this->freqshift_tilde_33_h_biquad1_dspsetup();
    this->freqshift_tilde_33_h_biquad2_dspsetup();
    this->freqshift_tilde_33_h_biquad3_dspsetup();
    this->freqshift_tilde_33_h_biquad4_dspsetup();
    this->freqshift_tilde_33_h_biquad5_dspsetup();
    this->freqshift_tilde_33_h_biquad6_dspsetup();
    this->freqshift_tilde_33_h_dspsetup();
    this->freqshift_tilde_33_p_dspsetup();
}

number freqshift_tilde_34_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad1_x1 * a1 + this->freqshift_tilde_34_h_biquad1_x2 * 1 - (this->freqshift_tilde_34_h_biquad1_y1 * b1 + this->freqshift_tilde_34_h_biquad1_y2 * b2);
    this->freqshift_tilde_34_h_biquad1_x2 = this->freqshift_tilde_34_h_biquad1_x1;
    this->freqshift_tilde_34_h_biquad1_x1 = x;
    this->freqshift_tilde_34_h_biquad1_y2 = this->freqshift_tilde_34_h_biquad1_y1;
    this->freqshift_tilde_34_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad1_clear() {
    this->freqshift_tilde_34_h_biquad1_reset();
}

void freqshift_tilde_34_h_biquad1_reset() {
    this->freqshift_tilde_34_h_biquad1_x1 = 0;
    this->freqshift_tilde_34_h_biquad1_x2 = 0;
    this->freqshift_tilde_34_h_biquad1_y1 = 0;
    this->freqshift_tilde_34_h_biquad1_y2 = 0;
}

void freqshift_tilde_34_h_biquad1_dspsetup() {
    this->freqshift_tilde_34_h_biquad1_reset();
}

number freqshift_tilde_34_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad2_x1 * a1 + this->freqshift_tilde_34_h_biquad2_x2 * 1 - (this->freqshift_tilde_34_h_biquad2_y1 * b1 + this->freqshift_tilde_34_h_biquad2_y2 * b2);
    this->freqshift_tilde_34_h_biquad2_x2 = this->freqshift_tilde_34_h_biquad2_x1;
    this->freqshift_tilde_34_h_biquad2_x1 = x;
    this->freqshift_tilde_34_h_biquad2_y2 = this->freqshift_tilde_34_h_biquad2_y1;
    this->freqshift_tilde_34_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad2_clear() {
    this->freqshift_tilde_34_h_biquad2_reset();
}

void freqshift_tilde_34_h_biquad2_reset() {
    this->freqshift_tilde_34_h_biquad2_x1 = 0;
    this->freqshift_tilde_34_h_biquad2_x2 = 0;
    this->freqshift_tilde_34_h_biquad2_y1 = 0;
    this->freqshift_tilde_34_h_biquad2_y2 = 0;
}

void freqshift_tilde_34_h_biquad2_dspsetup() {
    this->freqshift_tilde_34_h_biquad2_reset();
}

number freqshift_tilde_34_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad3_x1 * a1 + this->freqshift_tilde_34_h_biquad3_x2 * 1 - (this->freqshift_tilde_34_h_biquad3_y1 * b1 + this->freqshift_tilde_34_h_biquad3_y2 * b2);
    this->freqshift_tilde_34_h_biquad3_x2 = this->freqshift_tilde_34_h_biquad3_x1;
    this->freqshift_tilde_34_h_biquad3_x1 = x;
    this->freqshift_tilde_34_h_biquad3_y2 = this->freqshift_tilde_34_h_biquad3_y1;
    this->freqshift_tilde_34_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad3_clear() {
    this->freqshift_tilde_34_h_biquad3_reset();
}

void freqshift_tilde_34_h_biquad3_reset() {
    this->freqshift_tilde_34_h_biquad3_x1 = 0;
    this->freqshift_tilde_34_h_biquad3_x2 = 0;
    this->freqshift_tilde_34_h_biquad3_y1 = 0;
    this->freqshift_tilde_34_h_biquad3_y2 = 0;
}

void freqshift_tilde_34_h_biquad3_dspsetup() {
    this->freqshift_tilde_34_h_biquad3_reset();
}

number freqshift_tilde_34_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad4_x1 * a1 + this->freqshift_tilde_34_h_biquad4_x2 * 1 - (this->freqshift_tilde_34_h_biquad4_y1 * b1 + this->freqshift_tilde_34_h_biquad4_y2 * b2);
    this->freqshift_tilde_34_h_biquad4_x2 = this->freqshift_tilde_34_h_biquad4_x1;
    this->freqshift_tilde_34_h_biquad4_x1 = x;
    this->freqshift_tilde_34_h_biquad4_y2 = this->freqshift_tilde_34_h_biquad4_y1;
    this->freqshift_tilde_34_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad4_clear() {
    this->freqshift_tilde_34_h_biquad4_reset();
}

void freqshift_tilde_34_h_biquad4_reset() {
    this->freqshift_tilde_34_h_biquad4_x1 = 0;
    this->freqshift_tilde_34_h_biquad4_x2 = 0;
    this->freqshift_tilde_34_h_biquad4_y1 = 0;
    this->freqshift_tilde_34_h_biquad4_y2 = 0;
}

void freqshift_tilde_34_h_biquad4_dspsetup() {
    this->freqshift_tilde_34_h_biquad4_reset();
}

number freqshift_tilde_34_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad5_x1 * a1 + this->freqshift_tilde_34_h_biquad5_x2 * 1 - (this->freqshift_tilde_34_h_biquad5_y1 * b1 + this->freqshift_tilde_34_h_biquad5_y2 * b2);
    this->freqshift_tilde_34_h_biquad5_x2 = this->freqshift_tilde_34_h_biquad5_x1;
    this->freqshift_tilde_34_h_biquad5_x1 = x;
    this->freqshift_tilde_34_h_biquad5_y2 = this->freqshift_tilde_34_h_biquad5_y1;
    this->freqshift_tilde_34_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad5_clear() {
    this->freqshift_tilde_34_h_biquad5_reset();
}

void freqshift_tilde_34_h_biquad5_reset() {
    this->freqshift_tilde_34_h_biquad5_x1 = 0;
    this->freqshift_tilde_34_h_biquad5_x2 = 0;
    this->freqshift_tilde_34_h_biquad5_y1 = 0;
    this->freqshift_tilde_34_h_biquad5_y2 = 0;
}

void freqshift_tilde_34_h_biquad5_dspsetup() {
    this->freqshift_tilde_34_h_biquad5_reset();
}

number freqshift_tilde_34_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_34_h_biquad6_x1 * a1 + this->freqshift_tilde_34_h_biquad6_x2 * 1 - (this->freqshift_tilde_34_h_biquad6_y1 * b1 + this->freqshift_tilde_34_h_biquad6_y2 * b2);
    this->freqshift_tilde_34_h_biquad6_x2 = this->freqshift_tilde_34_h_biquad6_x1;
    this->freqshift_tilde_34_h_biquad6_x1 = x;
    this->freqshift_tilde_34_h_biquad6_y2 = this->freqshift_tilde_34_h_biquad6_y1;
    this->freqshift_tilde_34_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_34_h_biquad6_clear() {
    this->freqshift_tilde_34_h_biquad6_reset();
}

void freqshift_tilde_34_h_biquad6_reset() {
    this->freqshift_tilde_34_h_biquad6_x1 = 0;
    this->freqshift_tilde_34_h_biquad6_x2 = 0;
    this->freqshift_tilde_34_h_biquad6_y1 = 0;
    this->freqshift_tilde_34_h_biquad6_y2 = 0;
}

void freqshift_tilde_34_h_biquad6_dspsetup() {
    this->freqshift_tilde_34_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_34_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_34_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_34_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_34_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_34_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_34_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_34_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_34_h_clear() {
    this->freqshift_tilde_34_h_reset();
}

void freqshift_tilde_34_h_reset() {
    this->freqshift_tilde_34_h_biquad1_reset();
    this->freqshift_tilde_34_h_biquad2_reset();
    this->freqshift_tilde_34_h_biquad3_reset();
    this->freqshift_tilde_34_h_biquad4_reset();
    this->freqshift_tilde_34_h_biquad5_reset();
    this->freqshift_tilde_34_h_biquad6_reset();
}

void freqshift_tilde_34_h_dspsetup() {
    this->freqshift_tilde_34_h_reset();
}

number freqshift_tilde_34_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_34_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_34_p_conv;

    if (this->freqshift_tilde_34_p_currentPhase < 0.)
        this->freqshift_tilde_34_p_currentPhase = 1. + this->freqshift_tilde_34_p_currentPhase;

    if (this->freqshift_tilde_34_p_currentPhase > 1.)
        this->freqshift_tilde_34_p_currentPhase = this->freqshift_tilde_34_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_34_p_currentPhase;
    this->freqshift_tilde_34_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_34_p_reset() {
    this->freqshift_tilde_34_p_currentPhase = 0;
}

void freqshift_tilde_34_p_dspsetup() {
    this->freqshift_tilde_34_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_34_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_34_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_34_setupDone = true;
    this->freqshift_tilde_34_h_biquad1_dspsetup();
    this->freqshift_tilde_34_h_biquad2_dspsetup();
    this->freqshift_tilde_34_h_biquad3_dspsetup();
    this->freqshift_tilde_34_h_biquad4_dspsetup();
    this->freqshift_tilde_34_h_biquad5_dspsetup();
    this->freqshift_tilde_34_h_biquad6_dspsetup();
    this->freqshift_tilde_34_h_dspsetup();
    this->freqshift_tilde_34_p_dspsetup();
}

number gaintilde_36_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_36_ramp_d_prev);
    this->gaintilde_36_ramp_d_prev = x;
    return temp;
}

void gaintilde_36_ramp_d_dspsetup() {
    this->gaintilde_36_ramp_d_reset();
}

void gaintilde_36_ramp_d_reset() {
    this->gaintilde_36_ramp_d_prev = 0;
}

number gaintilde_36_ramp_next(number x, number up, number down) {
    if (this->gaintilde_36_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_36_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_36_ramp_index = _up;
            this->gaintilde_36_ramp_increment = (x - this->gaintilde_36_ramp_prev) / _up;
        } else if (x < this->gaintilde_36_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_36_ramp_index = _down;
            this->gaintilde_36_ramp_increment = (x - this->gaintilde_36_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_36_ramp_index > 0) {
        this->gaintilde_36_ramp_prev += this->gaintilde_36_ramp_increment;
        this->gaintilde_36_ramp_index -= 1;
    } else {
        this->gaintilde_36_ramp_prev = x;
    }

    return this->gaintilde_36_ramp_prev;
}

void gaintilde_36_ramp_reset() {
    this->gaintilde_36_ramp_prev = 0;
    this->gaintilde_36_ramp_index = 0;
    this->gaintilde_36_ramp_increment = 0;
    this->gaintilde_36_ramp_d_reset();
}

void gaintilde_36_init() {
    this->gaintilde_36_loginc = rnbo_log(1.072);
    this->gaintilde_36_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_36_loginc));
}

void gaintilde_36_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_36_value;
}

void gaintilde_36_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_36_value_set(preset["value"]);
}

void gaintilde_36_dspsetup(bool force) {
    if ((bool)(this->gaintilde_36_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_36_setupDone = true;
    this->gaintilde_36_ramp_d_dspsetup();
}

number gaintilde_37_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_37_ramp_d_prev);
    this->gaintilde_37_ramp_d_prev = x;
    return temp;
}

void gaintilde_37_ramp_d_dspsetup() {
    this->gaintilde_37_ramp_d_reset();
}

void gaintilde_37_ramp_d_reset() {
    this->gaintilde_37_ramp_d_prev = 0;
}

number gaintilde_37_ramp_next(number x, number up, number down) {
    if (this->gaintilde_37_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_37_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_37_ramp_index = _up;
            this->gaintilde_37_ramp_increment = (x - this->gaintilde_37_ramp_prev) / _up;
        } else if (x < this->gaintilde_37_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_37_ramp_index = _down;
            this->gaintilde_37_ramp_increment = (x - this->gaintilde_37_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_37_ramp_index > 0) {
        this->gaintilde_37_ramp_prev += this->gaintilde_37_ramp_increment;
        this->gaintilde_37_ramp_index -= 1;
    } else {
        this->gaintilde_37_ramp_prev = x;
    }

    return this->gaintilde_37_ramp_prev;
}

void gaintilde_37_ramp_reset() {
    this->gaintilde_37_ramp_prev = 0;
    this->gaintilde_37_ramp_index = 0;
    this->gaintilde_37_ramp_increment = 0;
    this->gaintilde_37_ramp_d_reset();
}

void gaintilde_37_init() {
    this->gaintilde_37_loginc = rnbo_log(1.072);
    this->gaintilde_37_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_37_loginc));
}

void gaintilde_37_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_37_value;
}

void gaintilde_37_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_37_value_set(preset["value"]);
}

void gaintilde_37_dspsetup(bool force) {
    if ((bool)(this->gaintilde_37_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_37_setupDone = true;
    this->gaintilde_37_ramp_d_dspsetup();
}

number freqshift_tilde_35_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad1_x1 * a1 + this->freqshift_tilde_35_h_biquad1_x2 * 1 - (this->freqshift_tilde_35_h_biquad1_y1 * b1 + this->freqshift_tilde_35_h_biquad1_y2 * b2);
    this->freqshift_tilde_35_h_biquad1_x2 = this->freqshift_tilde_35_h_biquad1_x1;
    this->freqshift_tilde_35_h_biquad1_x1 = x;
    this->freqshift_tilde_35_h_biquad1_y2 = this->freqshift_tilde_35_h_biquad1_y1;
    this->freqshift_tilde_35_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad1_clear() {
    this->freqshift_tilde_35_h_biquad1_reset();
}

void freqshift_tilde_35_h_biquad1_reset() {
    this->freqshift_tilde_35_h_biquad1_x1 = 0;
    this->freqshift_tilde_35_h_biquad1_x2 = 0;
    this->freqshift_tilde_35_h_biquad1_y1 = 0;
    this->freqshift_tilde_35_h_biquad1_y2 = 0;
}

void freqshift_tilde_35_h_biquad1_dspsetup() {
    this->freqshift_tilde_35_h_biquad1_reset();
}

number freqshift_tilde_35_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad2_x1 * a1 + this->freqshift_tilde_35_h_biquad2_x2 * 1 - (this->freqshift_tilde_35_h_biquad2_y1 * b1 + this->freqshift_tilde_35_h_biquad2_y2 * b2);
    this->freqshift_tilde_35_h_biquad2_x2 = this->freqshift_tilde_35_h_biquad2_x1;
    this->freqshift_tilde_35_h_biquad2_x1 = x;
    this->freqshift_tilde_35_h_biquad2_y2 = this->freqshift_tilde_35_h_biquad2_y1;
    this->freqshift_tilde_35_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad2_clear() {
    this->freqshift_tilde_35_h_biquad2_reset();
}

void freqshift_tilde_35_h_biquad2_reset() {
    this->freqshift_tilde_35_h_biquad2_x1 = 0;
    this->freqshift_tilde_35_h_biquad2_x2 = 0;
    this->freqshift_tilde_35_h_biquad2_y1 = 0;
    this->freqshift_tilde_35_h_biquad2_y2 = 0;
}

void freqshift_tilde_35_h_biquad2_dspsetup() {
    this->freqshift_tilde_35_h_biquad2_reset();
}

number freqshift_tilde_35_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad3_x1 * a1 + this->freqshift_tilde_35_h_biquad3_x2 * 1 - (this->freqshift_tilde_35_h_biquad3_y1 * b1 + this->freqshift_tilde_35_h_biquad3_y2 * b2);
    this->freqshift_tilde_35_h_biquad3_x2 = this->freqshift_tilde_35_h_biquad3_x1;
    this->freqshift_tilde_35_h_biquad3_x1 = x;
    this->freqshift_tilde_35_h_biquad3_y2 = this->freqshift_tilde_35_h_biquad3_y1;
    this->freqshift_tilde_35_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad3_clear() {
    this->freqshift_tilde_35_h_biquad3_reset();
}

void freqshift_tilde_35_h_biquad3_reset() {
    this->freqshift_tilde_35_h_biquad3_x1 = 0;
    this->freqshift_tilde_35_h_biquad3_x2 = 0;
    this->freqshift_tilde_35_h_biquad3_y1 = 0;
    this->freqshift_tilde_35_h_biquad3_y2 = 0;
}

void freqshift_tilde_35_h_biquad3_dspsetup() {
    this->freqshift_tilde_35_h_biquad3_reset();
}

number freqshift_tilde_35_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad4_x1 * a1 + this->freqshift_tilde_35_h_biquad4_x2 * 1 - (this->freqshift_tilde_35_h_biquad4_y1 * b1 + this->freqshift_tilde_35_h_biquad4_y2 * b2);
    this->freqshift_tilde_35_h_biquad4_x2 = this->freqshift_tilde_35_h_biquad4_x1;
    this->freqshift_tilde_35_h_biquad4_x1 = x;
    this->freqshift_tilde_35_h_biquad4_y2 = this->freqshift_tilde_35_h_biquad4_y1;
    this->freqshift_tilde_35_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad4_clear() {
    this->freqshift_tilde_35_h_biquad4_reset();
}

void freqshift_tilde_35_h_biquad4_reset() {
    this->freqshift_tilde_35_h_biquad4_x1 = 0;
    this->freqshift_tilde_35_h_biquad4_x2 = 0;
    this->freqshift_tilde_35_h_biquad4_y1 = 0;
    this->freqshift_tilde_35_h_biquad4_y2 = 0;
}

void freqshift_tilde_35_h_biquad4_dspsetup() {
    this->freqshift_tilde_35_h_biquad4_reset();
}

number freqshift_tilde_35_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad5_x1 * a1 + this->freqshift_tilde_35_h_biquad5_x2 * 1 - (this->freqshift_tilde_35_h_biquad5_y1 * b1 + this->freqshift_tilde_35_h_biquad5_y2 * b2);
    this->freqshift_tilde_35_h_biquad5_x2 = this->freqshift_tilde_35_h_biquad5_x1;
    this->freqshift_tilde_35_h_biquad5_x1 = x;
    this->freqshift_tilde_35_h_biquad5_y2 = this->freqshift_tilde_35_h_biquad5_y1;
    this->freqshift_tilde_35_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad5_clear() {
    this->freqshift_tilde_35_h_biquad5_reset();
}

void freqshift_tilde_35_h_biquad5_reset() {
    this->freqshift_tilde_35_h_biquad5_x1 = 0;
    this->freqshift_tilde_35_h_biquad5_x2 = 0;
    this->freqshift_tilde_35_h_biquad5_y1 = 0;
    this->freqshift_tilde_35_h_biquad5_y2 = 0;
}

void freqshift_tilde_35_h_biquad5_dspsetup() {
    this->freqshift_tilde_35_h_biquad5_reset();
}

number freqshift_tilde_35_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_35_h_biquad6_x1 * a1 + this->freqshift_tilde_35_h_biquad6_x2 * 1 - (this->freqshift_tilde_35_h_biquad6_y1 * b1 + this->freqshift_tilde_35_h_biquad6_y2 * b2);
    this->freqshift_tilde_35_h_biquad6_x2 = this->freqshift_tilde_35_h_biquad6_x1;
    this->freqshift_tilde_35_h_biquad6_x1 = x;
    this->freqshift_tilde_35_h_biquad6_y2 = this->freqshift_tilde_35_h_biquad6_y1;
    this->freqshift_tilde_35_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_35_h_biquad6_clear() {
    this->freqshift_tilde_35_h_biquad6_reset();
}

void freqshift_tilde_35_h_biquad6_reset() {
    this->freqshift_tilde_35_h_biquad6_x1 = 0;
    this->freqshift_tilde_35_h_biquad6_x2 = 0;
    this->freqshift_tilde_35_h_biquad6_y1 = 0;
    this->freqshift_tilde_35_h_biquad6_y2 = 0;
}

void freqshift_tilde_35_h_biquad6_dspsetup() {
    this->freqshift_tilde_35_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_35_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_35_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_35_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_35_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_35_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_35_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_35_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_35_h_clear() {
    this->freqshift_tilde_35_h_reset();
}

void freqshift_tilde_35_h_reset() {
    this->freqshift_tilde_35_h_biquad1_reset();
    this->freqshift_tilde_35_h_biquad2_reset();
    this->freqshift_tilde_35_h_biquad3_reset();
    this->freqshift_tilde_35_h_biquad4_reset();
    this->freqshift_tilde_35_h_biquad5_reset();
    this->freqshift_tilde_35_h_biquad6_reset();
}

void freqshift_tilde_35_h_dspsetup() {
    this->freqshift_tilde_35_h_reset();
}

number freqshift_tilde_35_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_35_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_35_p_conv;

    if (this->freqshift_tilde_35_p_currentPhase < 0.)
        this->freqshift_tilde_35_p_currentPhase = 1. + this->freqshift_tilde_35_p_currentPhase;

    if (this->freqshift_tilde_35_p_currentPhase > 1.)
        this->freqshift_tilde_35_p_currentPhase = this->freqshift_tilde_35_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_35_p_currentPhase;
    this->freqshift_tilde_35_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_35_p_reset() {
    this->freqshift_tilde_35_p_currentPhase = 0;
}

void freqshift_tilde_35_p_dspsetup() {
    this->freqshift_tilde_35_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_35_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_35_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_35_setupDone = true;
    this->freqshift_tilde_35_h_biquad1_dspsetup();
    this->freqshift_tilde_35_h_biquad2_dspsetup();
    this->freqshift_tilde_35_h_biquad3_dspsetup();
    this->freqshift_tilde_35_h_biquad4_dspsetup();
    this->freqshift_tilde_35_h_biquad5_dspsetup();
    this->freqshift_tilde_35_h_biquad6_dspsetup();
    this->freqshift_tilde_35_h_dspsetup();
    this->freqshift_tilde_35_p_dspsetup();
}

number freqshift_tilde_36_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad1_x1 * a1 + this->freqshift_tilde_36_h_biquad1_x2 * 1 - (this->freqshift_tilde_36_h_biquad1_y1 * b1 + this->freqshift_tilde_36_h_biquad1_y2 * b2);
    this->freqshift_tilde_36_h_biquad1_x2 = this->freqshift_tilde_36_h_biquad1_x1;
    this->freqshift_tilde_36_h_biquad1_x1 = x;
    this->freqshift_tilde_36_h_biquad1_y2 = this->freqshift_tilde_36_h_biquad1_y1;
    this->freqshift_tilde_36_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad1_clear() {
    this->freqshift_tilde_36_h_biquad1_reset();
}

void freqshift_tilde_36_h_biquad1_reset() {
    this->freqshift_tilde_36_h_biquad1_x1 = 0;
    this->freqshift_tilde_36_h_biquad1_x2 = 0;
    this->freqshift_tilde_36_h_biquad1_y1 = 0;
    this->freqshift_tilde_36_h_biquad1_y2 = 0;
}

void freqshift_tilde_36_h_biquad1_dspsetup() {
    this->freqshift_tilde_36_h_biquad1_reset();
}

number freqshift_tilde_36_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad2_x1 * a1 + this->freqshift_tilde_36_h_biquad2_x2 * 1 - (this->freqshift_tilde_36_h_biquad2_y1 * b1 + this->freqshift_tilde_36_h_biquad2_y2 * b2);
    this->freqshift_tilde_36_h_biquad2_x2 = this->freqshift_tilde_36_h_biquad2_x1;
    this->freqshift_tilde_36_h_biquad2_x1 = x;
    this->freqshift_tilde_36_h_biquad2_y2 = this->freqshift_tilde_36_h_biquad2_y1;
    this->freqshift_tilde_36_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad2_clear() {
    this->freqshift_tilde_36_h_biquad2_reset();
}

void freqshift_tilde_36_h_biquad2_reset() {
    this->freqshift_tilde_36_h_biquad2_x1 = 0;
    this->freqshift_tilde_36_h_biquad2_x2 = 0;
    this->freqshift_tilde_36_h_biquad2_y1 = 0;
    this->freqshift_tilde_36_h_biquad2_y2 = 0;
}

void freqshift_tilde_36_h_biquad2_dspsetup() {
    this->freqshift_tilde_36_h_biquad2_reset();
}

number freqshift_tilde_36_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad3_x1 * a1 + this->freqshift_tilde_36_h_biquad3_x2 * 1 - (this->freqshift_tilde_36_h_biquad3_y1 * b1 + this->freqshift_tilde_36_h_biquad3_y2 * b2);
    this->freqshift_tilde_36_h_biquad3_x2 = this->freqshift_tilde_36_h_biquad3_x1;
    this->freqshift_tilde_36_h_biquad3_x1 = x;
    this->freqshift_tilde_36_h_biquad3_y2 = this->freqshift_tilde_36_h_biquad3_y1;
    this->freqshift_tilde_36_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad3_clear() {
    this->freqshift_tilde_36_h_biquad3_reset();
}

void freqshift_tilde_36_h_biquad3_reset() {
    this->freqshift_tilde_36_h_biquad3_x1 = 0;
    this->freqshift_tilde_36_h_biquad3_x2 = 0;
    this->freqshift_tilde_36_h_biquad3_y1 = 0;
    this->freqshift_tilde_36_h_biquad3_y2 = 0;
}

void freqshift_tilde_36_h_biquad3_dspsetup() {
    this->freqshift_tilde_36_h_biquad3_reset();
}

number freqshift_tilde_36_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad4_x1 * a1 + this->freqshift_tilde_36_h_biquad4_x2 * 1 - (this->freqshift_tilde_36_h_biquad4_y1 * b1 + this->freqshift_tilde_36_h_biquad4_y2 * b2);
    this->freqshift_tilde_36_h_biquad4_x2 = this->freqshift_tilde_36_h_biquad4_x1;
    this->freqshift_tilde_36_h_biquad4_x1 = x;
    this->freqshift_tilde_36_h_biquad4_y2 = this->freqshift_tilde_36_h_biquad4_y1;
    this->freqshift_tilde_36_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad4_clear() {
    this->freqshift_tilde_36_h_biquad4_reset();
}

void freqshift_tilde_36_h_biquad4_reset() {
    this->freqshift_tilde_36_h_biquad4_x1 = 0;
    this->freqshift_tilde_36_h_biquad4_x2 = 0;
    this->freqshift_tilde_36_h_biquad4_y1 = 0;
    this->freqshift_tilde_36_h_biquad4_y2 = 0;
}

void freqshift_tilde_36_h_biquad4_dspsetup() {
    this->freqshift_tilde_36_h_biquad4_reset();
}

number freqshift_tilde_36_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad5_x1 * a1 + this->freqshift_tilde_36_h_biquad5_x2 * 1 - (this->freqshift_tilde_36_h_biquad5_y1 * b1 + this->freqshift_tilde_36_h_biquad5_y2 * b2);
    this->freqshift_tilde_36_h_biquad5_x2 = this->freqshift_tilde_36_h_biquad5_x1;
    this->freqshift_tilde_36_h_biquad5_x1 = x;
    this->freqshift_tilde_36_h_biquad5_y2 = this->freqshift_tilde_36_h_biquad5_y1;
    this->freqshift_tilde_36_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad5_clear() {
    this->freqshift_tilde_36_h_biquad5_reset();
}

void freqshift_tilde_36_h_biquad5_reset() {
    this->freqshift_tilde_36_h_biquad5_x1 = 0;
    this->freqshift_tilde_36_h_biquad5_x2 = 0;
    this->freqshift_tilde_36_h_biquad5_y1 = 0;
    this->freqshift_tilde_36_h_biquad5_y2 = 0;
}

void freqshift_tilde_36_h_biquad5_dspsetup() {
    this->freqshift_tilde_36_h_biquad5_reset();
}

number freqshift_tilde_36_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_36_h_biquad6_x1 * a1 + this->freqshift_tilde_36_h_biquad6_x2 * 1 - (this->freqshift_tilde_36_h_biquad6_y1 * b1 + this->freqshift_tilde_36_h_biquad6_y2 * b2);
    this->freqshift_tilde_36_h_biquad6_x2 = this->freqshift_tilde_36_h_biquad6_x1;
    this->freqshift_tilde_36_h_biquad6_x1 = x;
    this->freqshift_tilde_36_h_biquad6_y2 = this->freqshift_tilde_36_h_biquad6_y1;
    this->freqshift_tilde_36_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_36_h_biquad6_clear() {
    this->freqshift_tilde_36_h_biquad6_reset();
}

void freqshift_tilde_36_h_biquad6_reset() {
    this->freqshift_tilde_36_h_biquad6_x1 = 0;
    this->freqshift_tilde_36_h_biquad6_x2 = 0;
    this->freqshift_tilde_36_h_biquad6_y1 = 0;
    this->freqshift_tilde_36_h_biquad6_y2 = 0;
}

void freqshift_tilde_36_h_biquad6_dspsetup() {
    this->freqshift_tilde_36_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_36_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_36_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_36_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_36_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_36_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_36_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_36_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_36_h_clear() {
    this->freqshift_tilde_36_h_reset();
}

void freqshift_tilde_36_h_reset() {
    this->freqshift_tilde_36_h_biquad1_reset();
    this->freqshift_tilde_36_h_biquad2_reset();
    this->freqshift_tilde_36_h_biquad3_reset();
    this->freqshift_tilde_36_h_biquad4_reset();
    this->freqshift_tilde_36_h_biquad5_reset();
    this->freqshift_tilde_36_h_biquad6_reset();
}

void freqshift_tilde_36_h_dspsetup() {
    this->freqshift_tilde_36_h_reset();
}

number freqshift_tilde_36_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_36_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_36_p_conv;

    if (this->freqshift_tilde_36_p_currentPhase < 0.)
        this->freqshift_tilde_36_p_currentPhase = 1. + this->freqshift_tilde_36_p_currentPhase;

    if (this->freqshift_tilde_36_p_currentPhase > 1.)
        this->freqshift_tilde_36_p_currentPhase = this->freqshift_tilde_36_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_36_p_currentPhase;
    this->freqshift_tilde_36_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_36_p_reset() {
    this->freqshift_tilde_36_p_currentPhase = 0;
}

void freqshift_tilde_36_p_dspsetup() {
    this->freqshift_tilde_36_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_36_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_36_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_36_setupDone = true;
    this->freqshift_tilde_36_h_biquad1_dspsetup();
    this->freqshift_tilde_36_h_biquad2_dspsetup();
    this->freqshift_tilde_36_h_biquad3_dspsetup();
    this->freqshift_tilde_36_h_biquad4_dspsetup();
    this->freqshift_tilde_36_h_biquad5_dspsetup();
    this->freqshift_tilde_36_h_biquad6_dspsetup();
    this->freqshift_tilde_36_h_dspsetup();
    this->freqshift_tilde_36_p_dspsetup();
}

number gaintilde_38_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_38_ramp_d_prev);
    this->gaintilde_38_ramp_d_prev = x;
    return temp;
}

void gaintilde_38_ramp_d_dspsetup() {
    this->gaintilde_38_ramp_d_reset();
}

void gaintilde_38_ramp_d_reset() {
    this->gaintilde_38_ramp_d_prev = 0;
}

number gaintilde_38_ramp_next(number x, number up, number down) {
    if (this->gaintilde_38_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_38_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_38_ramp_index = _up;
            this->gaintilde_38_ramp_increment = (x - this->gaintilde_38_ramp_prev) / _up;
        } else if (x < this->gaintilde_38_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_38_ramp_index = _down;
            this->gaintilde_38_ramp_increment = (x - this->gaintilde_38_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_38_ramp_index > 0) {
        this->gaintilde_38_ramp_prev += this->gaintilde_38_ramp_increment;
        this->gaintilde_38_ramp_index -= 1;
    } else {
        this->gaintilde_38_ramp_prev = x;
    }

    return this->gaintilde_38_ramp_prev;
}

void gaintilde_38_ramp_reset() {
    this->gaintilde_38_ramp_prev = 0;
    this->gaintilde_38_ramp_index = 0;
    this->gaintilde_38_ramp_increment = 0;
    this->gaintilde_38_ramp_d_reset();
}

void gaintilde_38_init() {
    this->gaintilde_38_loginc = rnbo_log(1.072);
    this->gaintilde_38_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_38_loginc));
}

void gaintilde_38_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_38_value;
}

void gaintilde_38_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_38_value_set(preset["value"]);
}

void gaintilde_38_dspsetup(bool force) {
    if ((bool)(this->gaintilde_38_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_38_setupDone = true;
    this->gaintilde_38_ramp_d_dspsetup();
}

number gaintilde_39_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_39_ramp_d_prev);
    this->gaintilde_39_ramp_d_prev = x;
    return temp;
}

void gaintilde_39_ramp_d_dspsetup() {
    this->gaintilde_39_ramp_d_reset();
}

void gaintilde_39_ramp_d_reset() {
    this->gaintilde_39_ramp_d_prev = 0;
}

number gaintilde_39_ramp_next(number x, number up, number down) {
    if (this->gaintilde_39_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_39_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_39_ramp_index = _up;
            this->gaintilde_39_ramp_increment = (x - this->gaintilde_39_ramp_prev) / _up;
        } else if (x < this->gaintilde_39_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_39_ramp_index = _down;
            this->gaintilde_39_ramp_increment = (x - this->gaintilde_39_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_39_ramp_index > 0) {
        this->gaintilde_39_ramp_prev += this->gaintilde_39_ramp_increment;
        this->gaintilde_39_ramp_index -= 1;
    } else {
        this->gaintilde_39_ramp_prev = x;
    }

    return this->gaintilde_39_ramp_prev;
}

void gaintilde_39_ramp_reset() {
    this->gaintilde_39_ramp_prev = 0;
    this->gaintilde_39_ramp_index = 0;
    this->gaintilde_39_ramp_increment = 0;
    this->gaintilde_39_ramp_d_reset();
}

void gaintilde_39_init() {
    this->gaintilde_39_loginc = rnbo_log(1.072);
    this->gaintilde_39_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_39_loginc));
}

void gaintilde_39_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_39_value;
}

void gaintilde_39_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_39_value_set(preset["value"]);
}

void gaintilde_39_dspsetup(bool force) {
    if ((bool)(this->gaintilde_39_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_39_setupDone = true;
    this->gaintilde_39_ramp_d_dspsetup();
}

number freqshift_tilde_37_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad1_x1 * a1 + this->freqshift_tilde_37_h_biquad1_x2 * 1 - (this->freqshift_tilde_37_h_biquad1_y1 * b1 + this->freqshift_tilde_37_h_biquad1_y2 * b2);
    this->freqshift_tilde_37_h_biquad1_x2 = this->freqshift_tilde_37_h_biquad1_x1;
    this->freqshift_tilde_37_h_biquad1_x1 = x;
    this->freqshift_tilde_37_h_biquad1_y2 = this->freqshift_tilde_37_h_biquad1_y1;
    this->freqshift_tilde_37_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad1_clear() {
    this->freqshift_tilde_37_h_biquad1_reset();
}

void freqshift_tilde_37_h_biquad1_reset() {
    this->freqshift_tilde_37_h_biquad1_x1 = 0;
    this->freqshift_tilde_37_h_biquad1_x2 = 0;
    this->freqshift_tilde_37_h_biquad1_y1 = 0;
    this->freqshift_tilde_37_h_biquad1_y2 = 0;
}

void freqshift_tilde_37_h_biquad1_dspsetup() {
    this->freqshift_tilde_37_h_biquad1_reset();
}

number freqshift_tilde_37_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad2_x1 * a1 + this->freqshift_tilde_37_h_biquad2_x2 * 1 - (this->freqshift_tilde_37_h_biquad2_y1 * b1 + this->freqshift_tilde_37_h_biquad2_y2 * b2);
    this->freqshift_tilde_37_h_biquad2_x2 = this->freqshift_tilde_37_h_biquad2_x1;
    this->freqshift_tilde_37_h_biquad2_x1 = x;
    this->freqshift_tilde_37_h_biquad2_y2 = this->freqshift_tilde_37_h_biquad2_y1;
    this->freqshift_tilde_37_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad2_clear() {
    this->freqshift_tilde_37_h_biquad2_reset();
}

void freqshift_tilde_37_h_biquad2_reset() {
    this->freqshift_tilde_37_h_biquad2_x1 = 0;
    this->freqshift_tilde_37_h_biquad2_x2 = 0;
    this->freqshift_tilde_37_h_biquad2_y1 = 0;
    this->freqshift_tilde_37_h_biquad2_y2 = 0;
}

void freqshift_tilde_37_h_biquad2_dspsetup() {
    this->freqshift_tilde_37_h_biquad2_reset();
}

number freqshift_tilde_37_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad3_x1 * a1 + this->freqshift_tilde_37_h_biquad3_x2 * 1 - (this->freqshift_tilde_37_h_biquad3_y1 * b1 + this->freqshift_tilde_37_h_biquad3_y2 * b2);
    this->freqshift_tilde_37_h_biquad3_x2 = this->freqshift_tilde_37_h_biquad3_x1;
    this->freqshift_tilde_37_h_biquad3_x1 = x;
    this->freqshift_tilde_37_h_biquad3_y2 = this->freqshift_tilde_37_h_biquad3_y1;
    this->freqshift_tilde_37_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad3_clear() {
    this->freqshift_tilde_37_h_biquad3_reset();
}

void freqshift_tilde_37_h_biquad3_reset() {
    this->freqshift_tilde_37_h_biquad3_x1 = 0;
    this->freqshift_tilde_37_h_biquad3_x2 = 0;
    this->freqshift_tilde_37_h_biquad3_y1 = 0;
    this->freqshift_tilde_37_h_biquad3_y2 = 0;
}

void freqshift_tilde_37_h_biquad3_dspsetup() {
    this->freqshift_tilde_37_h_biquad3_reset();
}

number freqshift_tilde_37_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad4_x1 * a1 + this->freqshift_tilde_37_h_biquad4_x2 * 1 - (this->freqshift_tilde_37_h_biquad4_y1 * b1 + this->freqshift_tilde_37_h_biquad4_y2 * b2);
    this->freqshift_tilde_37_h_biquad4_x2 = this->freqshift_tilde_37_h_biquad4_x1;
    this->freqshift_tilde_37_h_biquad4_x1 = x;
    this->freqshift_tilde_37_h_biquad4_y2 = this->freqshift_tilde_37_h_biquad4_y1;
    this->freqshift_tilde_37_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad4_clear() {
    this->freqshift_tilde_37_h_biquad4_reset();
}

void freqshift_tilde_37_h_biquad4_reset() {
    this->freqshift_tilde_37_h_biquad4_x1 = 0;
    this->freqshift_tilde_37_h_biquad4_x2 = 0;
    this->freqshift_tilde_37_h_biquad4_y1 = 0;
    this->freqshift_tilde_37_h_biquad4_y2 = 0;
}

void freqshift_tilde_37_h_biquad4_dspsetup() {
    this->freqshift_tilde_37_h_biquad4_reset();
}

number freqshift_tilde_37_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad5_x1 * a1 + this->freqshift_tilde_37_h_biquad5_x2 * 1 - (this->freqshift_tilde_37_h_biquad5_y1 * b1 + this->freqshift_tilde_37_h_biquad5_y2 * b2);
    this->freqshift_tilde_37_h_biquad5_x2 = this->freqshift_tilde_37_h_biquad5_x1;
    this->freqshift_tilde_37_h_biquad5_x1 = x;
    this->freqshift_tilde_37_h_biquad5_y2 = this->freqshift_tilde_37_h_biquad5_y1;
    this->freqshift_tilde_37_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad5_clear() {
    this->freqshift_tilde_37_h_biquad5_reset();
}

void freqshift_tilde_37_h_biquad5_reset() {
    this->freqshift_tilde_37_h_biquad5_x1 = 0;
    this->freqshift_tilde_37_h_biquad5_x2 = 0;
    this->freqshift_tilde_37_h_biquad5_y1 = 0;
    this->freqshift_tilde_37_h_biquad5_y2 = 0;
}

void freqshift_tilde_37_h_biquad5_dspsetup() {
    this->freqshift_tilde_37_h_biquad5_reset();
}

number freqshift_tilde_37_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_37_h_biquad6_x1 * a1 + this->freqshift_tilde_37_h_biquad6_x2 * 1 - (this->freqshift_tilde_37_h_biquad6_y1 * b1 + this->freqshift_tilde_37_h_biquad6_y2 * b2);
    this->freqshift_tilde_37_h_biquad6_x2 = this->freqshift_tilde_37_h_biquad6_x1;
    this->freqshift_tilde_37_h_biquad6_x1 = x;
    this->freqshift_tilde_37_h_biquad6_y2 = this->freqshift_tilde_37_h_biquad6_y1;
    this->freqshift_tilde_37_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_37_h_biquad6_clear() {
    this->freqshift_tilde_37_h_biquad6_reset();
}

void freqshift_tilde_37_h_biquad6_reset() {
    this->freqshift_tilde_37_h_biquad6_x1 = 0;
    this->freqshift_tilde_37_h_biquad6_x2 = 0;
    this->freqshift_tilde_37_h_biquad6_y1 = 0;
    this->freqshift_tilde_37_h_biquad6_y2 = 0;
}

void freqshift_tilde_37_h_biquad6_dspsetup() {
    this->freqshift_tilde_37_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_37_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_37_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_37_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_37_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_37_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_37_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_37_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_37_h_clear() {
    this->freqshift_tilde_37_h_reset();
}

void freqshift_tilde_37_h_reset() {
    this->freqshift_tilde_37_h_biquad1_reset();
    this->freqshift_tilde_37_h_biquad2_reset();
    this->freqshift_tilde_37_h_biquad3_reset();
    this->freqshift_tilde_37_h_biquad4_reset();
    this->freqshift_tilde_37_h_biquad5_reset();
    this->freqshift_tilde_37_h_biquad6_reset();
}

void freqshift_tilde_37_h_dspsetup() {
    this->freqshift_tilde_37_h_reset();
}

number freqshift_tilde_37_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_37_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_37_p_conv;

    if (this->freqshift_tilde_37_p_currentPhase < 0.)
        this->freqshift_tilde_37_p_currentPhase = 1. + this->freqshift_tilde_37_p_currentPhase;

    if (this->freqshift_tilde_37_p_currentPhase > 1.)
        this->freqshift_tilde_37_p_currentPhase = this->freqshift_tilde_37_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_37_p_currentPhase;
    this->freqshift_tilde_37_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_37_p_reset() {
    this->freqshift_tilde_37_p_currentPhase = 0;
}

void freqshift_tilde_37_p_dspsetup() {
    this->freqshift_tilde_37_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_37_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_37_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_37_setupDone = true;
    this->freqshift_tilde_37_h_biquad1_dspsetup();
    this->freqshift_tilde_37_h_biquad2_dspsetup();
    this->freqshift_tilde_37_h_biquad3_dspsetup();
    this->freqshift_tilde_37_h_biquad4_dspsetup();
    this->freqshift_tilde_37_h_biquad5_dspsetup();
    this->freqshift_tilde_37_h_biquad6_dspsetup();
    this->freqshift_tilde_37_h_dspsetup();
    this->freqshift_tilde_37_p_dspsetup();
}

number freqshift_tilde_38_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad1_x1 * a1 + this->freqshift_tilde_38_h_biquad1_x2 * 1 - (this->freqshift_tilde_38_h_biquad1_y1 * b1 + this->freqshift_tilde_38_h_biquad1_y2 * b2);
    this->freqshift_tilde_38_h_biquad1_x2 = this->freqshift_tilde_38_h_biquad1_x1;
    this->freqshift_tilde_38_h_biquad1_x1 = x;
    this->freqshift_tilde_38_h_biquad1_y2 = this->freqshift_tilde_38_h_biquad1_y1;
    this->freqshift_tilde_38_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad1_clear() {
    this->freqshift_tilde_38_h_biquad1_reset();
}

void freqshift_tilde_38_h_biquad1_reset() {
    this->freqshift_tilde_38_h_biquad1_x1 = 0;
    this->freqshift_tilde_38_h_biquad1_x2 = 0;
    this->freqshift_tilde_38_h_biquad1_y1 = 0;
    this->freqshift_tilde_38_h_biquad1_y2 = 0;
}

void freqshift_tilde_38_h_biquad1_dspsetup() {
    this->freqshift_tilde_38_h_biquad1_reset();
}

number freqshift_tilde_38_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad2_x1 * a1 + this->freqshift_tilde_38_h_biquad2_x2 * 1 - (this->freqshift_tilde_38_h_biquad2_y1 * b1 + this->freqshift_tilde_38_h_biquad2_y2 * b2);
    this->freqshift_tilde_38_h_biquad2_x2 = this->freqshift_tilde_38_h_biquad2_x1;
    this->freqshift_tilde_38_h_biquad2_x1 = x;
    this->freqshift_tilde_38_h_biquad2_y2 = this->freqshift_tilde_38_h_biquad2_y1;
    this->freqshift_tilde_38_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad2_clear() {
    this->freqshift_tilde_38_h_biquad2_reset();
}

void freqshift_tilde_38_h_biquad2_reset() {
    this->freqshift_tilde_38_h_biquad2_x1 = 0;
    this->freqshift_tilde_38_h_biquad2_x2 = 0;
    this->freqshift_tilde_38_h_biquad2_y1 = 0;
    this->freqshift_tilde_38_h_biquad2_y2 = 0;
}

void freqshift_tilde_38_h_biquad2_dspsetup() {
    this->freqshift_tilde_38_h_biquad2_reset();
}

number freqshift_tilde_38_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad3_x1 * a1 + this->freqshift_tilde_38_h_biquad3_x2 * 1 - (this->freqshift_tilde_38_h_biquad3_y1 * b1 + this->freqshift_tilde_38_h_biquad3_y2 * b2);
    this->freqshift_tilde_38_h_biquad3_x2 = this->freqshift_tilde_38_h_biquad3_x1;
    this->freqshift_tilde_38_h_biquad3_x1 = x;
    this->freqshift_tilde_38_h_biquad3_y2 = this->freqshift_tilde_38_h_biquad3_y1;
    this->freqshift_tilde_38_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad3_clear() {
    this->freqshift_tilde_38_h_biquad3_reset();
}

void freqshift_tilde_38_h_biquad3_reset() {
    this->freqshift_tilde_38_h_biquad3_x1 = 0;
    this->freqshift_tilde_38_h_biquad3_x2 = 0;
    this->freqshift_tilde_38_h_biquad3_y1 = 0;
    this->freqshift_tilde_38_h_biquad3_y2 = 0;
}

void freqshift_tilde_38_h_biquad3_dspsetup() {
    this->freqshift_tilde_38_h_biquad3_reset();
}

number freqshift_tilde_38_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad4_x1 * a1 + this->freqshift_tilde_38_h_biquad4_x2 * 1 - (this->freqshift_tilde_38_h_biquad4_y1 * b1 + this->freqshift_tilde_38_h_biquad4_y2 * b2);
    this->freqshift_tilde_38_h_biquad4_x2 = this->freqshift_tilde_38_h_biquad4_x1;
    this->freqshift_tilde_38_h_biquad4_x1 = x;
    this->freqshift_tilde_38_h_biquad4_y2 = this->freqshift_tilde_38_h_biquad4_y1;
    this->freqshift_tilde_38_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad4_clear() {
    this->freqshift_tilde_38_h_biquad4_reset();
}

void freqshift_tilde_38_h_biquad4_reset() {
    this->freqshift_tilde_38_h_biquad4_x1 = 0;
    this->freqshift_tilde_38_h_biquad4_x2 = 0;
    this->freqshift_tilde_38_h_biquad4_y1 = 0;
    this->freqshift_tilde_38_h_biquad4_y2 = 0;
}

void freqshift_tilde_38_h_biquad4_dspsetup() {
    this->freqshift_tilde_38_h_biquad4_reset();
}

number freqshift_tilde_38_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad5_x1 * a1 + this->freqshift_tilde_38_h_biquad5_x2 * 1 - (this->freqshift_tilde_38_h_biquad5_y1 * b1 + this->freqshift_tilde_38_h_biquad5_y2 * b2);
    this->freqshift_tilde_38_h_biquad5_x2 = this->freqshift_tilde_38_h_biquad5_x1;
    this->freqshift_tilde_38_h_biquad5_x1 = x;
    this->freqshift_tilde_38_h_biquad5_y2 = this->freqshift_tilde_38_h_biquad5_y1;
    this->freqshift_tilde_38_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad5_clear() {
    this->freqshift_tilde_38_h_biquad5_reset();
}

void freqshift_tilde_38_h_biquad5_reset() {
    this->freqshift_tilde_38_h_biquad5_x1 = 0;
    this->freqshift_tilde_38_h_biquad5_x2 = 0;
    this->freqshift_tilde_38_h_biquad5_y1 = 0;
    this->freqshift_tilde_38_h_biquad5_y2 = 0;
}

void freqshift_tilde_38_h_biquad5_dspsetup() {
    this->freqshift_tilde_38_h_biquad5_reset();
}

number freqshift_tilde_38_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_38_h_biquad6_x1 * a1 + this->freqshift_tilde_38_h_biquad6_x2 * 1 - (this->freqshift_tilde_38_h_biquad6_y1 * b1 + this->freqshift_tilde_38_h_biquad6_y2 * b2);
    this->freqshift_tilde_38_h_biquad6_x2 = this->freqshift_tilde_38_h_biquad6_x1;
    this->freqshift_tilde_38_h_biquad6_x1 = x;
    this->freqshift_tilde_38_h_biquad6_y2 = this->freqshift_tilde_38_h_biquad6_y1;
    this->freqshift_tilde_38_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_38_h_biquad6_clear() {
    this->freqshift_tilde_38_h_biquad6_reset();
}

void freqshift_tilde_38_h_biquad6_reset() {
    this->freqshift_tilde_38_h_biquad6_x1 = 0;
    this->freqshift_tilde_38_h_biquad6_x2 = 0;
    this->freqshift_tilde_38_h_biquad6_y1 = 0;
    this->freqshift_tilde_38_h_biquad6_y2 = 0;
}

void freqshift_tilde_38_h_biquad6_dspsetup() {
    this->freqshift_tilde_38_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_38_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_38_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_38_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_38_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_38_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_38_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_38_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_38_h_clear() {
    this->freqshift_tilde_38_h_reset();
}

void freqshift_tilde_38_h_reset() {
    this->freqshift_tilde_38_h_biquad1_reset();
    this->freqshift_tilde_38_h_biquad2_reset();
    this->freqshift_tilde_38_h_biquad3_reset();
    this->freqshift_tilde_38_h_biquad4_reset();
    this->freqshift_tilde_38_h_biquad5_reset();
    this->freqshift_tilde_38_h_biquad6_reset();
}

void freqshift_tilde_38_h_dspsetup() {
    this->freqshift_tilde_38_h_reset();
}

number freqshift_tilde_38_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_38_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_38_p_conv;

    if (this->freqshift_tilde_38_p_currentPhase < 0.)
        this->freqshift_tilde_38_p_currentPhase = 1. + this->freqshift_tilde_38_p_currentPhase;

    if (this->freqshift_tilde_38_p_currentPhase > 1.)
        this->freqshift_tilde_38_p_currentPhase = this->freqshift_tilde_38_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_38_p_currentPhase;
    this->freqshift_tilde_38_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_38_p_reset() {
    this->freqshift_tilde_38_p_currentPhase = 0;
}

void freqshift_tilde_38_p_dspsetup() {
    this->freqshift_tilde_38_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_38_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_38_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_38_setupDone = true;
    this->freqshift_tilde_38_h_biquad1_dspsetup();
    this->freqshift_tilde_38_h_biquad2_dspsetup();
    this->freqshift_tilde_38_h_biquad3_dspsetup();
    this->freqshift_tilde_38_h_biquad4_dspsetup();
    this->freqshift_tilde_38_h_biquad5_dspsetup();
    this->freqshift_tilde_38_h_biquad6_dspsetup();
    this->freqshift_tilde_38_h_dspsetup();
    this->freqshift_tilde_38_p_dspsetup();
}

number gaintilde_40_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_40_ramp_d_prev);
    this->gaintilde_40_ramp_d_prev = x;
    return temp;
}

void gaintilde_40_ramp_d_dspsetup() {
    this->gaintilde_40_ramp_d_reset();
}

void gaintilde_40_ramp_d_reset() {
    this->gaintilde_40_ramp_d_prev = 0;
}

number gaintilde_40_ramp_next(number x, number up, number down) {
    if (this->gaintilde_40_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_40_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_40_ramp_index = _up;
            this->gaintilde_40_ramp_increment = (x - this->gaintilde_40_ramp_prev) / _up;
        } else if (x < this->gaintilde_40_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_40_ramp_index = _down;
            this->gaintilde_40_ramp_increment = (x - this->gaintilde_40_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_40_ramp_index > 0) {
        this->gaintilde_40_ramp_prev += this->gaintilde_40_ramp_increment;
        this->gaintilde_40_ramp_index -= 1;
    } else {
        this->gaintilde_40_ramp_prev = x;
    }

    return this->gaintilde_40_ramp_prev;
}

void gaintilde_40_ramp_reset() {
    this->gaintilde_40_ramp_prev = 0;
    this->gaintilde_40_ramp_index = 0;
    this->gaintilde_40_ramp_increment = 0;
    this->gaintilde_40_ramp_d_reset();
}

void gaintilde_40_init() {
    this->gaintilde_40_loginc = rnbo_log(1.072);
    this->gaintilde_40_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_40_loginc));
}

void gaintilde_40_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_40_value;
}

void gaintilde_40_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_40_value_set(preset["value"]);
}

void gaintilde_40_dspsetup(bool force) {
    if ((bool)(this->gaintilde_40_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_40_setupDone = true;
    this->gaintilde_40_ramp_d_dspsetup();
}

void param_26_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_26_value;
}

void param_26_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_26_value_set(preset["value"]);
}

void param_27_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_27_value;
}

void param_27_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_27_value_set(preset["value"]);
}

void param_28_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_28_value;
}

void param_28_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_28_value_set(preset["value"]);
}

void param_29_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_29_value;
}

void param_29_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_29_value_set(preset["value"]);
}

number freqshift_tilde_39_h_biquad1_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad1_x1 * a1 + this->freqshift_tilde_39_h_biquad1_x2 * 1 - (this->freqshift_tilde_39_h_biquad1_y1 * b1 + this->freqshift_tilde_39_h_biquad1_y2 * b2);
    this->freqshift_tilde_39_h_biquad1_x2 = this->freqshift_tilde_39_h_biquad1_x1;
    this->freqshift_tilde_39_h_biquad1_x1 = x;
    this->freqshift_tilde_39_h_biquad1_y2 = this->freqshift_tilde_39_h_biquad1_y1;
    this->freqshift_tilde_39_h_biquad1_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad1_clear() {
    this->freqshift_tilde_39_h_biquad1_reset();
}

void freqshift_tilde_39_h_biquad1_reset() {
    this->freqshift_tilde_39_h_biquad1_x1 = 0;
    this->freqshift_tilde_39_h_biquad1_x2 = 0;
    this->freqshift_tilde_39_h_biquad1_y1 = 0;
    this->freqshift_tilde_39_h_biquad1_y2 = 0;
}

void freqshift_tilde_39_h_biquad1_dspsetup() {
    this->freqshift_tilde_39_h_biquad1_reset();
}

number freqshift_tilde_39_h_biquad2_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad2_x1 * a1 + this->freqshift_tilde_39_h_biquad2_x2 * 1 - (this->freqshift_tilde_39_h_biquad2_y1 * b1 + this->freqshift_tilde_39_h_biquad2_y2 * b2);
    this->freqshift_tilde_39_h_biquad2_x2 = this->freqshift_tilde_39_h_biquad2_x1;
    this->freqshift_tilde_39_h_biquad2_x1 = x;
    this->freqshift_tilde_39_h_biquad2_y2 = this->freqshift_tilde_39_h_biquad2_y1;
    this->freqshift_tilde_39_h_biquad2_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad2_clear() {
    this->freqshift_tilde_39_h_biquad2_reset();
}

void freqshift_tilde_39_h_biquad2_reset() {
    this->freqshift_tilde_39_h_biquad2_x1 = 0;
    this->freqshift_tilde_39_h_biquad2_x2 = 0;
    this->freqshift_tilde_39_h_biquad2_y1 = 0;
    this->freqshift_tilde_39_h_biquad2_y2 = 0;
}

void freqshift_tilde_39_h_biquad2_dspsetup() {
    this->freqshift_tilde_39_h_biquad2_reset();
}

number freqshift_tilde_39_h_biquad3_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad3_x1 * a1 + this->freqshift_tilde_39_h_biquad3_x2 * 1 - (this->freqshift_tilde_39_h_biquad3_y1 * b1 + this->freqshift_tilde_39_h_biquad3_y2 * b2);
    this->freqshift_tilde_39_h_biquad3_x2 = this->freqshift_tilde_39_h_biquad3_x1;
    this->freqshift_tilde_39_h_biquad3_x1 = x;
    this->freqshift_tilde_39_h_biquad3_y2 = this->freqshift_tilde_39_h_biquad3_y1;
    this->freqshift_tilde_39_h_biquad3_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad3_clear() {
    this->freqshift_tilde_39_h_biquad3_reset();
}

void freqshift_tilde_39_h_biquad3_reset() {
    this->freqshift_tilde_39_h_biquad3_x1 = 0;
    this->freqshift_tilde_39_h_biquad3_x2 = 0;
    this->freqshift_tilde_39_h_biquad3_y1 = 0;
    this->freqshift_tilde_39_h_biquad3_y2 = 0;
}

void freqshift_tilde_39_h_biquad3_dspsetup() {
    this->freqshift_tilde_39_h_biquad3_reset();
}

number freqshift_tilde_39_h_biquad4_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad4_x1 * a1 + this->freqshift_tilde_39_h_biquad4_x2 * 1 - (this->freqshift_tilde_39_h_biquad4_y1 * b1 + this->freqshift_tilde_39_h_biquad4_y2 * b2);
    this->freqshift_tilde_39_h_biquad4_x2 = this->freqshift_tilde_39_h_biquad4_x1;
    this->freqshift_tilde_39_h_biquad4_x1 = x;
    this->freqshift_tilde_39_h_biquad4_y2 = this->freqshift_tilde_39_h_biquad4_y1;
    this->freqshift_tilde_39_h_biquad4_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad4_clear() {
    this->freqshift_tilde_39_h_biquad4_reset();
}

void freqshift_tilde_39_h_biquad4_reset() {
    this->freqshift_tilde_39_h_biquad4_x1 = 0;
    this->freqshift_tilde_39_h_biquad4_x2 = 0;
    this->freqshift_tilde_39_h_biquad4_y1 = 0;
    this->freqshift_tilde_39_h_biquad4_y2 = 0;
}

void freqshift_tilde_39_h_biquad4_dspsetup() {
    this->freqshift_tilde_39_h_biquad4_reset();
}

number freqshift_tilde_39_h_biquad5_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad5_x1 * a1 + this->freqshift_tilde_39_h_biquad5_x2 * 1 - (this->freqshift_tilde_39_h_biquad5_y1 * b1 + this->freqshift_tilde_39_h_biquad5_y2 * b2);
    this->freqshift_tilde_39_h_biquad5_x2 = this->freqshift_tilde_39_h_biquad5_x1;
    this->freqshift_tilde_39_h_biquad5_x1 = x;
    this->freqshift_tilde_39_h_biquad5_y2 = this->freqshift_tilde_39_h_biquad5_y1;
    this->freqshift_tilde_39_h_biquad5_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad5_clear() {
    this->freqshift_tilde_39_h_biquad5_reset();
}

void freqshift_tilde_39_h_biquad5_reset() {
    this->freqshift_tilde_39_h_biquad5_x1 = 0;
    this->freqshift_tilde_39_h_biquad5_x2 = 0;
    this->freqshift_tilde_39_h_biquad5_y1 = 0;
    this->freqshift_tilde_39_h_biquad5_y2 = 0;
}

void freqshift_tilde_39_h_biquad5_dspsetup() {
    this->freqshift_tilde_39_h_biquad5_reset();
}

number freqshift_tilde_39_h_biquad6_next(number x, number a0, number a1, number a2, number b1, number b2) {
    RNBO_UNUSED(a2);
    number tmp = x * a0 + this->freqshift_tilde_39_h_biquad6_x1 * a1 + this->freqshift_tilde_39_h_biquad6_x2 * 1 - (this->freqshift_tilde_39_h_biquad6_y1 * b1 + this->freqshift_tilde_39_h_biquad6_y2 * b2);
    this->freqshift_tilde_39_h_biquad6_x2 = this->freqshift_tilde_39_h_biquad6_x1;
    this->freqshift_tilde_39_h_biquad6_x1 = x;
    this->freqshift_tilde_39_h_biquad6_y2 = this->freqshift_tilde_39_h_biquad6_y1;
    this->freqshift_tilde_39_h_biquad6_y1 = tmp;
    return tmp;
}

void freqshift_tilde_39_h_biquad6_clear() {
    this->freqshift_tilde_39_h_biquad6_reset();
}

void freqshift_tilde_39_h_biquad6_reset() {
    this->freqshift_tilde_39_h_biquad6_x1 = 0;
    this->freqshift_tilde_39_h_biquad6_x2 = 0;
    this->freqshift_tilde_39_h_biquad6_y1 = 0;
    this->freqshift_tilde_39_h_biquad6_y2 = 0;
}

void freqshift_tilde_39_h_biquad6_dspsetup() {
    this->freqshift_tilde_39_h_biquad6_reset();
}

array<number, 2> freqshift_tilde_39_h_next(number x) {
    number C0 = 0.993392295379985;
    number C1 = -1.99338779183018;
    number C2 = 0.887299159297928;
    number C3 = -1.88514806717204;
    number C4 = 0.0536993765792374;
    number C5 = -0.75714576848209;
    number S0 = 0.9855313382235;
    number S1 = -1.98549972415061;
    number S2 = 0.786712815028413;
    number S3 = -1.77856079622493;
    number S4 = -0.217311176123061;
    number S5 = 0.055905451294768;
    number tmp1Real = this->freqshift_tilde_39_h_biquad1_next(x, C0, C1, 1.0, C1, C0);
    number tmp1Imag = this->freqshift_tilde_39_h_biquad2_next(x, S0, S1, 1.0, S1, S0);
    number tmp2Real = this->freqshift_tilde_39_h_biquad3_next(tmp1Real, C2, C3, 1.0, C3, C2);
    number tmp2Imag = this->freqshift_tilde_39_h_biquad4_next(tmp1Imag, S2, S3, 1.0, S3, S2);

    return {
        this->freqshift_tilde_39_h_biquad5_next(tmp2Real, C4, C5, 1.0, C5, C4),
        this->freqshift_tilde_39_h_biquad6_next(tmp2Imag, S4, S5, 1.0, S5, S4)
    };
}

void freqshift_tilde_39_h_clear() {
    this->freqshift_tilde_39_h_reset();
}

void freqshift_tilde_39_h_reset() {
    this->freqshift_tilde_39_h_biquad1_reset();
    this->freqshift_tilde_39_h_biquad2_reset();
    this->freqshift_tilde_39_h_biquad3_reset();
    this->freqshift_tilde_39_h_biquad4_reset();
    this->freqshift_tilde_39_h_biquad5_reset();
    this->freqshift_tilde_39_h_biquad6_reset();
}

void freqshift_tilde_39_h_dspsetup() {
    this->freqshift_tilde_39_h_reset();
}

number freqshift_tilde_39_p_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->freqshift_tilde_39_p_currentPhase = reset;
        }
    }

    number pincr = freq * this->freqshift_tilde_39_p_conv;

    if (this->freqshift_tilde_39_p_currentPhase < 0.)
        this->freqshift_tilde_39_p_currentPhase = 1. + this->freqshift_tilde_39_p_currentPhase;

    if (this->freqshift_tilde_39_p_currentPhase > 1.)
        this->freqshift_tilde_39_p_currentPhase = this->freqshift_tilde_39_p_currentPhase - 1.;

    number tmp = this->freqshift_tilde_39_p_currentPhase;
    this->freqshift_tilde_39_p_currentPhase += pincr;
    return tmp;
}

void freqshift_tilde_39_p_reset() {
    this->freqshift_tilde_39_p_currentPhase = 0;
}

void freqshift_tilde_39_p_dspsetup() {
    this->freqshift_tilde_39_p_conv = (number)1 / this->sr;
}

void freqshift_tilde_39_dspsetup(bool force) {
    if ((bool)(this->freqshift_tilde_39_setupDone) && (bool)(!(bool)(force)))
        return;

    this->freqshift_tilde_39_setupDone = true;
    this->freqshift_tilde_39_h_biquad1_dspsetup();
    this->freqshift_tilde_39_h_biquad2_dspsetup();
    this->freqshift_tilde_39_h_biquad3_dspsetup();
    this->freqshift_tilde_39_h_biquad4_dspsetup();
    this->freqshift_tilde_39_h_biquad5_dspsetup();
    this->freqshift_tilde_39_h_biquad6_dspsetup();
    this->freqshift_tilde_39_h_dspsetup();
    this->freqshift_tilde_39_p_dspsetup();
}

void param_30_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_30_value;
}

void param_30_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_30_value_set(preset["value"]);
}

void param_31_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_31_value;
}

void param_31_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_31_value_set(preset["value"]);
}

void param_32_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_32_value;
}

void param_32_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_32_value_set(preset["value"]);
}

void param_33_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_33_value;
}

void param_33_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_33_value_set(preset["value"]);
}

void param_34_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_34_value;
}

void param_34_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_34_value_set(preset["value"]);
}

void param_35_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_35_value;
}

void param_35_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_35_value_set(preset["value"]);
}

void param_36_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_36_value;
}

void param_36_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_36_value_set(preset["value"]);
}

void param_37_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_37_value;
}

void param_37_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_37_value_set(preset["value"]);
}

void param_38_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_38_value;
}

void param_38_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_38_value_set(preset["value"]);
}

void param_39_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_39_value;
}

void param_39_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_39_value_set(preset["value"]);
}

void param_40_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_40_value;
}

void param_40_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_40_value_set(preset["value"]);
}

void param_41_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_41_value;
}

void param_41_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_41_value_set(preset["value"]);
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    send_01_input_number = 0;
    param_01_value = 1;
    send_02_input_number = 0;
    param_02_value = 1;
    send_03_input_number = 0;
    param_03_value = 0;
    send_04_input_number = 0;
    param_04_value = 1;
    send_05_input_number = 0;
    param_05_value = 1;
    send_06_input_number = 0;
    param_06_value = 1;
    send_07_input_number = 0;
    param_07_value = 1;
    send_08_input_number = 0;
    param_08_value = 1;
    send_09_input_number = 0;
    param_09_value = 1;
    receive_01_output_number = 0;
    limi_01_bypass = 0;
    limi_01_dcblock = 0;
    limi_01_lookahead = 100;
    limi_01_lookahead_setter(limi_01_lookahead);
    limi_01_preamp = -5;
    limi_01_preamp_setter(limi_01_preamp);
    limi_01_postamp = -5;
    limi_01_postamp_setter(limi_01_postamp);
    limi_01_threshold = -10;
    limi_01_threshold_setter(limi_01_threshold);
    limi_01_release = 1000;
    receive_02_output_number = 0;
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    gaintilde_02_input_number = 0;
    gaintilde_02_value = 0;
    gaintilde_02_interp = 10;
    receive_03_output_number = 0;
    receive_04_output_number = 0;
    gaintilde_03_input_number = 0;
    gaintilde_03_value = 0;
    gaintilde_03_interp = 10;
    receive_05_output_number = 0;
    gaintilde_04_input_number = 0;
    gaintilde_04_value = 0;
    gaintilde_04_interp = 10;
    freqshift_tilde_01_x = 0;
    freqshift_tilde_01_frequency = 0;
    send_10_input_number = 0;
    param_10_value = 1;
    send_11_input_number = 0;
    param_11_value = 1;
    send_12_input_number = 0;
    param_12_value = 1;
    freqshift_tilde_02_x = 0;
    freqshift_tilde_02_frequency = 0;
    send_13_input_number = 0;
    param_13_value = 1;
    receive_06_output_number = 0;
    expr_01_in1 = 0;
    expr_01_in2 = 11;
    expr_01_out1 = 0;
    freqshift_tilde_03_x = 0;
    freqshift_tilde_03_frequency = 0;
    freqshift_tilde_04_x = 0;
    freqshift_tilde_04_frequency = 0;
    gaintilde_05_input_number = 0;
    gaintilde_05_value = 0;
    gaintilde_05_interp = 10;
    receive_07_output_number = 0;
    expr_02_in1 = 0;
    expr_02_in2 = 31;
    expr_02_out1 = 0;
    receive_08_output_number = 0;
    expr_03_in1 = 0;
    expr_03_in2 = 21;
    expr_03_out1 = 0;
    receive_09_output_number = 0;
    expr_04_in1 = 0;
    expr_04_in2 = 2;
    expr_04_out1 = 0;
    receive_10_output_number = 0;
    receive_11_output_number = 0;
    gaintilde_06_input_number = 0;
    gaintilde_06_value = 0;
    gaintilde_06_interp = 10;
    receive_12_output_number = 0;
    gaintilde_07_input_number = 0;
    gaintilde_07_value = 0;
    gaintilde_07_interp = 10;
    gaintilde_08_input_number = 0;
    gaintilde_08_value = 0;
    gaintilde_08_interp = 10;
    receive_13_output_number = 0;
    freqshift_tilde_05_x = 0;
    freqshift_tilde_05_frequency = 0;
    freqshift_tilde_06_x = 0;
    freqshift_tilde_06_frequency = 0;
    freqshift_tilde_07_x = 0;
    freqshift_tilde_07_frequency = 0;
    receive_14_output_number = 0;
    expr_05_in1 = 0;
    expr_05_in2 = 12;
    expr_05_out1 = 0;
    gaintilde_09_input_number = 0;
    gaintilde_09_value = 0;
    gaintilde_09_interp = 10;
    freqshift_tilde_08_x = 0;
    freqshift_tilde_08_frequency = 0;
    receive_15_output_number = 0;
    expr_06_in1 = 0;
    expr_06_in2 = 32;
    expr_06_out1 = 0;
    receive_16_output_number = 0;
    expr_07_in1 = 0;
    expr_07_in2 = 22;
    expr_07_out1 = 0;
    receive_17_output_number = 0;
    receive_18_output_number = 0;
    expr_08_in1 = 0;
    expr_08_in2 = 3;
    expr_08_out1 = 0;
    receive_19_output_number = 0;
    receive_20_output_number = 0;
    gaintilde_10_input_number = 0;
    gaintilde_10_value = 0;
    gaintilde_10_interp = 10;
    gaintilde_11_input_number = 0;
    gaintilde_11_value = 0;
    gaintilde_11_interp = 10;
    gaintilde_12_input_number = 0;
    gaintilde_12_value = 0;
    gaintilde_12_interp = 10;
    receive_21_output_number = 0;
    freqshift_tilde_09_x = 0;
    freqshift_tilde_09_frequency = 0;
    freqshift_tilde_10_x = 0;
    freqshift_tilde_10_frequency = 0;
    freqshift_tilde_11_x = 0;
    freqshift_tilde_11_frequency = 0;
    receive_22_output_number = 0;
    expr_09_in1 = 0;
    expr_09_in2 = 33;
    expr_09_out1 = 0;
    receive_23_output_number = 0;
    expr_10_in1 = 0;
    expr_10_in2 = 23;
    expr_10_out1 = 0;
    gaintilde_13_input_number = 0;
    gaintilde_13_value = 0;
    gaintilde_13_interp = 10;
    send_14_input_number = 0;
    param_14_value = 1;
    send_15_input_number = 0;
    param_15_value = 1;
    freqshift_tilde_12_x = 0;
    freqshift_tilde_12_frequency = 0;
    receive_24_output_number = 0;
    expr_11_in1 = 0;
    expr_11_in2 = 13;
    expr_11_out1 = 0;
    send_16_input_number = 0;
    param_16_value = 1;
    send_17_input_number = 0;
    param_17_value = 1;
    receive_25_output_number = 0;
    receive_26_output_number = 0;
    expr_12_in1 = 0;
    expr_12_in2 = 4;
    expr_12_out1 = 0;
    receive_27_output_number = 0;
    gaintilde_14_input_number = 0;
    gaintilde_14_value = 0;
    gaintilde_14_interp = 10;
    gaintilde_15_input_number = 0;
    gaintilde_15_value = 0;
    gaintilde_15_interp = 10;
    receive_28_output_number = 0;
    gaintilde_16_input_number = 0;
    gaintilde_16_value = 0;
    gaintilde_16_interp = 10;
    freqshift_tilde_13_x = 0;
    freqshift_tilde_13_frequency = 0;
    freqshift_tilde_14_x = 0;
    freqshift_tilde_14_frequency = 0;
    receive_29_output_number = 0;
    gaintilde_17_input_number = 0;
    gaintilde_17_value = 0;
    gaintilde_17_interp = 10;
    receive_30_output_number = 0;
    expr_13_in1 = 0;
    expr_13_in2 = 34;
    expr_13_out1 = 0;
    freqshift_tilde_15_x = 0;
    freqshift_tilde_15_frequency = 0;
    receive_31_output_number = 0;
    expr_14_in1 = 0;
    expr_14_in2 = 24;
    expr_14_out1 = 0;
    freqshift_tilde_16_x = 0;
    freqshift_tilde_16_frequency = 0;
    receive_32_output_number = 0;
    expr_15_in1 = 0;
    expr_15_in2 = 13;
    expr_15_out1 = 0;
    receive_33_output_number = 0;
    receive_34_output_number = 0;
    gaintilde_18_input_number = 0;
    gaintilde_18_value = 0;
    gaintilde_18_interp = 10;
    receive_35_output_number = 0;
    expr_16_in1 = 0;
    expr_16_in2 = 5;
    expr_16_out1 = 0;
    gaintilde_19_input_number = 0;
    gaintilde_19_value = 0;
    gaintilde_19_interp = 10;
    freqshift_tilde_17_x = 0;
    freqshift_tilde_17_frequency = 0;
    receive_36_output_number = 0;
    freqshift_tilde_18_x = 0;
    freqshift_tilde_18_frequency = 0;
    gaintilde_20_input_number = 0;
    gaintilde_20_value = 0;
    gaintilde_20_interp = 10;
    receive_37_output_number = 0;
    receive_38_output_number = 0;
    expr_17_in1 = 0;
    expr_17_in2 = 35;
    expr_17_out1 = 0;
    gaintilde_21_input_number = 0;
    gaintilde_21_value = 0;
    gaintilde_21_interp = 10;
    receive_39_output_number = 0;
    expr_18_in1 = 0;
    expr_18_in2 = 25;
    expr_18_out1 = 0;
    freqshift_tilde_19_x = 0;
    freqshift_tilde_19_frequency = 0;
    freqshift_tilde_20_x = 0;
    freqshift_tilde_20_frequency = 0;
    receive_40_output_number = 0;
    receive_41_output_number = 0;
    receive_42_output_number = 0;
    expr_19_in1 = 0;
    expr_19_in2 = 15;
    expr_19_out1 = 0;
    gaintilde_22_input_number = 0;
    gaintilde_22_value = 0;
    gaintilde_22_interp = 10;
    gaintilde_23_input_number = 0;
    gaintilde_23_value = 0;
    gaintilde_23_interp = 10;
    receive_43_output_number = 0;
    expr_20_in1 = 0;
    expr_20_in2 = 6;
    expr_20_out1 = 0;
    send_18_input_number = 0;
    param_18_value = 1;
    send_19_input_number = 0;
    param_19_value = 1;
    freqshift_tilde_21_x = 0;
    freqshift_tilde_21_frequency = 0;
    send_20_input_number = 0;
    param_20_value = 1;
    freqshift_tilde_22_x = 0;
    freqshift_tilde_22_frequency = 0;
    receive_44_output_number = 0;
    receive_45_output_number = 0;
    send_21_input_number = 0;
    param_21_value = 1;
    gaintilde_24_input_number = 0;
    gaintilde_24_value = 0;
    gaintilde_24_interp = 10;
    receive_46_output_number = 0;
    expr_21_in1 = 0;
    expr_21_in2 = 36;
    expr_21_out1 = 0;
    receive_47_output_number = 0;
    expr_22_in1 = 0;
    expr_22_in2 = 26;
    expr_22_out1 = 0;
    gaintilde_25_input_number = 0;
    gaintilde_25_value = 0;
    gaintilde_25_interp = 10;
    freqshift_tilde_23_x = 0;
    freqshift_tilde_23_frequency = 0;
    receive_48_output_number = 0;
    freqshift_tilde_24_x = 0;
    freqshift_tilde_24_frequency = 0;
    receive_49_output_number = 0;
    gaintilde_26_input_number = 0;
    gaintilde_26_value = 0;
    gaintilde_26_interp = 10;
    receive_50_output_number = 0;
    expr_23_in1 = 0;
    expr_23_in2 = 16;
    expr_23_out1 = 0;
    gaintilde_27_input_number = 0;
    gaintilde_27_value = 0;
    gaintilde_27_interp = 10;
    receive_51_output_number = 0;
    expr_24_in1 = 0;
    expr_24_in2 = 7;
    expr_24_out1 = 0;
    freqshift_tilde_25_x = 0;
    freqshift_tilde_25_frequency = 0;
    freqshift_tilde_26_x = 0;
    freqshift_tilde_26_frequency = 0;
    receive_52_output_number = 0;
    receive_53_output_number = 0;
    receive_54_output_number = 0;
    expr_25_in1 = 0;
    expr_25_in2 = 37;
    expr_25_out1 = 0;
    gaintilde_28_input_number = 0;
    gaintilde_28_value = 0;
    gaintilde_28_interp = 10;
    gaintilde_29_input_number = 0;
    gaintilde_29_value = 0;
    gaintilde_29_interp = 10;
    receive_55_output_number = 0;
    expr_26_in1 = 0;
    expr_26_in2 = 27;
    expr_26_out1 = 0;
    freqshift_tilde_27_x = 0;
    freqshift_tilde_27_frequency = 0;
    receive_56_output_number = 0;
    freqshift_tilde_28_x = 0;
    freqshift_tilde_28_frequency = 0;
    receive_57_output_number = 0;
    gaintilde_30_input_number = 0;
    gaintilde_30_value = 0;
    gaintilde_30_interp = 10;
    gaintilde_31_input_number = 0;
    gaintilde_31_value = 0;
    gaintilde_31_interp = 10;
    receive_58_output_number = 0;
    expr_27_in1 = 0;
    expr_27_in2 = 17;
    expr_27_out1 = 0;
    receive_59_output_number = 0;
    expr_28_in1 = 0;
    expr_28_in2 = 8;
    expr_28_out1 = 0;
    freqshift_tilde_29_x = 0;
    freqshift_tilde_29_frequency = 0;
    freqshift_tilde_30_x = 0;
    freqshift_tilde_30_frequency = 0;
    receive_60_output_number = 0;
    receive_61_output_number = 0;
    receive_62_output_number = 0;
    expr_29_in1 = 0;
    expr_29_in2 = 38;
    expr_29_out1 = 0;
    send_22_input_number = 0;
    param_22_value = 1;
    receive_63_output_number = 0;
    expr_30_in1 = 0;
    expr_30_in2 = 28;
    expr_30_out1 = 0;
    gaintilde_32_input_number = 0;
    gaintilde_32_value = 0;
    gaintilde_32_interp = 10;
    gaintilde_33_input_number = 0;
    gaintilde_33_value = 0;
    gaintilde_33_interp = 10;
    send_23_input_number = 0;
    param_23_value = 1;
    send_24_input_number = 0;
    param_24_value = 1;
    send_25_input_number = 0;
    param_25_value = 1;
    receive_64_output_number = 0;
    freqshift_tilde_31_x = 0;
    freqshift_tilde_31_frequency = 0;
    freqshift_tilde_32_x = 0;
    freqshift_tilde_32_frequency = 0;
    receive_65_output_number = 0;
    gaintilde_34_input_number = 0;
    gaintilde_34_value = 0;
    gaintilde_34_interp = 10;
    gaintilde_35_input_number = 0;
    gaintilde_35_value = 0;
    gaintilde_35_interp = 10;
    receive_66_output_number = 0;
    expr_31_in1 = 0;
    expr_31_in2 = 9;
    expr_31_out1 = 0;
    receive_67_output_number = 0;
    expr_32_in1 = 0;
    expr_32_in2 = 18;
    expr_32_out1 = 0;
    freqshift_tilde_33_x = 0;
    freqshift_tilde_33_frequency = 0;
    freqshift_tilde_34_x = 0;
    freqshift_tilde_34_frequency = 0;
    receive_68_output_number = 0;
    receive_69_output_number = 0;
    expr_33_in1 = 0;
    expr_33_in2 = 39;
    expr_33_out1 = 0;
    receive_70_output_number = 0;
    receive_71_output_number = 0;
    expr_34_in1 = 0;
    expr_34_in2 = 29;
    expr_34_out1 = 0;
    gaintilde_36_input_number = 0;
    gaintilde_36_value = 0;
    gaintilde_36_interp = 10;
    gaintilde_37_input_number = 0;
    gaintilde_37_value = 0;
    gaintilde_37_interp = 10;
    receive_72_output_number = 0;
    receive_73_output_number = 0;
    freqshift_tilde_35_x = 0;
    freqshift_tilde_35_frequency = 0;
    freqshift_tilde_36_x = 0;
    freqshift_tilde_36_frequency = 0;
    gaintilde_38_input_number = 0;
    gaintilde_38_value = 0;
    gaintilde_38_interp = 10;
    gaintilde_39_input_number = 0;
    gaintilde_39_value = 0;
    gaintilde_39_interp = 10;
    receive_74_output_number = 0;
    expr_35_in1 = 0;
    expr_35_in2 = 10;
    expr_35_out1 = 0;
    receive_75_output_number = 0;
    expr_36_in1 = 0;
    expr_36_in2 = 19;
    expr_36_out1 = 0;
    freqshift_tilde_37_x = 0;
    freqshift_tilde_37_frequency = 0;
    freqshift_tilde_38_x = 0;
    freqshift_tilde_38_frequency = 0;
    receive_76_output_number = 0;
    expr_37_in1 = 0;
    expr_37_in2 = 40;
    expr_37_out1 = 0;
    receive_77_output_number = 0;
    expr_38_in1 = 0;
    expr_38_in2 = 30;
    expr_38_out1 = 0;
    receive_78_output_number = 0;
    gaintilde_40_input_number = 0;
    gaintilde_40_value = 0;
    gaintilde_40_interp = 10;
    send_26_input_number = 0;
    param_26_value = 1;
    send_27_input_number = 0;
    param_27_value = 1;
    send_28_input_number = 0;
    param_28_value = 1;
    send_29_input_number = 0;
    param_29_value = 1;
    freqshift_tilde_39_x = 0;
    freqshift_tilde_39_frequency = 0;
    receive_79_output_number = 0;
    expr_39_in1 = 0;
    expr_39_in2 = 20;
    expr_39_out1 = 0;
    send_30_input_number = 0;
    param_30_value = 1;
    send_31_input_number = 0;
    param_31_value = 1;
    send_32_input_number = 0;
    param_32_value = 1;
    send_33_input_number = 0;
    param_33_value = 1;
    send_34_input_number = 0;
    param_34_value = 1;
    send_35_input_number = 0;
    param_35_value = 1;
    send_36_input_number = 0;
    param_36_value = 1;
    send_37_input_number = 0;
    param_37_value = 1;
    send_38_input_number = 0;
    param_38_value = 1;
    send_39_input_number = 0;
    param_39_value = 1;
    send_40_input_number = 0;
    param_40_value = 1;
    send_41_input_number = 0;
    param_41_value = 1;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    signals[6] = nullptr;
    signals[7] = nullptr;
    signals[8] = nullptr;
    signals[9] = nullptr;
    signals[10] = nullptr;
    signals[11] = nullptr;
    signals[12] = nullptr;
    signals[13] = nullptr;
    signals[14] = nullptr;
    signals[15] = nullptr;
    signals[16] = nullptr;
    signals[17] = nullptr;
    signals[18] = nullptr;
    signals[19] = nullptr;
    signals[20] = nullptr;
    signals[21] = nullptr;
    signals[22] = nullptr;
    signals[23] = nullptr;
    signals[24] = nullptr;
    signals[25] = nullptr;
    signals[26] = nullptr;
    signals[27] = nullptr;
    signals[28] = nullptr;
    signals[29] = nullptr;
    signals[30] = nullptr;
    signals[31] = nullptr;
    signals[32] = nullptr;
    signals[33] = nullptr;
    signals[34] = nullptr;
    signals[35] = nullptr;
    signals[36] = nullptr;
    signals[37] = nullptr;
    signals[38] = nullptr;
    signals[39] = nullptr;
    signals[40] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    limi_01_last = 0;
    limi_01_lookaheadIndex = 0;
    limi_01_recover = 0;
    limi_01_lookaheadInv = 0;
    limi_01_dc1_xm1 = 0;
    limi_01_dc1_ym1 = 0;
    limi_01_setupDone = false;
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
    gaintilde_02_lastValue = 0;
    gaintilde_02_loginc = 1;
    gaintilde_02_zval = 0;
    gaintilde_02_ramp_d_prev = 0;
    gaintilde_02_ramp_prev = 0;
    gaintilde_02_ramp_index = 0;
    gaintilde_02_ramp_increment = 0;
    gaintilde_02_setupDone = false;
    gaintilde_03_lastValue = 0;
    gaintilde_03_loginc = 1;
    gaintilde_03_zval = 0;
    gaintilde_03_ramp_d_prev = 0;
    gaintilde_03_ramp_prev = 0;
    gaintilde_03_ramp_index = 0;
    gaintilde_03_ramp_increment = 0;
    gaintilde_03_setupDone = false;
    gaintilde_04_lastValue = 0;
    gaintilde_04_loginc = 1;
    gaintilde_04_zval = 0;
    gaintilde_04_ramp_d_prev = 0;
    gaintilde_04_ramp_prev = 0;
    gaintilde_04_ramp_index = 0;
    gaintilde_04_ramp_increment = 0;
    gaintilde_04_setupDone = false;
    freqshift_tilde_01_h_biquad1_x1 = 0;
    freqshift_tilde_01_h_biquad1_x2 = 0;
    freqshift_tilde_01_h_biquad1_y1 = 0;
    freqshift_tilde_01_h_biquad1_y2 = 0;
    freqshift_tilde_01_h_biquad2_x1 = 0;
    freqshift_tilde_01_h_biquad2_x2 = 0;
    freqshift_tilde_01_h_biquad2_y1 = 0;
    freqshift_tilde_01_h_biquad2_y2 = 0;
    freqshift_tilde_01_h_biquad3_x1 = 0;
    freqshift_tilde_01_h_biquad3_x2 = 0;
    freqshift_tilde_01_h_biquad3_y1 = 0;
    freqshift_tilde_01_h_biquad3_y2 = 0;
    freqshift_tilde_01_h_biquad4_x1 = 0;
    freqshift_tilde_01_h_biquad4_x2 = 0;
    freqshift_tilde_01_h_biquad4_y1 = 0;
    freqshift_tilde_01_h_biquad4_y2 = 0;
    freqshift_tilde_01_h_biquad5_x1 = 0;
    freqshift_tilde_01_h_biquad5_x2 = 0;
    freqshift_tilde_01_h_biquad5_y1 = 0;
    freqshift_tilde_01_h_biquad5_y2 = 0;
    freqshift_tilde_01_h_biquad6_x1 = 0;
    freqshift_tilde_01_h_biquad6_x2 = 0;
    freqshift_tilde_01_h_biquad6_y1 = 0;
    freqshift_tilde_01_h_biquad6_y2 = 0;
    freqshift_tilde_01_p_currentPhase = 0;
    freqshift_tilde_01_p_conv = 0;
    freqshift_tilde_01_setupDone = false;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    freqshift_tilde_02_h_biquad1_x1 = 0;
    freqshift_tilde_02_h_biquad1_x2 = 0;
    freqshift_tilde_02_h_biquad1_y1 = 0;
    freqshift_tilde_02_h_biquad1_y2 = 0;
    freqshift_tilde_02_h_biquad2_x1 = 0;
    freqshift_tilde_02_h_biquad2_x2 = 0;
    freqshift_tilde_02_h_biquad2_y1 = 0;
    freqshift_tilde_02_h_biquad2_y2 = 0;
    freqshift_tilde_02_h_biquad3_x1 = 0;
    freqshift_tilde_02_h_biquad3_x2 = 0;
    freqshift_tilde_02_h_biquad3_y1 = 0;
    freqshift_tilde_02_h_biquad3_y2 = 0;
    freqshift_tilde_02_h_biquad4_x1 = 0;
    freqshift_tilde_02_h_biquad4_x2 = 0;
    freqshift_tilde_02_h_biquad4_y1 = 0;
    freqshift_tilde_02_h_biquad4_y2 = 0;
    freqshift_tilde_02_h_biquad5_x1 = 0;
    freqshift_tilde_02_h_biquad5_x2 = 0;
    freqshift_tilde_02_h_biquad5_y1 = 0;
    freqshift_tilde_02_h_biquad5_y2 = 0;
    freqshift_tilde_02_h_biquad6_x1 = 0;
    freqshift_tilde_02_h_biquad6_x2 = 0;
    freqshift_tilde_02_h_biquad6_y1 = 0;
    freqshift_tilde_02_h_biquad6_y2 = 0;
    freqshift_tilde_02_p_currentPhase = 0;
    freqshift_tilde_02_p_conv = 0;
    freqshift_tilde_02_setupDone = false;
    param_13_lastValue = 0;
    freqshift_tilde_03_h_biquad1_x1 = 0;
    freqshift_tilde_03_h_biquad1_x2 = 0;
    freqshift_tilde_03_h_biquad1_y1 = 0;
    freqshift_tilde_03_h_biquad1_y2 = 0;
    freqshift_tilde_03_h_biquad2_x1 = 0;
    freqshift_tilde_03_h_biquad2_x2 = 0;
    freqshift_tilde_03_h_biquad2_y1 = 0;
    freqshift_tilde_03_h_biquad2_y2 = 0;
    freqshift_tilde_03_h_biquad3_x1 = 0;
    freqshift_tilde_03_h_biquad3_x2 = 0;
    freqshift_tilde_03_h_biquad3_y1 = 0;
    freqshift_tilde_03_h_biquad3_y2 = 0;
    freqshift_tilde_03_h_biquad4_x1 = 0;
    freqshift_tilde_03_h_biquad4_x2 = 0;
    freqshift_tilde_03_h_biquad4_y1 = 0;
    freqshift_tilde_03_h_biquad4_y2 = 0;
    freqshift_tilde_03_h_biquad5_x1 = 0;
    freqshift_tilde_03_h_biquad5_x2 = 0;
    freqshift_tilde_03_h_biquad5_y1 = 0;
    freqshift_tilde_03_h_biquad5_y2 = 0;
    freqshift_tilde_03_h_biquad6_x1 = 0;
    freqshift_tilde_03_h_biquad6_x2 = 0;
    freqshift_tilde_03_h_biquad6_y1 = 0;
    freqshift_tilde_03_h_biquad6_y2 = 0;
    freqshift_tilde_03_p_currentPhase = 0;
    freqshift_tilde_03_p_conv = 0;
    freqshift_tilde_03_setupDone = false;
    freqshift_tilde_04_h_biquad1_x1 = 0;
    freqshift_tilde_04_h_biquad1_x2 = 0;
    freqshift_tilde_04_h_biquad1_y1 = 0;
    freqshift_tilde_04_h_biquad1_y2 = 0;
    freqshift_tilde_04_h_biquad2_x1 = 0;
    freqshift_tilde_04_h_biquad2_x2 = 0;
    freqshift_tilde_04_h_biquad2_y1 = 0;
    freqshift_tilde_04_h_biquad2_y2 = 0;
    freqshift_tilde_04_h_biquad3_x1 = 0;
    freqshift_tilde_04_h_biquad3_x2 = 0;
    freqshift_tilde_04_h_biquad3_y1 = 0;
    freqshift_tilde_04_h_biquad3_y2 = 0;
    freqshift_tilde_04_h_biquad4_x1 = 0;
    freqshift_tilde_04_h_biquad4_x2 = 0;
    freqshift_tilde_04_h_biquad4_y1 = 0;
    freqshift_tilde_04_h_biquad4_y2 = 0;
    freqshift_tilde_04_h_biquad5_x1 = 0;
    freqshift_tilde_04_h_biquad5_x2 = 0;
    freqshift_tilde_04_h_biquad5_y1 = 0;
    freqshift_tilde_04_h_biquad5_y2 = 0;
    freqshift_tilde_04_h_biquad6_x1 = 0;
    freqshift_tilde_04_h_biquad6_x2 = 0;
    freqshift_tilde_04_h_biquad6_y1 = 0;
    freqshift_tilde_04_h_biquad6_y2 = 0;
    freqshift_tilde_04_p_currentPhase = 0;
    freqshift_tilde_04_p_conv = 0;
    freqshift_tilde_04_setupDone = false;
    gaintilde_05_lastValue = 0;
    gaintilde_05_loginc = 1;
    gaintilde_05_zval = 0;
    gaintilde_05_ramp_d_prev = 0;
    gaintilde_05_ramp_prev = 0;
    gaintilde_05_ramp_index = 0;
    gaintilde_05_ramp_increment = 0;
    gaintilde_05_setupDone = false;
    gaintilde_06_lastValue = 0;
    gaintilde_06_loginc = 1;
    gaintilde_06_zval = 0;
    gaintilde_06_ramp_d_prev = 0;
    gaintilde_06_ramp_prev = 0;
    gaintilde_06_ramp_index = 0;
    gaintilde_06_ramp_increment = 0;
    gaintilde_06_setupDone = false;
    gaintilde_07_lastValue = 0;
    gaintilde_07_loginc = 1;
    gaintilde_07_zval = 0;
    gaintilde_07_ramp_d_prev = 0;
    gaintilde_07_ramp_prev = 0;
    gaintilde_07_ramp_index = 0;
    gaintilde_07_ramp_increment = 0;
    gaintilde_07_setupDone = false;
    gaintilde_08_lastValue = 0;
    gaintilde_08_loginc = 1;
    gaintilde_08_zval = 0;
    gaintilde_08_ramp_d_prev = 0;
    gaintilde_08_ramp_prev = 0;
    gaintilde_08_ramp_index = 0;
    gaintilde_08_ramp_increment = 0;
    gaintilde_08_setupDone = false;
    freqshift_tilde_05_h_biquad1_x1 = 0;
    freqshift_tilde_05_h_biquad1_x2 = 0;
    freqshift_tilde_05_h_biquad1_y1 = 0;
    freqshift_tilde_05_h_biquad1_y2 = 0;
    freqshift_tilde_05_h_biquad2_x1 = 0;
    freqshift_tilde_05_h_biquad2_x2 = 0;
    freqshift_tilde_05_h_biquad2_y1 = 0;
    freqshift_tilde_05_h_biquad2_y2 = 0;
    freqshift_tilde_05_h_biquad3_x1 = 0;
    freqshift_tilde_05_h_biquad3_x2 = 0;
    freqshift_tilde_05_h_biquad3_y1 = 0;
    freqshift_tilde_05_h_biquad3_y2 = 0;
    freqshift_tilde_05_h_biquad4_x1 = 0;
    freqshift_tilde_05_h_biquad4_x2 = 0;
    freqshift_tilde_05_h_biquad4_y1 = 0;
    freqshift_tilde_05_h_biquad4_y2 = 0;
    freqshift_tilde_05_h_biquad5_x1 = 0;
    freqshift_tilde_05_h_biquad5_x2 = 0;
    freqshift_tilde_05_h_biquad5_y1 = 0;
    freqshift_tilde_05_h_biquad5_y2 = 0;
    freqshift_tilde_05_h_biquad6_x1 = 0;
    freqshift_tilde_05_h_biquad6_x2 = 0;
    freqshift_tilde_05_h_biquad6_y1 = 0;
    freqshift_tilde_05_h_biquad6_y2 = 0;
    freqshift_tilde_05_p_currentPhase = 0;
    freqshift_tilde_05_p_conv = 0;
    freqshift_tilde_05_setupDone = false;
    freqshift_tilde_06_h_biquad1_x1 = 0;
    freqshift_tilde_06_h_biquad1_x2 = 0;
    freqshift_tilde_06_h_biquad1_y1 = 0;
    freqshift_tilde_06_h_biquad1_y2 = 0;
    freqshift_tilde_06_h_biquad2_x1 = 0;
    freqshift_tilde_06_h_biquad2_x2 = 0;
    freqshift_tilde_06_h_biquad2_y1 = 0;
    freqshift_tilde_06_h_biquad2_y2 = 0;
    freqshift_tilde_06_h_biquad3_x1 = 0;
    freqshift_tilde_06_h_biquad3_x2 = 0;
    freqshift_tilde_06_h_biquad3_y1 = 0;
    freqshift_tilde_06_h_biquad3_y2 = 0;
    freqshift_tilde_06_h_biquad4_x1 = 0;
    freqshift_tilde_06_h_biquad4_x2 = 0;
    freqshift_tilde_06_h_biquad4_y1 = 0;
    freqshift_tilde_06_h_biquad4_y2 = 0;
    freqshift_tilde_06_h_biquad5_x1 = 0;
    freqshift_tilde_06_h_biquad5_x2 = 0;
    freqshift_tilde_06_h_biquad5_y1 = 0;
    freqshift_tilde_06_h_biquad5_y2 = 0;
    freqshift_tilde_06_h_biquad6_x1 = 0;
    freqshift_tilde_06_h_biquad6_x2 = 0;
    freqshift_tilde_06_h_biquad6_y1 = 0;
    freqshift_tilde_06_h_biquad6_y2 = 0;
    freqshift_tilde_06_p_currentPhase = 0;
    freqshift_tilde_06_p_conv = 0;
    freqshift_tilde_06_setupDone = false;
    freqshift_tilde_07_h_biquad1_x1 = 0;
    freqshift_tilde_07_h_biquad1_x2 = 0;
    freqshift_tilde_07_h_biquad1_y1 = 0;
    freqshift_tilde_07_h_biquad1_y2 = 0;
    freqshift_tilde_07_h_biquad2_x1 = 0;
    freqshift_tilde_07_h_biquad2_x2 = 0;
    freqshift_tilde_07_h_biquad2_y1 = 0;
    freqshift_tilde_07_h_biquad2_y2 = 0;
    freqshift_tilde_07_h_biquad3_x1 = 0;
    freqshift_tilde_07_h_biquad3_x2 = 0;
    freqshift_tilde_07_h_biquad3_y1 = 0;
    freqshift_tilde_07_h_biquad3_y2 = 0;
    freqshift_tilde_07_h_biquad4_x1 = 0;
    freqshift_tilde_07_h_biquad4_x2 = 0;
    freqshift_tilde_07_h_biquad4_y1 = 0;
    freqshift_tilde_07_h_biquad4_y2 = 0;
    freqshift_tilde_07_h_biquad5_x1 = 0;
    freqshift_tilde_07_h_biquad5_x2 = 0;
    freqshift_tilde_07_h_biquad5_y1 = 0;
    freqshift_tilde_07_h_biquad5_y2 = 0;
    freqshift_tilde_07_h_biquad6_x1 = 0;
    freqshift_tilde_07_h_biquad6_x2 = 0;
    freqshift_tilde_07_h_biquad6_y1 = 0;
    freqshift_tilde_07_h_biquad6_y2 = 0;
    freqshift_tilde_07_p_currentPhase = 0;
    freqshift_tilde_07_p_conv = 0;
    freqshift_tilde_07_setupDone = false;
    gaintilde_09_lastValue = 0;
    gaintilde_09_loginc = 1;
    gaintilde_09_zval = 0;
    gaintilde_09_ramp_d_prev = 0;
    gaintilde_09_ramp_prev = 0;
    gaintilde_09_ramp_index = 0;
    gaintilde_09_ramp_increment = 0;
    gaintilde_09_setupDone = false;
    freqshift_tilde_08_h_biquad1_x1 = 0;
    freqshift_tilde_08_h_biquad1_x2 = 0;
    freqshift_tilde_08_h_biquad1_y1 = 0;
    freqshift_tilde_08_h_biquad1_y2 = 0;
    freqshift_tilde_08_h_biquad2_x1 = 0;
    freqshift_tilde_08_h_biquad2_x2 = 0;
    freqshift_tilde_08_h_biquad2_y1 = 0;
    freqshift_tilde_08_h_biquad2_y2 = 0;
    freqshift_tilde_08_h_biquad3_x1 = 0;
    freqshift_tilde_08_h_biquad3_x2 = 0;
    freqshift_tilde_08_h_biquad3_y1 = 0;
    freqshift_tilde_08_h_biquad3_y2 = 0;
    freqshift_tilde_08_h_biquad4_x1 = 0;
    freqshift_tilde_08_h_biquad4_x2 = 0;
    freqshift_tilde_08_h_biquad4_y1 = 0;
    freqshift_tilde_08_h_biquad4_y2 = 0;
    freqshift_tilde_08_h_biquad5_x1 = 0;
    freqshift_tilde_08_h_biquad5_x2 = 0;
    freqshift_tilde_08_h_biquad5_y1 = 0;
    freqshift_tilde_08_h_biquad5_y2 = 0;
    freqshift_tilde_08_h_biquad6_x1 = 0;
    freqshift_tilde_08_h_biquad6_x2 = 0;
    freqshift_tilde_08_h_biquad6_y1 = 0;
    freqshift_tilde_08_h_biquad6_y2 = 0;
    freqshift_tilde_08_p_currentPhase = 0;
    freqshift_tilde_08_p_conv = 0;
    freqshift_tilde_08_setupDone = false;
    gaintilde_10_lastValue = 0;
    gaintilde_10_loginc = 1;
    gaintilde_10_zval = 0;
    gaintilde_10_ramp_d_prev = 0;
    gaintilde_10_ramp_prev = 0;
    gaintilde_10_ramp_index = 0;
    gaintilde_10_ramp_increment = 0;
    gaintilde_10_setupDone = false;
    gaintilde_11_lastValue = 0;
    gaintilde_11_loginc = 1;
    gaintilde_11_zval = 0;
    gaintilde_11_ramp_d_prev = 0;
    gaintilde_11_ramp_prev = 0;
    gaintilde_11_ramp_index = 0;
    gaintilde_11_ramp_increment = 0;
    gaintilde_11_setupDone = false;
    gaintilde_12_lastValue = 0;
    gaintilde_12_loginc = 1;
    gaintilde_12_zval = 0;
    gaintilde_12_ramp_d_prev = 0;
    gaintilde_12_ramp_prev = 0;
    gaintilde_12_ramp_index = 0;
    gaintilde_12_ramp_increment = 0;
    gaintilde_12_setupDone = false;
    freqshift_tilde_09_h_biquad1_x1 = 0;
    freqshift_tilde_09_h_biquad1_x2 = 0;
    freqshift_tilde_09_h_biquad1_y1 = 0;
    freqshift_tilde_09_h_biquad1_y2 = 0;
    freqshift_tilde_09_h_biquad2_x1 = 0;
    freqshift_tilde_09_h_biquad2_x2 = 0;
    freqshift_tilde_09_h_biquad2_y1 = 0;
    freqshift_tilde_09_h_biquad2_y2 = 0;
    freqshift_tilde_09_h_biquad3_x1 = 0;
    freqshift_tilde_09_h_biquad3_x2 = 0;
    freqshift_tilde_09_h_biquad3_y1 = 0;
    freqshift_tilde_09_h_biquad3_y2 = 0;
    freqshift_tilde_09_h_biquad4_x1 = 0;
    freqshift_tilde_09_h_biquad4_x2 = 0;
    freqshift_tilde_09_h_biquad4_y1 = 0;
    freqshift_tilde_09_h_biquad4_y2 = 0;
    freqshift_tilde_09_h_biquad5_x1 = 0;
    freqshift_tilde_09_h_biquad5_x2 = 0;
    freqshift_tilde_09_h_biquad5_y1 = 0;
    freqshift_tilde_09_h_biquad5_y2 = 0;
    freqshift_tilde_09_h_biquad6_x1 = 0;
    freqshift_tilde_09_h_biquad6_x2 = 0;
    freqshift_tilde_09_h_biquad6_y1 = 0;
    freqshift_tilde_09_h_biquad6_y2 = 0;
    freqshift_tilde_09_p_currentPhase = 0;
    freqshift_tilde_09_p_conv = 0;
    freqshift_tilde_09_setupDone = false;
    freqshift_tilde_10_h_biquad1_x1 = 0;
    freqshift_tilde_10_h_biquad1_x2 = 0;
    freqshift_tilde_10_h_biquad1_y1 = 0;
    freqshift_tilde_10_h_biquad1_y2 = 0;
    freqshift_tilde_10_h_biquad2_x1 = 0;
    freqshift_tilde_10_h_biquad2_x2 = 0;
    freqshift_tilde_10_h_biquad2_y1 = 0;
    freqshift_tilde_10_h_biquad2_y2 = 0;
    freqshift_tilde_10_h_biquad3_x1 = 0;
    freqshift_tilde_10_h_biquad3_x2 = 0;
    freqshift_tilde_10_h_biquad3_y1 = 0;
    freqshift_tilde_10_h_biquad3_y2 = 0;
    freqshift_tilde_10_h_biquad4_x1 = 0;
    freqshift_tilde_10_h_biquad4_x2 = 0;
    freqshift_tilde_10_h_biquad4_y1 = 0;
    freqshift_tilde_10_h_biquad4_y2 = 0;
    freqshift_tilde_10_h_biquad5_x1 = 0;
    freqshift_tilde_10_h_biquad5_x2 = 0;
    freqshift_tilde_10_h_biquad5_y1 = 0;
    freqshift_tilde_10_h_biquad5_y2 = 0;
    freqshift_tilde_10_h_biquad6_x1 = 0;
    freqshift_tilde_10_h_biquad6_x2 = 0;
    freqshift_tilde_10_h_biquad6_y1 = 0;
    freqshift_tilde_10_h_biquad6_y2 = 0;
    freqshift_tilde_10_p_currentPhase = 0;
    freqshift_tilde_10_p_conv = 0;
    freqshift_tilde_10_setupDone = false;
    freqshift_tilde_11_h_biquad1_x1 = 0;
    freqshift_tilde_11_h_biquad1_x2 = 0;
    freqshift_tilde_11_h_biquad1_y1 = 0;
    freqshift_tilde_11_h_biquad1_y2 = 0;
    freqshift_tilde_11_h_biquad2_x1 = 0;
    freqshift_tilde_11_h_biquad2_x2 = 0;
    freqshift_tilde_11_h_biquad2_y1 = 0;
    freqshift_tilde_11_h_biquad2_y2 = 0;
    freqshift_tilde_11_h_biquad3_x1 = 0;
    freqshift_tilde_11_h_biquad3_x2 = 0;
    freqshift_tilde_11_h_biquad3_y1 = 0;
    freqshift_tilde_11_h_biquad3_y2 = 0;
    freqshift_tilde_11_h_biquad4_x1 = 0;
    freqshift_tilde_11_h_biquad4_x2 = 0;
    freqshift_tilde_11_h_biquad4_y1 = 0;
    freqshift_tilde_11_h_biquad4_y2 = 0;
    freqshift_tilde_11_h_biquad5_x1 = 0;
    freqshift_tilde_11_h_biquad5_x2 = 0;
    freqshift_tilde_11_h_biquad5_y1 = 0;
    freqshift_tilde_11_h_biquad5_y2 = 0;
    freqshift_tilde_11_h_biquad6_x1 = 0;
    freqshift_tilde_11_h_biquad6_x2 = 0;
    freqshift_tilde_11_h_biquad6_y1 = 0;
    freqshift_tilde_11_h_biquad6_y2 = 0;
    freqshift_tilde_11_p_currentPhase = 0;
    freqshift_tilde_11_p_conv = 0;
    freqshift_tilde_11_setupDone = false;
    gaintilde_13_lastValue = 0;
    gaintilde_13_loginc = 1;
    gaintilde_13_zval = 0;
    gaintilde_13_ramp_d_prev = 0;
    gaintilde_13_ramp_prev = 0;
    gaintilde_13_ramp_index = 0;
    gaintilde_13_ramp_increment = 0;
    gaintilde_13_setupDone = false;
    param_14_lastValue = 0;
    param_15_lastValue = 0;
    freqshift_tilde_12_h_biquad1_x1 = 0;
    freqshift_tilde_12_h_biquad1_x2 = 0;
    freqshift_tilde_12_h_biquad1_y1 = 0;
    freqshift_tilde_12_h_biquad1_y2 = 0;
    freqshift_tilde_12_h_biquad2_x1 = 0;
    freqshift_tilde_12_h_biquad2_x2 = 0;
    freqshift_tilde_12_h_biquad2_y1 = 0;
    freqshift_tilde_12_h_biquad2_y2 = 0;
    freqshift_tilde_12_h_biquad3_x1 = 0;
    freqshift_tilde_12_h_biquad3_x2 = 0;
    freqshift_tilde_12_h_biquad3_y1 = 0;
    freqshift_tilde_12_h_biquad3_y2 = 0;
    freqshift_tilde_12_h_biquad4_x1 = 0;
    freqshift_tilde_12_h_biquad4_x2 = 0;
    freqshift_tilde_12_h_biquad4_y1 = 0;
    freqshift_tilde_12_h_biquad4_y2 = 0;
    freqshift_tilde_12_h_biquad5_x1 = 0;
    freqshift_tilde_12_h_biquad5_x2 = 0;
    freqshift_tilde_12_h_biquad5_y1 = 0;
    freqshift_tilde_12_h_biquad5_y2 = 0;
    freqshift_tilde_12_h_biquad6_x1 = 0;
    freqshift_tilde_12_h_biquad6_x2 = 0;
    freqshift_tilde_12_h_biquad6_y1 = 0;
    freqshift_tilde_12_h_biquad6_y2 = 0;
    freqshift_tilde_12_p_currentPhase = 0;
    freqshift_tilde_12_p_conv = 0;
    freqshift_tilde_12_setupDone = false;
    param_16_lastValue = 0;
    param_17_lastValue = 0;
    gaintilde_14_lastValue = 0;
    gaintilde_14_loginc = 1;
    gaintilde_14_zval = 0;
    gaintilde_14_ramp_d_prev = 0;
    gaintilde_14_ramp_prev = 0;
    gaintilde_14_ramp_index = 0;
    gaintilde_14_ramp_increment = 0;
    gaintilde_14_setupDone = false;
    gaintilde_15_lastValue = 0;
    gaintilde_15_loginc = 1;
    gaintilde_15_zval = 0;
    gaintilde_15_ramp_d_prev = 0;
    gaintilde_15_ramp_prev = 0;
    gaintilde_15_ramp_index = 0;
    gaintilde_15_ramp_increment = 0;
    gaintilde_15_setupDone = false;
    gaintilde_16_lastValue = 0;
    gaintilde_16_loginc = 1;
    gaintilde_16_zval = 0;
    gaintilde_16_ramp_d_prev = 0;
    gaintilde_16_ramp_prev = 0;
    gaintilde_16_ramp_index = 0;
    gaintilde_16_ramp_increment = 0;
    gaintilde_16_setupDone = false;
    freqshift_tilde_13_h_biquad1_x1 = 0;
    freqshift_tilde_13_h_biquad1_x2 = 0;
    freqshift_tilde_13_h_biquad1_y1 = 0;
    freqshift_tilde_13_h_biquad1_y2 = 0;
    freqshift_tilde_13_h_biquad2_x1 = 0;
    freqshift_tilde_13_h_biquad2_x2 = 0;
    freqshift_tilde_13_h_biquad2_y1 = 0;
    freqshift_tilde_13_h_biquad2_y2 = 0;
    freqshift_tilde_13_h_biquad3_x1 = 0;
    freqshift_tilde_13_h_biquad3_x2 = 0;
    freqshift_tilde_13_h_biquad3_y1 = 0;
    freqshift_tilde_13_h_biquad3_y2 = 0;
    freqshift_tilde_13_h_biquad4_x1 = 0;
    freqshift_tilde_13_h_biquad4_x2 = 0;
    freqshift_tilde_13_h_biquad4_y1 = 0;
    freqshift_tilde_13_h_biquad4_y2 = 0;
    freqshift_tilde_13_h_biquad5_x1 = 0;
    freqshift_tilde_13_h_biquad5_x2 = 0;
    freqshift_tilde_13_h_biquad5_y1 = 0;
    freqshift_tilde_13_h_biquad5_y2 = 0;
    freqshift_tilde_13_h_biquad6_x1 = 0;
    freqshift_tilde_13_h_biquad6_x2 = 0;
    freqshift_tilde_13_h_biquad6_y1 = 0;
    freqshift_tilde_13_h_biquad6_y2 = 0;
    freqshift_tilde_13_p_currentPhase = 0;
    freqshift_tilde_13_p_conv = 0;
    freqshift_tilde_13_setupDone = false;
    freqshift_tilde_14_h_biquad1_x1 = 0;
    freqshift_tilde_14_h_biquad1_x2 = 0;
    freqshift_tilde_14_h_biquad1_y1 = 0;
    freqshift_tilde_14_h_biquad1_y2 = 0;
    freqshift_tilde_14_h_biquad2_x1 = 0;
    freqshift_tilde_14_h_biquad2_x2 = 0;
    freqshift_tilde_14_h_biquad2_y1 = 0;
    freqshift_tilde_14_h_biquad2_y2 = 0;
    freqshift_tilde_14_h_biquad3_x1 = 0;
    freqshift_tilde_14_h_biquad3_x2 = 0;
    freqshift_tilde_14_h_biquad3_y1 = 0;
    freqshift_tilde_14_h_biquad3_y2 = 0;
    freqshift_tilde_14_h_biquad4_x1 = 0;
    freqshift_tilde_14_h_biquad4_x2 = 0;
    freqshift_tilde_14_h_biquad4_y1 = 0;
    freqshift_tilde_14_h_biquad4_y2 = 0;
    freqshift_tilde_14_h_biquad5_x1 = 0;
    freqshift_tilde_14_h_biquad5_x2 = 0;
    freqshift_tilde_14_h_biquad5_y1 = 0;
    freqshift_tilde_14_h_biquad5_y2 = 0;
    freqshift_tilde_14_h_biquad6_x1 = 0;
    freqshift_tilde_14_h_biquad6_x2 = 0;
    freqshift_tilde_14_h_biquad6_y1 = 0;
    freqshift_tilde_14_h_biquad6_y2 = 0;
    freqshift_tilde_14_p_currentPhase = 0;
    freqshift_tilde_14_p_conv = 0;
    freqshift_tilde_14_setupDone = false;
    gaintilde_17_lastValue = 0;
    gaintilde_17_loginc = 1;
    gaintilde_17_zval = 0;
    gaintilde_17_ramp_d_prev = 0;
    gaintilde_17_ramp_prev = 0;
    gaintilde_17_ramp_index = 0;
    gaintilde_17_ramp_increment = 0;
    gaintilde_17_setupDone = false;
    freqshift_tilde_15_h_biquad1_x1 = 0;
    freqshift_tilde_15_h_biquad1_x2 = 0;
    freqshift_tilde_15_h_biquad1_y1 = 0;
    freqshift_tilde_15_h_biquad1_y2 = 0;
    freqshift_tilde_15_h_biquad2_x1 = 0;
    freqshift_tilde_15_h_biquad2_x2 = 0;
    freqshift_tilde_15_h_biquad2_y1 = 0;
    freqshift_tilde_15_h_biquad2_y2 = 0;
    freqshift_tilde_15_h_biquad3_x1 = 0;
    freqshift_tilde_15_h_biquad3_x2 = 0;
    freqshift_tilde_15_h_biquad3_y1 = 0;
    freqshift_tilde_15_h_biquad3_y2 = 0;
    freqshift_tilde_15_h_biquad4_x1 = 0;
    freqshift_tilde_15_h_biquad4_x2 = 0;
    freqshift_tilde_15_h_biquad4_y1 = 0;
    freqshift_tilde_15_h_biquad4_y2 = 0;
    freqshift_tilde_15_h_biquad5_x1 = 0;
    freqshift_tilde_15_h_biquad5_x2 = 0;
    freqshift_tilde_15_h_biquad5_y1 = 0;
    freqshift_tilde_15_h_biquad5_y2 = 0;
    freqshift_tilde_15_h_biquad6_x1 = 0;
    freqshift_tilde_15_h_biquad6_x2 = 0;
    freqshift_tilde_15_h_biquad6_y1 = 0;
    freqshift_tilde_15_h_biquad6_y2 = 0;
    freqshift_tilde_15_p_currentPhase = 0;
    freqshift_tilde_15_p_conv = 0;
    freqshift_tilde_15_setupDone = false;
    freqshift_tilde_16_h_biquad1_x1 = 0;
    freqshift_tilde_16_h_biquad1_x2 = 0;
    freqshift_tilde_16_h_biquad1_y1 = 0;
    freqshift_tilde_16_h_biquad1_y2 = 0;
    freqshift_tilde_16_h_biquad2_x1 = 0;
    freqshift_tilde_16_h_biquad2_x2 = 0;
    freqshift_tilde_16_h_biquad2_y1 = 0;
    freqshift_tilde_16_h_biquad2_y2 = 0;
    freqshift_tilde_16_h_biquad3_x1 = 0;
    freqshift_tilde_16_h_biquad3_x2 = 0;
    freqshift_tilde_16_h_biquad3_y1 = 0;
    freqshift_tilde_16_h_biquad3_y2 = 0;
    freqshift_tilde_16_h_biquad4_x1 = 0;
    freqshift_tilde_16_h_biquad4_x2 = 0;
    freqshift_tilde_16_h_biquad4_y1 = 0;
    freqshift_tilde_16_h_biquad4_y2 = 0;
    freqshift_tilde_16_h_biquad5_x1 = 0;
    freqshift_tilde_16_h_biquad5_x2 = 0;
    freqshift_tilde_16_h_biquad5_y1 = 0;
    freqshift_tilde_16_h_biquad5_y2 = 0;
    freqshift_tilde_16_h_biquad6_x1 = 0;
    freqshift_tilde_16_h_biquad6_x2 = 0;
    freqshift_tilde_16_h_biquad6_y1 = 0;
    freqshift_tilde_16_h_biquad6_y2 = 0;
    freqshift_tilde_16_p_currentPhase = 0;
    freqshift_tilde_16_p_conv = 0;
    freqshift_tilde_16_setupDone = false;
    gaintilde_18_lastValue = 0;
    gaintilde_18_loginc = 1;
    gaintilde_18_zval = 0;
    gaintilde_18_ramp_d_prev = 0;
    gaintilde_18_ramp_prev = 0;
    gaintilde_18_ramp_index = 0;
    gaintilde_18_ramp_increment = 0;
    gaintilde_18_setupDone = false;
    gaintilde_19_lastValue = 0;
    gaintilde_19_loginc = 1;
    gaintilde_19_zval = 0;
    gaintilde_19_ramp_d_prev = 0;
    gaintilde_19_ramp_prev = 0;
    gaintilde_19_ramp_index = 0;
    gaintilde_19_ramp_increment = 0;
    gaintilde_19_setupDone = false;
    freqshift_tilde_17_h_biquad1_x1 = 0;
    freqshift_tilde_17_h_biquad1_x2 = 0;
    freqshift_tilde_17_h_biquad1_y1 = 0;
    freqshift_tilde_17_h_biquad1_y2 = 0;
    freqshift_tilde_17_h_biquad2_x1 = 0;
    freqshift_tilde_17_h_biquad2_x2 = 0;
    freqshift_tilde_17_h_biquad2_y1 = 0;
    freqshift_tilde_17_h_biquad2_y2 = 0;
    freqshift_tilde_17_h_biquad3_x1 = 0;
    freqshift_tilde_17_h_biquad3_x2 = 0;
    freqshift_tilde_17_h_biquad3_y1 = 0;
    freqshift_tilde_17_h_biquad3_y2 = 0;
    freqshift_tilde_17_h_biquad4_x1 = 0;
    freqshift_tilde_17_h_biquad4_x2 = 0;
    freqshift_tilde_17_h_biquad4_y1 = 0;
    freqshift_tilde_17_h_biquad4_y2 = 0;
    freqshift_tilde_17_h_biquad5_x1 = 0;
    freqshift_tilde_17_h_biquad5_x2 = 0;
    freqshift_tilde_17_h_biquad5_y1 = 0;
    freqshift_tilde_17_h_biquad5_y2 = 0;
    freqshift_tilde_17_h_biquad6_x1 = 0;
    freqshift_tilde_17_h_biquad6_x2 = 0;
    freqshift_tilde_17_h_biquad6_y1 = 0;
    freqshift_tilde_17_h_biquad6_y2 = 0;
    freqshift_tilde_17_p_currentPhase = 0;
    freqshift_tilde_17_p_conv = 0;
    freqshift_tilde_17_setupDone = false;
    freqshift_tilde_18_h_biquad1_x1 = 0;
    freqshift_tilde_18_h_biquad1_x2 = 0;
    freqshift_tilde_18_h_biquad1_y1 = 0;
    freqshift_tilde_18_h_biquad1_y2 = 0;
    freqshift_tilde_18_h_biquad2_x1 = 0;
    freqshift_tilde_18_h_biquad2_x2 = 0;
    freqshift_tilde_18_h_biquad2_y1 = 0;
    freqshift_tilde_18_h_biquad2_y2 = 0;
    freqshift_tilde_18_h_biquad3_x1 = 0;
    freqshift_tilde_18_h_biquad3_x2 = 0;
    freqshift_tilde_18_h_biquad3_y1 = 0;
    freqshift_tilde_18_h_biquad3_y2 = 0;
    freqshift_tilde_18_h_biquad4_x1 = 0;
    freqshift_tilde_18_h_biquad4_x2 = 0;
    freqshift_tilde_18_h_biquad4_y1 = 0;
    freqshift_tilde_18_h_biquad4_y2 = 0;
    freqshift_tilde_18_h_biquad5_x1 = 0;
    freqshift_tilde_18_h_biquad5_x2 = 0;
    freqshift_tilde_18_h_biquad5_y1 = 0;
    freqshift_tilde_18_h_biquad5_y2 = 0;
    freqshift_tilde_18_h_biquad6_x1 = 0;
    freqshift_tilde_18_h_biquad6_x2 = 0;
    freqshift_tilde_18_h_biquad6_y1 = 0;
    freqshift_tilde_18_h_biquad6_y2 = 0;
    freqshift_tilde_18_p_currentPhase = 0;
    freqshift_tilde_18_p_conv = 0;
    freqshift_tilde_18_setupDone = false;
    gaintilde_20_lastValue = 0;
    gaintilde_20_loginc = 1;
    gaintilde_20_zval = 0;
    gaintilde_20_ramp_d_prev = 0;
    gaintilde_20_ramp_prev = 0;
    gaintilde_20_ramp_index = 0;
    gaintilde_20_ramp_increment = 0;
    gaintilde_20_setupDone = false;
    gaintilde_21_lastValue = 0;
    gaintilde_21_loginc = 1;
    gaintilde_21_zval = 0;
    gaintilde_21_ramp_d_prev = 0;
    gaintilde_21_ramp_prev = 0;
    gaintilde_21_ramp_index = 0;
    gaintilde_21_ramp_increment = 0;
    gaintilde_21_setupDone = false;
    freqshift_tilde_19_h_biquad1_x1 = 0;
    freqshift_tilde_19_h_biquad1_x2 = 0;
    freqshift_tilde_19_h_biquad1_y1 = 0;
    freqshift_tilde_19_h_biquad1_y2 = 0;
    freqshift_tilde_19_h_biquad2_x1 = 0;
    freqshift_tilde_19_h_biquad2_x2 = 0;
    freqshift_tilde_19_h_biquad2_y1 = 0;
    freqshift_tilde_19_h_biquad2_y2 = 0;
    freqshift_tilde_19_h_biquad3_x1 = 0;
    freqshift_tilde_19_h_biquad3_x2 = 0;
    freqshift_tilde_19_h_biquad3_y1 = 0;
    freqshift_tilde_19_h_biquad3_y2 = 0;
    freqshift_tilde_19_h_biquad4_x1 = 0;
    freqshift_tilde_19_h_biquad4_x2 = 0;
    freqshift_tilde_19_h_biquad4_y1 = 0;
    freqshift_tilde_19_h_biquad4_y2 = 0;
    freqshift_tilde_19_h_biquad5_x1 = 0;
    freqshift_tilde_19_h_biquad5_x2 = 0;
    freqshift_tilde_19_h_biquad5_y1 = 0;
    freqshift_tilde_19_h_biquad5_y2 = 0;
    freqshift_tilde_19_h_biquad6_x1 = 0;
    freqshift_tilde_19_h_biquad6_x2 = 0;
    freqshift_tilde_19_h_biquad6_y1 = 0;
    freqshift_tilde_19_h_biquad6_y2 = 0;
    freqshift_tilde_19_p_currentPhase = 0;
    freqshift_tilde_19_p_conv = 0;
    freqshift_tilde_19_setupDone = false;
    freqshift_tilde_20_h_biquad1_x1 = 0;
    freqshift_tilde_20_h_biquad1_x2 = 0;
    freqshift_tilde_20_h_biquad1_y1 = 0;
    freqshift_tilde_20_h_biquad1_y2 = 0;
    freqshift_tilde_20_h_biquad2_x1 = 0;
    freqshift_tilde_20_h_biquad2_x2 = 0;
    freqshift_tilde_20_h_biquad2_y1 = 0;
    freqshift_tilde_20_h_biquad2_y2 = 0;
    freqshift_tilde_20_h_biquad3_x1 = 0;
    freqshift_tilde_20_h_biquad3_x2 = 0;
    freqshift_tilde_20_h_biquad3_y1 = 0;
    freqshift_tilde_20_h_biquad3_y2 = 0;
    freqshift_tilde_20_h_biquad4_x1 = 0;
    freqshift_tilde_20_h_biquad4_x2 = 0;
    freqshift_tilde_20_h_biquad4_y1 = 0;
    freqshift_tilde_20_h_biquad4_y2 = 0;
    freqshift_tilde_20_h_biquad5_x1 = 0;
    freqshift_tilde_20_h_biquad5_x2 = 0;
    freqshift_tilde_20_h_biquad5_y1 = 0;
    freqshift_tilde_20_h_biquad5_y2 = 0;
    freqshift_tilde_20_h_biquad6_x1 = 0;
    freqshift_tilde_20_h_biquad6_x2 = 0;
    freqshift_tilde_20_h_biquad6_y1 = 0;
    freqshift_tilde_20_h_biquad6_y2 = 0;
    freqshift_tilde_20_p_currentPhase = 0;
    freqshift_tilde_20_p_conv = 0;
    freqshift_tilde_20_setupDone = false;
    gaintilde_22_lastValue = 0;
    gaintilde_22_loginc = 1;
    gaintilde_22_zval = 0;
    gaintilde_22_ramp_d_prev = 0;
    gaintilde_22_ramp_prev = 0;
    gaintilde_22_ramp_index = 0;
    gaintilde_22_ramp_increment = 0;
    gaintilde_22_setupDone = false;
    gaintilde_23_lastValue = 0;
    gaintilde_23_loginc = 1;
    gaintilde_23_zval = 0;
    gaintilde_23_ramp_d_prev = 0;
    gaintilde_23_ramp_prev = 0;
    gaintilde_23_ramp_index = 0;
    gaintilde_23_ramp_increment = 0;
    gaintilde_23_setupDone = false;
    param_18_lastValue = 0;
    param_19_lastValue = 0;
    freqshift_tilde_21_h_biquad1_x1 = 0;
    freqshift_tilde_21_h_biquad1_x2 = 0;
    freqshift_tilde_21_h_biquad1_y1 = 0;
    freqshift_tilde_21_h_biquad1_y2 = 0;
    freqshift_tilde_21_h_biquad2_x1 = 0;
    freqshift_tilde_21_h_biquad2_x2 = 0;
    freqshift_tilde_21_h_biquad2_y1 = 0;
    freqshift_tilde_21_h_biquad2_y2 = 0;
    freqshift_tilde_21_h_biquad3_x1 = 0;
    freqshift_tilde_21_h_biquad3_x2 = 0;
    freqshift_tilde_21_h_biquad3_y1 = 0;
    freqshift_tilde_21_h_biquad3_y2 = 0;
    freqshift_tilde_21_h_biquad4_x1 = 0;
    freqshift_tilde_21_h_biquad4_x2 = 0;
    freqshift_tilde_21_h_biquad4_y1 = 0;
    freqshift_tilde_21_h_biquad4_y2 = 0;
    freqshift_tilde_21_h_biquad5_x1 = 0;
    freqshift_tilde_21_h_biquad5_x2 = 0;
    freqshift_tilde_21_h_biquad5_y1 = 0;
    freqshift_tilde_21_h_biquad5_y2 = 0;
    freqshift_tilde_21_h_biquad6_x1 = 0;
    freqshift_tilde_21_h_biquad6_x2 = 0;
    freqshift_tilde_21_h_biquad6_y1 = 0;
    freqshift_tilde_21_h_biquad6_y2 = 0;
    freqshift_tilde_21_p_currentPhase = 0;
    freqshift_tilde_21_p_conv = 0;
    freqshift_tilde_21_setupDone = false;
    param_20_lastValue = 0;
    freqshift_tilde_22_h_biquad1_x1 = 0;
    freqshift_tilde_22_h_biquad1_x2 = 0;
    freqshift_tilde_22_h_biquad1_y1 = 0;
    freqshift_tilde_22_h_biquad1_y2 = 0;
    freqshift_tilde_22_h_biquad2_x1 = 0;
    freqshift_tilde_22_h_biquad2_x2 = 0;
    freqshift_tilde_22_h_biquad2_y1 = 0;
    freqshift_tilde_22_h_biquad2_y2 = 0;
    freqshift_tilde_22_h_biquad3_x1 = 0;
    freqshift_tilde_22_h_biquad3_x2 = 0;
    freqshift_tilde_22_h_biquad3_y1 = 0;
    freqshift_tilde_22_h_biquad3_y2 = 0;
    freqshift_tilde_22_h_biquad4_x1 = 0;
    freqshift_tilde_22_h_biquad4_x2 = 0;
    freqshift_tilde_22_h_biquad4_y1 = 0;
    freqshift_tilde_22_h_biquad4_y2 = 0;
    freqshift_tilde_22_h_biquad5_x1 = 0;
    freqshift_tilde_22_h_biquad5_x2 = 0;
    freqshift_tilde_22_h_biquad5_y1 = 0;
    freqshift_tilde_22_h_biquad5_y2 = 0;
    freqshift_tilde_22_h_biquad6_x1 = 0;
    freqshift_tilde_22_h_biquad6_x2 = 0;
    freqshift_tilde_22_h_biquad6_y1 = 0;
    freqshift_tilde_22_h_biquad6_y2 = 0;
    freqshift_tilde_22_p_currentPhase = 0;
    freqshift_tilde_22_p_conv = 0;
    freqshift_tilde_22_setupDone = false;
    param_21_lastValue = 0;
    gaintilde_24_lastValue = 0;
    gaintilde_24_loginc = 1;
    gaintilde_24_zval = 0;
    gaintilde_24_ramp_d_prev = 0;
    gaintilde_24_ramp_prev = 0;
    gaintilde_24_ramp_index = 0;
    gaintilde_24_ramp_increment = 0;
    gaintilde_24_setupDone = false;
    gaintilde_25_lastValue = 0;
    gaintilde_25_loginc = 1;
    gaintilde_25_zval = 0;
    gaintilde_25_ramp_d_prev = 0;
    gaintilde_25_ramp_prev = 0;
    gaintilde_25_ramp_index = 0;
    gaintilde_25_ramp_increment = 0;
    gaintilde_25_setupDone = false;
    freqshift_tilde_23_h_biquad1_x1 = 0;
    freqshift_tilde_23_h_biquad1_x2 = 0;
    freqshift_tilde_23_h_biquad1_y1 = 0;
    freqshift_tilde_23_h_biquad1_y2 = 0;
    freqshift_tilde_23_h_biquad2_x1 = 0;
    freqshift_tilde_23_h_biquad2_x2 = 0;
    freqshift_tilde_23_h_biquad2_y1 = 0;
    freqshift_tilde_23_h_biquad2_y2 = 0;
    freqshift_tilde_23_h_biquad3_x1 = 0;
    freqshift_tilde_23_h_biquad3_x2 = 0;
    freqshift_tilde_23_h_biquad3_y1 = 0;
    freqshift_tilde_23_h_biquad3_y2 = 0;
    freqshift_tilde_23_h_biquad4_x1 = 0;
    freqshift_tilde_23_h_biquad4_x2 = 0;
    freqshift_tilde_23_h_biquad4_y1 = 0;
    freqshift_tilde_23_h_biquad4_y2 = 0;
    freqshift_tilde_23_h_biquad5_x1 = 0;
    freqshift_tilde_23_h_biquad5_x2 = 0;
    freqshift_tilde_23_h_biquad5_y1 = 0;
    freqshift_tilde_23_h_biquad5_y2 = 0;
    freqshift_tilde_23_h_biquad6_x1 = 0;
    freqshift_tilde_23_h_biquad6_x2 = 0;
    freqshift_tilde_23_h_biquad6_y1 = 0;
    freqshift_tilde_23_h_biquad6_y2 = 0;
    freqshift_tilde_23_p_currentPhase = 0;
    freqshift_tilde_23_p_conv = 0;
    freqshift_tilde_23_setupDone = false;
    freqshift_tilde_24_h_biquad1_x1 = 0;
    freqshift_tilde_24_h_biquad1_x2 = 0;
    freqshift_tilde_24_h_biquad1_y1 = 0;
    freqshift_tilde_24_h_biquad1_y2 = 0;
    freqshift_tilde_24_h_biquad2_x1 = 0;
    freqshift_tilde_24_h_biquad2_x2 = 0;
    freqshift_tilde_24_h_biquad2_y1 = 0;
    freqshift_tilde_24_h_biquad2_y2 = 0;
    freqshift_tilde_24_h_biquad3_x1 = 0;
    freqshift_tilde_24_h_biquad3_x2 = 0;
    freqshift_tilde_24_h_biquad3_y1 = 0;
    freqshift_tilde_24_h_biquad3_y2 = 0;
    freqshift_tilde_24_h_biquad4_x1 = 0;
    freqshift_tilde_24_h_biquad4_x2 = 0;
    freqshift_tilde_24_h_biquad4_y1 = 0;
    freqshift_tilde_24_h_biquad4_y2 = 0;
    freqshift_tilde_24_h_biquad5_x1 = 0;
    freqshift_tilde_24_h_biquad5_x2 = 0;
    freqshift_tilde_24_h_biquad5_y1 = 0;
    freqshift_tilde_24_h_biquad5_y2 = 0;
    freqshift_tilde_24_h_biquad6_x1 = 0;
    freqshift_tilde_24_h_biquad6_x2 = 0;
    freqshift_tilde_24_h_biquad6_y1 = 0;
    freqshift_tilde_24_h_biquad6_y2 = 0;
    freqshift_tilde_24_p_currentPhase = 0;
    freqshift_tilde_24_p_conv = 0;
    freqshift_tilde_24_setupDone = false;
    gaintilde_26_lastValue = 0;
    gaintilde_26_loginc = 1;
    gaintilde_26_zval = 0;
    gaintilde_26_ramp_d_prev = 0;
    gaintilde_26_ramp_prev = 0;
    gaintilde_26_ramp_index = 0;
    gaintilde_26_ramp_increment = 0;
    gaintilde_26_setupDone = false;
    gaintilde_27_lastValue = 0;
    gaintilde_27_loginc = 1;
    gaintilde_27_zval = 0;
    gaintilde_27_ramp_d_prev = 0;
    gaintilde_27_ramp_prev = 0;
    gaintilde_27_ramp_index = 0;
    gaintilde_27_ramp_increment = 0;
    gaintilde_27_setupDone = false;
    freqshift_tilde_25_h_biquad1_x1 = 0;
    freqshift_tilde_25_h_biquad1_x2 = 0;
    freqshift_tilde_25_h_biquad1_y1 = 0;
    freqshift_tilde_25_h_biquad1_y2 = 0;
    freqshift_tilde_25_h_biquad2_x1 = 0;
    freqshift_tilde_25_h_biquad2_x2 = 0;
    freqshift_tilde_25_h_biquad2_y1 = 0;
    freqshift_tilde_25_h_biquad2_y2 = 0;
    freqshift_tilde_25_h_biquad3_x1 = 0;
    freqshift_tilde_25_h_biquad3_x2 = 0;
    freqshift_tilde_25_h_biquad3_y1 = 0;
    freqshift_tilde_25_h_biquad3_y2 = 0;
    freqshift_tilde_25_h_biquad4_x1 = 0;
    freqshift_tilde_25_h_biquad4_x2 = 0;
    freqshift_tilde_25_h_biquad4_y1 = 0;
    freqshift_tilde_25_h_biquad4_y2 = 0;
    freqshift_tilde_25_h_biquad5_x1 = 0;
    freqshift_tilde_25_h_biquad5_x2 = 0;
    freqshift_tilde_25_h_biquad5_y1 = 0;
    freqshift_tilde_25_h_biquad5_y2 = 0;
    freqshift_tilde_25_h_biquad6_x1 = 0;
    freqshift_tilde_25_h_biquad6_x2 = 0;
    freqshift_tilde_25_h_biquad6_y1 = 0;
    freqshift_tilde_25_h_biquad6_y2 = 0;
    freqshift_tilde_25_p_currentPhase = 0;
    freqshift_tilde_25_p_conv = 0;
    freqshift_tilde_25_setupDone = false;
    freqshift_tilde_26_h_biquad1_x1 = 0;
    freqshift_tilde_26_h_biquad1_x2 = 0;
    freqshift_tilde_26_h_biquad1_y1 = 0;
    freqshift_tilde_26_h_biquad1_y2 = 0;
    freqshift_tilde_26_h_biquad2_x1 = 0;
    freqshift_tilde_26_h_biquad2_x2 = 0;
    freqshift_tilde_26_h_biquad2_y1 = 0;
    freqshift_tilde_26_h_biquad2_y2 = 0;
    freqshift_tilde_26_h_biquad3_x1 = 0;
    freqshift_tilde_26_h_biquad3_x2 = 0;
    freqshift_tilde_26_h_biquad3_y1 = 0;
    freqshift_tilde_26_h_biquad3_y2 = 0;
    freqshift_tilde_26_h_biquad4_x1 = 0;
    freqshift_tilde_26_h_biquad4_x2 = 0;
    freqshift_tilde_26_h_biquad4_y1 = 0;
    freqshift_tilde_26_h_biquad4_y2 = 0;
    freqshift_tilde_26_h_biquad5_x1 = 0;
    freqshift_tilde_26_h_biquad5_x2 = 0;
    freqshift_tilde_26_h_biquad5_y1 = 0;
    freqshift_tilde_26_h_biquad5_y2 = 0;
    freqshift_tilde_26_h_biquad6_x1 = 0;
    freqshift_tilde_26_h_biquad6_x2 = 0;
    freqshift_tilde_26_h_biquad6_y1 = 0;
    freqshift_tilde_26_h_biquad6_y2 = 0;
    freqshift_tilde_26_p_currentPhase = 0;
    freqshift_tilde_26_p_conv = 0;
    freqshift_tilde_26_setupDone = false;
    gaintilde_28_lastValue = 0;
    gaintilde_28_loginc = 1;
    gaintilde_28_zval = 0;
    gaintilde_28_ramp_d_prev = 0;
    gaintilde_28_ramp_prev = 0;
    gaintilde_28_ramp_index = 0;
    gaintilde_28_ramp_increment = 0;
    gaintilde_28_setupDone = false;
    gaintilde_29_lastValue = 0;
    gaintilde_29_loginc = 1;
    gaintilde_29_zval = 0;
    gaintilde_29_ramp_d_prev = 0;
    gaintilde_29_ramp_prev = 0;
    gaintilde_29_ramp_index = 0;
    gaintilde_29_ramp_increment = 0;
    gaintilde_29_setupDone = false;
    freqshift_tilde_27_h_biquad1_x1 = 0;
    freqshift_tilde_27_h_biquad1_x2 = 0;
    freqshift_tilde_27_h_biquad1_y1 = 0;
    freqshift_tilde_27_h_biquad1_y2 = 0;
    freqshift_tilde_27_h_biquad2_x1 = 0;
    freqshift_tilde_27_h_biquad2_x2 = 0;
    freqshift_tilde_27_h_biquad2_y1 = 0;
    freqshift_tilde_27_h_biquad2_y2 = 0;
    freqshift_tilde_27_h_biquad3_x1 = 0;
    freqshift_tilde_27_h_biquad3_x2 = 0;
    freqshift_tilde_27_h_biquad3_y1 = 0;
    freqshift_tilde_27_h_biquad3_y2 = 0;
    freqshift_tilde_27_h_biquad4_x1 = 0;
    freqshift_tilde_27_h_biquad4_x2 = 0;
    freqshift_tilde_27_h_biquad4_y1 = 0;
    freqshift_tilde_27_h_biquad4_y2 = 0;
    freqshift_tilde_27_h_biquad5_x1 = 0;
    freqshift_tilde_27_h_biquad5_x2 = 0;
    freqshift_tilde_27_h_biquad5_y1 = 0;
    freqshift_tilde_27_h_biquad5_y2 = 0;
    freqshift_tilde_27_h_biquad6_x1 = 0;
    freqshift_tilde_27_h_biquad6_x2 = 0;
    freqshift_tilde_27_h_biquad6_y1 = 0;
    freqshift_tilde_27_h_biquad6_y2 = 0;
    freqshift_tilde_27_p_currentPhase = 0;
    freqshift_tilde_27_p_conv = 0;
    freqshift_tilde_27_setupDone = false;
    freqshift_tilde_28_h_biquad1_x1 = 0;
    freqshift_tilde_28_h_biquad1_x2 = 0;
    freqshift_tilde_28_h_biquad1_y1 = 0;
    freqshift_tilde_28_h_biquad1_y2 = 0;
    freqshift_tilde_28_h_biquad2_x1 = 0;
    freqshift_tilde_28_h_biquad2_x2 = 0;
    freqshift_tilde_28_h_biquad2_y1 = 0;
    freqshift_tilde_28_h_biquad2_y2 = 0;
    freqshift_tilde_28_h_biquad3_x1 = 0;
    freqshift_tilde_28_h_biquad3_x2 = 0;
    freqshift_tilde_28_h_biquad3_y1 = 0;
    freqshift_tilde_28_h_biquad3_y2 = 0;
    freqshift_tilde_28_h_biquad4_x1 = 0;
    freqshift_tilde_28_h_biquad4_x2 = 0;
    freqshift_tilde_28_h_biquad4_y1 = 0;
    freqshift_tilde_28_h_biquad4_y2 = 0;
    freqshift_tilde_28_h_biquad5_x1 = 0;
    freqshift_tilde_28_h_biquad5_x2 = 0;
    freqshift_tilde_28_h_biquad5_y1 = 0;
    freqshift_tilde_28_h_biquad5_y2 = 0;
    freqshift_tilde_28_h_biquad6_x1 = 0;
    freqshift_tilde_28_h_biquad6_x2 = 0;
    freqshift_tilde_28_h_biquad6_y1 = 0;
    freqshift_tilde_28_h_biquad6_y2 = 0;
    freqshift_tilde_28_p_currentPhase = 0;
    freqshift_tilde_28_p_conv = 0;
    freqshift_tilde_28_setupDone = false;
    gaintilde_30_lastValue = 0;
    gaintilde_30_loginc = 1;
    gaintilde_30_zval = 0;
    gaintilde_30_ramp_d_prev = 0;
    gaintilde_30_ramp_prev = 0;
    gaintilde_30_ramp_index = 0;
    gaintilde_30_ramp_increment = 0;
    gaintilde_30_setupDone = false;
    gaintilde_31_lastValue = 0;
    gaintilde_31_loginc = 1;
    gaintilde_31_zval = 0;
    gaintilde_31_ramp_d_prev = 0;
    gaintilde_31_ramp_prev = 0;
    gaintilde_31_ramp_index = 0;
    gaintilde_31_ramp_increment = 0;
    gaintilde_31_setupDone = false;
    freqshift_tilde_29_h_biquad1_x1 = 0;
    freqshift_tilde_29_h_biquad1_x2 = 0;
    freqshift_tilde_29_h_biquad1_y1 = 0;
    freqshift_tilde_29_h_biquad1_y2 = 0;
    freqshift_tilde_29_h_biquad2_x1 = 0;
    freqshift_tilde_29_h_biquad2_x2 = 0;
    freqshift_tilde_29_h_biquad2_y1 = 0;
    freqshift_tilde_29_h_biquad2_y2 = 0;
    freqshift_tilde_29_h_biquad3_x1 = 0;
    freqshift_tilde_29_h_biquad3_x2 = 0;
    freqshift_tilde_29_h_biquad3_y1 = 0;
    freqshift_tilde_29_h_biquad3_y2 = 0;
    freqshift_tilde_29_h_biquad4_x1 = 0;
    freqshift_tilde_29_h_biquad4_x2 = 0;
    freqshift_tilde_29_h_biquad4_y1 = 0;
    freqshift_tilde_29_h_biquad4_y2 = 0;
    freqshift_tilde_29_h_biquad5_x1 = 0;
    freqshift_tilde_29_h_biquad5_x2 = 0;
    freqshift_tilde_29_h_biquad5_y1 = 0;
    freqshift_tilde_29_h_biquad5_y2 = 0;
    freqshift_tilde_29_h_biquad6_x1 = 0;
    freqshift_tilde_29_h_biquad6_x2 = 0;
    freqshift_tilde_29_h_biquad6_y1 = 0;
    freqshift_tilde_29_h_biquad6_y2 = 0;
    freqshift_tilde_29_p_currentPhase = 0;
    freqshift_tilde_29_p_conv = 0;
    freqshift_tilde_29_setupDone = false;
    freqshift_tilde_30_h_biquad1_x1 = 0;
    freqshift_tilde_30_h_biquad1_x2 = 0;
    freqshift_tilde_30_h_biquad1_y1 = 0;
    freqshift_tilde_30_h_biquad1_y2 = 0;
    freqshift_tilde_30_h_biquad2_x1 = 0;
    freqshift_tilde_30_h_biquad2_x2 = 0;
    freqshift_tilde_30_h_biquad2_y1 = 0;
    freqshift_tilde_30_h_biquad2_y2 = 0;
    freqshift_tilde_30_h_biquad3_x1 = 0;
    freqshift_tilde_30_h_biquad3_x2 = 0;
    freqshift_tilde_30_h_biquad3_y1 = 0;
    freqshift_tilde_30_h_biquad3_y2 = 0;
    freqshift_tilde_30_h_biquad4_x1 = 0;
    freqshift_tilde_30_h_biquad4_x2 = 0;
    freqshift_tilde_30_h_biquad4_y1 = 0;
    freqshift_tilde_30_h_biquad4_y2 = 0;
    freqshift_tilde_30_h_biquad5_x1 = 0;
    freqshift_tilde_30_h_biquad5_x2 = 0;
    freqshift_tilde_30_h_biquad5_y1 = 0;
    freqshift_tilde_30_h_biquad5_y2 = 0;
    freqshift_tilde_30_h_biquad6_x1 = 0;
    freqshift_tilde_30_h_biquad6_x2 = 0;
    freqshift_tilde_30_h_biquad6_y1 = 0;
    freqshift_tilde_30_h_biquad6_y2 = 0;
    freqshift_tilde_30_p_currentPhase = 0;
    freqshift_tilde_30_p_conv = 0;
    freqshift_tilde_30_setupDone = false;
    param_22_lastValue = 0;
    gaintilde_32_lastValue = 0;
    gaintilde_32_loginc = 1;
    gaintilde_32_zval = 0;
    gaintilde_32_ramp_d_prev = 0;
    gaintilde_32_ramp_prev = 0;
    gaintilde_32_ramp_index = 0;
    gaintilde_32_ramp_increment = 0;
    gaintilde_32_setupDone = false;
    gaintilde_33_lastValue = 0;
    gaintilde_33_loginc = 1;
    gaintilde_33_zval = 0;
    gaintilde_33_ramp_d_prev = 0;
    gaintilde_33_ramp_prev = 0;
    gaintilde_33_ramp_index = 0;
    gaintilde_33_ramp_increment = 0;
    gaintilde_33_setupDone = false;
    param_23_lastValue = 0;
    param_24_lastValue = 0;
    param_25_lastValue = 0;
    freqshift_tilde_31_h_biquad1_x1 = 0;
    freqshift_tilde_31_h_biquad1_x2 = 0;
    freqshift_tilde_31_h_biquad1_y1 = 0;
    freqshift_tilde_31_h_biquad1_y2 = 0;
    freqshift_tilde_31_h_biquad2_x1 = 0;
    freqshift_tilde_31_h_biquad2_x2 = 0;
    freqshift_tilde_31_h_biquad2_y1 = 0;
    freqshift_tilde_31_h_biquad2_y2 = 0;
    freqshift_tilde_31_h_biquad3_x1 = 0;
    freqshift_tilde_31_h_biquad3_x2 = 0;
    freqshift_tilde_31_h_biquad3_y1 = 0;
    freqshift_tilde_31_h_biquad3_y2 = 0;
    freqshift_tilde_31_h_biquad4_x1 = 0;
    freqshift_tilde_31_h_biquad4_x2 = 0;
    freqshift_tilde_31_h_biquad4_y1 = 0;
    freqshift_tilde_31_h_biquad4_y2 = 0;
    freqshift_tilde_31_h_biquad5_x1 = 0;
    freqshift_tilde_31_h_biquad5_x2 = 0;
    freqshift_tilde_31_h_biquad5_y1 = 0;
    freqshift_tilde_31_h_biquad5_y2 = 0;
    freqshift_tilde_31_h_biquad6_x1 = 0;
    freqshift_tilde_31_h_biquad6_x2 = 0;
    freqshift_tilde_31_h_biquad6_y1 = 0;
    freqshift_tilde_31_h_biquad6_y2 = 0;
    freqshift_tilde_31_p_currentPhase = 0;
    freqshift_tilde_31_p_conv = 0;
    freqshift_tilde_31_setupDone = false;
    freqshift_tilde_32_h_biquad1_x1 = 0;
    freqshift_tilde_32_h_biquad1_x2 = 0;
    freqshift_tilde_32_h_biquad1_y1 = 0;
    freqshift_tilde_32_h_biquad1_y2 = 0;
    freqshift_tilde_32_h_biquad2_x1 = 0;
    freqshift_tilde_32_h_biquad2_x2 = 0;
    freqshift_tilde_32_h_biquad2_y1 = 0;
    freqshift_tilde_32_h_biquad2_y2 = 0;
    freqshift_tilde_32_h_biquad3_x1 = 0;
    freqshift_tilde_32_h_biquad3_x2 = 0;
    freqshift_tilde_32_h_biquad3_y1 = 0;
    freqshift_tilde_32_h_biquad3_y2 = 0;
    freqshift_tilde_32_h_biquad4_x1 = 0;
    freqshift_tilde_32_h_biquad4_x2 = 0;
    freqshift_tilde_32_h_biquad4_y1 = 0;
    freqshift_tilde_32_h_biquad4_y2 = 0;
    freqshift_tilde_32_h_biquad5_x1 = 0;
    freqshift_tilde_32_h_biquad5_x2 = 0;
    freqshift_tilde_32_h_biquad5_y1 = 0;
    freqshift_tilde_32_h_biquad5_y2 = 0;
    freqshift_tilde_32_h_biquad6_x1 = 0;
    freqshift_tilde_32_h_biquad6_x2 = 0;
    freqshift_tilde_32_h_biquad6_y1 = 0;
    freqshift_tilde_32_h_biquad6_y2 = 0;
    freqshift_tilde_32_p_currentPhase = 0;
    freqshift_tilde_32_p_conv = 0;
    freqshift_tilde_32_setupDone = false;
    gaintilde_34_lastValue = 0;
    gaintilde_34_loginc = 1;
    gaintilde_34_zval = 0;
    gaintilde_34_ramp_d_prev = 0;
    gaintilde_34_ramp_prev = 0;
    gaintilde_34_ramp_index = 0;
    gaintilde_34_ramp_increment = 0;
    gaintilde_34_setupDone = false;
    gaintilde_35_lastValue = 0;
    gaintilde_35_loginc = 1;
    gaintilde_35_zval = 0;
    gaintilde_35_ramp_d_prev = 0;
    gaintilde_35_ramp_prev = 0;
    gaintilde_35_ramp_index = 0;
    gaintilde_35_ramp_increment = 0;
    gaintilde_35_setupDone = false;
    freqshift_tilde_33_h_biquad1_x1 = 0;
    freqshift_tilde_33_h_biquad1_x2 = 0;
    freqshift_tilde_33_h_biquad1_y1 = 0;
    freqshift_tilde_33_h_biquad1_y2 = 0;
    freqshift_tilde_33_h_biquad2_x1 = 0;
    freqshift_tilde_33_h_biquad2_x2 = 0;
    freqshift_tilde_33_h_biquad2_y1 = 0;
    freqshift_tilde_33_h_biquad2_y2 = 0;
    freqshift_tilde_33_h_biquad3_x1 = 0;
    freqshift_tilde_33_h_biquad3_x2 = 0;
    freqshift_tilde_33_h_biquad3_y1 = 0;
    freqshift_tilde_33_h_biquad3_y2 = 0;
    freqshift_tilde_33_h_biquad4_x1 = 0;
    freqshift_tilde_33_h_biquad4_x2 = 0;
    freqshift_tilde_33_h_biquad4_y1 = 0;
    freqshift_tilde_33_h_biquad4_y2 = 0;
    freqshift_tilde_33_h_biquad5_x1 = 0;
    freqshift_tilde_33_h_biquad5_x2 = 0;
    freqshift_tilde_33_h_biquad5_y1 = 0;
    freqshift_tilde_33_h_biquad5_y2 = 0;
    freqshift_tilde_33_h_biquad6_x1 = 0;
    freqshift_tilde_33_h_biquad6_x2 = 0;
    freqshift_tilde_33_h_biquad6_y1 = 0;
    freqshift_tilde_33_h_biquad6_y2 = 0;
    freqshift_tilde_33_p_currentPhase = 0;
    freqshift_tilde_33_p_conv = 0;
    freqshift_tilde_33_setupDone = false;
    freqshift_tilde_34_h_biquad1_x1 = 0;
    freqshift_tilde_34_h_biquad1_x2 = 0;
    freqshift_tilde_34_h_biquad1_y1 = 0;
    freqshift_tilde_34_h_biquad1_y2 = 0;
    freqshift_tilde_34_h_biquad2_x1 = 0;
    freqshift_tilde_34_h_biquad2_x2 = 0;
    freqshift_tilde_34_h_biquad2_y1 = 0;
    freqshift_tilde_34_h_biquad2_y2 = 0;
    freqshift_tilde_34_h_biquad3_x1 = 0;
    freqshift_tilde_34_h_biquad3_x2 = 0;
    freqshift_tilde_34_h_biquad3_y1 = 0;
    freqshift_tilde_34_h_biquad3_y2 = 0;
    freqshift_tilde_34_h_biquad4_x1 = 0;
    freqshift_tilde_34_h_biquad4_x2 = 0;
    freqshift_tilde_34_h_biquad4_y1 = 0;
    freqshift_tilde_34_h_biquad4_y2 = 0;
    freqshift_tilde_34_h_biquad5_x1 = 0;
    freqshift_tilde_34_h_biquad5_x2 = 0;
    freqshift_tilde_34_h_biquad5_y1 = 0;
    freqshift_tilde_34_h_biquad5_y2 = 0;
    freqshift_tilde_34_h_biquad6_x1 = 0;
    freqshift_tilde_34_h_biquad6_x2 = 0;
    freqshift_tilde_34_h_biquad6_y1 = 0;
    freqshift_tilde_34_h_biquad6_y2 = 0;
    freqshift_tilde_34_p_currentPhase = 0;
    freqshift_tilde_34_p_conv = 0;
    freqshift_tilde_34_setupDone = false;
    gaintilde_36_lastValue = 0;
    gaintilde_36_loginc = 1;
    gaintilde_36_zval = 0;
    gaintilde_36_ramp_d_prev = 0;
    gaintilde_36_ramp_prev = 0;
    gaintilde_36_ramp_index = 0;
    gaintilde_36_ramp_increment = 0;
    gaintilde_36_setupDone = false;
    gaintilde_37_lastValue = 0;
    gaintilde_37_loginc = 1;
    gaintilde_37_zval = 0;
    gaintilde_37_ramp_d_prev = 0;
    gaintilde_37_ramp_prev = 0;
    gaintilde_37_ramp_index = 0;
    gaintilde_37_ramp_increment = 0;
    gaintilde_37_setupDone = false;
    freqshift_tilde_35_h_biquad1_x1 = 0;
    freqshift_tilde_35_h_biquad1_x2 = 0;
    freqshift_tilde_35_h_biquad1_y1 = 0;
    freqshift_tilde_35_h_biquad1_y2 = 0;
    freqshift_tilde_35_h_biquad2_x1 = 0;
    freqshift_tilde_35_h_biquad2_x2 = 0;
    freqshift_tilde_35_h_biquad2_y1 = 0;
    freqshift_tilde_35_h_biquad2_y2 = 0;
    freqshift_tilde_35_h_biquad3_x1 = 0;
    freqshift_tilde_35_h_biquad3_x2 = 0;
    freqshift_tilde_35_h_biquad3_y1 = 0;
    freqshift_tilde_35_h_biquad3_y2 = 0;
    freqshift_tilde_35_h_biquad4_x1 = 0;
    freqshift_tilde_35_h_biquad4_x2 = 0;
    freqshift_tilde_35_h_biquad4_y1 = 0;
    freqshift_tilde_35_h_biquad4_y2 = 0;
    freqshift_tilde_35_h_biquad5_x1 = 0;
    freqshift_tilde_35_h_biquad5_x2 = 0;
    freqshift_tilde_35_h_biquad5_y1 = 0;
    freqshift_tilde_35_h_biquad5_y2 = 0;
    freqshift_tilde_35_h_biquad6_x1 = 0;
    freqshift_tilde_35_h_biquad6_x2 = 0;
    freqshift_tilde_35_h_biquad6_y1 = 0;
    freqshift_tilde_35_h_biquad6_y2 = 0;
    freqshift_tilde_35_p_currentPhase = 0;
    freqshift_tilde_35_p_conv = 0;
    freqshift_tilde_35_setupDone = false;
    freqshift_tilde_36_h_biquad1_x1 = 0;
    freqshift_tilde_36_h_biquad1_x2 = 0;
    freqshift_tilde_36_h_biquad1_y1 = 0;
    freqshift_tilde_36_h_biquad1_y2 = 0;
    freqshift_tilde_36_h_biquad2_x1 = 0;
    freqshift_tilde_36_h_biquad2_x2 = 0;
    freqshift_tilde_36_h_biquad2_y1 = 0;
    freqshift_tilde_36_h_biquad2_y2 = 0;
    freqshift_tilde_36_h_biquad3_x1 = 0;
    freqshift_tilde_36_h_biquad3_x2 = 0;
    freqshift_tilde_36_h_biquad3_y1 = 0;
    freqshift_tilde_36_h_biquad3_y2 = 0;
    freqshift_tilde_36_h_biquad4_x1 = 0;
    freqshift_tilde_36_h_biquad4_x2 = 0;
    freqshift_tilde_36_h_biquad4_y1 = 0;
    freqshift_tilde_36_h_biquad4_y2 = 0;
    freqshift_tilde_36_h_biquad5_x1 = 0;
    freqshift_tilde_36_h_biquad5_x2 = 0;
    freqshift_tilde_36_h_biquad5_y1 = 0;
    freqshift_tilde_36_h_biquad5_y2 = 0;
    freqshift_tilde_36_h_biquad6_x1 = 0;
    freqshift_tilde_36_h_biquad6_x2 = 0;
    freqshift_tilde_36_h_biquad6_y1 = 0;
    freqshift_tilde_36_h_biquad6_y2 = 0;
    freqshift_tilde_36_p_currentPhase = 0;
    freqshift_tilde_36_p_conv = 0;
    freqshift_tilde_36_setupDone = false;
    gaintilde_38_lastValue = 0;
    gaintilde_38_loginc = 1;
    gaintilde_38_zval = 0;
    gaintilde_38_ramp_d_prev = 0;
    gaintilde_38_ramp_prev = 0;
    gaintilde_38_ramp_index = 0;
    gaintilde_38_ramp_increment = 0;
    gaintilde_38_setupDone = false;
    gaintilde_39_lastValue = 0;
    gaintilde_39_loginc = 1;
    gaintilde_39_zval = 0;
    gaintilde_39_ramp_d_prev = 0;
    gaintilde_39_ramp_prev = 0;
    gaintilde_39_ramp_index = 0;
    gaintilde_39_ramp_increment = 0;
    gaintilde_39_setupDone = false;
    freqshift_tilde_37_h_biquad1_x1 = 0;
    freqshift_tilde_37_h_biquad1_x2 = 0;
    freqshift_tilde_37_h_biquad1_y1 = 0;
    freqshift_tilde_37_h_biquad1_y2 = 0;
    freqshift_tilde_37_h_biquad2_x1 = 0;
    freqshift_tilde_37_h_biquad2_x2 = 0;
    freqshift_tilde_37_h_biquad2_y1 = 0;
    freqshift_tilde_37_h_biquad2_y2 = 0;
    freqshift_tilde_37_h_biquad3_x1 = 0;
    freqshift_tilde_37_h_biquad3_x2 = 0;
    freqshift_tilde_37_h_biquad3_y1 = 0;
    freqshift_tilde_37_h_biquad3_y2 = 0;
    freqshift_tilde_37_h_biquad4_x1 = 0;
    freqshift_tilde_37_h_biquad4_x2 = 0;
    freqshift_tilde_37_h_biquad4_y1 = 0;
    freqshift_tilde_37_h_biquad4_y2 = 0;
    freqshift_tilde_37_h_biquad5_x1 = 0;
    freqshift_tilde_37_h_biquad5_x2 = 0;
    freqshift_tilde_37_h_biquad5_y1 = 0;
    freqshift_tilde_37_h_biquad5_y2 = 0;
    freqshift_tilde_37_h_biquad6_x1 = 0;
    freqshift_tilde_37_h_biquad6_x2 = 0;
    freqshift_tilde_37_h_biquad6_y1 = 0;
    freqshift_tilde_37_h_biquad6_y2 = 0;
    freqshift_tilde_37_p_currentPhase = 0;
    freqshift_tilde_37_p_conv = 0;
    freqshift_tilde_37_setupDone = false;
    freqshift_tilde_38_h_biquad1_x1 = 0;
    freqshift_tilde_38_h_biquad1_x2 = 0;
    freqshift_tilde_38_h_biquad1_y1 = 0;
    freqshift_tilde_38_h_biquad1_y2 = 0;
    freqshift_tilde_38_h_biquad2_x1 = 0;
    freqshift_tilde_38_h_biquad2_x2 = 0;
    freqshift_tilde_38_h_biquad2_y1 = 0;
    freqshift_tilde_38_h_biquad2_y2 = 0;
    freqshift_tilde_38_h_biquad3_x1 = 0;
    freqshift_tilde_38_h_biquad3_x2 = 0;
    freqshift_tilde_38_h_biquad3_y1 = 0;
    freqshift_tilde_38_h_biquad3_y2 = 0;
    freqshift_tilde_38_h_biquad4_x1 = 0;
    freqshift_tilde_38_h_biquad4_x2 = 0;
    freqshift_tilde_38_h_biquad4_y1 = 0;
    freqshift_tilde_38_h_biquad4_y2 = 0;
    freqshift_tilde_38_h_biquad5_x1 = 0;
    freqshift_tilde_38_h_biquad5_x2 = 0;
    freqshift_tilde_38_h_biquad5_y1 = 0;
    freqshift_tilde_38_h_biquad5_y2 = 0;
    freqshift_tilde_38_h_biquad6_x1 = 0;
    freqshift_tilde_38_h_biquad6_x2 = 0;
    freqshift_tilde_38_h_biquad6_y1 = 0;
    freqshift_tilde_38_h_biquad6_y2 = 0;
    freqshift_tilde_38_p_currentPhase = 0;
    freqshift_tilde_38_p_conv = 0;
    freqshift_tilde_38_setupDone = false;
    gaintilde_40_lastValue = 0;
    gaintilde_40_loginc = 1;
    gaintilde_40_zval = 0;
    gaintilde_40_ramp_d_prev = 0;
    gaintilde_40_ramp_prev = 0;
    gaintilde_40_ramp_index = 0;
    gaintilde_40_ramp_increment = 0;
    gaintilde_40_setupDone = false;
    param_26_lastValue = 0;
    param_27_lastValue = 0;
    param_28_lastValue = 0;
    param_29_lastValue = 0;
    freqshift_tilde_39_h_biquad1_x1 = 0;
    freqshift_tilde_39_h_biquad1_x2 = 0;
    freqshift_tilde_39_h_biquad1_y1 = 0;
    freqshift_tilde_39_h_biquad1_y2 = 0;
    freqshift_tilde_39_h_biquad2_x1 = 0;
    freqshift_tilde_39_h_biquad2_x2 = 0;
    freqshift_tilde_39_h_biquad2_y1 = 0;
    freqshift_tilde_39_h_biquad2_y2 = 0;
    freqshift_tilde_39_h_biquad3_x1 = 0;
    freqshift_tilde_39_h_biquad3_x2 = 0;
    freqshift_tilde_39_h_biquad3_y1 = 0;
    freqshift_tilde_39_h_biquad3_y2 = 0;
    freqshift_tilde_39_h_biquad4_x1 = 0;
    freqshift_tilde_39_h_biquad4_x2 = 0;
    freqshift_tilde_39_h_biquad4_y1 = 0;
    freqshift_tilde_39_h_biquad4_y2 = 0;
    freqshift_tilde_39_h_biquad5_x1 = 0;
    freqshift_tilde_39_h_biquad5_x2 = 0;
    freqshift_tilde_39_h_biquad5_y1 = 0;
    freqshift_tilde_39_h_biquad5_y2 = 0;
    freqshift_tilde_39_h_biquad6_x1 = 0;
    freqshift_tilde_39_h_biquad6_x2 = 0;
    freqshift_tilde_39_h_biquad6_y1 = 0;
    freqshift_tilde_39_h_biquad6_y2 = 0;
    freqshift_tilde_39_p_currentPhase = 0;
    freqshift_tilde_39_p_conv = 0;
    freqshift_tilde_39_setupDone = false;
    param_30_lastValue = 0;
    param_31_lastValue = 0;
    param_32_lastValue = 0;
    param_33_lastValue = 0;
    param_34_lastValue = 0;
    param_35_lastValue = 0;
    param_36_lastValue = 0;
    param_37_lastValue = 0;
    param_38_lastValue = 0;
    param_39_lastValue = 0;
    param_40_lastValue = 0;
    param_41_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number send_01_input_number;
    list send_01_input_list;
    number param_01_value;
    number send_02_input_number;
    list send_02_input_list;
    number param_02_value;
    number send_03_input_number;
    list send_03_input_list;
    number param_03_value;
    number send_04_input_number;
    list send_04_input_list;
    number param_04_value;
    number send_05_input_number;
    list send_05_input_list;
    number param_05_value;
    number send_06_input_number;
    list send_06_input_list;
    number param_06_value;
    number send_07_input_number;
    list send_07_input_list;
    number param_07_value;
    number send_08_input_number;
    list send_08_input_list;
    number param_08_value;
    number send_09_input_number;
    list send_09_input_list;
    number param_09_value;
    number receive_01_output_number;
    list receive_01_output_list;
    number limi_01_bypass;
    number limi_01_dcblock;
    number limi_01_lookahead;
    number limi_01_preamp;
    number limi_01_postamp;
    number limi_01_threshold;
    number limi_01_release;
    number receive_02_output_number;
    list receive_02_output_list;
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number gaintilde_02_input_number;
    number gaintilde_02_value;
    number gaintilde_02_interp;
    number receive_03_output_number;
    list receive_03_output_list;
    number receive_04_output_number;
    list receive_04_output_list;
    number gaintilde_03_input_number;
    number gaintilde_03_value;
    number gaintilde_03_interp;
    number receive_05_output_number;
    list receive_05_output_list;
    number gaintilde_04_input_number;
    number gaintilde_04_value;
    number gaintilde_04_interp;
    number freqshift_tilde_01_x;
    number freqshift_tilde_01_frequency;
    number send_10_input_number;
    list send_10_input_list;
    number param_10_value;
    number send_11_input_number;
    list send_11_input_list;
    number param_11_value;
    number send_12_input_number;
    list send_12_input_list;
    number param_12_value;
    number freqshift_tilde_02_x;
    number freqshift_tilde_02_frequency;
    number send_13_input_number;
    list send_13_input_list;
    number param_13_value;
    number receive_06_output_number;
    list receive_06_output_list;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    number freqshift_tilde_03_x;
    number freqshift_tilde_03_frequency;
    number freqshift_tilde_04_x;
    number freqshift_tilde_04_frequency;
    number gaintilde_05_input_number;
    number gaintilde_05_value;
    number gaintilde_05_interp;
    number receive_07_output_number;
    list receive_07_output_list;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number receive_08_output_number;
    list receive_08_output_list;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number receive_09_output_number;
    list receive_09_output_list;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number receive_10_output_number;
    list receive_10_output_list;
    number receive_11_output_number;
    list receive_11_output_list;
    number gaintilde_06_input_number;
    number gaintilde_06_value;
    number gaintilde_06_interp;
    number receive_12_output_number;
    list receive_12_output_list;
    number gaintilde_07_input_number;
    number gaintilde_07_value;
    number gaintilde_07_interp;
    number gaintilde_08_input_number;
    number gaintilde_08_value;
    number gaintilde_08_interp;
    number receive_13_output_number;
    list receive_13_output_list;
    number freqshift_tilde_05_x;
    number freqshift_tilde_05_frequency;
    number freqshift_tilde_06_x;
    number freqshift_tilde_06_frequency;
    number freqshift_tilde_07_x;
    number freqshift_tilde_07_frequency;
    number receive_14_output_number;
    list receive_14_output_list;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number gaintilde_09_input_number;
    number gaintilde_09_value;
    number gaintilde_09_interp;
    number freqshift_tilde_08_x;
    number freqshift_tilde_08_frequency;
    number receive_15_output_number;
    list receive_15_output_list;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number receive_16_output_number;
    list receive_16_output_list;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    number receive_17_output_number;
    list receive_17_output_list;
    number receive_18_output_number;
    list receive_18_output_list;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number receive_19_output_number;
    list receive_19_output_list;
    number receive_20_output_number;
    list receive_20_output_list;
    number gaintilde_10_input_number;
    number gaintilde_10_value;
    number gaintilde_10_interp;
    number gaintilde_11_input_number;
    number gaintilde_11_value;
    number gaintilde_11_interp;
    number gaintilde_12_input_number;
    number gaintilde_12_value;
    number gaintilde_12_interp;
    number receive_21_output_number;
    list receive_21_output_list;
    number freqshift_tilde_09_x;
    number freqshift_tilde_09_frequency;
    number freqshift_tilde_10_x;
    number freqshift_tilde_10_frequency;
    number freqshift_tilde_11_x;
    number freqshift_tilde_11_frequency;
    number receive_22_output_number;
    list receive_22_output_list;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    number receive_23_output_number;
    list receive_23_output_list;
    number expr_10_in1;
    number expr_10_in2;
    number expr_10_out1;
    number gaintilde_13_input_number;
    number gaintilde_13_value;
    number gaintilde_13_interp;
    number send_14_input_number;
    list send_14_input_list;
    number param_14_value;
    number send_15_input_number;
    list send_15_input_list;
    number param_15_value;
    number freqshift_tilde_12_x;
    number freqshift_tilde_12_frequency;
    number receive_24_output_number;
    list receive_24_output_list;
    number expr_11_in1;
    number expr_11_in2;
    number expr_11_out1;
    number send_16_input_number;
    list send_16_input_list;
    number param_16_value;
    number send_17_input_number;
    list send_17_input_list;
    number param_17_value;
    number receive_25_output_number;
    list receive_25_output_list;
    number receive_26_output_number;
    list receive_26_output_list;
    number expr_12_in1;
    number expr_12_in2;
    number expr_12_out1;
    number receive_27_output_number;
    list receive_27_output_list;
    number gaintilde_14_input_number;
    number gaintilde_14_value;
    number gaintilde_14_interp;
    number gaintilde_15_input_number;
    number gaintilde_15_value;
    number gaintilde_15_interp;
    number receive_28_output_number;
    list receive_28_output_list;
    number gaintilde_16_input_number;
    number gaintilde_16_value;
    number gaintilde_16_interp;
    number freqshift_tilde_13_x;
    number freqshift_tilde_13_frequency;
    number freqshift_tilde_14_x;
    number freqshift_tilde_14_frequency;
    number receive_29_output_number;
    list receive_29_output_list;
    number gaintilde_17_input_number;
    number gaintilde_17_value;
    number gaintilde_17_interp;
    number receive_30_output_number;
    list receive_30_output_list;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number freqshift_tilde_15_x;
    number freqshift_tilde_15_frequency;
    number receive_31_output_number;
    list receive_31_output_list;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number freqshift_tilde_16_x;
    number freqshift_tilde_16_frequency;
    number receive_32_output_number;
    list receive_32_output_list;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number receive_33_output_number;
    list receive_33_output_list;
    number receive_34_output_number;
    list receive_34_output_list;
    number gaintilde_18_input_number;
    number gaintilde_18_value;
    number gaintilde_18_interp;
    number receive_35_output_number;
    list receive_35_output_list;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    number gaintilde_19_input_number;
    number gaintilde_19_value;
    number gaintilde_19_interp;
    number freqshift_tilde_17_x;
    number freqshift_tilde_17_frequency;
    number receive_36_output_number;
    list receive_36_output_list;
    number freqshift_tilde_18_x;
    number freqshift_tilde_18_frequency;
    number gaintilde_20_input_number;
    number gaintilde_20_value;
    number gaintilde_20_interp;
    number receive_37_output_number;
    list receive_37_output_list;
    number receive_38_output_number;
    list receive_38_output_list;
    number expr_17_in1;
    number expr_17_in2;
    number expr_17_out1;
    number gaintilde_21_input_number;
    number gaintilde_21_value;
    number gaintilde_21_interp;
    number receive_39_output_number;
    list receive_39_output_list;
    number expr_18_in1;
    number expr_18_in2;
    number expr_18_out1;
    number freqshift_tilde_19_x;
    number freqshift_tilde_19_frequency;
    number freqshift_tilde_20_x;
    number freqshift_tilde_20_frequency;
    number receive_40_output_number;
    list receive_40_output_list;
    number receive_41_output_number;
    list receive_41_output_list;
    number receive_42_output_number;
    list receive_42_output_list;
    number expr_19_in1;
    number expr_19_in2;
    number expr_19_out1;
    number gaintilde_22_input_number;
    number gaintilde_22_value;
    number gaintilde_22_interp;
    number gaintilde_23_input_number;
    number gaintilde_23_value;
    number gaintilde_23_interp;
    number receive_43_output_number;
    list receive_43_output_list;
    number expr_20_in1;
    number expr_20_in2;
    number expr_20_out1;
    number send_18_input_number;
    list send_18_input_list;
    number param_18_value;
    number send_19_input_number;
    list send_19_input_list;
    number param_19_value;
    number freqshift_tilde_21_x;
    number freqshift_tilde_21_frequency;
    number send_20_input_number;
    list send_20_input_list;
    number param_20_value;
    number freqshift_tilde_22_x;
    number freqshift_tilde_22_frequency;
    number receive_44_output_number;
    list receive_44_output_list;
    number receive_45_output_number;
    list receive_45_output_list;
    number send_21_input_number;
    list send_21_input_list;
    number param_21_value;
    number gaintilde_24_input_number;
    number gaintilde_24_value;
    number gaintilde_24_interp;
    number receive_46_output_number;
    list receive_46_output_list;
    number expr_21_in1;
    number expr_21_in2;
    number expr_21_out1;
    number receive_47_output_number;
    list receive_47_output_list;
    number expr_22_in1;
    number expr_22_in2;
    number expr_22_out1;
    number gaintilde_25_input_number;
    number gaintilde_25_value;
    number gaintilde_25_interp;
    number freqshift_tilde_23_x;
    number freqshift_tilde_23_frequency;
    number receive_48_output_number;
    list receive_48_output_list;
    number freqshift_tilde_24_x;
    number freqshift_tilde_24_frequency;
    number receive_49_output_number;
    list receive_49_output_list;
    number gaintilde_26_input_number;
    number gaintilde_26_value;
    number gaintilde_26_interp;
    number receive_50_output_number;
    list receive_50_output_list;
    number expr_23_in1;
    number expr_23_in2;
    number expr_23_out1;
    number gaintilde_27_input_number;
    number gaintilde_27_value;
    number gaintilde_27_interp;
    number receive_51_output_number;
    list receive_51_output_list;
    number expr_24_in1;
    number expr_24_in2;
    number expr_24_out1;
    number freqshift_tilde_25_x;
    number freqshift_tilde_25_frequency;
    number freqshift_tilde_26_x;
    number freqshift_tilde_26_frequency;
    number receive_52_output_number;
    list receive_52_output_list;
    number receive_53_output_number;
    list receive_53_output_list;
    number receive_54_output_number;
    list receive_54_output_list;
    number expr_25_in1;
    number expr_25_in2;
    number expr_25_out1;
    number gaintilde_28_input_number;
    number gaintilde_28_value;
    number gaintilde_28_interp;
    number gaintilde_29_input_number;
    number gaintilde_29_value;
    number gaintilde_29_interp;
    number receive_55_output_number;
    list receive_55_output_list;
    number expr_26_in1;
    number expr_26_in2;
    number expr_26_out1;
    number freqshift_tilde_27_x;
    number freqshift_tilde_27_frequency;
    number receive_56_output_number;
    list receive_56_output_list;
    number freqshift_tilde_28_x;
    number freqshift_tilde_28_frequency;
    number receive_57_output_number;
    list receive_57_output_list;
    number gaintilde_30_input_number;
    number gaintilde_30_value;
    number gaintilde_30_interp;
    number gaintilde_31_input_number;
    number gaintilde_31_value;
    number gaintilde_31_interp;
    number receive_58_output_number;
    list receive_58_output_list;
    number expr_27_in1;
    number expr_27_in2;
    number expr_27_out1;
    number receive_59_output_number;
    list receive_59_output_list;
    number expr_28_in1;
    number expr_28_in2;
    number expr_28_out1;
    number freqshift_tilde_29_x;
    number freqshift_tilde_29_frequency;
    number freqshift_tilde_30_x;
    number freqshift_tilde_30_frequency;
    number receive_60_output_number;
    list receive_60_output_list;
    number receive_61_output_number;
    list receive_61_output_list;
    number receive_62_output_number;
    list receive_62_output_list;
    number expr_29_in1;
    number expr_29_in2;
    number expr_29_out1;
    number send_22_input_number;
    list send_22_input_list;
    number param_22_value;
    number receive_63_output_number;
    list receive_63_output_list;
    number expr_30_in1;
    number expr_30_in2;
    number expr_30_out1;
    number gaintilde_32_input_number;
    number gaintilde_32_value;
    number gaintilde_32_interp;
    number gaintilde_33_input_number;
    number gaintilde_33_value;
    number gaintilde_33_interp;
    number send_23_input_number;
    list send_23_input_list;
    number param_23_value;
    number send_24_input_number;
    list send_24_input_list;
    number param_24_value;
    number send_25_input_number;
    list send_25_input_list;
    number param_25_value;
    number receive_64_output_number;
    list receive_64_output_list;
    number freqshift_tilde_31_x;
    number freqshift_tilde_31_frequency;
    number freqshift_tilde_32_x;
    number freqshift_tilde_32_frequency;
    number receive_65_output_number;
    list receive_65_output_list;
    number gaintilde_34_input_number;
    number gaintilde_34_value;
    number gaintilde_34_interp;
    number gaintilde_35_input_number;
    number gaintilde_35_value;
    number gaintilde_35_interp;
    number receive_66_output_number;
    list receive_66_output_list;
    number expr_31_in1;
    number expr_31_in2;
    number expr_31_out1;
    number receive_67_output_number;
    list receive_67_output_list;
    number expr_32_in1;
    number expr_32_in2;
    number expr_32_out1;
    number freqshift_tilde_33_x;
    number freqshift_tilde_33_frequency;
    number freqshift_tilde_34_x;
    number freqshift_tilde_34_frequency;
    number receive_68_output_number;
    list receive_68_output_list;
    number receive_69_output_number;
    list receive_69_output_list;
    number expr_33_in1;
    number expr_33_in2;
    number expr_33_out1;
    number receive_70_output_number;
    list receive_70_output_list;
    number receive_71_output_number;
    list receive_71_output_list;
    number expr_34_in1;
    number expr_34_in2;
    number expr_34_out1;
    number gaintilde_36_input_number;
    number gaintilde_36_value;
    number gaintilde_36_interp;
    number gaintilde_37_input_number;
    number gaintilde_37_value;
    number gaintilde_37_interp;
    number receive_72_output_number;
    list receive_72_output_list;
    number receive_73_output_number;
    list receive_73_output_list;
    number freqshift_tilde_35_x;
    number freqshift_tilde_35_frequency;
    number freqshift_tilde_36_x;
    number freqshift_tilde_36_frequency;
    number gaintilde_38_input_number;
    number gaintilde_38_value;
    number gaintilde_38_interp;
    number gaintilde_39_input_number;
    number gaintilde_39_value;
    number gaintilde_39_interp;
    number receive_74_output_number;
    list receive_74_output_list;
    number expr_35_in1;
    number expr_35_in2;
    number expr_35_out1;
    number receive_75_output_number;
    list receive_75_output_list;
    number expr_36_in1;
    number expr_36_in2;
    number expr_36_out1;
    number freqshift_tilde_37_x;
    number freqshift_tilde_37_frequency;
    number freqshift_tilde_38_x;
    number freqshift_tilde_38_frequency;
    number receive_76_output_number;
    list receive_76_output_list;
    number expr_37_in1;
    number expr_37_in2;
    number expr_37_out1;
    number receive_77_output_number;
    list receive_77_output_list;
    number expr_38_in1;
    number expr_38_in2;
    number expr_38_out1;
    number receive_78_output_number;
    list receive_78_output_list;
    number gaintilde_40_input_number;
    number gaintilde_40_value;
    number gaintilde_40_interp;
    number send_26_input_number;
    list send_26_input_list;
    number param_26_value;
    number send_27_input_number;
    list send_27_input_list;
    number param_27_value;
    number send_28_input_number;
    list send_28_input_list;
    number param_28_value;
    number send_29_input_number;
    list send_29_input_list;
    number param_29_value;
    number freqshift_tilde_39_x;
    number freqshift_tilde_39_frequency;
    number receive_79_output_number;
    list receive_79_output_list;
    number expr_39_in1;
    number expr_39_in2;
    number expr_39_out1;
    number send_30_input_number;
    list send_30_input_list;
    number param_30_value;
    number send_31_input_number;
    list send_31_input_list;
    number param_31_value;
    number send_32_input_number;
    list send_32_input_list;
    number param_32_value;
    number send_33_input_number;
    list send_33_input_list;
    number param_33_value;
    number send_34_input_number;
    list send_34_input_list;
    number param_34_value;
    number send_35_input_number;
    list send_35_input_list;
    number param_35_value;
    number send_36_input_number;
    list send_36_input_list;
    number param_36_value;
    number send_37_input_number;
    list send_37_input_list;
    number param_37_value;
    number send_38_input_number;
    list send_38_input_list;
    number param_38_value;
    number send_39_input_number;
    list send_39_input_list;
    number param_39_value;
    number send_40_input_number;
    list send_40_input_list;
    number param_40_value;
    number send_41_input_number;
    list send_41_input_list;
    number param_41_value;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[41];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    SampleValue limi_01_lookaheadBuffers[1][512] = { };
    SampleValue limi_01_gainBuffer[512] = { };
    number limi_01_last;
    int limi_01_lookaheadIndex;
    number limi_01_recover;
    number limi_01_lookaheadInv;
    number limi_01_dc1_xm1;
    number limi_01_dc1_ym1;
    bool limi_01_setupDone;
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
    number gaintilde_02_lastValue;
    number gaintilde_02_loginc;
    number gaintilde_02_zval;
    number gaintilde_02_ramp_d_prev;
    number gaintilde_02_ramp_prev;
    number gaintilde_02_ramp_index;
    number gaintilde_02_ramp_increment;
    bool gaintilde_02_setupDone;
    number gaintilde_03_lastValue;
    number gaintilde_03_loginc;
    number gaintilde_03_zval;
    number gaintilde_03_ramp_d_prev;
    number gaintilde_03_ramp_prev;
    number gaintilde_03_ramp_index;
    number gaintilde_03_ramp_increment;
    bool gaintilde_03_setupDone;
    number gaintilde_04_lastValue;
    number gaintilde_04_loginc;
    number gaintilde_04_zval;
    number gaintilde_04_ramp_d_prev;
    number gaintilde_04_ramp_prev;
    number gaintilde_04_ramp_index;
    number gaintilde_04_ramp_increment;
    bool gaintilde_04_setupDone;
    number freqshift_tilde_01_h_biquad1_x1;
    number freqshift_tilde_01_h_biquad1_x2;
    number freqshift_tilde_01_h_biquad1_y1;
    number freqshift_tilde_01_h_biquad1_y2;
    number freqshift_tilde_01_h_biquad2_x1;
    number freqshift_tilde_01_h_biquad2_x2;
    number freqshift_tilde_01_h_biquad2_y1;
    number freqshift_tilde_01_h_biquad2_y2;
    number freqshift_tilde_01_h_biquad3_x1;
    number freqshift_tilde_01_h_biquad3_x2;
    number freqshift_tilde_01_h_biquad3_y1;
    number freqshift_tilde_01_h_biquad3_y2;
    number freqshift_tilde_01_h_biquad4_x1;
    number freqshift_tilde_01_h_biquad4_x2;
    number freqshift_tilde_01_h_biquad4_y1;
    number freqshift_tilde_01_h_biquad4_y2;
    number freqshift_tilde_01_h_biquad5_x1;
    number freqshift_tilde_01_h_biquad5_x2;
    number freqshift_tilde_01_h_biquad5_y1;
    number freqshift_tilde_01_h_biquad5_y2;
    number freqshift_tilde_01_h_biquad6_x1;
    number freqshift_tilde_01_h_biquad6_x2;
    number freqshift_tilde_01_h_biquad6_y1;
    number freqshift_tilde_01_h_biquad6_y2;
    number freqshift_tilde_01_p_currentPhase;
    number freqshift_tilde_01_p_conv;
    bool freqshift_tilde_01_setupDone;
    number param_10_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    number freqshift_tilde_02_h_biquad1_x1;
    number freqshift_tilde_02_h_biquad1_x2;
    number freqshift_tilde_02_h_biquad1_y1;
    number freqshift_tilde_02_h_biquad1_y2;
    number freqshift_tilde_02_h_biquad2_x1;
    number freqshift_tilde_02_h_biquad2_x2;
    number freqshift_tilde_02_h_biquad2_y1;
    number freqshift_tilde_02_h_biquad2_y2;
    number freqshift_tilde_02_h_biquad3_x1;
    number freqshift_tilde_02_h_biquad3_x2;
    number freqshift_tilde_02_h_biquad3_y1;
    number freqshift_tilde_02_h_biquad3_y2;
    number freqshift_tilde_02_h_biquad4_x1;
    number freqshift_tilde_02_h_biquad4_x2;
    number freqshift_tilde_02_h_biquad4_y1;
    number freqshift_tilde_02_h_biquad4_y2;
    number freqshift_tilde_02_h_biquad5_x1;
    number freqshift_tilde_02_h_biquad5_x2;
    number freqshift_tilde_02_h_biquad5_y1;
    number freqshift_tilde_02_h_biquad5_y2;
    number freqshift_tilde_02_h_biquad6_x1;
    number freqshift_tilde_02_h_biquad6_x2;
    number freqshift_tilde_02_h_biquad6_y1;
    number freqshift_tilde_02_h_biquad6_y2;
    number freqshift_tilde_02_p_currentPhase;
    number freqshift_tilde_02_p_conv;
    bool freqshift_tilde_02_setupDone;
    number param_13_lastValue;
    number freqshift_tilde_03_h_biquad1_x1;
    number freqshift_tilde_03_h_biquad1_x2;
    number freqshift_tilde_03_h_biquad1_y1;
    number freqshift_tilde_03_h_biquad1_y2;
    number freqshift_tilde_03_h_biquad2_x1;
    number freqshift_tilde_03_h_biquad2_x2;
    number freqshift_tilde_03_h_biquad2_y1;
    number freqshift_tilde_03_h_biquad2_y2;
    number freqshift_tilde_03_h_biquad3_x1;
    number freqshift_tilde_03_h_biquad3_x2;
    number freqshift_tilde_03_h_biquad3_y1;
    number freqshift_tilde_03_h_biquad3_y2;
    number freqshift_tilde_03_h_biquad4_x1;
    number freqshift_tilde_03_h_biquad4_x2;
    number freqshift_tilde_03_h_biquad4_y1;
    number freqshift_tilde_03_h_biquad4_y2;
    number freqshift_tilde_03_h_biquad5_x1;
    number freqshift_tilde_03_h_biquad5_x2;
    number freqshift_tilde_03_h_biquad5_y1;
    number freqshift_tilde_03_h_biquad5_y2;
    number freqshift_tilde_03_h_biquad6_x1;
    number freqshift_tilde_03_h_biquad6_x2;
    number freqshift_tilde_03_h_biquad6_y1;
    number freqshift_tilde_03_h_biquad6_y2;
    number freqshift_tilde_03_p_currentPhase;
    number freqshift_tilde_03_p_conv;
    bool freqshift_tilde_03_setupDone;
    number freqshift_tilde_04_h_biquad1_x1;
    number freqshift_tilde_04_h_biquad1_x2;
    number freqshift_tilde_04_h_biquad1_y1;
    number freqshift_tilde_04_h_biquad1_y2;
    number freqshift_tilde_04_h_biquad2_x1;
    number freqshift_tilde_04_h_biquad2_x2;
    number freqshift_tilde_04_h_biquad2_y1;
    number freqshift_tilde_04_h_biquad2_y2;
    number freqshift_tilde_04_h_biquad3_x1;
    number freqshift_tilde_04_h_biquad3_x2;
    number freqshift_tilde_04_h_biquad3_y1;
    number freqshift_tilde_04_h_biquad3_y2;
    number freqshift_tilde_04_h_biquad4_x1;
    number freqshift_tilde_04_h_biquad4_x2;
    number freqshift_tilde_04_h_biquad4_y1;
    number freqshift_tilde_04_h_biquad4_y2;
    number freqshift_tilde_04_h_biquad5_x1;
    number freqshift_tilde_04_h_biquad5_x2;
    number freqshift_tilde_04_h_biquad5_y1;
    number freqshift_tilde_04_h_biquad5_y2;
    number freqshift_tilde_04_h_biquad6_x1;
    number freqshift_tilde_04_h_biquad6_x2;
    number freqshift_tilde_04_h_biquad6_y1;
    number freqshift_tilde_04_h_biquad6_y2;
    number freqshift_tilde_04_p_currentPhase;
    number freqshift_tilde_04_p_conv;
    bool freqshift_tilde_04_setupDone;
    number gaintilde_05_lastValue;
    number gaintilde_05_loginc;
    number gaintilde_05_zval;
    number gaintilde_05_ramp_d_prev;
    number gaintilde_05_ramp_prev;
    number gaintilde_05_ramp_index;
    number gaintilde_05_ramp_increment;
    bool gaintilde_05_setupDone;
    number gaintilde_06_lastValue;
    number gaintilde_06_loginc;
    number gaintilde_06_zval;
    number gaintilde_06_ramp_d_prev;
    number gaintilde_06_ramp_prev;
    number gaintilde_06_ramp_index;
    number gaintilde_06_ramp_increment;
    bool gaintilde_06_setupDone;
    number gaintilde_07_lastValue;
    number gaintilde_07_loginc;
    number gaintilde_07_zval;
    number gaintilde_07_ramp_d_prev;
    number gaintilde_07_ramp_prev;
    number gaintilde_07_ramp_index;
    number gaintilde_07_ramp_increment;
    bool gaintilde_07_setupDone;
    number gaintilde_08_lastValue;
    number gaintilde_08_loginc;
    number gaintilde_08_zval;
    number gaintilde_08_ramp_d_prev;
    number gaintilde_08_ramp_prev;
    number gaintilde_08_ramp_index;
    number gaintilde_08_ramp_increment;
    bool gaintilde_08_setupDone;
    number freqshift_tilde_05_h_biquad1_x1;
    number freqshift_tilde_05_h_biquad1_x2;
    number freqshift_tilde_05_h_biquad1_y1;
    number freqshift_tilde_05_h_biquad1_y2;
    number freqshift_tilde_05_h_biquad2_x1;
    number freqshift_tilde_05_h_biquad2_x2;
    number freqshift_tilde_05_h_biquad2_y1;
    number freqshift_tilde_05_h_biquad2_y2;
    number freqshift_tilde_05_h_biquad3_x1;
    number freqshift_tilde_05_h_biquad3_x2;
    number freqshift_tilde_05_h_biquad3_y1;
    number freqshift_tilde_05_h_biquad3_y2;
    number freqshift_tilde_05_h_biquad4_x1;
    number freqshift_tilde_05_h_biquad4_x2;
    number freqshift_tilde_05_h_biquad4_y1;
    number freqshift_tilde_05_h_biquad4_y2;
    number freqshift_tilde_05_h_biquad5_x1;
    number freqshift_tilde_05_h_biquad5_x2;
    number freqshift_tilde_05_h_biquad5_y1;
    number freqshift_tilde_05_h_biquad5_y2;
    number freqshift_tilde_05_h_biquad6_x1;
    number freqshift_tilde_05_h_biquad6_x2;
    number freqshift_tilde_05_h_biquad6_y1;
    number freqshift_tilde_05_h_biquad6_y2;
    number freqshift_tilde_05_p_currentPhase;
    number freqshift_tilde_05_p_conv;
    bool freqshift_tilde_05_setupDone;
    number freqshift_tilde_06_h_biquad1_x1;
    number freqshift_tilde_06_h_biquad1_x2;
    number freqshift_tilde_06_h_biquad1_y1;
    number freqshift_tilde_06_h_biquad1_y2;
    number freqshift_tilde_06_h_biquad2_x1;
    number freqshift_tilde_06_h_biquad2_x2;
    number freqshift_tilde_06_h_biquad2_y1;
    number freqshift_tilde_06_h_biquad2_y2;
    number freqshift_tilde_06_h_biquad3_x1;
    number freqshift_tilde_06_h_biquad3_x2;
    number freqshift_tilde_06_h_biquad3_y1;
    number freqshift_tilde_06_h_biquad3_y2;
    number freqshift_tilde_06_h_biquad4_x1;
    number freqshift_tilde_06_h_biquad4_x2;
    number freqshift_tilde_06_h_biquad4_y1;
    number freqshift_tilde_06_h_biquad4_y2;
    number freqshift_tilde_06_h_biquad5_x1;
    number freqshift_tilde_06_h_biquad5_x2;
    number freqshift_tilde_06_h_biquad5_y1;
    number freqshift_tilde_06_h_biquad5_y2;
    number freqshift_tilde_06_h_biquad6_x1;
    number freqshift_tilde_06_h_biquad6_x2;
    number freqshift_tilde_06_h_biquad6_y1;
    number freqshift_tilde_06_h_biquad6_y2;
    number freqshift_tilde_06_p_currentPhase;
    number freqshift_tilde_06_p_conv;
    bool freqshift_tilde_06_setupDone;
    number freqshift_tilde_07_h_biquad1_x1;
    number freqshift_tilde_07_h_biquad1_x2;
    number freqshift_tilde_07_h_biquad1_y1;
    number freqshift_tilde_07_h_biquad1_y2;
    number freqshift_tilde_07_h_biquad2_x1;
    number freqshift_tilde_07_h_biquad2_x2;
    number freqshift_tilde_07_h_biquad2_y1;
    number freqshift_tilde_07_h_biquad2_y2;
    number freqshift_tilde_07_h_biquad3_x1;
    number freqshift_tilde_07_h_biquad3_x2;
    number freqshift_tilde_07_h_biquad3_y1;
    number freqshift_tilde_07_h_biquad3_y2;
    number freqshift_tilde_07_h_biquad4_x1;
    number freqshift_tilde_07_h_biquad4_x2;
    number freqshift_tilde_07_h_biquad4_y1;
    number freqshift_tilde_07_h_biquad4_y2;
    number freqshift_tilde_07_h_biquad5_x1;
    number freqshift_tilde_07_h_biquad5_x2;
    number freqshift_tilde_07_h_biquad5_y1;
    number freqshift_tilde_07_h_biquad5_y2;
    number freqshift_tilde_07_h_biquad6_x1;
    number freqshift_tilde_07_h_biquad6_x2;
    number freqshift_tilde_07_h_biquad6_y1;
    number freqshift_tilde_07_h_biquad6_y2;
    number freqshift_tilde_07_p_currentPhase;
    number freqshift_tilde_07_p_conv;
    bool freqshift_tilde_07_setupDone;
    number gaintilde_09_lastValue;
    number gaintilde_09_loginc;
    number gaintilde_09_zval;
    number gaintilde_09_ramp_d_prev;
    number gaintilde_09_ramp_prev;
    number gaintilde_09_ramp_index;
    number gaintilde_09_ramp_increment;
    bool gaintilde_09_setupDone;
    number freqshift_tilde_08_h_biquad1_x1;
    number freqshift_tilde_08_h_biquad1_x2;
    number freqshift_tilde_08_h_biquad1_y1;
    number freqshift_tilde_08_h_biquad1_y2;
    number freqshift_tilde_08_h_biquad2_x1;
    number freqshift_tilde_08_h_biquad2_x2;
    number freqshift_tilde_08_h_biquad2_y1;
    number freqshift_tilde_08_h_biquad2_y2;
    number freqshift_tilde_08_h_biquad3_x1;
    number freqshift_tilde_08_h_biquad3_x2;
    number freqshift_tilde_08_h_biquad3_y1;
    number freqshift_tilde_08_h_biquad3_y2;
    number freqshift_tilde_08_h_biquad4_x1;
    number freqshift_tilde_08_h_biquad4_x2;
    number freqshift_tilde_08_h_biquad4_y1;
    number freqshift_tilde_08_h_biquad4_y2;
    number freqshift_tilde_08_h_biquad5_x1;
    number freqshift_tilde_08_h_biquad5_x2;
    number freqshift_tilde_08_h_biquad5_y1;
    number freqshift_tilde_08_h_biquad5_y2;
    number freqshift_tilde_08_h_biquad6_x1;
    number freqshift_tilde_08_h_biquad6_x2;
    number freqshift_tilde_08_h_biquad6_y1;
    number freqshift_tilde_08_h_biquad6_y2;
    number freqshift_tilde_08_p_currentPhase;
    number freqshift_tilde_08_p_conv;
    bool freqshift_tilde_08_setupDone;
    number gaintilde_10_lastValue;
    number gaintilde_10_loginc;
    number gaintilde_10_zval;
    number gaintilde_10_ramp_d_prev;
    number gaintilde_10_ramp_prev;
    number gaintilde_10_ramp_index;
    number gaintilde_10_ramp_increment;
    bool gaintilde_10_setupDone;
    number gaintilde_11_lastValue;
    number gaintilde_11_loginc;
    number gaintilde_11_zval;
    number gaintilde_11_ramp_d_prev;
    number gaintilde_11_ramp_prev;
    number gaintilde_11_ramp_index;
    number gaintilde_11_ramp_increment;
    bool gaintilde_11_setupDone;
    number gaintilde_12_lastValue;
    number gaintilde_12_loginc;
    number gaintilde_12_zval;
    number gaintilde_12_ramp_d_prev;
    number gaintilde_12_ramp_prev;
    number gaintilde_12_ramp_index;
    number gaintilde_12_ramp_increment;
    bool gaintilde_12_setupDone;
    number freqshift_tilde_09_h_biquad1_x1;
    number freqshift_tilde_09_h_biquad1_x2;
    number freqshift_tilde_09_h_biquad1_y1;
    number freqshift_tilde_09_h_biquad1_y2;
    number freqshift_tilde_09_h_biquad2_x1;
    number freqshift_tilde_09_h_biquad2_x2;
    number freqshift_tilde_09_h_biquad2_y1;
    number freqshift_tilde_09_h_biquad2_y2;
    number freqshift_tilde_09_h_biquad3_x1;
    number freqshift_tilde_09_h_biquad3_x2;
    number freqshift_tilde_09_h_biquad3_y1;
    number freqshift_tilde_09_h_biquad3_y2;
    number freqshift_tilde_09_h_biquad4_x1;
    number freqshift_tilde_09_h_biquad4_x2;
    number freqshift_tilde_09_h_biquad4_y1;
    number freqshift_tilde_09_h_biquad4_y2;
    number freqshift_tilde_09_h_biquad5_x1;
    number freqshift_tilde_09_h_biquad5_x2;
    number freqshift_tilde_09_h_biquad5_y1;
    number freqshift_tilde_09_h_biquad5_y2;
    number freqshift_tilde_09_h_biquad6_x1;
    number freqshift_tilde_09_h_biquad6_x2;
    number freqshift_tilde_09_h_biquad6_y1;
    number freqshift_tilde_09_h_biquad6_y2;
    number freqshift_tilde_09_p_currentPhase;
    number freqshift_tilde_09_p_conv;
    bool freqshift_tilde_09_setupDone;
    number freqshift_tilde_10_h_biquad1_x1;
    number freqshift_tilde_10_h_biquad1_x2;
    number freqshift_tilde_10_h_biquad1_y1;
    number freqshift_tilde_10_h_biquad1_y2;
    number freqshift_tilde_10_h_biquad2_x1;
    number freqshift_tilde_10_h_biquad2_x2;
    number freqshift_tilde_10_h_biquad2_y1;
    number freqshift_tilde_10_h_biquad2_y2;
    number freqshift_tilde_10_h_biquad3_x1;
    number freqshift_tilde_10_h_biquad3_x2;
    number freqshift_tilde_10_h_biquad3_y1;
    number freqshift_tilde_10_h_biquad3_y2;
    number freqshift_tilde_10_h_biquad4_x1;
    number freqshift_tilde_10_h_biquad4_x2;
    number freqshift_tilde_10_h_biquad4_y1;
    number freqshift_tilde_10_h_biquad4_y2;
    number freqshift_tilde_10_h_biquad5_x1;
    number freqshift_tilde_10_h_biquad5_x2;
    number freqshift_tilde_10_h_biquad5_y1;
    number freqshift_tilde_10_h_biquad5_y2;
    number freqshift_tilde_10_h_biquad6_x1;
    number freqshift_tilde_10_h_biquad6_x2;
    number freqshift_tilde_10_h_biquad6_y1;
    number freqshift_tilde_10_h_biquad6_y2;
    number freqshift_tilde_10_p_currentPhase;
    number freqshift_tilde_10_p_conv;
    bool freqshift_tilde_10_setupDone;
    number freqshift_tilde_11_h_biquad1_x1;
    number freqshift_tilde_11_h_biquad1_x2;
    number freqshift_tilde_11_h_biquad1_y1;
    number freqshift_tilde_11_h_biquad1_y2;
    number freqshift_tilde_11_h_biquad2_x1;
    number freqshift_tilde_11_h_biquad2_x2;
    number freqshift_tilde_11_h_biquad2_y1;
    number freqshift_tilde_11_h_biquad2_y2;
    number freqshift_tilde_11_h_biquad3_x1;
    number freqshift_tilde_11_h_biquad3_x2;
    number freqshift_tilde_11_h_biquad3_y1;
    number freqshift_tilde_11_h_biquad3_y2;
    number freqshift_tilde_11_h_biquad4_x1;
    number freqshift_tilde_11_h_biquad4_x2;
    number freqshift_tilde_11_h_biquad4_y1;
    number freqshift_tilde_11_h_biquad4_y2;
    number freqshift_tilde_11_h_biquad5_x1;
    number freqshift_tilde_11_h_biquad5_x2;
    number freqshift_tilde_11_h_biquad5_y1;
    number freqshift_tilde_11_h_biquad5_y2;
    number freqshift_tilde_11_h_biquad6_x1;
    number freqshift_tilde_11_h_biquad6_x2;
    number freqshift_tilde_11_h_biquad6_y1;
    number freqshift_tilde_11_h_biquad6_y2;
    number freqshift_tilde_11_p_currentPhase;
    number freqshift_tilde_11_p_conv;
    bool freqshift_tilde_11_setupDone;
    number gaintilde_13_lastValue;
    number gaintilde_13_loginc;
    number gaintilde_13_zval;
    number gaintilde_13_ramp_d_prev;
    number gaintilde_13_ramp_prev;
    number gaintilde_13_ramp_index;
    number gaintilde_13_ramp_increment;
    bool gaintilde_13_setupDone;
    number param_14_lastValue;
    number param_15_lastValue;
    number freqshift_tilde_12_h_biquad1_x1;
    number freqshift_tilde_12_h_biquad1_x2;
    number freqshift_tilde_12_h_biquad1_y1;
    number freqshift_tilde_12_h_biquad1_y2;
    number freqshift_tilde_12_h_biquad2_x1;
    number freqshift_tilde_12_h_biquad2_x2;
    number freqshift_tilde_12_h_biquad2_y1;
    number freqshift_tilde_12_h_biquad2_y2;
    number freqshift_tilde_12_h_biquad3_x1;
    number freqshift_tilde_12_h_biquad3_x2;
    number freqshift_tilde_12_h_biquad3_y1;
    number freqshift_tilde_12_h_biquad3_y2;
    number freqshift_tilde_12_h_biquad4_x1;
    number freqshift_tilde_12_h_biquad4_x2;
    number freqshift_tilde_12_h_biquad4_y1;
    number freqshift_tilde_12_h_biquad4_y2;
    number freqshift_tilde_12_h_biquad5_x1;
    number freqshift_tilde_12_h_biquad5_x2;
    number freqshift_tilde_12_h_biquad5_y1;
    number freqshift_tilde_12_h_biquad5_y2;
    number freqshift_tilde_12_h_biquad6_x1;
    number freqshift_tilde_12_h_biquad6_x2;
    number freqshift_tilde_12_h_biquad6_y1;
    number freqshift_tilde_12_h_biquad6_y2;
    number freqshift_tilde_12_p_currentPhase;
    number freqshift_tilde_12_p_conv;
    bool freqshift_tilde_12_setupDone;
    number param_16_lastValue;
    number param_17_lastValue;
    number gaintilde_14_lastValue;
    number gaintilde_14_loginc;
    number gaintilde_14_zval;
    number gaintilde_14_ramp_d_prev;
    number gaintilde_14_ramp_prev;
    number gaintilde_14_ramp_index;
    number gaintilde_14_ramp_increment;
    bool gaintilde_14_setupDone;
    number gaintilde_15_lastValue;
    number gaintilde_15_loginc;
    number gaintilde_15_zval;
    number gaintilde_15_ramp_d_prev;
    number gaintilde_15_ramp_prev;
    number gaintilde_15_ramp_index;
    number gaintilde_15_ramp_increment;
    bool gaintilde_15_setupDone;
    number gaintilde_16_lastValue;
    number gaintilde_16_loginc;
    number gaintilde_16_zval;
    number gaintilde_16_ramp_d_prev;
    number gaintilde_16_ramp_prev;
    number gaintilde_16_ramp_index;
    number gaintilde_16_ramp_increment;
    bool gaintilde_16_setupDone;
    number freqshift_tilde_13_h_biquad1_x1;
    number freqshift_tilde_13_h_biquad1_x2;
    number freqshift_tilde_13_h_biquad1_y1;
    number freqshift_tilde_13_h_biquad1_y2;
    number freqshift_tilde_13_h_biquad2_x1;
    number freqshift_tilde_13_h_biquad2_x2;
    number freqshift_tilde_13_h_biquad2_y1;
    number freqshift_tilde_13_h_biquad2_y2;
    number freqshift_tilde_13_h_biquad3_x1;
    number freqshift_tilde_13_h_biquad3_x2;
    number freqshift_tilde_13_h_biquad3_y1;
    number freqshift_tilde_13_h_biquad3_y2;
    number freqshift_tilde_13_h_biquad4_x1;
    number freqshift_tilde_13_h_biquad4_x2;
    number freqshift_tilde_13_h_biquad4_y1;
    number freqshift_tilde_13_h_biquad4_y2;
    number freqshift_tilde_13_h_biquad5_x1;
    number freqshift_tilde_13_h_biquad5_x2;
    number freqshift_tilde_13_h_biquad5_y1;
    number freqshift_tilde_13_h_biquad5_y2;
    number freqshift_tilde_13_h_biquad6_x1;
    number freqshift_tilde_13_h_biquad6_x2;
    number freqshift_tilde_13_h_biquad6_y1;
    number freqshift_tilde_13_h_biquad6_y2;
    number freqshift_tilde_13_p_currentPhase;
    number freqshift_tilde_13_p_conv;
    bool freqshift_tilde_13_setupDone;
    number freqshift_tilde_14_h_biquad1_x1;
    number freqshift_tilde_14_h_biquad1_x2;
    number freqshift_tilde_14_h_biquad1_y1;
    number freqshift_tilde_14_h_biquad1_y2;
    number freqshift_tilde_14_h_biquad2_x1;
    number freqshift_tilde_14_h_biquad2_x2;
    number freqshift_tilde_14_h_biquad2_y1;
    number freqshift_tilde_14_h_biquad2_y2;
    number freqshift_tilde_14_h_biquad3_x1;
    number freqshift_tilde_14_h_biquad3_x2;
    number freqshift_tilde_14_h_biquad3_y1;
    number freqshift_tilde_14_h_biquad3_y2;
    number freqshift_tilde_14_h_biquad4_x1;
    number freqshift_tilde_14_h_biquad4_x2;
    number freqshift_tilde_14_h_biquad4_y1;
    number freqshift_tilde_14_h_biquad4_y2;
    number freqshift_tilde_14_h_biquad5_x1;
    number freqshift_tilde_14_h_biquad5_x2;
    number freqshift_tilde_14_h_biquad5_y1;
    number freqshift_tilde_14_h_biquad5_y2;
    number freqshift_tilde_14_h_biquad6_x1;
    number freqshift_tilde_14_h_biquad6_x2;
    number freqshift_tilde_14_h_biquad6_y1;
    number freqshift_tilde_14_h_biquad6_y2;
    number freqshift_tilde_14_p_currentPhase;
    number freqshift_tilde_14_p_conv;
    bool freqshift_tilde_14_setupDone;
    number gaintilde_17_lastValue;
    number gaintilde_17_loginc;
    number gaintilde_17_zval;
    number gaintilde_17_ramp_d_prev;
    number gaintilde_17_ramp_prev;
    number gaintilde_17_ramp_index;
    number gaintilde_17_ramp_increment;
    bool gaintilde_17_setupDone;
    number freqshift_tilde_15_h_biquad1_x1;
    number freqshift_tilde_15_h_biquad1_x2;
    number freqshift_tilde_15_h_biquad1_y1;
    number freqshift_tilde_15_h_biquad1_y2;
    number freqshift_tilde_15_h_biquad2_x1;
    number freqshift_tilde_15_h_biquad2_x2;
    number freqshift_tilde_15_h_biquad2_y1;
    number freqshift_tilde_15_h_biquad2_y2;
    number freqshift_tilde_15_h_biquad3_x1;
    number freqshift_tilde_15_h_biquad3_x2;
    number freqshift_tilde_15_h_biquad3_y1;
    number freqshift_tilde_15_h_biquad3_y2;
    number freqshift_tilde_15_h_biquad4_x1;
    number freqshift_tilde_15_h_biquad4_x2;
    number freqshift_tilde_15_h_biquad4_y1;
    number freqshift_tilde_15_h_biquad4_y2;
    number freqshift_tilde_15_h_biquad5_x1;
    number freqshift_tilde_15_h_biquad5_x2;
    number freqshift_tilde_15_h_biquad5_y1;
    number freqshift_tilde_15_h_biquad5_y2;
    number freqshift_tilde_15_h_biquad6_x1;
    number freqshift_tilde_15_h_biquad6_x2;
    number freqshift_tilde_15_h_biquad6_y1;
    number freqshift_tilde_15_h_biquad6_y2;
    number freqshift_tilde_15_p_currentPhase;
    number freqshift_tilde_15_p_conv;
    bool freqshift_tilde_15_setupDone;
    number freqshift_tilde_16_h_biquad1_x1;
    number freqshift_tilde_16_h_biquad1_x2;
    number freqshift_tilde_16_h_biquad1_y1;
    number freqshift_tilde_16_h_biquad1_y2;
    number freqshift_tilde_16_h_biquad2_x1;
    number freqshift_tilde_16_h_biquad2_x2;
    number freqshift_tilde_16_h_biquad2_y1;
    number freqshift_tilde_16_h_biquad2_y2;
    number freqshift_tilde_16_h_biquad3_x1;
    number freqshift_tilde_16_h_biquad3_x2;
    number freqshift_tilde_16_h_biquad3_y1;
    number freqshift_tilde_16_h_biquad3_y2;
    number freqshift_tilde_16_h_biquad4_x1;
    number freqshift_tilde_16_h_biquad4_x2;
    number freqshift_tilde_16_h_biquad4_y1;
    number freqshift_tilde_16_h_biquad4_y2;
    number freqshift_tilde_16_h_biquad5_x1;
    number freqshift_tilde_16_h_biquad5_x2;
    number freqshift_tilde_16_h_biquad5_y1;
    number freqshift_tilde_16_h_biquad5_y2;
    number freqshift_tilde_16_h_biquad6_x1;
    number freqshift_tilde_16_h_biquad6_x2;
    number freqshift_tilde_16_h_biquad6_y1;
    number freqshift_tilde_16_h_biquad6_y2;
    number freqshift_tilde_16_p_currentPhase;
    number freqshift_tilde_16_p_conv;
    bool freqshift_tilde_16_setupDone;
    number gaintilde_18_lastValue;
    number gaintilde_18_loginc;
    number gaintilde_18_zval;
    number gaintilde_18_ramp_d_prev;
    number gaintilde_18_ramp_prev;
    number gaintilde_18_ramp_index;
    number gaintilde_18_ramp_increment;
    bool gaintilde_18_setupDone;
    number gaintilde_19_lastValue;
    number gaintilde_19_loginc;
    number gaintilde_19_zval;
    number gaintilde_19_ramp_d_prev;
    number gaintilde_19_ramp_prev;
    number gaintilde_19_ramp_index;
    number gaintilde_19_ramp_increment;
    bool gaintilde_19_setupDone;
    number freqshift_tilde_17_h_biquad1_x1;
    number freqshift_tilde_17_h_biquad1_x2;
    number freqshift_tilde_17_h_biquad1_y1;
    number freqshift_tilde_17_h_biquad1_y2;
    number freqshift_tilde_17_h_biquad2_x1;
    number freqshift_tilde_17_h_biquad2_x2;
    number freqshift_tilde_17_h_biquad2_y1;
    number freqshift_tilde_17_h_biquad2_y2;
    number freqshift_tilde_17_h_biquad3_x1;
    number freqshift_tilde_17_h_biquad3_x2;
    number freqshift_tilde_17_h_biquad3_y1;
    number freqshift_tilde_17_h_biquad3_y2;
    number freqshift_tilde_17_h_biquad4_x1;
    number freqshift_tilde_17_h_biquad4_x2;
    number freqshift_tilde_17_h_biquad4_y1;
    number freqshift_tilde_17_h_biquad4_y2;
    number freqshift_tilde_17_h_biquad5_x1;
    number freqshift_tilde_17_h_biquad5_x2;
    number freqshift_tilde_17_h_biquad5_y1;
    number freqshift_tilde_17_h_biquad5_y2;
    number freqshift_tilde_17_h_biquad6_x1;
    number freqshift_tilde_17_h_biquad6_x2;
    number freqshift_tilde_17_h_biquad6_y1;
    number freqshift_tilde_17_h_biquad6_y2;
    number freqshift_tilde_17_p_currentPhase;
    number freqshift_tilde_17_p_conv;
    bool freqshift_tilde_17_setupDone;
    number freqshift_tilde_18_h_biquad1_x1;
    number freqshift_tilde_18_h_biquad1_x2;
    number freqshift_tilde_18_h_biquad1_y1;
    number freqshift_tilde_18_h_biquad1_y2;
    number freqshift_tilde_18_h_biquad2_x1;
    number freqshift_tilde_18_h_biquad2_x2;
    number freqshift_tilde_18_h_biquad2_y1;
    number freqshift_tilde_18_h_biquad2_y2;
    number freqshift_tilde_18_h_biquad3_x1;
    number freqshift_tilde_18_h_biquad3_x2;
    number freqshift_tilde_18_h_biquad3_y1;
    number freqshift_tilde_18_h_biquad3_y2;
    number freqshift_tilde_18_h_biquad4_x1;
    number freqshift_tilde_18_h_biquad4_x2;
    number freqshift_tilde_18_h_biquad4_y1;
    number freqshift_tilde_18_h_biquad4_y2;
    number freqshift_tilde_18_h_biquad5_x1;
    number freqshift_tilde_18_h_biquad5_x2;
    number freqshift_tilde_18_h_biquad5_y1;
    number freqshift_tilde_18_h_biquad5_y2;
    number freqshift_tilde_18_h_biquad6_x1;
    number freqshift_tilde_18_h_biquad6_x2;
    number freqshift_tilde_18_h_biquad6_y1;
    number freqshift_tilde_18_h_biquad6_y2;
    number freqshift_tilde_18_p_currentPhase;
    number freqshift_tilde_18_p_conv;
    bool freqshift_tilde_18_setupDone;
    number gaintilde_20_lastValue;
    number gaintilde_20_loginc;
    number gaintilde_20_zval;
    number gaintilde_20_ramp_d_prev;
    number gaintilde_20_ramp_prev;
    number gaintilde_20_ramp_index;
    number gaintilde_20_ramp_increment;
    bool gaintilde_20_setupDone;
    number gaintilde_21_lastValue;
    number gaintilde_21_loginc;
    number gaintilde_21_zval;
    number gaintilde_21_ramp_d_prev;
    number gaintilde_21_ramp_prev;
    number gaintilde_21_ramp_index;
    number gaintilde_21_ramp_increment;
    bool gaintilde_21_setupDone;
    number freqshift_tilde_19_h_biquad1_x1;
    number freqshift_tilde_19_h_biquad1_x2;
    number freqshift_tilde_19_h_biquad1_y1;
    number freqshift_tilde_19_h_biquad1_y2;
    number freqshift_tilde_19_h_biquad2_x1;
    number freqshift_tilde_19_h_biquad2_x2;
    number freqshift_tilde_19_h_biquad2_y1;
    number freqshift_tilde_19_h_biquad2_y2;
    number freqshift_tilde_19_h_biquad3_x1;
    number freqshift_tilde_19_h_biquad3_x2;
    number freqshift_tilde_19_h_biquad3_y1;
    number freqshift_tilde_19_h_biquad3_y2;
    number freqshift_tilde_19_h_biquad4_x1;
    number freqshift_tilde_19_h_biquad4_x2;
    number freqshift_tilde_19_h_biquad4_y1;
    number freqshift_tilde_19_h_biquad4_y2;
    number freqshift_tilde_19_h_biquad5_x1;
    number freqshift_tilde_19_h_biquad5_x2;
    number freqshift_tilde_19_h_biquad5_y1;
    number freqshift_tilde_19_h_biquad5_y2;
    number freqshift_tilde_19_h_biquad6_x1;
    number freqshift_tilde_19_h_biquad6_x2;
    number freqshift_tilde_19_h_biquad6_y1;
    number freqshift_tilde_19_h_biquad6_y2;
    number freqshift_tilde_19_p_currentPhase;
    number freqshift_tilde_19_p_conv;
    bool freqshift_tilde_19_setupDone;
    number freqshift_tilde_20_h_biquad1_x1;
    number freqshift_tilde_20_h_biquad1_x2;
    number freqshift_tilde_20_h_biquad1_y1;
    number freqshift_tilde_20_h_biquad1_y2;
    number freqshift_tilde_20_h_biquad2_x1;
    number freqshift_tilde_20_h_biquad2_x2;
    number freqshift_tilde_20_h_biquad2_y1;
    number freqshift_tilde_20_h_biquad2_y2;
    number freqshift_tilde_20_h_biquad3_x1;
    number freqshift_tilde_20_h_biquad3_x2;
    number freqshift_tilde_20_h_biquad3_y1;
    number freqshift_tilde_20_h_biquad3_y2;
    number freqshift_tilde_20_h_biquad4_x1;
    number freqshift_tilde_20_h_biquad4_x2;
    number freqshift_tilde_20_h_biquad4_y1;
    number freqshift_tilde_20_h_biquad4_y2;
    number freqshift_tilde_20_h_biquad5_x1;
    number freqshift_tilde_20_h_biquad5_x2;
    number freqshift_tilde_20_h_biquad5_y1;
    number freqshift_tilde_20_h_biquad5_y2;
    number freqshift_tilde_20_h_biquad6_x1;
    number freqshift_tilde_20_h_biquad6_x2;
    number freqshift_tilde_20_h_biquad6_y1;
    number freqshift_tilde_20_h_biquad6_y2;
    number freqshift_tilde_20_p_currentPhase;
    number freqshift_tilde_20_p_conv;
    bool freqshift_tilde_20_setupDone;
    number gaintilde_22_lastValue;
    number gaintilde_22_loginc;
    number gaintilde_22_zval;
    number gaintilde_22_ramp_d_prev;
    number gaintilde_22_ramp_prev;
    number gaintilde_22_ramp_index;
    number gaintilde_22_ramp_increment;
    bool gaintilde_22_setupDone;
    number gaintilde_23_lastValue;
    number gaintilde_23_loginc;
    number gaintilde_23_zval;
    number gaintilde_23_ramp_d_prev;
    number gaintilde_23_ramp_prev;
    number gaintilde_23_ramp_index;
    number gaintilde_23_ramp_increment;
    bool gaintilde_23_setupDone;
    number param_18_lastValue;
    number param_19_lastValue;
    number freqshift_tilde_21_h_biquad1_x1;
    number freqshift_tilde_21_h_biquad1_x2;
    number freqshift_tilde_21_h_biquad1_y1;
    number freqshift_tilde_21_h_biquad1_y2;
    number freqshift_tilde_21_h_biquad2_x1;
    number freqshift_tilde_21_h_biquad2_x2;
    number freqshift_tilde_21_h_biquad2_y1;
    number freqshift_tilde_21_h_biquad2_y2;
    number freqshift_tilde_21_h_biquad3_x1;
    number freqshift_tilde_21_h_biquad3_x2;
    number freqshift_tilde_21_h_biquad3_y1;
    number freqshift_tilde_21_h_biquad3_y2;
    number freqshift_tilde_21_h_biquad4_x1;
    number freqshift_tilde_21_h_biquad4_x2;
    number freqshift_tilde_21_h_biquad4_y1;
    number freqshift_tilde_21_h_biquad4_y2;
    number freqshift_tilde_21_h_biquad5_x1;
    number freqshift_tilde_21_h_biquad5_x2;
    number freqshift_tilde_21_h_biquad5_y1;
    number freqshift_tilde_21_h_biquad5_y2;
    number freqshift_tilde_21_h_biquad6_x1;
    number freqshift_tilde_21_h_biquad6_x2;
    number freqshift_tilde_21_h_biquad6_y1;
    number freqshift_tilde_21_h_biquad6_y2;
    number freqshift_tilde_21_p_currentPhase;
    number freqshift_tilde_21_p_conv;
    bool freqshift_tilde_21_setupDone;
    number param_20_lastValue;
    number freqshift_tilde_22_h_biquad1_x1;
    number freqshift_tilde_22_h_biquad1_x2;
    number freqshift_tilde_22_h_biquad1_y1;
    number freqshift_tilde_22_h_biquad1_y2;
    number freqshift_tilde_22_h_biquad2_x1;
    number freqshift_tilde_22_h_biquad2_x2;
    number freqshift_tilde_22_h_biquad2_y1;
    number freqshift_tilde_22_h_biquad2_y2;
    number freqshift_tilde_22_h_biquad3_x1;
    number freqshift_tilde_22_h_biquad3_x2;
    number freqshift_tilde_22_h_biquad3_y1;
    number freqshift_tilde_22_h_biquad3_y2;
    number freqshift_tilde_22_h_biquad4_x1;
    number freqshift_tilde_22_h_biquad4_x2;
    number freqshift_tilde_22_h_biquad4_y1;
    number freqshift_tilde_22_h_biquad4_y2;
    number freqshift_tilde_22_h_biquad5_x1;
    number freqshift_tilde_22_h_biquad5_x2;
    number freqshift_tilde_22_h_biquad5_y1;
    number freqshift_tilde_22_h_biquad5_y2;
    number freqshift_tilde_22_h_biquad6_x1;
    number freqshift_tilde_22_h_biquad6_x2;
    number freqshift_tilde_22_h_biquad6_y1;
    number freqshift_tilde_22_h_biquad6_y2;
    number freqshift_tilde_22_p_currentPhase;
    number freqshift_tilde_22_p_conv;
    bool freqshift_tilde_22_setupDone;
    number param_21_lastValue;
    number gaintilde_24_lastValue;
    number gaintilde_24_loginc;
    number gaintilde_24_zval;
    number gaintilde_24_ramp_d_prev;
    number gaintilde_24_ramp_prev;
    number gaintilde_24_ramp_index;
    number gaintilde_24_ramp_increment;
    bool gaintilde_24_setupDone;
    number gaintilde_25_lastValue;
    number gaintilde_25_loginc;
    number gaintilde_25_zval;
    number gaintilde_25_ramp_d_prev;
    number gaintilde_25_ramp_prev;
    number gaintilde_25_ramp_index;
    number gaintilde_25_ramp_increment;
    bool gaintilde_25_setupDone;
    number freqshift_tilde_23_h_biquad1_x1;
    number freqshift_tilde_23_h_biquad1_x2;
    number freqshift_tilde_23_h_biquad1_y1;
    number freqshift_tilde_23_h_biquad1_y2;
    number freqshift_tilde_23_h_biquad2_x1;
    number freqshift_tilde_23_h_biquad2_x2;
    number freqshift_tilde_23_h_biquad2_y1;
    number freqshift_tilde_23_h_biquad2_y2;
    number freqshift_tilde_23_h_biquad3_x1;
    number freqshift_tilde_23_h_biquad3_x2;
    number freqshift_tilde_23_h_biquad3_y1;
    number freqshift_tilde_23_h_biquad3_y2;
    number freqshift_tilde_23_h_biquad4_x1;
    number freqshift_tilde_23_h_biquad4_x2;
    number freqshift_tilde_23_h_biquad4_y1;
    number freqshift_tilde_23_h_biquad4_y2;
    number freqshift_tilde_23_h_biquad5_x1;
    number freqshift_tilde_23_h_biquad5_x2;
    number freqshift_tilde_23_h_biquad5_y1;
    number freqshift_tilde_23_h_biquad5_y2;
    number freqshift_tilde_23_h_biquad6_x1;
    number freqshift_tilde_23_h_biquad6_x2;
    number freqshift_tilde_23_h_biquad6_y1;
    number freqshift_tilde_23_h_biquad6_y2;
    number freqshift_tilde_23_p_currentPhase;
    number freqshift_tilde_23_p_conv;
    bool freqshift_tilde_23_setupDone;
    number freqshift_tilde_24_h_biquad1_x1;
    number freqshift_tilde_24_h_biquad1_x2;
    number freqshift_tilde_24_h_biquad1_y1;
    number freqshift_tilde_24_h_biquad1_y2;
    number freqshift_tilde_24_h_biquad2_x1;
    number freqshift_tilde_24_h_biquad2_x2;
    number freqshift_tilde_24_h_biquad2_y1;
    number freqshift_tilde_24_h_biquad2_y2;
    number freqshift_tilde_24_h_biquad3_x1;
    number freqshift_tilde_24_h_biquad3_x2;
    number freqshift_tilde_24_h_biquad3_y1;
    number freqshift_tilde_24_h_biquad3_y2;
    number freqshift_tilde_24_h_biquad4_x1;
    number freqshift_tilde_24_h_biquad4_x2;
    number freqshift_tilde_24_h_biquad4_y1;
    number freqshift_tilde_24_h_biquad4_y2;
    number freqshift_tilde_24_h_biquad5_x1;
    number freqshift_tilde_24_h_biquad5_x2;
    number freqshift_tilde_24_h_biquad5_y1;
    number freqshift_tilde_24_h_biquad5_y2;
    number freqshift_tilde_24_h_biquad6_x1;
    number freqshift_tilde_24_h_biquad6_x2;
    number freqshift_tilde_24_h_biquad6_y1;
    number freqshift_tilde_24_h_biquad6_y2;
    number freqshift_tilde_24_p_currentPhase;
    number freqshift_tilde_24_p_conv;
    bool freqshift_tilde_24_setupDone;
    number gaintilde_26_lastValue;
    number gaintilde_26_loginc;
    number gaintilde_26_zval;
    number gaintilde_26_ramp_d_prev;
    number gaintilde_26_ramp_prev;
    number gaintilde_26_ramp_index;
    number gaintilde_26_ramp_increment;
    bool gaintilde_26_setupDone;
    number gaintilde_27_lastValue;
    number gaintilde_27_loginc;
    number gaintilde_27_zval;
    number gaintilde_27_ramp_d_prev;
    number gaintilde_27_ramp_prev;
    number gaintilde_27_ramp_index;
    number gaintilde_27_ramp_increment;
    bool gaintilde_27_setupDone;
    number freqshift_tilde_25_h_biquad1_x1;
    number freqshift_tilde_25_h_biquad1_x2;
    number freqshift_tilde_25_h_biquad1_y1;
    number freqshift_tilde_25_h_biquad1_y2;
    number freqshift_tilde_25_h_biquad2_x1;
    number freqshift_tilde_25_h_biquad2_x2;
    number freqshift_tilde_25_h_biquad2_y1;
    number freqshift_tilde_25_h_biquad2_y2;
    number freqshift_tilde_25_h_biquad3_x1;
    number freqshift_tilde_25_h_biquad3_x2;
    number freqshift_tilde_25_h_biquad3_y1;
    number freqshift_tilde_25_h_biquad3_y2;
    number freqshift_tilde_25_h_biquad4_x1;
    number freqshift_tilde_25_h_biquad4_x2;
    number freqshift_tilde_25_h_biquad4_y1;
    number freqshift_tilde_25_h_biquad4_y2;
    number freqshift_tilde_25_h_biquad5_x1;
    number freqshift_tilde_25_h_biquad5_x2;
    number freqshift_tilde_25_h_biquad5_y1;
    number freqshift_tilde_25_h_biquad5_y2;
    number freqshift_tilde_25_h_biquad6_x1;
    number freqshift_tilde_25_h_biquad6_x2;
    number freqshift_tilde_25_h_biquad6_y1;
    number freqshift_tilde_25_h_biquad6_y2;
    number freqshift_tilde_25_p_currentPhase;
    number freqshift_tilde_25_p_conv;
    bool freqshift_tilde_25_setupDone;
    number freqshift_tilde_26_h_biquad1_x1;
    number freqshift_tilde_26_h_biquad1_x2;
    number freqshift_tilde_26_h_biquad1_y1;
    number freqshift_tilde_26_h_biquad1_y2;
    number freqshift_tilde_26_h_biquad2_x1;
    number freqshift_tilde_26_h_biquad2_x2;
    number freqshift_tilde_26_h_biquad2_y1;
    number freqshift_tilde_26_h_biquad2_y2;
    number freqshift_tilde_26_h_biquad3_x1;
    number freqshift_tilde_26_h_biquad3_x2;
    number freqshift_tilde_26_h_biquad3_y1;
    number freqshift_tilde_26_h_biquad3_y2;
    number freqshift_tilde_26_h_biquad4_x1;
    number freqshift_tilde_26_h_biquad4_x2;
    number freqshift_tilde_26_h_biquad4_y1;
    number freqshift_tilde_26_h_biquad4_y2;
    number freqshift_tilde_26_h_biquad5_x1;
    number freqshift_tilde_26_h_biquad5_x2;
    number freqshift_tilde_26_h_biquad5_y1;
    number freqshift_tilde_26_h_biquad5_y2;
    number freqshift_tilde_26_h_biquad6_x1;
    number freqshift_tilde_26_h_biquad6_x2;
    number freqshift_tilde_26_h_biquad6_y1;
    number freqshift_tilde_26_h_biquad6_y2;
    number freqshift_tilde_26_p_currentPhase;
    number freqshift_tilde_26_p_conv;
    bool freqshift_tilde_26_setupDone;
    number gaintilde_28_lastValue;
    number gaintilde_28_loginc;
    number gaintilde_28_zval;
    number gaintilde_28_ramp_d_prev;
    number gaintilde_28_ramp_prev;
    number gaintilde_28_ramp_index;
    number gaintilde_28_ramp_increment;
    bool gaintilde_28_setupDone;
    number gaintilde_29_lastValue;
    number gaintilde_29_loginc;
    number gaintilde_29_zval;
    number gaintilde_29_ramp_d_prev;
    number gaintilde_29_ramp_prev;
    number gaintilde_29_ramp_index;
    number gaintilde_29_ramp_increment;
    bool gaintilde_29_setupDone;
    number freqshift_tilde_27_h_biquad1_x1;
    number freqshift_tilde_27_h_biquad1_x2;
    number freqshift_tilde_27_h_biquad1_y1;
    number freqshift_tilde_27_h_biquad1_y2;
    number freqshift_tilde_27_h_biquad2_x1;
    number freqshift_tilde_27_h_biquad2_x2;
    number freqshift_tilde_27_h_biquad2_y1;
    number freqshift_tilde_27_h_biquad2_y2;
    number freqshift_tilde_27_h_biquad3_x1;
    number freqshift_tilde_27_h_biquad3_x2;
    number freqshift_tilde_27_h_biquad3_y1;
    number freqshift_tilde_27_h_biquad3_y2;
    number freqshift_tilde_27_h_biquad4_x1;
    number freqshift_tilde_27_h_biquad4_x2;
    number freqshift_tilde_27_h_biquad4_y1;
    number freqshift_tilde_27_h_biquad4_y2;
    number freqshift_tilde_27_h_biquad5_x1;
    number freqshift_tilde_27_h_biquad5_x2;
    number freqshift_tilde_27_h_biquad5_y1;
    number freqshift_tilde_27_h_biquad5_y2;
    number freqshift_tilde_27_h_biquad6_x1;
    number freqshift_tilde_27_h_biquad6_x2;
    number freqshift_tilde_27_h_biquad6_y1;
    number freqshift_tilde_27_h_biquad6_y2;
    number freqshift_tilde_27_p_currentPhase;
    number freqshift_tilde_27_p_conv;
    bool freqshift_tilde_27_setupDone;
    number freqshift_tilde_28_h_biquad1_x1;
    number freqshift_tilde_28_h_biquad1_x2;
    number freqshift_tilde_28_h_biquad1_y1;
    number freqshift_tilde_28_h_biquad1_y2;
    number freqshift_tilde_28_h_biquad2_x1;
    number freqshift_tilde_28_h_biquad2_x2;
    number freqshift_tilde_28_h_biquad2_y1;
    number freqshift_tilde_28_h_biquad2_y2;
    number freqshift_tilde_28_h_biquad3_x1;
    number freqshift_tilde_28_h_biquad3_x2;
    number freqshift_tilde_28_h_biquad3_y1;
    number freqshift_tilde_28_h_biquad3_y2;
    number freqshift_tilde_28_h_biquad4_x1;
    number freqshift_tilde_28_h_biquad4_x2;
    number freqshift_tilde_28_h_biquad4_y1;
    number freqshift_tilde_28_h_biquad4_y2;
    number freqshift_tilde_28_h_biquad5_x1;
    number freqshift_tilde_28_h_biquad5_x2;
    number freqshift_tilde_28_h_biquad5_y1;
    number freqshift_tilde_28_h_biquad5_y2;
    number freqshift_tilde_28_h_biquad6_x1;
    number freqshift_tilde_28_h_biquad6_x2;
    number freqshift_tilde_28_h_biquad6_y1;
    number freqshift_tilde_28_h_biquad6_y2;
    number freqshift_tilde_28_p_currentPhase;
    number freqshift_tilde_28_p_conv;
    bool freqshift_tilde_28_setupDone;
    number gaintilde_30_lastValue;
    number gaintilde_30_loginc;
    number gaintilde_30_zval;
    number gaintilde_30_ramp_d_prev;
    number gaintilde_30_ramp_prev;
    number gaintilde_30_ramp_index;
    number gaintilde_30_ramp_increment;
    bool gaintilde_30_setupDone;
    number gaintilde_31_lastValue;
    number gaintilde_31_loginc;
    number gaintilde_31_zval;
    number gaintilde_31_ramp_d_prev;
    number gaintilde_31_ramp_prev;
    number gaintilde_31_ramp_index;
    number gaintilde_31_ramp_increment;
    bool gaintilde_31_setupDone;
    number freqshift_tilde_29_h_biquad1_x1;
    number freqshift_tilde_29_h_biquad1_x2;
    number freqshift_tilde_29_h_biquad1_y1;
    number freqshift_tilde_29_h_biquad1_y2;
    number freqshift_tilde_29_h_biquad2_x1;
    number freqshift_tilde_29_h_biquad2_x2;
    number freqshift_tilde_29_h_biquad2_y1;
    number freqshift_tilde_29_h_biquad2_y2;
    number freqshift_tilde_29_h_biquad3_x1;
    number freqshift_tilde_29_h_biquad3_x2;
    number freqshift_tilde_29_h_biquad3_y1;
    number freqshift_tilde_29_h_biquad3_y2;
    number freqshift_tilde_29_h_biquad4_x1;
    number freqshift_tilde_29_h_biquad4_x2;
    number freqshift_tilde_29_h_biquad4_y1;
    number freqshift_tilde_29_h_biquad4_y2;
    number freqshift_tilde_29_h_biquad5_x1;
    number freqshift_tilde_29_h_biquad5_x2;
    number freqshift_tilde_29_h_biquad5_y1;
    number freqshift_tilde_29_h_biquad5_y2;
    number freqshift_tilde_29_h_biquad6_x1;
    number freqshift_tilde_29_h_biquad6_x2;
    number freqshift_tilde_29_h_biquad6_y1;
    number freqshift_tilde_29_h_biquad6_y2;
    number freqshift_tilde_29_p_currentPhase;
    number freqshift_tilde_29_p_conv;
    bool freqshift_tilde_29_setupDone;
    number freqshift_tilde_30_h_biquad1_x1;
    number freqshift_tilde_30_h_biquad1_x2;
    number freqshift_tilde_30_h_biquad1_y1;
    number freqshift_tilde_30_h_biquad1_y2;
    number freqshift_tilde_30_h_biquad2_x1;
    number freqshift_tilde_30_h_biquad2_x2;
    number freqshift_tilde_30_h_biquad2_y1;
    number freqshift_tilde_30_h_biquad2_y2;
    number freqshift_tilde_30_h_biquad3_x1;
    number freqshift_tilde_30_h_biquad3_x2;
    number freqshift_tilde_30_h_biquad3_y1;
    number freqshift_tilde_30_h_biquad3_y2;
    number freqshift_tilde_30_h_biquad4_x1;
    number freqshift_tilde_30_h_biquad4_x2;
    number freqshift_tilde_30_h_biquad4_y1;
    number freqshift_tilde_30_h_biquad4_y2;
    number freqshift_tilde_30_h_biquad5_x1;
    number freqshift_tilde_30_h_biquad5_x2;
    number freqshift_tilde_30_h_biquad5_y1;
    number freqshift_tilde_30_h_biquad5_y2;
    number freqshift_tilde_30_h_biquad6_x1;
    number freqshift_tilde_30_h_biquad6_x2;
    number freqshift_tilde_30_h_biquad6_y1;
    number freqshift_tilde_30_h_biquad6_y2;
    number freqshift_tilde_30_p_currentPhase;
    number freqshift_tilde_30_p_conv;
    bool freqshift_tilde_30_setupDone;
    number param_22_lastValue;
    number gaintilde_32_lastValue;
    number gaintilde_32_loginc;
    number gaintilde_32_zval;
    number gaintilde_32_ramp_d_prev;
    number gaintilde_32_ramp_prev;
    number gaintilde_32_ramp_index;
    number gaintilde_32_ramp_increment;
    bool gaintilde_32_setupDone;
    number gaintilde_33_lastValue;
    number gaintilde_33_loginc;
    number gaintilde_33_zval;
    number gaintilde_33_ramp_d_prev;
    number gaintilde_33_ramp_prev;
    number gaintilde_33_ramp_index;
    number gaintilde_33_ramp_increment;
    bool gaintilde_33_setupDone;
    number param_23_lastValue;
    number param_24_lastValue;
    number param_25_lastValue;
    number freqshift_tilde_31_h_biquad1_x1;
    number freqshift_tilde_31_h_biquad1_x2;
    number freqshift_tilde_31_h_biquad1_y1;
    number freqshift_tilde_31_h_biquad1_y2;
    number freqshift_tilde_31_h_biquad2_x1;
    number freqshift_tilde_31_h_biquad2_x2;
    number freqshift_tilde_31_h_biquad2_y1;
    number freqshift_tilde_31_h_biquad2_y2;
    number freqshift_tilde_31_h_biquad3_x1;
    number freqshift_tilde_31_h_biquad3_x2;
    number freqshift_tilde_31_h_biquad3_y1;
    number freqshift_tilde_31_h_biquad3_y2;
    number freqshift_tilde_31_h_biquad4_x1;
    number freqshift_tilde_31_h_biquad4_x2;
    number freqshift_tilde_31_h_biquad4_y1;
    number freqshift_tilde_31_h_biquad4_y2;
    number freqshift_tilde_31_h_biquad5_x1;
    number freqshift_tilde_31_h_biquad5_x2;
    number freqshift_tilde_31_h_biquad5_y1;
    number freqshift_tilde_31_h_biquad5_y2;
    number freqshift_tilde_31_h_biquad6_x1;
    number freqshift_tilde_31_h_biquad6_x2;
    number freqshift_tilde_31_h_biquad6_y1;
    number freqshift_tilde_31_h_biquad6_y2;
    number freqshift_tilde_31_p_currentPhase;
    number freqshift_tilde_31_p_conv;
    bool freqshift_tilde_31_setupDone;
    number freqshift_tilde_32_h_biquad1_x1;
    number freqshift_tilde_32_h_biquad1_x2;
    number freqshift_tilde_32_h_biquad1_y1;
    number freqshift_tilde_32_h_biquad1_y2;
    number freqshift_tilde_32_h_biquad2_x1;
    number freqshift_tilde_32_h_biquad2_x2;
    number freqshift_tilde_32_h_biquad2_y1;
    number freqshift_tilde_32_h_biquad2_y2;
    number freqshift_tilde_32_h_biquad3_x1;
    number freqshift_tilde_32_h_biquad3_x2;
    number freqshift_tilde_32_h_biquad3_y1;
    number freqshift_tilde_32_h_biquad3_y2;
    number freqshift_tilde_32_h_biquad4_x1;
    number freqshift_tilde_32_h_biquad4_x2;
    number freqshift_tilde_32_h_biquad4_y1;
    number freqshift_tilde_32_h_biquad4_y2;
    number freqshift_tilde_32_h_biquad5_x1;
    number freqshift_tilde_32_h_biquad5_x2;
    number freqshift_tilde_32_h_biquad5_y1;
    number freqshift_tilde_32_h_biquad5_y2;
    number freqshift_tilde_32_h_biquad6_x1;
    number freqshift_tilde_32_h_biquad6_x2;
    number freqshift_tilde_32_h_biquad6_y1;
    number freqshift_tilde_32_h_biquad6_y2;
    number freqshift_tilde_32_p_currentPhase;
    number freqshift_tilde_32_p_conv;
    bool freqshift_tilde_32_setupDone;
    number gaintilde_34_lastValue;
    number gaintilde_34_loginc;
    number gaintilde_34_zval;
    number gaintilde_34_ramp_d_prev;
    number gaintilde_34_ramp_prev;
    number gaintilde_34_ramp_index;
    number gaintilde_34_ramp_increment;
    bool gaintilde_34_setupDone;
    number gaintilde_35_lastValue;
    number gaintilde_35_loginc;
    number gaintilde_35_zval;
    number gaintilde_35_ramp_d_prev;
    number gaintilde_35_ramp_prev;
    number gaintilde_35_ramp_index;
    number gaintilde_35_ramp_increment;
    bool gaintilde_35_setupDone;
    number freqshift_tilde_33_h_biquad1_x1;
    number freqshift_tilde_33_h_biquad1_x2;
    number freqshift_tilde_33_h_biquad1_y1;
    number freqshift_tilde_33_h_biquad1_y2;
    number freqshift_tilde_33_h_biquad2_x1;
    number freqshift_tilde_33_h_biquad2_x2;
    number freqshift_tilde_33_h_biquad2_y1;
    number freqshift_tilde_33_h_biquad2_y2;
    number freqshift_tilde_33_h_biquad3_x1;
    number freqshift_tilde_33_h_biquad3_x2;
    number freqshift_tilde_33_h_biquad3_y1;
    number freqshift_tilde_33_h_biquad3_y2;
    number freqshift_tilde_33_h_biquad4_x1;
    number freqshift_tilde_33_h_biquad4_x2;
    number freqshift_tilde_33_h_biquad4_y1;
    number freqshift_tilde_33_h_biquad4_y2;
    number freqshift_tilde_33_h_biquad5_x1;
    number freqshift_tilde_33_h_biquad5_x2;
    number freqshift_tilde_33_h_biquad5_y1;
    number freqshift_tilde_33_h_biquad5_y2;
    number freqshift_tilde_33_h_biquad6_x1;
    number freqshift_tilde_33_h_biquad6_x2;
    number freqshift_tilde_33_h_biquad6_y1;
    number freqshift_tilde_33_h_biquad6_y2;
    number freqshift_tilde_33_p_currentPhase;
    number freqshift_tilde_33_p_conv;
    bool freqshift_tilde_33_setupDone;
    number freqshift_tilde_34_h_biquad1_x1;
    number freqshift_tilde_34_h_biquad1_x2;
    number freqshift_tilde_34_h_biquad1_y1;
    number freqshift_tilde_34_h_biquad1_y2;
    number freqshift_tilde_34_h_biquad2_x1;
    number freqshift_tilde_34_h_biquad2_x2;
    number freqshift_tilde_34_h_biquad2_y1;
    number freqshift_tilde_34_h_biquad2_y2;
    number freqshift_tilde_34_h_biquad3_x1;
    number freqshift_tilde_34_h_biquad3_x2;
    number freqshift_tilde_34_h_biquad3_y1;
    number freqshift_tilde_34_h_biquad3_y2;
    number freqshift_tilde_34_h_biquad4_x1;
    number freqshift_tilde_34_h_biquad4_x2;
    number freqshift_tilde_34_h_biquad4_y1;
    number freqshift_tilde_34_h_biquad4_y2;
    number freqshift_tilde_34_h_biquad5_x1;
    number freqshift_tilde_34_h_biquad5_x2;
    number freqshift_tilde_34_h_biquad5_y1;
    number freqshift_tilde_34_h_biquad5_y2;
    number freqshift_tilde_34_h_biquad6_x1;
    number freqshift_tilde_34_h_biquad6_x2;
    number freqshift_tilde_34_h_biquad6_y1;
    number freqshift_tilde_34_h_biquad6_y2;
    number freqshift_tilde_34_p_currentPhase;
    number freqshift_tilde_34_p_conv;
    bool freqshift_tilde_34_setupDone;
    number gaintilde_36_lastValue;
    number gaintilde_36_loginc;
    number gaintilde_36_zval;
    number gaintilde_36_ramp_d_prev;
    number gaintilde_36_ramp_prev;
    number gaintilde_36_ramp_index;
    number gaintilde_36_ramp_increment;
    bool gaintilde_36_setupDone;
    number gaintilde_37_lastValue;
    number gaintilde_37_loginc;
    number gaintilde_37_zval;
    number gaintilde_37_ramp_d_prev;
    number gaintilde_37_ramp_prev;
    number gaintilde_37_ramp_index;
    number gaintilde_37_ramp_increment;
    bool gaintilde_37_setupDone;
    number freqshift_tilde_35_h_biquad1_x1;
    number freqshift_tilde_35_h_biquad1_x2;
    number freqshift_tilde_35_h_biquad1_y1;
    number freqshift_tilde_35_h_biquad1_y2;
    number freqshift_tilde_35_h_biquad2_x1;
    number freqshift_tilde_35_h_biquad2_x2;
    number freqshift_tilde_35_h_biquad2_y1;
    number freqshift_tilde_35_h_biquad2_y2;
    number freqshift_tilde_35_h_biquad3_x1;
    number freqshift_tilde_35_h_biquad3_x2;
    number freqshift_tilde_35_h_biquad3_y1;
    number freqshift_tilde_35_h_biquad3_y2;
    number freqshift_tilde_35_h_biquad4_x1;
    number freqshift_tilde_35_h_biquad4_x2;
    number freqshift_tilde_35_h_biquad4_y1;
    number freqshift_tilde_35_h_biquad4_y2;
    number freqshift_tilde_35_h_biquad5_x1;
    number freqshift_tilde_35_h_biquad5_x2;
    number freqshift_tilde_35_h_biquad5_y1;
    number freqshift_tilde_35_h_biquad5_y2;
    number freqshift_tilde_35_h_biquad6_x1;
    number freqshift_tilde_35_h_biquad6_x2;
    number freqshift_tilde_35_h_biquad6_y1;
    number freqshift_tilde_35_h_biquad6_y2;
    number freqshift_tilde_35_p_currentPhase;
    number freqshift_tilde_35_p_conv;
    bool freqshift_tilde_35_setupDone;
    number freqshift_tilde_36_h_biquad1_x1;
    number freqshift_tilde_36_h_biquad1_x2;
    number freqshift_tilde_36_h_biquad1_y1;
    number freqshift_tilde_36_h_biquad1_y2;
    number freqshift_tilde_36_h_biquad2_x1;
    number freqshift_tilde_36_h_biquad2_x2;
    number freqshift_tilde_36_h_biquad2_y1;
    number freqshift_tilde_36_h_biquad2_y2;
    number freqshift_tilde_36_h_biquad3_x1;
    number freqshift_tilde_36_h_biquad3_x2;
    number freqshift_tilde_36_h_biquad3_y1;
    number freqshift_tilde_36_h_biquad3_y2;
    number freqshift_tilde_36_h_biquad4_x1;
    number freqshift_tilde_36_h_biquad4_x2;
    number freqshift_tilde_36_h_biquad4_y1;
    number freqshift_tilde_36_h_biquad4_y2;
    number freqshift_tilde_36_h_biquad5_x1;
    number freqshift_tilde_36_h_biquad5_x2;
    number freqshift_tilde_36_h_biquad5_y1;
    number freqshift_tilde_36_h_biquad5_y2;
    number freqshift_tilde_36_h_biquad6_x1;
    number freqshift_tilde_36_h_biquad6_x2;
    number freqshift_tilde_36_h_biquad6_y1;
    number freqshift_tilde_36_h_biquad6_y2;
    number freqshift_tilde_36_p_currentPhase;
    number freqshift_tilde_36_p_conv;
    bool freqshift_tilde_36_setupDone;
    number gaintilde_38_lastValue;
    number gaintilde_38_loginc;
    number gaintilde_38_zval;
    number gaintilde_38_ramp_d_prev;
    number gaintilde_38_ramp_prev;
    number gaintilde_38_ramp_index;
    number gaintilde_38_ramp_increment;
    bool gaintilde_38_setupDone;
    number gaintilde_39_lastValue;
    number gaintilde_39_loginc;
    number gaintilde_39_zval;
    number gaintilde_39_ramp_d_prev;
    number gaintilde_39_ramp_prev;
    number gaintilde_39_ramp_index;
    number gaintilde_39_ramp_increment;
    bool gaintilde_39_setupDone;
    number freqshift_tilde_37_h_biquad1_x1;
    number freqshift_tilde_37_h_biquad1_x2;
    number freqshift_tilde_37_h_biquad1_y1;
    number freqshift_tilde_37_h_biquad1_y2;
    number freqshift_tilde_37_h_biquad2_x1;
    number freqshift_tilde_37_h_biquad2_x2;
    number freqshift_tilde_37_h_biquad2_y1;
    number freqshift_tilde_37_h_biquad2_y2;
    number freqshift_tilde_37_h_biquad3_x1;
    number freqshift_tilde_37_h_biquad3_x2;
    number freqshift_tilde_37_h_biquad3_y1;
    number freqshift_tilde_37_h_biquad3_y2;
    number freqshift_tilde_37_h_biquad4_x1;
    number freqshift_tilde_37_h_biquad4_x2;
    number freqshift_tilde_37_h_biquad4_y1;
    number freqshift_tilde_37_h_biquad4_y2;
    number freqshift_tilde_37_h_biquad5_x1;
    number freqshift_tilde_37_h_biquad5_x2;
    number freqshift_tilde_37_h_biquad5_y1;
    number freqshift_tilde_37_h_biquad5_y2;
    number freqshift_tilde_37_h_biquad6_x1;
    number freqshift_tilde_37_h_biquad6_x2;
    number freqshift_tilde_37_h_biquad6_y1;
    number freqshift_tilde_37_h_biquad6_y2;
    number freqshift_tilde_37_p_currentPhase;
    number freqshift_tilde_37_p_conv;
    bool freqshift_tilde_37_setupDone;
    number freqshift_tilde_38_h_biquad1_x1;
    number freqshift_tilde_38_h_biquad1_x2;
    number freqshift_tilde_38_h_biquad1_y1;
    number freqshift_tilde_38_h_biquad1_y2;
    number freqshift_tilde_38_h_biquad2_x1;
    number freqshift_tilde_38_h_biquad2_x2;
    number freqshift_tilde_38_h_biquad2_y1;
    number freqshift_tilde_38_h_biquad2_y2;
    number freqshift_tilde_38_h_biquad3_x1;
    number freqshift_tilde_38_h_biquad3_x2;
    number freqshift_tilde_38_h_biquad3_y1;
    number freqshift_tilde_38_h_biquad3_y2;
    number freqshift_tilde_38_h_biquad4_x1;
    number freqshift_tilde_38_h_biquad4_x2;
    number freqshift_tilde_38_h_biquad4_y1;
    number freqshift_tilde_38_h_biquad4_y2;
    number freqshift_tilde_38_h_biquad5_x1;
    number freqshift_tilde_38_h_biquad5_x2;
    number freqshift_tilde_38_h_biquad5_y1;
    number freqshift_tilde_38_h_biquad5_y2;
    number freqshift_tilde_38_h_biquad6_x1;
    number freqshift_tilde_38_h_biquad6_x2;
    number freqshift_tilde_38_h_biquad6_y1;
    number freqshift_tilde_38_h_biquad6_y2;
    number freqshift_tilde_38_p_currentPhase;
    number freqshift_tilde_38_p_conv;
    bool freqshift_tilde_38_setupDone;
    number gaintilde_40_lastValue;
    number gaintilde_40_loginc;
    number gaintilde_40_zval;
    number gaintilde_40_ramp_d_prev;
    number gaintilde_40_ramp_prev;
    number gaintilde_40_ramp_index;
    number gaintilde_40_ramp_increment;
    bool gaintilde_40_setupDone;
    number param_26_lastValue;
    number param_27_lastValue;
    number param_28_lastValue;
    number param_29_lastValue;
    number freqshift_tilde_39_h_biquad1_x1;
    number freqshift_tilde_39_h_biquad1_x2;
    number freqshift_tilde_39_h_biquad1_y1;
    number freqshift_tilde_39_h_biquad1_y2;
    number freqshift_tilde_39_h_biquad2_x1;
    number freqshift_tilde_39_h_biquad2_x2;
    number freqshift_tilde_39_h_biquad2_y1;
    number freqshift_tilde_39_h_biquad2_y2;
    number freqshift_tilde_39_h_biquad3_x1;
    number freqshift_tilde_39_h_biquad3_x2;
    number freqshift_tilde_39_h_biquad3_y1;
    number freqshift_tilde_39_h_biquad3_y2;
    number freqshift_tilde_39_h_biquad4_x1;
    number freqshift_tilde_39_h_biquad4_x2;
    number freqshift_tilde_39_h_biquad4_y1;
    number freqshift_tilde_39_h_biquad4_y2;
    number freqshift_tilde_39_h_biquad5_x1;
    number freqshift_tilde_39_h_biquad5_x2;
    number freqshift_tilde_39_h_biquad5_y1;
    number freqshift_tilde_39_h_biquad5_y2;
    number freqshift_tilde_39_h_biquad6_x1;
    number freqshift_tilde_39_h_biquad6_x2;
    number freqshift_tilde_39_h_biquad6_y1;
    number freqshift_tilde_39_h_biquad6_y2;
    number freqshift_tilde_39_p_currentPhase;
    number freqshift_tilde_39_p_conv;
    bool freqshift_tilde_39_setupDone;
    number param_30_lastValue;
    number param_31_lastValue;
    number param_32_lastValue;
    number param_33_lastValue;
    number param_34_lastValue;
    number param_35_lastValue;
    number param_36_lastValue;
    number param_37_lastValue;
    number param_38_lastValue;
    number param_39_lastValue;
    number param_40_lastValue;
    number param_41_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

