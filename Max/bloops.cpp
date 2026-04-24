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
    getEngine()->flushClockEvents(this, -1987572531, false);
    getEngine()->flushClockEvents(this, 1935387534, false);
    getEngine()->flushClockEvents(this, -724810028, false);
    getEngine()->flushClockEvents(this, -1468824490, false);
    getEngine()->flushClockEvents(this, -1096817259, false);
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

number samplerate() {
    return this->sr;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

Index vectorsize() {
    return this->vs;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

Index voice() {
    return this->_voiceIndex;
}

number random(number low, number high) {
    number range = high - low;
    return rand01() * range + low;
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
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);

    this->cycle_tilde_01_perform(
        this->cycle_tilde_01_frequency,
        this->cycle_tilde_01_phase_offset,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_01_perform(this->signals[0], this->signals[1], n);

    this->cycle_tilde_02_perform(
        this->cycle_tilde_02_frequency,
        this->cycle_tilde_02_phase_offset,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->reson_tilde_01_perform(
        this->signals[0],
        this->reson_tilde_01_centerFreq,
        this->reson_tilde_01_resonanceValue,
        this->signals[2],
        n
    );

    this->gaintilde_02_perform(this->signals[2], this->signals[0], n);

    this->cycle_tilde_03_perform(
        this->cycle_tilde_03_frequency,
        this->cycle_tilde_03_phase_offset,
        this->signals[2],
        this->dummyBuffer,
        n
    );

    this->reson_tilde_02_perform(
        this->signals[2],
        this->reson_tilde_02_centerFreq,
        this->reson_tilde_02_resonanceValue,
        this->signals[3],
        n
    );

    this->gaintilde_03_perform(this->signals[3], this->signals[2], n);

    this->cycle_tilde_04_perform(
        this->cycle_tilde_04_frequency,
        this->cycle_tilde_04_phase_offset,
        this->signals[3],
        this->dummyBuffer,
        n
    );

    this->adsr_01_perform(
        this->adsr_01_attack,
        this->adsr_01_decay,
        this->adsr_01_sustain,
        this->adsr_01_release,
        this->zeroBuffer,
        this->signals[4],
        n
    );

    this->dspexpr_02_perform(this->signals[3], this->signals[4], this->signals[5], n);

    this->cycle_tilde_05_perform(
        this->cycle_tilde_05_frequency,
        this->cycle_tilde_05_phase_offset,
        this->signals[4],
        this->dummyBuffer,
        n
    );

    this->adsr_02_perform(
        this->adsr_02_attack,
        this->adsr_02_decay,
        this->adsr_02_sustain,
        this->adsr_02_release,
        this->zeroBuffer,
        this->signals[3],
        n
    );

    this->adsr_03_perform(
        this->adsr_03_attack,
        this->adsr_03_decay,
        this->adsr_03_sustain,
        this->adsr_03_release,
        this->zeroBuffer,
        this->signals[6],
        n
    );

    this->dspexpr_03_perform(this->signals[4], this->signals[6], this->signals[7], n);
    this->signaladder_01_perform(this->signals[7], this->signals[5], this->signals[5], n);

    this->reson_tilde_03_perform(
        this->signals[5],
        this->reson_tilde_03_centerFreq,
        this->reson_tilde_03_resonanceValue,
        this->signals[6],
        n
    );

    this->gaintilde_04_perform(this->signals[6], this->signals[7], n);
    this->delaytilde_02_perform(this->delaytilde_02_delay, this->signals[6], this->signals[4], n);
    this->gaintilde_05_perform(this->signals[4], this->signals[6], n);
    this->noise_tilde_01_perform(this->signals[4], n);

    this->reson_tilde_04_perform(
        this->signals[4],
        this->reson_tilde_04_centerFreq,
        this->reson_tilde_04_resonanceValue,
        this->signals[8],
        n
    );

    this->gaintilde_06_perform(this->signals[8], this->signals[4], n);

    this->signaladder_02_perform(
        this->signals[2],
        this->signals[4],
        this->signals[7],
        this->signals[6],
        this->signals[0],
        this->signals[9],
        n
    );

    this->delaytilde_01_perform(this->delaytilde_01_delay, this->signals[9], this->signals[8], n);

    this->signaladder_03_perform(
        this->signals[8],
        this->signals[2],
        this->signals[4],
        this->signals[7],
        this->signals[6],
        this->signals[0],
        this->signals[1],
        this->signals[1],
        n
    );

    this->dspexpr_01_perform(this->signals[1], this->signals[3], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 10; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
        this->adsr_02_triggerBuf = resizeSignal(this->adsr_02_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_02_triggerValueBuf = resizeSignal(this->adsr_02_triggerValueBuf, this->maxvs, maxBlockSize);
        this->adsr_03_triggerBuf = resizeSignal(this->adsr_03_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_03_triggerValueBuf = resizeSignal(this->adsr_03_triggerValueBuf, this->maxvs, maxBlockSize);
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

    this->cycle_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_02_dspsetup(forceDSPSetup);
    this->reson_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_02_dspsetup(forceDSPSetup);
    this->cycle_tilde_03_dspsetup(forceDSPSetup);
    this->reson_tilde_02_dspsetup(forceDSPSetup);
    this->gaintilde_03_dspsetup(forceDSPSetup);
    this->cycle_tilde_04_dspsetup(forceDSPSetup);
    this->adsr_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_05_dspsetup(forceDSPSetup);
    this->adsr_02_dspsetup(forceDSPSetup);
    this->adsr_03_dspsetup(forceDSPSetup);
    this->reson_tilde_03_dspsetup(forceDSPSetup);
    this->gaintilde_04_dspsetup(forceDSPSetup);
    this->delaytilde_02_dspsetup(forceDSPSetup);
    this->gaintilde_05_dspsetup(forceDSPSetup);
    this->reson_tilde_04_dspsetup(forceDSPSetup);
    this->gaintilde_06_dspsetup(forceDSPSetup);
    this->delaytilde_01_dspsetup(forceDSPSetup);
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
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 1:
        {
        return addressOf(this->delaytilde_01_del_bufferobj);
        break;
        }
    case 2:
        {
        return addressOf(this->delaytilde_02_del_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 3;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_01_bufferUpdated();
        this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_02_bufferUpdated();
        this->cycle_tilde_03_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_03_bufferUpdated();
        this->cycle_tilde_04_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_04_bufferUpdated();
        this->cycle_tilde_05_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_05_bufferUpdated();
    }

    if (index == 1) {
        this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    }

    if (index == 2) {
        this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
    }
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr, "buffer~");
    this->delaytilde_02_del_bufferobj = initDataRef("delaytilde_02_del_bufferobj", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_03_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_04_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_05_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->delaytilde_01_del_bufferobj->setIndex(1);
    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    this->delaytilde_02_del_bufferobj->setIndex(2);
    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
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
    this->param_01_getPresetValue(getSubState(preset, "freq"));
    this->param_02_getPresetValue(getSubState(preset, "src"));
    this->param_03_getPresetValue(getSubState(preset, "dt1"));
    this->param_04_getPresetValue(getSubState(preset, "phase1"));
    this->param_05_getPresetValue(getSubState(preset, "dt2"));
    this->param_06_getPresetValue(getSubState(preset, "bloop1"));
    this->param_07_getPresetValue(getSubState(preset, "phase2"));
    this->param_08_getPresetValue(getSubState(preset, "t"));
    this->param_09_getPresetValue(getSubState(preset, "bloop2"));
    this->param_10_getPresetValue(getSubState(preset, "adsr"));
    this->param_11_getPresetValue(getSubState(preset, "noise"));
    this->param_12_getPresetValue(getSubState(preset, "attack"));
    this->param_13_getPresetValue(getSubState(preset, "decay"));
    this->param_14_getPresetValue(getSubState(preset, "sustain"));
    this->param_15_getPresetValue(getSubState(preset, "release"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "freq"));
    this->param_02_setPresetValue(getSubState(preset, "src"));
    this->param_03_setPresetValue(getSubState(preset, "dt1"));
    this->param_04_setPresetValue(getSubState(preset, "phase1"));
    this->param_05_setPresetValue(getSubState(preset, "dt2"));
    this->param_06_setPresetValue(getSubState(preset, "bloop1"));
    this->param_07_setPresetValue(getSubState(preset, "phase2"));
    this->param_08_setPresetValue(getSubState(preset, "t"));
    this->param_09_setPresetValue(getSubState(preset, "bloop2"));
    this->param_10_setPresetValue(getSubState(preset, "adsr"));
    this->param_11_setPresetValue(getSubState(preset, "noise"));
    this->param_12_setPresetValue(getSubState(preset, "attack"));
    this->param_13_setPresetValue(getSubState(preset, "decay"));
    this->param_14_setPresetValue(getSubState(preset, "sustain"));
    this->param_15_setPresetValue(getSubState(preset, "release"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false))
        {}
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->metro_01_onTransportChanged(state);
        this->metro_02_onTransportChanged(state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->metro_01_onBeatTimeChanged(beattime);
        this->metro_02_onBeatTimeChanged(beattime);
    }
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
    return 15;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "freq";
        }
    case 1:
        {
        return "src";
        }
    case 2:
        {
        return "dt1";
        }
    case 3:
        {
        return "phase1";
        }
    case 4:
        {
        return "dt2";
        }
    case 5:
        {
        return "bloop1";
        }
    case 6:
        {
        return "phase2";
        }
    case 7:
        {
        return "t";
        }
    case 8:
        {
        return "bloop2";
        }
    case 9:
        {
        return "adsr";
        }
    case 10:
        {
        return "noise";
        }
    case 11:
        {
        return "attack";
        }
    case 12:
        {
        return "decay";
        }
    case 13:
        {
        return "sustain";
        }
    case 14:
        {
        return "release";
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
        return "freq";
        }
    case 1:
        {
        return "src";
        }
    case 2:
        {
        return "dt1";
        }
    case 3:
        {
        return "phase1";
        }
    case 4:
        {
        return "dt2";
        }
    case 5:
        {
        return "bloop1";
        }
    case 6:
        {
        return "phase2";
        }
    case 7:
        {
        return "t";
        }
    case 8:
        {
        return "bloop2";
        }
    case 9:
        {
        return "adsr";
        }
    case 10:
        {
        return "noise";
        }
    case 11:
        {
        return "attack";
        }
    case 12:
        {
        return "decay";
        }
    case 13:
        {
        return "sustain";
        }
    case 14:
        {
        return "release";
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 20000;
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
            info->initialValue = 0;
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
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
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
            info->initialValue = 0;
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
            info->initialValue = 0;
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
            info->initialValue = 0.2;
            info->min = 0;
            info->max = 1;
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
            info->max = 1;
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
            info->initialValue = 0;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
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
            info->initialValue = 0;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 2000;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 2000;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 2000;
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
    case 3:
    case 6:
    case 7:
    case 9:
    case 13:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 1:
    case 2:
    case 4:
    case 5:
    case 8:
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 158 ? 158 : value));
            ParameterValue normalizedValue = (value - 0) / (158 - 0);
            return normalizedValue;
        }
        }
    case 11:
    case 12:
    case 14:
        {
        {
            value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 0) / (2000 - 0);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 0) / (20000 - 0);
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
    case 3:
    case 6:
    case 7:
    case 9:
    case 13:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 1:
    case 2:
    case 4:
    case 5:
    case 8:
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (158 - 0);
            }
        }
        }
    case 11:
    case 12:
    case 14:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (2000 - 0);
            }
        }
        }
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (20000 - 0);
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

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -1987572531:
        {
        this->metro_01_tick_bang();
        break;
        }
    case 1935387534:
        {
        this->metro_02_tick_bang();
        break;
        }
    case -724810028:
        {
        this->adsr_01_mute_bang();
        break;
        }
    case -1468824490:
        {
        this->adsr_02_mute_bang();
        break;
        }
    case -1096817259:
        {
        this->adsr_03_mute_bang();
        break;
        }
    }
}

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
        if (TAG("gain~_obj-69") == objectId)
            this->gaintilde_01_valin_set(payload);

        if (TAG("gain~_obj-70") == objectId)
            this->gaintilde_02_valin_set(payload);

        if (TAG("number_obj-22") == objectId)
            this->numberobj_01_valin_set(payload);

        if (TAG("gain~_obj-74") == objectId)
            this->gaintilde_03_valin_set(payload);

        if (TAG("gain~_obj-72") == objectId)
            this->gaintilde_04_valin_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_02_valin_set(payload);

        if (TAG("toggle_obj-30") == objectId)
            this->toggle_01_valin_set(payload);

        if (TAG("gain~_obj-71") == objectId)
            this->gaintilde_05_valin_set(payload);

        if (TAG("number_obj-54") == objectId)
            this->numberobj_03_valin_set(payload);

        if (TAG("gain~_obj-73") == objectId)
            this->gaintilde_06_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-22") == objectId)
            this->numberobj_01_format_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_02_format_set(payload);

        if (TAG("number_obj-54") == objectId)
            this->numberobj_03_format_set(payload);

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-61") == objectId)
            this->message_01_listin_number_set(payload);

        if (TAG("message_obj-57") == objectId)
            this->message_02_listin_number_set(payload);

        break;
        }
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-61") == objectId)
            this->message_01_listin_list_set(payload);

        if (TAG("message_obj-57") == objectId)
            this->message_02_listin_list_set(payload);

        break;
        }
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("bangin"):
        {
        if (TAG("button_obj-32") == objectId)
            this->button_01_bangin_bang();

        if (TAG("button_obj-42") == objectId)
            this->button_02_bangin_bang();

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-61") == objectId)
            this->message_01_listin_bang_bang();

        if (TAG("message_obj-57") == objectId)
            this->message_02_listin_bang_bang();

        break;
        }
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("gain~_obj-69"):
        {
        return "gain~_obj-69";
        }
    case TAG("gain~_obj-70"):
        {
        return "gain~_obj-70";
        }
    case TAG("number_obj-22"):
        {
        return "number_obj-22";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("gain~_obj-74"):
        {
        return "gain~_obj-74";
        }
    case TAG("gain~_obj-72"):
        {
        return "gain~_obj-72";
        }
    case TAG("number_obj-24"):
        {
        return "number_obj-24";
        }
    case TAG("bangout"):
        {
        return "bangout";
        }
    case TAG("button_obj-32"):
        {
        return "button_obj-32";
        }
    case TAG("toggle_obj-30"):
        {
        return "toggle_obj-30";
        }
    case TAG("gain~_obj-71"):
        {
        return "gain~_obj-71";
        }
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-61"):
        {
        return "message_obj-61";
        }
    case TAG("number_obj-54"):
        {
        return "number_obj-54";
        }
    case TAG("button_obj-42"):
        {
        return "button_obj-42";
        }
    case TAG("gain~_obj-73"):
        {
        return "gain~_obj-73";
        }
    case TAG("message_obj-57"):
        {
        return "message_obj-57";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    case TAG("bangin"):
        {
        return "bangin";
        }
    case TAG("listin"):
        {
        return "listin";
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

    this->gaintilde_01_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->gaintilde_02_input_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->numberobj_01_value_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->gaintilde_03_input_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->gaintilde_04_input_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->numberobj_02_value_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->toggle_01_value_number_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->gaintilde_05_input_number_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->adsr_02_trigger_number_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->gaintilde_06_input_number_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->adsr_02_attack_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->adsr_02_decay_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->adsr_02_sustain_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(14, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->adsr_02_release_set(v);
}

void gaintilde_01_valin_set(number v) {
    this->gaintilde_01_value_set(v);
}

void gaintilde_02_valin_set(number v) {
    this->gaintilde_02_value_set(v);
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void gaintilde_03_valin_set(number v) {
    this->gaintilde_03_value_set(v);
}

void gaintilde_04_valin_set(number v) {
    this->gaintilde_04_value_set(v);
}

void numberobj_02_valin_set(number v) {
    this->numberobj_02_value_set(v);
}

void numberobj_02_format_set(number v) {
    this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void button_01_bangin_bang() {
    this->button_01_bangval_bang();
}

void toggle_01_valin_set(number v) {
    this->toggle_01_value_number_set(v);
}

void metro_01_tick_bang() {
    this->metro_01_tickout_bang();
    this->getEngine()->flushClockEvents(this, -1987572531, false);;

    if ((bool)(this->metro_01_on)) {
        this->metro_01_last = this->currenttime();

        {
            this->metro_01_next = this->metro_01_last + this->metro_01_interval;
            this->getEngine()->scheduleClockEvent(this, -1987572531, this->metro_01_interval + this->_currentTime);;
        }
    }
}

void gaintilde_05_valin_set(number v) {
    this->gaintilde_05_value_set(v);
}

void message_01_listin_list_set(const list& v) {
    this->message_01_set_set(v);
}

void message_01_listin_number_set(number v) {
    this->message_01_set_set(v);
}

void message_01_listin_bang_bang() {
    this->message_01_trigger_bang();
}

void numberobj_03_valin_set(number v) {
    this->numberobj_03_value_set(v);
}

void numberobj_03_format_set(number v) {
    this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void button_02_bangin_bang() {
    this->button_02_bangval_bang();
}

void metro_02_tick_bang() {
    this->metro_02_tickout_bang();
    this->getEngine()->flushClockEvents(this, 1935387534, false);;

    if ((bool)(this->metro_02_on)) {
        this->metro_02_last = this->currenttime();

        {
            this->metro_02_next = this->metro_02_last + this->metro_02_interval;
            this->getEngine()->scheduleClockEvent(this, 1935387534, this->metro_02_interval + this->_currentTime);;
        }
    }
}

void gaintilde_06_valin_set(number v) {
    this->gaintilde_06_value_set(v);
}

void message_02_listin_list_set(const list& v) {
    this->message_02_set_set(v);
}

void message_02_listin_number_set(number v) {
    this->message_02_set_set(v);
}

void message_02_listin_bang_bang() {
    this->message_02_trigger_bang();
}

void adsr_01_mute_bang() {}

void adsr_02_mute_bang() {}

void adsr_03_mute_bang() {}

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
    return 0;
}

Index getNumOutputChannels() const {
    return 1;
}

void allocateDataRefs() {
    this->cycle_tilde_01_buffer->requestSize(16384, 1);
    this->cycle_tilde_01_buffer->setSampleRate(this->sr);
    this->cycle_tilde_02_buffer->requestSize(16384, 1);
    this->cycle_tilde_02_buffer->setSampleRate(this->sr);
    this->cycle_tilde_03_buffer->requestSize(16384, 1);
    this->cycle_tilde_03_buffer->setSampleRate(this->sr);
    this->cycle_tilde_04_buffer->requestSize(16384, 1);
    this->cycle_tilde_04_buffer->setSampleRate(this->sr);
    this->cycle_tilde_05_buffer->requestSize(16384, 1);
    this->cycle_tilde_05_buffer->setSampleRate(this->sr);
    this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
    this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
    this->cycle_tilde_03_buffer = this->cycle_tilde_03_buffer->allocateIfNeeded();
    this->cycle_tilde_04_buffer = this->cycle_tilde_04_buffer->allocateIfNeeded();
    this->cycle_tilde_05_buffer = this->cycle_tilde_05_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();

    if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_01_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_01_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();

    if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_02_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_02_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(2);
    }
}

void initializeObjects() {
    this->gaintilde_01_init();
    this->gaintilde_02_init();
    this->numberobj_01_init();
    this->gaintilde_03_init();
    this->gaintilde_04_init();
    this->numberobj_02_init();
    this->delaytilde_01_del_init();
    this->random_01_nz_init();
    this->gaintilde_05_init();
    this->delaytilde_02_del_init();
    this->message_01_init();
    this->numberobj_03_init();
    this->random_02_nz_init();
    this->gaintilde_06_init();
    this->message_02_init();
    this->noise_tilde_01_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    if ((bool)(this->metro_01_on))
        this->metro_01_on_set(1);

    if ((bool)(this->metro_02_on))
        this->metro_02_on_set(1);

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

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 20000 ? 20000 : (v < 0 ? 0 : v));
    return v;
}

void cycle_tilde_01_frequency_set(number v) {
    this->cycle_tilde_01_frequency = v;
}

void receive_01_output_number_set(number v) {
    this->receive_01_output_number = v;
    this->cycle_tilde_01_frequency_set(v);
}

void cycle_tilde_02_frequency_set(number v) {
    this->cycle_tilde_02_frequency = v;
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->cycle_tilde_02_frequency_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;
    this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:+_obj-10:1
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->expr_01_in1_set(v);
}

void cycle_tilde_03_frequency_set(number v) {
    this->cycle_tilde_03_frequency = v;
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->cycle_tilde_03_frequency_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 - this->expr_02_in2);//#map:-_obj-13:1
}

void receive_03_output_number_set(number v) {
    this->receive_03_output_number = v;
    this->expr_02_in1_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_01_output_number_set(v);
    this->receive_02_output_number_set(v);
    this->receive_03_output_number_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-69"), v, this->_currentTime);
    this->gaintilde_01_outval_set(value);
}

void gaintilde_01_input_number_set(number v) {
    this->gaintilde_01_input_number = v;

    this->gaintilde_01_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_03_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_02_outval_set(number ) {}

void gaintilde_02_value_set(number v) {
    this->gaintilde_02_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-70"), v, this->_currentTime);
    this->gaintilde_02_outval_set(value);
}

void gaintilde_02_input_number_set(number v) {
    this->gaintilde_02_input_number = v;

    this->gaintilde_02_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_04_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void cycle_tilde_02_phase_offset_set(number v) {
    this->cycle_tilde_02_phase_offset = v;
}

void numberobj_01_output_set(number v) {
    this->cycle_tilde_02_phase_offset_set(v);
}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-22"), localvalue, this->_currentTime);
    this->numberobj_01_output_set(localvalue);
}

static number param_05_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_03_outval_set(number ) {}

void gaintilde_03_value_set(number v) {
    this->gaintilde_03_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-74"), v, this->_currentTime);
    this->gaintilde_03_outval_set(value);
}

void gaintilde_03_input_number_set(number v) {
    this->gaintilde_03_input_number = v;

    this->gaintilde_03_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_06_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_04_outval_set(number ) {}

void gaintilde_04_value_set(number v) {
    this->gaintilde_04_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-72"), v, this->_currentTime);
    this->gaintilde_04_outval_set(value);
}

void gaintilde_04_input_number_set(number v) {
    this->gaintilde_04_input_number = v;

    this->gaintilde_04_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_07_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void cycle_tilde_03_phase_offset_set(number v) {
    this->cycle_tilde_03_phase_offset = v;
}

void numberobj_02_output_set(number v) {
    this->cycle_tilde_03_phase_offset_set(v);
}

void numberobj_02_value_set(number v) {
    this->numberobj_02_value_setter(v);
    v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-24"), localvalue, this->_currentTime);
    this->numberobj_02_output_set(localvalue);
}

static number param_08_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void metro_02_on_set(number v) {
    this->metro_02_on = v;
    this->getEngine()->flushClockEvents(this, 1935387534, false);;

    if ((bool)(v)) {
        {
            this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
        }
    }
}

void metro_01_on_set(number v) {
    this->metro_01_on = v;
    this->getEngine()->flushClockEvents(this, -1987572531, false);;

    if ((bool)(v)) {
        {
            this->getEngine()->scheduleClockEvent(this, -1987572531, 0 + this->_currentTime);;
        }
    }
}

void toggle_01_output_set(number v) {
    this->metro_02_on_set(v);
    this->metro_01_on_set(v);
}

void toggle_01_value_number_set(number v) {
    this->toggle_01_value_number_setter(v);
    v = this->toggle_01_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-30"), v, this->_currentTime);
    this->toggle_01_output_set(v);
}

static number param_09_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_05_outval_set(number ) {}

void gaintilde_05_value_set(number v) {
    this->gaintilde_05_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-71"), v, this->_currentTime);
    this->gaintilde_05_outval_set(value);
}

void gaintilde_05_input_number_set(number v) {
    this->gaintilde_05_input_number = v;

    this->gaintilde_05_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_10_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void adsr_02_trigger_number_set(number v) {
    this->adsr_02_trigger_number = v;

    if (v != 0)
        this->adsr_02_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
        this->adsr_02_triggerValueBuf[(Index)i] = v;
    }
}

static number param_11_value_constrain(number v) {
    v = (v > 158 ? 158 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_06_outval_set(number ) {}

void gaintilde_06_value_set(number v) {
    this->gaintilde_06_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-73"), v, this->_currentTime);
    this->gaintilde_06_outval_set(value);
}

void gaintilde_06_input_number_set(number v) {
    this->gaintilde_06_input_number = v;

    this->gaintilde_06_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

static number param_12_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_02_attack_set(number v) {
    this->adsr_02_attack = v;
}

static number param_13_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_02_decay_set(number v) {
    this->adsr_02_decay = v;
}

static number param_14_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void adsr_02_sustain_set(number v) {
    this->adsr_02_sustain = v;
}

static number param_15_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_02_release_set(number v) {
    this->adsr_02_release = v;
}

void adsr_01_trigger_number_set(number v) {
    this->adsr_01_trigger_number = v;

    if (v != 0)
        this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
        this->adsr_01_triggerValueBuf[(Index)i] = v;
    }
}

void message_01_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->adsr_01_trigger_number_set(converted);
    }
}

void message_01_trigger_bang() {
    this->message_01_out_set(this->message_01_set);
}

void cycle_tilde_04_frequency_set(number v) {
    this->cycle_tilde_04_frequency = v;
}

void random_01_result_set(number v) {
    this->cycle_tilde_04_frequency_set(v);
}

void random_01_trigger_bang() {
    {
        this->random_01_result_set(this->random(0, this->random_01_limit));
    }
}

void button_01_output_bang() {
    this->message_01_trigger_bang();
    this->random_01_trigger_bang();
}

void button_01_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-32"), this->_currentTime);;
    this->button_01_output_bang();
}

void metro_01_tickout_bang() {
    this->button_01_bangval_bang();
}

void message_01_set_set(const list& v) {
    this->message_01_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-61"), v, this->_currentTime);
}

void cycle_tilde_05_frequency_set(number v) {
    this->cycle_tilde_05_frequency = v;
}

void numberobj_03_output_set(number v) {
    this->cycle_tilde_05_frequency_set(v);
}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-54"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

void adsr_03_trigger_number_set(number v) {
    this->adsr_03_trigger_number = v;

    if (v != 0)
        this->adsr_03_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
        this->adsr_03_triggerValueBuf[(Index)i] = v;
    }
}

void message_02_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->adsr_03_trigger_number_set(converted);
    }
}

void message_02_trigger_bang() {
    this->message_02_out_set(this->message_02_set);
}

void random_02_result_set(number v) {
    this->numberobj_03_value_set(v);
}

void random_02_trigger_bang() {
    {
        this->random_02_result_set(this->random(0, this->random_02_limit));
    }
}

void button_02_output_bang() {
    this->message_02_trigger_bang();
    this->random_02_trigger_bang();
}

void button_02_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-42"), this->_currentTime);;
    this->button_02_output_bang();
}

void metro_02_tickout_bang() {
    this->button_02_bangval_bang();
}

void message_02_set_set(const list& v) {
    this->message_02_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-57"), v, this->_currentTime);
}

void cycle_tilde_01_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
    auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
    auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_01_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_01_buffer[(Index)idx];
            number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_01_f2i));
                __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
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

void cycle_tilde_02_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
    auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
    auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            if (phase_offset != 0 || 0 == 2) {
                uint_phase = uint32_add(uint32_trunc(phase_offset * 4294967296.0), __cycle_tilde_02_phasei);
            } else {
                uint_phase = __cycle_tilde_02_phasei;
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_02_buffer[(Index)idx];
            number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_02_f2i));
                __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
}

void reson_tilde_01_perform(
    const Sample * x,
    number centerFreq,
    number resonanceValue,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(resonanceValue);
    RNBO_UNUSED(centerFreq);
    auto __reson_tilde_01_xm1 = this->reson_tilde_01_xm1;
    auto __reson_tilde_01_ym2 = this->reson_tilde_01_ym2;
    auto __reson_tilde_01_ym1 = this->reson_tilde_01_ym1;
    auto __reson_tilde_01_xm2 = this->reson_tilde_01_xm2;
    auto __reson_tilde_01_c2 = this->reson_tilde_01_c2;
    auto __reson_tilde_01_c1 = this->reson_tilde_01_c1;
    auto __reson_tilde_01_gainScale = this->reson_tilde_01_gainScale;
    auto __reson_tilde_01_r = this->reson_tilde_01_r;
    Index i;

    for (i = 0; i < n; i++) {
        number __centerFreq = 1000;
        __centerFreq = rnbo_abs(__centerFreq);

        if (this->reson_tilde_01_d_next(__centerFreq) != 0 || this->reson_tilde_01_d2_next(40) != 0) {
            number clippedResonance = 40;
            number bandWidth = __centerFreq * ((number)1 / clippedResonance);
            number twoPIOverSampleRate = 6.28318530717958647692 / this->sr;
            __reson_tilde_01_r = rnbo_exp(-(twoPIOverSampleRate * bandWidth));
            __reson_tilde_01_gainScale = 1 - __reson_tilde_01_r;
            __reson_tilde_01_c1 = 2. * __reson_tilde_01_r * rnbo_cos(__centerFreq * twoPIOverSampleRate);
            __reson_tilde_01_c2 = -(__reson_tilde_01_r * __reson_tilde_01_r);
        }

        number yn = __reson_tilde_01_gainScale * (x[(Index)i] - __reson_tilde_01_r * __reson_tilde_01_xm2) + __reson_tilde_01_c1 * __reson_tilde_01_ym1 + __reson_tilde_01_c2 * __reson_tilde_01_ym2;
        __reson_tilde_01_ym2 = __reson_tilde_01_ym1;
        __reson_tilde_01_ym1 = yn;
        __reson_tilde_01_xm2 = __reson_tilde_01_xm1;
        __reson_tilde_01_xm1 = x[(Index)i];
        out1[(Index)i] = yn;
    }

    this->reson_tilde_01_r = __reson_tilde_01_r;
    this->reson_tilde_01_gainScale = __reson_tilde_01_gainScale;
    this->reson_tilde_01_c1 = __reson_tilde_01_c1;
    this->reson_tilde_01_c2 = __reson_tilde_01_c2;
    this->reson_tilde_01_xm2 = __reson_tilde_01_xm2;
    this->reson_tilde_01_ym1 = __reson_tilde_01_ym1;
    this->reson_tilde_01_ym2 = __reson_tilde_01_ym2;
    this->reson_tilde_01_xm1 = __reson_tilde_01_xm1;
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

void cycle_tilde_03_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cycle_tilde_03_f2i = this->cycle_tilde_03_f2i;
    auto __cycle_tilde_03_buffer = this->cycle_tilde_03_buffer;
    auto __cycle_tilde_03_phasei = this->cycle_tilde_03_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            if (phase_offset != 0 || 0 == 2) {
                uint_phase = uint32_add(uint32_trunc(phase_offset * 4294967296.0), __cycle_tilde_03_phasei);
            } else {
                uint_phase = __cycle_tilde_03_phasei;
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_03_buffer[(Index)idx];
            number y1 = __cycle_tilde_03_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_03_f2i));
                __cycle_tilde_03_phasei = uint32_add(__cycle_tilde_03_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_03_phasei = __cycle_tilde_03_phasei;
}

void reson_tilde_02_perform(
    const Sample * x,
    number centerFreq,
    number resonanceValue,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(resonanceValue);
    RNBO_UNUSED(centerFreq);
    auto __reson_tilde_02_xm1 = this->reson_tilde_02_xm1;
    auto __reson_tilde_02_ym2 = this->reson_tilde_02_ym2;
    auto __reson_tilde_02_ym1 = this->reson_tilde_02_ym1;
    auto __reson_tilde_02_xm2 = this->reson_tilde_02_xm2;
    auto __reson_tilde_02_c2 = this->reson_tilde_02_c2;
    auto __reson_tilde_02_c1 = this->reson_tilde_02_c1;
    auto __reson_tilde_02_gainScale = this->reson_tilde_02_gainScale;
    auto __reson_tilde_02_r = this->reson_tilde_02_r;
    Index i;

    for (i = 0; i < n; i++) {
        number __centerFreq = 8000;
        __centerFreq = rnbo_abs(__centerFreq);

        if (this->reson_tilde_02_d_next(__centerFreq) != 0 || this->reson_tilde_02_d2_next(30) != 0) {
            number clippedResonance = 30;
            number bandWidth = __centerFreq * ((number)1 / clippedResonance);
            number twoPIOverSampleRate = 6.28318530717958647692 / this->sr;
            __reson_tilde_02_r = rnbo_exp(-(twoPIOverSampleRate * bandWidth));
            __reson_tilde_02_gainScale = 1 - __reson_tilde_02_r;
            __reson_tilde_02_c1 = 2. * __reson_tilde_02_r * rnbo_cos(__centerFreq * twoPIOverSampleRate);
            __reson_tilde_02_c2 = -(__reson_tilde_02_r * __reson_tilde_02_r);
        }

        number yn = __reson_tilde_02_gainScale * (x[(Index)i] - __reson_tilde_02_r * __reson_tilde_02_xm2) + __reson_tilde_02_c1 * __reson_tilde_02_ym1 + __reson_tilde_02_c2 * __reson_tilde_02_ym2;
        __reson_tilde_02_ym2 = __reson_tilde_02_ym1;
        __reson_tilde_02_ym1 = yn;
        __reson_tilde_02_xm2 = __reson_tilde_02_xm1;
        __reson_tilde_02_xm1 = x[(Index)i];
        out1[(Index)i] = yn;
    }

    this->reson_tilde_02_r = __reson_tilde_02_r;
    this->reson_tilde_02_gainScale = __reson_tilde_02_gainScale;
    this->reson_tilde_02_c1 = __reson_tilde_02_c1;
    this->reson_tilde_02_c2 = __reson_tilde_02_c2;
    this->reson_tilde_02_xm2 = __reson_tilde_02_xm2;
    this->reson_tilde_02_ym1 = __reson_tilde_02_ym1;
    this->reson_tilde_02_ym2 = __reson_tilde_02_ym2;
    this->reson_tilde_02_xm1 = __reson_tilde_02_xm1;
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

void cycle_tilde_04_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_04_f2i = this->cycle_tilde_04_f2i;
    auto __cycle_tilde_04_buffer = this->cycle_tilde_04_buffer;
    auto __cycle_tilde_04_phasei = this->cycle_tilde_04_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_04_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_04_buffer[(Index)idx];
            number y1 = __cycle_tilde_04_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_04_f2i));
                __cycle_tilde_04_phasei = uint32_add(__cycle_tilde_04_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_04_phasei = __cycle_tilde_04_phasei;
}

void adsr_01_perform(
    number attack,
    number decay,
    number sustain,
    number release,
    const SampleValue * trigger_signal,
    SampleValue * out,
    Index n
) {
    RNBO_UNUSED(trigger_signal);
    RNBO_UNUSED(release);
    RNBO_UNUSED(sustain);
    RNBO_UNUSED(decay);
    RNBO_UNUSED(attack);
    auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
    auto __adsr_01_time = this->adsr_01_time;
    auto __adsr_01_amplitude = this->adsr_01_amplitude;
    auto __adsr_01_outval = this->adsr_01_outval;
    auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
    auto __adsr_01_phase = this->adsr_01_phase;
    auto __adsr_01_legato = this->adsr_01_legato;
    auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
    auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
    bool bangMute = false;

    for (Index i = 0; i < n; i++) {
        number clampedattack = (15 > __adsr_01_mspersamp ? 15 : __adsr_01_mspersamp);
        number clampeddecay = (300 > __adsr_01_mspersamp ? 300 : __adsr_01_mspersamp);
        number clampedrelease = (0 > __adsr_01_mspersamp ? 0 : __adsr_01_mspersamp);
        number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];

        if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
            if ((bool)(__adsr_01_legato)) {
                if (__adsr_01_phase != 0) {
                    __adsr_01_startingpoint = __adsr_01_outval;
                } else {
                    __adsr_01_startingpoint = 0;
                }
            } else {
                __adsr_01_startingpoint = 0;
            }

            __adsr_01_amplitude = currentTriggerVal;
            __adsr_01_phase = 1;
            __adsr_01_time = 0.0;
            bangMute = false;
        } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
            if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                __adsr_01_phase = 4;
                __adsr_01_amplitude = __adsr_01_outval;
                __adsr_01_time = 0.0;
            }
        }

        __adsr_01_time += __adsr_01_mspersamp;

        if (__adsr_01_phase == 0) {
            __adsr_01_outval = 0;
        } else if (__adsr_01_phase == 1) {
            if (__adsr_01_time > clampedattack) {
                __adsr_01_time -= clampedattack;
                __adsr_01_phase = 2;
                __adsr_01_outval = __adsr_01_amplitude;
            } else {
                __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
            }
        } else if (__adsr_01_phase == 2) {
            if (__adsr_01_time > clampeddecay) {
                __adsr_01_time -= clampeddecay;
                __adsr_01_phase = 3;
                __adsr_01_outval = __adsr_01_amplitude * 0;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * 0 + (__adsr_01_amplitude - __adsr_01_amplitude * 0) * (1. - __adsr_01_time / clampeddecay);
            }
        } else if (__adsr_01_phase == 3) {
            __adsr_01_outval = __adsr_01_amplitude * 0;
        } else if (__adsr_01_phase == 4) {
            if (__adsr_01_time > clampedrelease) {
                __adsr_01_time = 0;
                __adsr_01_phase = 0;
                __adsr_01_outval = 0;
                __adsr_01_amplitude = 0;
                bangMute = true;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
            }
        }

        out[(Index)i] = __adsr_01_outval;
        this->adsr_01_triggerBuf[(Index)i] = 0;
        this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
        __adsr_01_lastTriggerVal = currentTriggerVal;
    }

    if ((bool)(bangMute)) {
        this->getEngine()->scheduleClockEventWithValue(
            this,
            -724810028,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            0
        );;
    }

    this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
    this->adsr_01_phase = __adsr_01_phase;
    this->adsr_01_startingpoint = __adsr_01_startingpoint;
    this->adsr_01_outval = __adsr_01_outval;
    this->adsr_01_amplitude = __adsr_01_amplitude;
    this->adsr_01_time = __adsr_01_time;
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void cycle_tilde_05_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_05_f2i = this->cycle_tilde_05_f2i;
    auto __cycle_tilde_05_buffer = this->cycle_tilde_05_buffer;
    auto __cycle_tilde_05_phasei = this->cycle_tilde_05_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_05_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_05_buffer[(Index)idx];
            number y1 = __cycle_tilde_05_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency * __cycle_tilde_05_f2i));
                __cycle_tilde_05_phasei = uint32_add(__cycle_tilde_05_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_05_phasei = __cycle_tilde_05_phasei;
}

void adsr_02_perform(
    number attack,
    number decay,
    number sustain,
    number release,
    const SampleValue * trigger_signal,
    SampleValue * out,
    Index n
) {
    RNBO_UNUSED(trigger_signal);
    auto __adsr_02_trigger_number = this->adsr_02_trigger_number;
    auto __adsr_02_time = this->adsr_02_time;
    auto __adsr_02_amplitude = this->adsr_02_amplitude;
    auto __adsr_02_outval = this->adsr_02_outval;
    auto __adsr_02_startingpoint = this->adsr_02_startingpoint;
    auto __adsr_02_phase = this->adsr_02_phase;
    auto __adsr_02_legato = this->adsr_02_legato;
    auto __adsr_02_lastTriggerVal = this->adsr_02_lastTriggerVal;
    auto __adsr_02_mspersamp = this->adsr_02_mspersamp;
    bool bangMute = false;

    for (Index i = 0; i < n; i++) {
        number clampedattack = (attack > __adsr_02_mspersamp ? attack : __adsr_02_mspersamp);
        number clampeddecay = (decay > __adsr_02_mspersamp ? decay : __adsr_02_mspersamp);
        number clampedrelease = (release > __adsr_02_mspersamp ? release : __adsr_02_mspersamp);
        number currentTriggerVal = this->adsr_02_triggerValueBuf[(Index)i];

        if ((__adsr_02_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_02_triggerBuf[(Index)i] == 1) {
            if ((bool)(__adsr_02_legato)) {
                if (__adsr_02_phase != 0) {
                    __adsr_02_startingpoint = __adsr_02_outval;
                } else {
                    __adsr_02_startingpoint = 0;
                }
            } else {
                __adsr_02_startingpoint = 0;
            }

            __adsr_02_amplitude = currentTriggerVal;
            __adsr_02_phase = 1;
            __adsr_02_time = 0.0;
            bangMute = false;
        } else if (__adsr_02_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
            if (__adsr_02_phase != 4 && __adsr_02_phase != 0) {
                __adsr_02_phase = 4;
                __adsr_02_amplitude = __adsr_02_outval;
                __adsr_02_time = 0.0;
            }
        }

        __adsr_02_time += __adsr_02_mspersamp;

        if (__adsr_02_phase == 0) {
            __adsr_02_outval = 0;
        } else if (__adsr_02_phase == 1) {
            if (__adsr_02_time > clampedattack) {
                __adsr_02_time -= clampedattack;
                __adsr_02_phase = 2;
                __adsr_02_outval = __adsr_02_amplitude;
            } else {
                __adsr_02_outval = (__adsr_02_amplitude - __adsr_02_startingpoint) * __adsr_02_time / clampedattack + __adsr_02_startingpoint;
            }
        } else if (__adsr_02_phase == 2) {
            if (__adsr_02_time > clampeddecay) {
                __adsr_02_time -= clampeddecay;
                __adsr_02_phase = 3;
                __adsr_02_outval = __adsr_02_amplitude * sustain;
            } else {
                __adsr_02_outval = __adsr_02_amplitude * sustain + (__adsr_02_amplitude - __adsr_02_amplitude * sustain) * (1. - __adsr_02_time / clampeddecay);
            }
        } else if (__adsr_02_phase == 3) {
            __adsr_02_outval = __adsr_02_amplitude * sustain;
        } else if (__adsr_02_phase == 4) {
            if (__adsr_02_time > clampedrelease) {
                __adsr_02_time = 0;
                __adsr_02_phase = 0;
                __adsr_02_outval = 0;
                __adsr_02_amplitude = 0;
                bangMute = true;
            } else {
                __adsr_02_outval = __adsr_02_amplitude * (1.0 - __adsr_02_time / clampedrelease);
            }
        }

        out[(Index)i] = __adsr_02_outval;
        this->adsr_02_triggerBuf[(Index)i] = 0;
        this->adsr_02_triggerValueBuf[(Index)i] = __adsr_02_trigger_number;
        __adsr_02_lastTriggerVal = currentTriggerVal;
    }

    if ((bool)(bangMute)) {
        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1468824490,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            0
        );;
    }

    this->adsr_02_lastTriggerVal = __adsr_02_lastTriggerVal;
    this->adsr_02_phase = __adsr_02_phase;
    this->adsr_02_startingpoint = __adsr_02_startingpoint;
    this->adsr_02_outval = __adsr_02_outval;
    this->adsr_02_amplitude = __adsr_02_amplitude;
    this->adsr_02_time = __adsr_02_time;
}

void adsr_03_perform(
    number attack,
    number decay,
    number sustain,
    number release,
    const SampleValue * trigger_signal,
    SampleValue * out,
    Index n
) {
    RNBO_UNUSED(trigger_signal);
    RNBO_UNUSED(release);
    RNBO_UNUSED(sustain);
    RNBO_UNUSED(decay);
    RNBO_UNUSED(attack);
    auto __adsr_03_trigger_number = this->adsr_03_trigger_number;
    auto __adsr_03_time = this->adsr_03_time;
    auto __adsr_03_amplitude = this->adsr_03_amplitude;
    auto __adsr_03_outval = this->adsr_03_outval;
    auto __adsr_03_startingpoint = this->adsr_03_startingpoint;
    auto __adsr_03_phase = this->adsr_03_phase;
    auto __adsr_03_legato = this->adsr_03_legato;
    auto __adsr_03_lastTriggerVal = this->adsr_03_lastTriggerVal;
    auto __adsr_03_mspersamp = this->adsr_03_mspersamp;
    bool bangMute = false;

    for (Index i = 0; i < n; i++) {
        number clampedattack = (20 > __adsr_03_mspersamp ? 20 : __adsr_03_mspersamp);
        number clampeddecay = (50 > __adsr_03_mspersamp ? 50 : __adsr_03_mspersamp);
        number clampedrelease = (0 > __adsr_03_mspersamp ? 0 : __adsr_03_mspersamp);
        number currentTriggerVal = this->adsr_03_triggerValueBuf[(Index)i];

        if ((__adsr_03_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_03_triggerBuf[(Index)i] == 1) {
            if ((bool)(__adsr_03_legato)) {
                if (__adsr_03_phase != 0) {
                    __adsr_03_startingpoint = __adsr_03_outval;
                } else {
                    __adsr_03_startingpoint = 0;
                }
            } else {
                __adsr_03_startingpoint = 0;
            }

            __adsr_03_amplitude = currentTriggerVal;
            __adsr_03_phase = 1;
            __adsr_03_time = 0.0;
            bangMute = false;
        } else if (__adsr_03_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
            if (__adsr_03_phase != 4 && __adsr_03_phase != 0) {
                __adsr_03_phase = 4;
                __adsr_03_amplitude = __adsr_03_outval;
                __adsr_03_time = 0.0;
            }
        }

        __adsr_03_time += __adsr_03_mspersamp;

        if (__adsr_03_phase == 0) {
            __adsr_03_outval = 0;
        } else if (__adsr_03_phase == 1) {
            if (__adsr_03_time > clampedattack) {
                __adsr_03_time -= clampedattack;
                __adsr_03_phase = 2;
                __adsr_03_outval = __adsr_03_amplitude;
            } else {
                __adsr_03_outval = (__adsr_03_amplitude - __adsr_03_startingpoint) * __adsr_03_time / clampedattack + __adsr_03_startingpoint;
            }
        } else if (__adsr_03_phase == 2) {
            if (__adsr_03_time > clampeddecay) {
                __adsr_03_time -= clampeddecay;
                __adsr_03_phase = 3;
                __adsr_03_outval = __adsr_03_amplitude * 0;
            } else {
                __adsr_03_outval = __adsr_03_amplitude * 0 + (__adsr_03_amplitude - __adsr_03_amplitude * 0) * (1. - __adsr_03_time / clampeddecay);
            }
        } else if (__adsr_03_phase == 3) {
            __adsr_03_outval = __adsr_03_amplitude * 0;
        } else if (__adsr_03_phase == 4) {
            if (__adsr_03_time > clampedrelease) {
                __adsr_03_time = 0;
                __adsr_03_phase = 0;
                __adsr_03_outval = 0;
                __adsr_03_amplitude = 0;
                bangMute = true;
            } else {
                __adsr_03_outval = __adsr_03_amplitude * (1.0 - __adsr_03_time / clampedrelease);
            }
        }

        out[(Index)i] = __adsr_03_outval;
        this->adsr_03_triggerBuf[(Index)i] = 0;
        this->adsr_03_triggerValueBuf[(Index)i] = __adsr_03_trigger_number;
        __adsr_03_lastTriggerVal = currentTriggerVal;
    }

    if ((bool)(bangMute)) {
        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1096817259,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            0
        );;
    }

    this->adsr_03_lastTriggerVal = __adsr_03_lastTriggerVal;
    this->adsr_03_phase = __adsr_03_phase;
    this->adsr_03_startingpoint = __adsr_03_startingpoint;
    this->adsr_03_outval = __adsr_03_outval;
    this->adsr_03_amplitude = __adsr_03_amplitude;
    this->adsr_03_time = __adsr_03_time;
}

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void reson_tilde_03_perform(
    const Sample * x,
    number centerFreq,
    number resonanceValue,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(resonanceValue);
    RNBO_UNUSED(centerFreq);
    auto __reson_tilde_03_xm1 = this->reson_tilde_03_xm1;
    auto __reson_tilde_03_ym2 = this->reson_tilde_03_ym2;
    auto __reson_tilde_03_ym1 = this->reson_tilde_03_ym1;
    auto __reson_tilde_03_xm2 = this->reson_tilde_03_xm2;
    auto __reson_tilde_03_c2 = this->reson_tilde_03_c2;
    auto __reson_tilde_03_c1 = this->reson_tilde_03_c1;
    auto __reson_tilde_03_gainScale = this->reson_tilde_03_gainScale;
    auto __reson_tilde_03_r = this->reson_tilde_03_r;
    Index i;

    for (i = 0; i < n; i++) {
        number __centerFreq = 5000;
        __centerFreq = rnbo_abs(__centerFreq);

        if (this->reson_tilde_03_d_next(__centerFreq) != 0 || this->reson_tilde_03_d2_next(50) != 0) {
            number clippedResonance = 50;
            number bandWidth = __centerFreq * ((number)1 / clippedResonance);
            number twoPIOverSampleRate = 6.28318530717958647692 / this->sr;
            __reson_tilde_03_r = rnbo_exp(-(twoPIOverSampleRate * bandWidth));
            __reson_tilde_03_gainScale = 1 - __reson_tilde_03_r;
            __reson_tilde_03_c1 = 2. * __reson_tilde_03_r * rnbo_cos(__centerFreq * twoPIOverSampleRate);
            __reson_tilde_03_c2 = -(__reson_tilde_03_r * __reson_tilde_03_r);
        }

        number yn = __reson_tilde_03_gainScale * (x[(Index)i] - __reson_tilde_03_r * __reson_tilde_03_xm2) + __reson_tilde_03_c1 * __reson_tilde_03_ym1 + __reson_tilde_03_c2 * __reson_tilde_03_ym2;
        __reson_tilde_03_ym2 = __reson_tilde_03_ym1;
        __reson_tilde_03_ym1 = yn;
        __reson_tilde_03_xm2 = __reson_tilde_03_xm1;
        __reson_tilde_03_xm1 = x[(Index)i];
        out1[(Index)i] = yn;
    }

    this->reson_tilde_03_r = __reson_tilde_03_r;
    this->reson_tilde_03_gainScale = __reson_tilde_03_gainScale;
    this->reson_tilde_03_c1 = __reson_tilde_03_c1;
    this->reson_tilde_03_c2 = __reson_tilde_03_c2;
    this->reson_tilde_03_xm2 = __reson_tilde_03_xm2;
    this->reson_tilde_03_ym1 = __reson_tilde_03_ym1;
    this->reson_tilde_03_ym2 = __reson_tilde_03_ym2;
    this->reson_tilde_03_xm1 = __reson_tilde_03_xm1;
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

void delaytilde_02_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
    RNBO_UNUSED(delay);
    auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
    auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
    auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
    auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_02_lastDelay == -1) {
            __delaytilde_02_lastDelay = this->delaytilde_02_del_size();
        }

        if (__delaytilde_02_ramp > 0) {
            number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
            output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
            __delaytilde_02_ramp--;
        } else {
            number effectiveDelay = this->delaytilde_02_del_size();

            if (effectiveDelay != __delaytilde_02_lastDelay) {
                __delaytilde_02_ramp = __delaytilde_02_rampInSamples;
                __delaytilde_02_crossfadeDelay = __delaytilde_02_lastDelay;
                __delaytilde_02_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0);
                __delaytilde_02_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_02_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_02_del_write(input[(Index)i]);
        this->delaytilde_02_del_step();
    }

    this->delaytilde_02_lastDelay = __delaytilde_02_lastDelay;
    this->delaytilde_02_ramp = __delaytilde_02_ramp;
    this->delaytilde_02_crossfadeDelay = __delaytilde_02_crossfadeDelay;
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

void noise_tilde_01_perform(SampleValue * out1, Index n) {
    auto __noise_tilde_01_state = this->noise_tilde_01_state;
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = xoshiro_next(__noise_tilde_01_state);
    }
}

void reson_tilde_04_perform(
    const Sample * x,
    number centerFreq,
    number resonanceValue,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(resonanceValue);
    RNBO_UNUSED(centerFreq);
    auto __reson_tilde_04_xm1 = this->reson_tilde_04_xm1;
    auto __reson_tilde_04_ym2 = this->reson_tilde_04_ym2;
    auto __reson_tilde_04_ym1 = this->reson_tilde_04_ym1;
    auto __reson_tilde_04_xm2 = this->reson_tilde_04_xm2;
    auto __reson_tilde_04_c2 = this->reson_tilde_04_c2;
    auto __reson_tilde_04_c1 = this->reson_tilde_04_c1;
    auto __reson_tilde_04_gainScale = this->reson_tilde_04_gainScale;
    auto __reson_tilde_04_r = this->reson_tilde_04_r;
    Index i;

    for (i = 0; i < n; i++) {
        number __centerFreq = 15000;
        __centerFreq = rnbo_abs(__centerFreq);

        if (this->reson_tilde_04_d_next(__centerFreq) != 0 || this->reson_tilde_04_d2_next(20) != 0) {
            number clippedResonance = 20;
            number bandWidth = __centerFreq * ((number)1 / clippedResonance);
            number twoPIOverSampleRate = 6.28318530717958647692 / this->sr;
            __reson_tilde_04_r = rnbo_exp(-(twoPIOverSampleRate * bandWidth));
            __reson_tilde_04_gainScale = 1 - __reson_tilde_04_r;
            __reson_tilde_04_c1 = 2. * __reson_tilde_04_r * rnbo_cos(__centerFreq * twoPIOverSampleRate);
            __reson_tilde_04_c2 = -(__reson_tilde_04_r * __reson_tilde_04_r);
        }

        number yn = __reson_tilde_04_gainScale * (x[(Index)i] - __reson_tilde_04_r * __reson_tilde_04_xm2) + __reson_tilde_04_c1 * __reson_tilde_04_ym1 + __reson_tilde_04_c2 * __reson_tilde_04_ym2;
        __reson_tilde_04_ym2 = __reson_tilde_04_ym1;
        __reson_tilde_04_ym1 = yn;
        __reson_tilde_04_xm2 = __reson_tilde_04_xm1;
        __reson_tilde_04_xm1 = x[(Index)i];
        out1[(Index)i] = yn;
    }

    this->reson_tilde_04_r = __reson_tilde_04_r;
    this->reson_tilde_04_gainScale = __reson_tilde_04_gainScale;
    this->reson_tilde_04_c1 = __reson_tilde_04_c1;
    this->reson_tilde_04_c2 = __reson_tilde_04_c2;
    this->reson_tilde_04_xm2 = __reson_tilde_04_xm2;
    this->reson_tilde_04_ym1 = __reson_tilde_04_ym1;
    this->reson_tilde_04_ym2 = __reson_tilde_04_ym2;
    this->reson_tilde_04_xm1 = __reson_tilde_04_xm1;
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

void signaladder_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i] + in4[(Index)i] + in5[(Index)i];
    }
}

void delaytilde_01_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
    RNBO_UNUSED(delay);
    auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
    auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
    auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
    auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_01_lastDelay == -1) {
            __delaytilde_01_lastDelay = this->delaytilde_01_del_size();
        }

        if (__delaytilde_01_ramp > 0) {
            number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
            __delaytilde_01_ramp--;
        } else {
            number effectiveDelay = this->delaytilde_01_del_size();

            if (effectiveDelay != __delaytilde_01_lastDelay) {
                __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                __delaytilde_01_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                __delaytilde_01_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_01_del_write(input[(Index)i]);
        this->delaytilde_01_del_step();
    }

    this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
    this->delaytilde_01_ramp = __delaytilde_01_ramp;
    this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
}

void signaladder_03_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    const SampleValue * in6,
    const SampleValue * in7,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i] + in4[(Index)i] + in5[(Index)i] + in6[(Index)i] + in7[(Index)i];
    }
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void numberobj_02_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_02_value = localvalue;
}

void random_01_limit_setter(number v) {
    if (v >= 0)
        this->random_01_limit = v;
}

void toggle_01_value_number_setter(number v) {
    this->toggle_01_value_number = (v != 0 ? 1 : 0);
}

void metro_01_interval_setter(number v) {
    this->metro_01_interval = (v > 0 ? v : 0);
}

void numberobj_03_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_03_value = localvalue;
}

void random_02_limit_setter(number v) {
    if (v >= 0)
        this->random_02_limit = v;
}

void metro_02_interval_setter(number v) {
    this->metro_02_interval = (v > 0 ? v : 0);
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

number cycle_tilde_01_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_01_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_01_ph_conv;

    if (this->cycle_tilde_01_ph_currentPhase < 0.)
        this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;

    if (this->cycle_tilde_01_ph_currentPhase > 1.)
        this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_01_ph_currentPhase;
    this->cycle_tilde_01_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_01_ph_reset() {
    this->cycle_tilde_01_ph_currentPhase = 0;
}

void cycle_tilde_01_ph_dspsetup() {
    this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_01_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_01_phasei = 0;
    this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
    this->cycle_tilde_01_setupDone = true;
    this->cycle_tilde_01_ph_dspsetup();
}

void cycle_tilde_01_bufferUpdated() {
    this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
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

number reson_tilde_01_d_next(number x) {
    number temp = (number)(x - this->reson_tilde_01_d_prev);
    this->reson_tilde_01_d_prev = x;
    return temp;
}

void reson_tilde_01_d_dspsetup() {
    this->reson_tilde_01_d_reset();
}

void reson_tilde_01_d_reset() {
    this->reson_tilde_01_d_prev = 0;
}

number reson_tilde_01_d2_next(number x) {
    number temp = (number)(x - this->reson_tilde_01_d2_prev);
    this->reson_tilde_01_d2_prev = x;
    return temp;
}

void reson_tilde_01_d2_dspsetup() {
    this->reson_tilde_01_d2_reset();
}

void reson_tilde_01_d2_reset() {
    this->reson_tilde_01_d2_prev = 0;
}

void reson_tilde_01_reset() {
    this->reson_tilde_01_xm1 = 0;
    this->reson_tilde_01_xm2 = 0;
    this->reson_tilde_01_ym1 = 0;
    this->reson_tilde_01_ym2 = 0;
}

void reson_tilde_01_dspsetup(bool force) {
    if ((bool)(this->reson_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->reson_tilde_01_reset();
    this->reson_tilde_01_setupDone = true;
    this->reson_tilde_01_d_dspsetup();
    this->reson_tilde_01_d2_dspsetup();
}

number cycle_tilde_02_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_02_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_02_ph_conv;

    if (this->cycle_tilde_02_ph_currentPhase < 0.)
        this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;

    if (this->cycle_tilde_02_ph_currentPhase > 1.)
        this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_02_ph_currentPhase;
    this->cycle_tilde_02_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_02_ph_reset() {
    this->cycle_tilde_02_ph_currentPhase = 0;
}

void cycle_tilde_02_ph_dspsetup() {
    this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_02_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_02_phasei = 0;
    this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
    this->cycle_tilde_02_setupDone = true;
    this->cycle_tilde_02_ph_dspsetup();
}

void cycle_tilde_02_bufferUpdated() {
    this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-22"), 1, this->_currentTime);
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
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

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

number reson_tilde_02_d_next(number x) {
    number temp = (number)(x - this->reson_tilde_02_d_prev);
    this->reson_tilde_02_d_prev = x;
    return temp;
}

void reson_tilde_02_d_dspsetup() {
    this->reson_tilde_02_d_reset();
}

void reson_tilde_02_d_reset() {
    this->reson_tilde_02_d_prev = 0;
}

number reson_tilde_02_d2_next(number x) {
    number temp = (number)(x - this->reson_tilde_02_d2_prev);
    this->reson_tilde_02_d2_prev = x;
    return temp;
}

void reson_tilde_02_d2_dspsetup() {
    this->reson_tilde_02_d2_reset();
}

void reson_tilde_02_d2_reset() {
    this->reson_tilde_02_d2_prev = 0;
}

void reson_tilde_02_reset() {
    this->reson_tilde_02_xm1 = 0;
    this->reson_tilde_02_xm2 = 0;
    this->reson_tilde_02_ym1 = 0;
    this->reson_tilde_02_ym2 = 0;
}

void reson_tilde_02_dspsetup(bool force) {
    if ((bool)(this->reson_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->reson_tilde_02_reset();
    this->reson_tilde_02_setupDone = true;
    this->reson_tilde_02_d_dspsetup();
    this->reson_tilde_02_d2_dspsetup();
}

number cycle_tilde_03_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_03_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_03_ph_conv;

    if (this->cycle_tilde_03_ph_currentPhase < 0.)
        this->cycle_tilde_03_ph_currentPhase = 1. + this->cycle_tilde_03_ph_currentPhase;

    if (this->cycle_tilde_03_ph_currentPhase > 1.)
        this->cycle_tilde_03_ph_currentPhase = this->cycle_tilde_03_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_03_ph_currentPhase;
    this->cycle_tilde_03_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_03_ph_reset() {
    this->cycle_tilde_03_ph_currentPhase = 0;
}

void cycle_tilde_03_ph_dspsetup() {
    this->cycle_tilde_03_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_03_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_03_phasei = 0;
    this->cycle_tilde_03_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_03_wrap = (long)(this->cycle_tilde_03_buffer->getSize()) - 1;
    this->cycle_tilde_03_setupDone = true;
    this->cycle_tilde_03_ph_dspsetup();
}

void cycle_tilde_03_bufferUpdated() {
    this->cycle_tilde_03_wrap = (long)(this->cycle_tilde_03_buffer->getSize()) - 1;
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
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

void numberobj_02_init() {
    this->numberobj_02_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-24"), 1, this->_currentTime);
}

void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_02_value;
}

void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_02_value_set(preset["value"]);
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

number reson_tilde_03_d_next(number x) {
    number temp = (number)(x - this->reson_tilde_03_d_prev);
    this->reson_tilde_03_d_prev = x;
    return temp;
}

void reson_tilde_03_d_dspsetup() {
    this->reson_tilde_03_d_reset();
}

void reson_tilde_03_d_reset() {
    this->reson_tilde_03_d_prev = 0;
}

number reson_tilde_03_d2_next(number x) {
    number temp = (number)(x - this->reson_tilde_03_d2_prev);
    this->reson_tilde_03_d2_prev = x;
    return temp;
}

void reson_tilde_03_d2_dspsetup() {
    this->reson_tilde_03_d2_reset();
}

void reson_tilde_03_d2_reset() {
    this->reson_tilde_03_d2_prev = 0;
}

void reson_tilde_03_reset() {
    this->reson_tilde_03_xm1 = 0;
    this->reson_tilde_03_xm2 = 0;
    this->reson_tilde_03_ym1 = 0;
    this->reson_tilde_03_ym2 = 0;
}

void reson_tilde_03_dspsetup(bool force) {
    if ((bool)(this->reson_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->reson_tilde_03_reset();
    this->reson_tilde_03_setupDone = true;
    this->reson_tilde_03_d_dspsetup();
    this->reson_tilde_03_d2_dspsetup();
}

void delaytilde_01_del_step() {
    this->delaytilde_01_del_reader++;

    if (this->delaytilde_01_del_reader >= (int)(this->delaytilde_01_del_buffer->getSize()))
        this->delaytilde_01_del_reader = 0;
}

number delaytilde_01_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    }

    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->delaytilde_01_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
    );
}

void delaytilde_01_del_write(number v) {
    this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
    this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
}

number delaytilde_01_del_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
    number val = this->delaytilde_01_del_read(effectiveSize, 0);
    this->delaytilde_01_del_write(v);
    this->delaytilde_01_del_step();
    return val;
}

array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->delaytilde_01_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_01_del_init() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_01_del_clear() {
    this->delaytilde_01_del_buffer->setZero();
}

void delaytilde_01_del_reset() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_01_del_buffer);
    this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
    this->delaytilde_01_del_clear();

    if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
        this->delaytilde_01_del_reader = 0;
        this->delaytilde_01_del_writer = 0;
    }
}

void delaytilde_01_del_dspsetup() {
    this->delaytilde_01_del_reset();
}

number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 400;
}

number delaytilde_01_del_size() {
    return this->delaytilde_01_del__maxdelay;
}

void delaytilde_01_dspsetup(bool force) {
    if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_01_rampInSamples = (long)(this->mstosamps(50));
    this->delaytilde_01_lastDelay = -1;
    this->delaytilde_01_setupDone = true;
    this->delaytilde_01_del_dspsetup();
}

void random_01_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->random_01_nz_state
    );
}

void random_01_nz_init() {
    this->random_01_nz_reset();
}

void random_01_nz_seed(number v) {
    xoshiro_reset(v, this->random_01_nz_state);
}

number random_01_nz_next() {
    return xoshiro_next(this->random_01_nz_state);
}

number cycle_tilde_04_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_04_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_04_ph_conv;

    if (this->cycle_tilde_04_ph_currentPhase < 0.)
        this->cycle_tilde_04_ph_currentPhase = 1. + this->cycle_tilde_04_ph_currentPhase;

    if (this->cycle_tilde_04_ph_currentPhase > 1.)
        this->cycle_tilde_04_ph_currentPhase = this->cycle_tilde_04_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_04_ph_currentPhase;
    this->cycle_tilde_04_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_04_ph_reset() {
    this->cycle_tilde_04_ph_currentPhase = 0;
}

void cycle_tilde_04_ph_dspsetup() {
    this->cycle_tilde_04_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_04_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_04_phasei = 0;
    this->cycle_tilde_04_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_04_wrap = (long)(this->cycle_tilde_04_buffer->getSize()) - 1;
    this->cycle_tilde_04_setupDone = true;
    this->cycle_tilde_04_ph_dspsetup();
}

void cycle_tilde_04_bufferUpdated() {
    this->cycle_tilde_04_wrap = (long)(this->cycle_tilde_04_buffer->getSize()) - 1;
}

void toggle_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_01_value_number;
}

void toggle_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_01_value_number_set(preset["value"]);
}

void metro_01_onTransportChanged(number ) {}

void metro_01_onBeatTimeChanged(number ) {}

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

void delaytilde_02_del_step() {
    this->delaytilde_02_del_reader++;

    if (this->delaytilde_02_del_reader >= (int)(this->delaytilde_02_del_buffer->getSize()))
        this->delaytilde_02_del_reader = 0;
}

number delaytilde_02_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    }

    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->delaytilde_02_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
    );
}

void delaytilde_02_del_write(number v) {
    this->delaytilde_02_del_writer = this->delaytilde_02_del_reader;
    this->delaytilde_02_del_buffer[(Index)this->delaytilde_02_del_writer] = v;
}

number delaytilde_02_del_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_02_del__maxdelay : size);
    number val = this->delaytilde_02_del_read(effectiveSize, 0);
    this->delaytilde_02_del_write(v);
    this->delaytilde_02_del_step();
    return val;
}

array<Index, 2> delaytilde_02_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_02_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->delaytilde_02_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_02_del_init() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_02_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_02_del_clear() {
    this->delaytilde_02_del_buffer->setZero();
}

void delaytilde_02_del_reset() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_02_del_buffer);
    this->delaytilde_02_del_wrap = this->delaytilde_02_del_buffer->getSize() - 1;
    this->delaytilde_02_del_clear();

    if (this->delaytilde_02_del_reader >= this->delaytilde_02_del__maxdelay || this->delaytilde_02_del_writer >= this->delaytilde_02_del__maxdelay) {
        this->delaytilde_02_del_reader = 0;
        this->delaytilde_02_del_writer = 0;
    }
}

void delaytilde_02_del_dspsetup() {
    this->delaytilde_02_del_reset();
}

number delaytilde_02_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 150;
}

number delaytilde_02_del_size() {
    return this->delaytilde_02_del__maxdelay;
}

void delaytilde_02_dspsetup(bool force) {
    if ((bool)(this->delaytilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_02_rampInSamples = (long)(this->mstosamps(50));
    this->delaytilde_02_lastDelay = -1;
    this->delaytilde_02_setupDone = true;
    this->delaytilde_02_del_dspsetup();
}

void adsr_01_dspsetup(bool force) {
    if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_01_mspersamp = (number)1000 / this->sr;
    this->adsr_01_setupDone = true;
}

void message_01_init() {
    this->message_01_set_set({1});
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
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

number cycle_tilde_05_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_05_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_05_ph_conv;

    if (this->cycle_tilde_05_ph_currentPhase < 0.)
        this->cycle_tilde_05_ph_currentPhase = 1. + this->cycle_tilde_05_ph_currentPhase;

    if (this->cycle_tilde_05_ph_currentPhase > 1.)
        this->cycle_tilde_05_ph_currentPhase = this->cycle_tilde_05_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_05_ph_currentPhase;
    this->cycle_tilde_05_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_05_ph_reset() {
    this->cycle_tilde_05_ph_currentPhase = 0;
}

void cycle_tilde_05_ph_dspsetup() {
    this->cycle_tilde_05_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_05_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_05_phasei = 0;
    this->cycle_tilde_05_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_05_wrap = (long)(this->cycle_tilde_05_buffer->getSize()) - 1;
    this->cycle_tilde_05_setupDone = true;
    this->cycle_tilde_05_ph_dspsetup();
}

void cycle_tilde_05_bufferUpdated() {
    this->cycle_tilde_05_wrap = (long)(this->cycle_tilde_05_buffer->getSize()) - 1;
}

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-54"), 1, this->_currentTime);
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

void random_02_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->random_02_nz_state
    );
}

void random_02_nz_init() {
    this->random_02_nz_reset();
}

void random_02_nz_seed(number v) {
    xoshiro_reset(v, this->random_02_nz_state);
}

number random_02_nz_next() {
    return xoshiro_next(this->random_02_nz_state);
}

void metro_02_onTransportChanged(number ) {}

void metro_02_onBeatTimeChanged(number ) {}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void adsr_02_dspsetup(bool force) {
    if ((bool)(this->adsr_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_02_mspersamp = (number)1000 / this->sr;
    this->adsr_02_setupDone = true;
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
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

void message_02_init() {
    this->message_02_set_set({1});
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

void adsr_03_dspsetup(bool force) {
    if ((bool)(this->adsr_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_03_mspersamp = (number)1000 / this->sr;
    this->adsr_03_setupDone = true;
}

number reson_tilde_04_d_next(number x) {
    number temp = (number)(x - this->reson_tilde_04_d_prev);
    this->reson_tilde_04_d_prev = x;
    return temp;
}

void reson_tilde_04_d_dspsetup() {
    this->reson_tilde_04_d_reset();
}

void reson_tilde_04_d_reset() {
    this->reson_tilde_04_d_prev = 0;
}

number reson_tilde_04_d2_next(number x) {
    number temp = (number)(x - this->reson_tilde_04_d2_prev);
    this->reson_tilde_04_d2_prev = x;
    return temp;
}

void reson_tilde_04_d2_dspsetup() {
    this->reson_tilde_04_d2_reset();
}

void reson_tilde_04_d2_reset() {
    this->reson_tilde_04_d2_prev = 0;
}

void reson_tilde_04_reset() {
    this->reson_tilde_04_xm1 = 0;
    this->reson_tilde_04_xm2 = 0;
    this->reson_tilde_04_ym1 = 0;
    this->reson_tilde_04_ym2 = 0;
}

void reson_tilde_04_dspsetup(bool force) {
    if ((bool)(this->reson_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->reson_tilde_04_reset();
    this->reson_tilde_04_setupDone = true;
    this->reson_tilde_04_d_dspsetup();
    this->reson_tilde_04_d2_dspsetup();
}

void noise_tilde_01_init() {
    this->noise_tilde_01_reset();
}

void noise_tilde_01_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_01_state
    );
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
    param_01_value = 0;
    param_02_value = 0;
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    receive_01_output_number = 0;
    cycle_tilde_01_frequency = 0;
    cycle_tilde_01_phase_offset = 0;
    param_03_value = 0;
    gaintilde_02_input_number = 0;
    gaintilde_02_value = 0;
    gaintilde_02_interp = 10;
    expr_01_in1 = 0;
    expr_01_in2 = 12;
    expr_01_out1 = 0;
    receive_02_output_number = 0;
    reson_tilde_01_x = 0;
    reson_tilde_01_centerFreq = 1000;
    reson_tilde_01_resonanceValue = 40;
    cycle_tilde_02_frequency = 0;
    cycle_tilde_02_phase_offset = 0;
    param_04_value = 0.5;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    gaintilde_03_input_number = 0;
    gaintilde_03_value = 0;
    gaintilde_03_interp = 10;
    param_05_value = 0;
    reson_tilde_02_x = 0;
    reson_tilde_02_centerFreq = 8000;
    reson_tilde_02_resonanceValue = 30;
    cycle_tilde_03_frequency = 0;
    cycle_tilde_03_phase_offset = 0;
    expr_02_in1 = 0;
    expr_02_in2 = 14;
    expr_02_out1 = 0;
    receive_03_output_number = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    param_06_value = 0;
    gaintilde_04_input_number = 0;
    gaintilde_04_value = 0;
    gaintilde_04_interp = 10;
    numberobj_02_value = 0;
    numberobj_02_value_setter(numberobj_02_value);
    param_07_value = 0.2;
    param_08_value = 1;
    reson_tilde_03_x = 0;
    reson_tilde_03_centerFreq = 5000;
    reson_tilde_03_resonanceValue = 50;
    delaytilde_01_delay = 0;
    random_01_limit = 8000;
    random_01_limit_setter(random_01_limit);
    random_01_seed = 0;
    cycle_tilde_04_frequency = 0;
    cycle_tilde_04_phase_offset = 0;
    toggle_01_value_number = 0;
    toggle_01_value_number_setter(toggle_01_value_number);
    metro_01_on = 0;
    metro_01_interval = 500;
    metro_01_interval_setter(metro_01_interval);
    gaintilde_05_input_number = 0;
    gaintilde_05_value = 0;
    gaintilde_05_interp = 10;
    delaytilde_02_delay = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    adsr_01_trigger_number = 0;
    adsr_01_attack = 15;
    adsr_01_decay = 300;
    adsr_01_sustain = 0;
    adsr_01_release = 0;
    adsr_01_legato = 0;
    param_09_value = 0;
    param_10_value = 0;
    param_11_value = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    cycle_tilde_05_frequency = 0;
    cycle_tilde_05_phase_offset = 0;
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    random_02_limit = 8000;
    random_02_limit_setter(random_02_limit);
    random_02_seed = 0;
    metro_02_on = 0;
    metro_02_interval = 100;
    metro_02_interval_setter(metro_02_interval);
    param_12_value = 0;
    adsr_02_trigger_number = 0;
    adsr_02_attack = 0;
    adsr_02_decay = 0;
    adsr_02_sustain = 0;
    adsr_02_release = 0;
    adsr_02_legato = 0;
    param_13_value = 0;
    param_14_value = 0;
    gaintilde_06_input_number = 0;
    gaintilde_06_value = 0;
    gaintilde_06_interp = 10;
    param_15_value = 0;
    adsr_03_trigger_number = 0;
    adsr_03_attack = 20;
    adsr_03_decay = 50;
    adsr_03_sustain = 0;
    adsr_03_release = 0;
    adsr_03_legato = 0;
    reson_tilde_04_x = 0;
    reson_tilde_04_centerFreq = 15000;
    reson_tilde_04_resonanceValue = 20;
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
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
    cycle_tilde_01_wrap = 0;
    cycle_tilde_01_ph_currentPhase = 0;
    cycle_tilde_01_ph_conv = 0;
    cycle_tilde_01_setupDone = false;
    param_03_lastValue = 0;
    gaintilde_02_lastValue = 0;
    gaintilde_02_loginc = 1;
    gaintilde_02_zval = 0;
    gaintilde_02_ramp_d_prev = 0;
    gaintilde_02_ramp_prev = 0;
    gaintilde_02_ramp_index = 0;
    gaintilde_02_ramp_increment = 0;
    gaintilde_02_setupDone = false;
    reson_tilde_01_r = 0;
    reson_tilde_01_c1 = 0;
    reson_tilde_01_c2 = 0;
    reson_tilde_01_gainScale = 0;
    reson_tilde_01_xm1 = 0;
    reson_tilde_01_xm2 = 0;
    reson_tilde_01_ym1 = 0;
    reson_tilde_01_ym2 = 0;
    reson_tilde_01_d_prev = 0;
    reson_tilde_01_d2_prev = 0;
    reson_tilde_01_setupDone = false;
    cycle_tilde_02_wrap = 0;
    cycle_tilde_02_ph_currentPhase = 0;
    cycle_tilde_02_ph_conv = 0;
    cycle_tilde_02_setupDone = false;
    param_04_lastValue = 0;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    gaintilde_03_lastValue = 0;
    gaintilde_03_loginc = 1;
    gaintilde_03_zval = 0;
    gaintilde_03_ramp_d_prev = 0;
    gaintilde_03_ramp_prev = 0;
    gaintilde_03_ramp_index = 0;
    gaintilde_03_ramp_increment = 0;
    gaintilde_03_setupDone = false;
    param_05_lastValue = 0;
    reson_tilde_02_r = 0;
    reson_tilde_02_c1 = 0;
    reson_tilde_02_c2 = 0;
    reson_tilde_02_gainScale = 0;
    reson_tilde_02_xm1 = 0;
    reson_tilde_02_xm2 = 0;
    reson_tilde_02_ym1 = 0;
    reson_tilde_02_ym2 = 0;
    reson_tilde_02_d_prev = 0;
    reson_tilde_02_d2_prev = 0;
    reson_tilde_02_setupDone = false;
    cycle_tilde_03_wrap = 0;
    cycle_tilde_03_ph_currentPhase = 0;
    cycle_tilde_03_ph_conv = 0;
    cycle_tilde_03_setupDone = false;
    param_06_lastValue = 0;
    gaintilde_04_lastValue = 0;
    gaintilde_04_loginc = 1;
    gaintilde_04_zval = 0;
    gaintilde_04_ramp_d_prev = 0;
    gaintilde_04_ramp_prev = 0;
    gaintilde_04_ramp_index = 0;
    gaintilde_04_ramp_increment = 0;
    gaintilde_04_setupDone = false;
    numberobj_02_currentFormat = 6;
    numberobj_02_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    reson_tilde_03_r = 0;
    reson_tilde_03_c1 = 0;
    reson_tilde_03_c2 = 0;
    reson_tilde_03_gainScale = 0;
    reson_tilde_03_xm1 = 0;
    reson_tilde_03_xm2 = 0;
    reson_tilde_03_ym1 = 0;
    reson_tilde_03_ym2 = 0;
    reson_tilde_03_d_prev = 0;
    reson_tilde_03_d2_prev = 0;
    reson_tilde_03_setupDone = false;
    delaytilde_01_lastDelay = -1;
    delaytilde_01_crossfadeDelay = 0;
    delaytilde_01_ramp = 0;
    delaytilde_01_rampInSamples = 0;
    delaytilde_01_del__maxdelay = 0;
    delaytilde_01_del_sizemode = 0;
    delaytilde_01_del_wrap = 0;
    delaytilde_01_del_reader = 0;
    delaytilde_01_del_writer = 0;
    delaytilde_01_setupDone = false;
    cycle_tilde_04_wrap = 0;
    cycle_tilde_04_ph_currentPhase = 0;
    cycle_tilde_04_ph_conv = 0;
    cycle_tilde_04_setupDone = false;
    toggle_01_lastValue = 0;
    metro_01_last = -1;
    metro_01_next = -1;
    gaintilde_05_lastValue = 0;
    gaintilde_05_loginc = 1;
    gaintilde_05_zval = 0;
    gaintilde_05_ramp_d_prev = 0;
    gaintilde_05_ramp_prev = 0;
    gaintilde_05_ramp_index = 0;
    gaintilde_05_ramp_increment = 0;
    gaintilde_05_setupDone = false;
    delaytilde_02_lastDelay = -1;
    delaytilde_02_crossfadeDelay = 0;
    delaytilde_02_ramp = 0;
    delaytilde_02_rampInSamples = 0;
    delaytilde_02_del__maxdelay = 0;
    delaytilde_02_del_sizemode = 0;
    delaytilde_02_del_wrap = 0;
    delaytilde_02_del_reader = 0;
    delaytilde_02_del_writer = 0;
    delaytilde_02_setupDone = false;
    adsr_01_phase = 3;
    adsr_01_mspersamp = 0;
    adsr_01_time = 0;
    adsr_01_lastTriggerVal = 0;
    adsr_01_amplitude = 0;
    adsr_01_outval = 0;
    adsr_01_startingpoint = 0;
    adsr_01_triggerBuf = nullptr;
    adsr_01_triggerValueBuf = nullptr;
    adsr_01_setupDone = false;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    cycle_tilde_05_wrap = 0;
    cycle_tilde_05_ph_currentPhase = 0;
    cycle_tilde_05_ph_conv = 0;
    cycle_tilde_05_setupDone = false;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    metro_02_last = -1;
    metro_02_next = -1;
    param_12_lastValue = 0;
    adsr_02_phase = 3;
    adsr_02_mspersamp = 0;
    adsr_02_time = 0;
    adsr_02_lastTriggerVal = 0;
    adsr_02_amplitude = 0;
    adsr_02_outval = 0;
    adsr_02_startingpoint = 0;
    adsr_02_triggerBuf = nullptr;
    adsr_02_triggerValueBuf = nullptr;
    adsr_02_setupDone = false;
    param_13_lastValue = 0;
    param_14_lastValue = 0;
    gaintilde_06_lastValue = 0;
    gaintilde_06_loginc = 1;
    gaintilde_06_zval = 0;
    gaintilde_06_ramp_d_prev = 0;
    gaintilde_06_ramp_prev = 0;
    gaintilde_06_ramp_index = 0;
    gaintilde_06_ramp_increment = 0;
    gaintilde_06_setupDone = false;
    param_15_lastValue = 0;
    adsr_03_phase = 3;
    adsr_03_mspersamp = 0;
    adsr_03_time = 0;
    adsr_03_lastTriggerVal = 0;
    adsr_03_amplitude = 0;
    adsr_03_outval = 0;
    adsr_03_startingpoint = 0;
    adsr_03_triggerBuf = nullptr;
    adsr_03_triggerValueBuf = nullptr;
    adsr_03_setupDone = false;
    reson_tilde_04_r = 0;
    reson_tilde_04_c1 = 0;
    reson_tilde_04_c2 = 0;
    reson_tilde_04_gainScale = 0;
    reson_tilde_04_xm1 = 0;
    reson_tilde_04_xm2 = 0;
    reson_tilde_04_ym1 = 0;
    reson_tilde_04_ym2 = 0;
    reson_tilde_04_d_prev = 0;
    reson_tilde_04_d2_prev = 0;
    reson_tilde_04_setupDone = false;
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
    number param_02_value;
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number receive_01_output_number;
    list receive_01_output_list;
    number cycle_tilde_01_frequency;
    number cycle_tilde_01_phase_offset;
    number param_03_value;
    number gaintilde_02_input_number;
    number gaintilde_02_value;
    number gaintilde_02_interp;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    number receive_02_output_number;
    list receive_02_output_list;
    number reson_tilde_01_x;
    number reson_tilde_01_centerFreq;
    number reson_tilde_01_resonanceValue;
    number cycle_tilde_02_frequency;
    number cycle_tilde_02_phase_offset;
    number param_04_value;
    number numberobj_01_value;
    number gaintilde_03_input_number;
    number gaintilde_03_value;
    number gaintilde_03_interp;
    number param_05_value;
    number reson_tilde_02_x;
    number reson_tilde_02_centerFreq;
    number reson_tilde_02_resonanceValue;
    number cycle_tilde_03_frequency;
    number cycle_tilde_03_phase_offset;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number receive_03_output_number;
    list receive_03_output_list;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number param_06_value;
    number gaintilde_04_input_number;
    number gaintilde_04_value;
    number gaintilde_04_interp;
    number numberobj_02_value;
    number param_07_value;
    number param_08_value;
    number reson_tilde_03_x;
    number reson_tilde_03_centerFreq;
    number reson_tilde_03_resonanceValue;
    number delaytilde_01_delay;
    number random_01_limit;
    number random_01_seed;
    number cycle_tilde_04_frequency;
    number cycle_tilde_04_phase_offset;
    number toggle_01_value_number;
    number metro_01_on;
    number metro_01_interval;
    number gaintilde_05_input_number;
    number gaintilde_05_value;
    number gaintilde_05_interp;
    number delaytilde_02_delay;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number adsr_01_trigger_number;
    number adsr_01_attack;
    number adsr_01_decay;
    number adsr_01_sustain;
    number adsr_01_release;
    number adsr_01_legato;
    list message_01_set;
    number param_09_value;
    number param_10_value;
    number param_11_value;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number cycle_tilde_05_frequency;
    number cycle_tilde_05_phase_offset;
    number numberobj_03_value;
    number random_02_limit;
    number random_02_seed;
    number metro_02_on;
    number metro_02_interval;
    number param_12_value;
    number adsr_02_trigger_number;
    number adsr_02_attack;
    number adsr_02_decay;
    number adsr_02_sustain;
    number adsr_02_release;
    number adsr_02_legato;
    number param_13_value;
    number param_14_value;
    number gaintilde_06_input_number;
    number gaintilde_06_value;
    number gaintilde_06_interp;
    list message_02_set;
    number param_15_value;
    number adsr_03_trigger_number;
    number adsr_03_attack;
    number adsr_03_decay;
    number adsr_03_sustain;
    number adsr_03_release;
    number adsr_03_legato;
    number reson_tilde_04_x;
    number reson_tilde_04_centerFreq;
    number reson_tilde_04_resonanceValue;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[10];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
    Float64BufferRef cycle_tilde_01_buffer;
    long cycle_tilde_01_wrap;
    uint32_t cycle_tilde_01_phasei;
    SampleValue cycle_tilde_01_f2i;
    number cycle_tilde_01_ph_currentPhase;
    number cycle_tilde_01_ph_conv;
    bool cycle_tilde_01_setupDone;
    number param_03_lastValue;
    number gaintilde_02_lastValue;
    number gaintilde_02_loginc;
    number gaintilde_02_zval;
    number gaintilde_02_ramp_d_prev;
    number gaintilde_02_ramp_prev;
    number gaintilde_02_ramp_index;
    number gaintilde_02_ramp_increment;
    bool gaintilde_02_setupDone;
    number reson_tilde_01_r;
    number reson_tilde_01_c1;
    number reson_tilde_01_c2;
    number reson_tilde_01_gainScale;
    number reson_tilde_01_xm1;
    number reson_tilde_01_xm2;
    number reson_tilde_01_ym1;
    number reson_tilde_01_ym2;
    number reson_tilde_01_d_prev;
    number reson_tilde_01_d2_prev;
    bool reson_tilde_01_setupDone;
    Float64BufferRef cycle_tilde_02_buffer;
    long cycle_tilde_02_wrap;
    uint32_t cycle_tilde_02_phasei;
    SampleValue cycle_tilde_02_f2i;
    number cycle_tilde_02_ph_currentPhase;
    number cycle_tilde_02_ph_conv;
    bool cycle_tilde_02_setupDone;
    number param_04_lastValue;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    number gaintilde_03_lastValue;
    number gaintilde_03_loginc;
    number gaintilde_03_zval;
    number gaintilde_03_ramp_d_prev;
    number gaintilde_03_ramp_prev;
    number gaintilde_03_ramp_index;
    number gaintilde_03_ramp_increment;
    bool gaintilde_03_setupDone;
    number param_05_lastValue;
    number reson_tilde_02_r;
    number reson_tilde_02_c1;
    number reson_tilde_02_c2;
    number reson_tilde_02_gainScale;
    number reson_tilde_02_xm1;
    number reson_tilde_02_xm2;
    number reson_tilde_02_ym1;
    number reson_tilde_02_ym2;
    number reson_tilde_02_d_prev;
    number reson_tilde_02_d2_prev;
    bool reson_tilde_02_setupDone;
    Float64BufferRef cycle_tilde_03_buffer;
    long cycle_tilde_03_wrap;
    uint32_t cycle_tilde_03_phasei;
    SampleValue cycle_tilde_03_f2i;
    number cycle_tilde_03_ph_currentPhase;
    number cycle_tilde_03_ph_conv;
    bool cycle_tilde_03_setupDone;
    number param_06_lastValue;
    number gaintilde_04_lastValue;
    number gaintilde_04_loginc;
    number gaintilde_04_zval;
    number gaintilde_04_ramp_d_prev;
    number gaintilde_04_ramp_prev;
    number gaintilde_04_ramp_index;
    number gaintilde_04_ramp_increment;
    bool gaintilde_04_setupDone;
    Int numberobj_02_currentFormat;
    number numberobj_02_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number reson_tilde_03_r;
    number reson_tilde_03_c1;
    number reson_tilde_03_c2;
    number reson_tilde_03_gainScale;
    number reson_tilde_03_xm1;
    number reson_tilde_03_xm2;
    number reson_tilde_03_ym1;
    number reson_tilde_03_ym2;
    number reson_tilde_03_d_prev;
    number reson_tilde_03_d2_prev;
    bool reson_tilde_03_setupDone;
    number delaytilde_01_lastDelay;
    number delaytilde_01_crossfadeDelay;
    number delaytilde_01_ramp;
    long delaytilde_01_rampInSamples;
    Float64BufferRef delaytilde_01_del_buffer;
    Index delaytilde_01_del__maxdelay;
    Int delaytilde_01_del_sizemode;
    Index delaytilde_01_del_wrap;
    Int delaytilde_01_del_reader;
    Int delaytilde_01_del_writer;
    bool delaytilde_01_setupDone;
    UInt random_01_nz_state[4] = { };
    Float64BufferRef cycle_tilde_04_buffer;
    long cycle_tilde_04_wrap;
    uint32_t cycle_tilde_04_phasei;
    SampleValue cycle_tilde_04_f2i;
    number cycle_tilde_04_ph_currentPhase;
    number cycle_tilde_04_ph_conv;
    bool cycle_tilde_04_setupDone;
    number toggle_01_lastValue;
    number metro_01_last;
    number metro_01_next;
    number gaintilde_05_lastValue;
    number gaintilde_05_loginc;
    number gaintilde_05_zval;
    number gaintilde_05_ramp_d_prev;
    number gaintilde_05_ramp_prev;
    number gaintilde_05_ramp_index;
    number gaintilde_05_ramp_increment;
    bool gaintilde_05_setupDone;
    number delaytilde_02_lastDelay;
    number delaytilde_02_crossfadeDelay;
    number delaytilde_02_ramp;
    long delaytilde_02_rampInSamples;
    Float64BufferRef delaytilde_02_del_buffer;
    Index delaytilde_02_del__maxdelay;
    Int delaytilde_02_del_sizemode;
    Index delaytilde_02_del_wrap;
    Int delaytilde_02_del_reader;
    Int delaytilde_02_del_writer;
    bool delaytilde_02_setupDone;
    Int adsr_01_phase;
    number adsr_01_mspersamp;
    number adsr_01_time;
    number adsr_01_lastTriggerVal;
    number adsr_01_amplitude;
    number adsr_01_outval;
    number adsr_01_startingpoint;
    signal adsr_01_triggerBuf;
    signal adsr_01_triggerValueBuf;
    bool adsr_01_setupDone;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    Float64BufferRef cycle_tilde_05_buffer;
    long cycle_tilde_05_wrap;
    uint32_t cycle_tilde_05_phasei;
    SampleValue cycle_tilde_05_f2i;
    number cycle_tilde_05_ph_currentPhase;
    number cycle_tilde_05_ph_conv;
    bool cycle_tilde_05_setupDone;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    UInt random_02_nz_state[4] = { };
    number metro_02_last;
    number metro_02_next;
    number param_12_lastValue;
    Int adsr_02_phase;
    number adsr_02_mspersamp;
    number adsr_02_time;
    number adsr_02_lastTriggerVal;
    number adsr_02_amplitude;
    number adsr_02_outval;
    number adsr_02_startingpoint;
    signal adsr_02_triggerBuf;
    signal adsr_02_triggerValueBuf;
    bool adsr_02_setupDone;
    number param_13_lastValue;
    number param_14_lastValue;
    number gaintilde_06_lastValue;
    number gaintilde_06_loginc;
    number gaintilde_06_zval;
    number gaintilde_06_ramp_d_prev;
    number gaintilde_06_ramp_prev;
    number gaintilde_06_ramp_index;
    number gaintilde_06_ramp_increment;
    bool gaintilde_06_setupDone;
    number param_15_lastValue;
    Int adsr_03_phase;
    number adsr_03_mspersamp;
    number adsr_03_time;
    number adsr_03_lastTriggerVal;
    number adsr_03_amplitude;
    number adsr_03_outval;
    number adsr_03_startingpoint;
    signal adsr_03_triggerBuf;
    signal adsr_03_triggerValueBuf;
    bool adsr_03_setupDone;
    number reson_tilde_04_r;
    number reson_tilde_04_c1;
    number reson_tilde_04_c2;
    number reson_tilde_04_gainScale;
    number reson_tilde_04_xm1;
    number reson_tilde_04_xm2;
    number reson_tilde_04_ym1;
    number reson_tilde_04_ym2;
    number reson_tilde_04_d_prev;
    number reson_tilde_04_d2_prev;
    bool reson_tilde_04_setupDone;
    UInt noise_tilde_01_state[4] = { };
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
    DataRef RNBODefaultSinus;
    DataRef delaytilde_01_del_bufferobj;
    DataRef delaytilde_02_del_bufferobj;
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

