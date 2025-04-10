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

    this->reson_tilde_01_perform(
        this->signals[0],
        this->reson_tilde_01_centerFreq,
        this->reson_tilde_01_resonanceValue,
        this->signals[1],
        n
    );

    this->cycle_tilde_02_perform(
        this->cycle_tilde_02_frequency,
        this->cycle_tilde_02_phase_offset,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->cycle_tilde_03_perform(
        this->cycle_tilde_03_frequency,
        this->cycle_tilde_03_phase_offset,
        this->signals[2],
        this->dummyBuffer,
        n
    );

    this->biquad_tilde_01_perform(
        this->signals[1],
        this->signals[0],
        this->biquad_tilde_01_a1,
        this->signals[2],
        this->biquad_tilde_01_b1,
        this->signals[0],
        this->signals[3],
        n
    );

    this->gaintilde_01_perform(this->signals[3], this->signals[2], n);

    this->cycle_tilde_04_perform(
        this->cycle_tilde_04_frequency,
        this->cycle_tilde_04_phase_offset,
        this->signals[3],
        this->dummyBuffer,
        n
    );

    this->cycle_tilde_05_perform(
        this->cycle_tilde_05_frequency,
        this->cycle_tilde_05_phase_offset,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->comb_tilde_01_perform(
        this->signals[1],
        this->comb_tilde_01_delayTime,
        this->signals[3],
        this->signals[0],
        this->comb_tilde_01_fbGain,
        this->signals[4],
        n
    );

    this->gaintilde_02_perform(this->signals[4], this->signals[0], n);
    this->signaladder_01_perform(this->signals[2], this->signals[0], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 5; i++) {
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

    this->cycle_tilde_01_dspsetup(forceDSPSetup);
    this->reson_tilde_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_02_dspsetup(forceDSPSetup);
    this->cycle_tilde_03_dspsetup(forceDSPSetup);
    this->biquad_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_04_dspsetup(forceDSPSetup);
    this->cycle_tilde_05_dspsetup(forceDSPSetup);
    this->comb_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_02_dspsetup(forceDSPSetup);
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
        return addressOf(this->comb_tilde_01_feedForward_bufferobj);
        break;
        }
    case 2:
        {
        return addressOf(this->comb_tilde_01_feedBack_bufferobj);
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
        this->comb_tilde_01_feedForward_buffer = new Float64Buffer(this->comb_tilde_01_feedForward_bufferobj);
    }

    if (index == 2) {
        this->comb_tilde_01_feedBack_buffer = new Float64Buffer(this->comb_tilde_01_feedBack_bufferobj);
    }
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->comb_tilde_01_feedForward_bufferobj = initDataRef("comb_tilde_01_feedForward_bufferobj", true, nullptr, "buffer~");
    this->comb_tilde_01_feedBack_bufferobj = initDataRef("comb_tilde_01_feedBack_bufferobj", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_03_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_04_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_05_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->comb_tilde_01_feedForward_bufferobj->setIndex(1);
    this->comb_tilde_01_feedForward_buffer = new Float64Buffer(this->comb_tilde_01_feedForward_bufferobj);
    this->comb_tilde_01_feedBack_bufferobj->setIndex(2);
    this->comb_tilde_01_feedBack_buffer = new Float64Buffer(this->comb_tilde_01_feedBack_bufferobj);
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
    this->param_01_getPresetValue(getSubState(preset, "fbgain"));
    this->param_02_getPresetValue(getSubState(preset, "cgain"));
    this->param_03_getPresetValue(getSubState(preset, "delaytime"));
    this->param_04_getPresetValue(getSubState(preset, "freq"));
    this->param_05_getPresetValue(getSubState(preset, "ffgain"));
    this->param_06_getPresetValue(getSubState(preset, "reson"));
    this->param_07_getPresetValue(getSubState(preset, "bpfreq"));
    this->param_08_getPresetValue(getSubState(preset, "soft"));
    this->param_09_getPresetValue(getSubState(preset, "grit"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "fbgain"));
    this->param_02_setPresetValue(getSubState(preset, "cgain"));
    this->param_03_setPresetValue(getSubState(preset, "delaytime"));
    this->param_04_setPresetValue(getSubState(preset, "freq"));
    this->param_05_setPresetValue(getSubState(preset, "ffgain"));
    this->param_06_setPresetValue(getSubState(preset, "reson"));
    this->param_07_setPresetValue(getSubState(preset, "bpfreq"));
    this->param_08_setPresetValue(getSubState(preset, "soft"));
    this->param_09_setPresetValue(getSubState(preset, "grit"));
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
    return 9;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "fbgain";
        }
    case 1:
        {
        return "cgain";
        }
    case 2:
        {
        return "delaytime";
        }
    case 3:
        {
        return "freq";
        }
    case 4:
        {
        return "ffgain";
        }
    case 5:
        {
        return "reson";
        }
    case 6:
        {
        return "bpfreq";
        }
    case 7:
        {
        return "soft";
        }
    case 8:
        {
        return "grit";
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
        return "fbgain";
        }
    case 1:
        {
        return "cgain";
        }
    case 2:
        {
        return "delaytime";
        }
    case 3:
        {
        return "freq";
        }
    case 4:
        {
        return "ffgain";
        }
    case 5:
        {
        return "reson";
        }
    case 6:
        {
        return "bpfreq";
        }
    case 7:
        {
        return "soft";
        }
    case 8:
        {
        return "grit";
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
        case 1:
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
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 5000;
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
        case 4:
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
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 100;
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
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 157;
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
            info->max = 157;
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
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 7:
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 157 ? 157 : value));
            ParameterValue normalizedValue = (value - 0) / (157 - 0);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
            ParameterValue normalizedValue = (value - 0) / (5000 - 0);
            return normalizedValue;
        }
        }
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 0) / (20000 - 0);
            return normalizedValue;
        }
        }
    case 3:
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
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 7:
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (157 - 0);
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (5000 - 0);
            }
        }
        }
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (20000 - 0);
            }
        }
        }
    case 3:
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
        if (TAG("gain~_obj-6") == objectId)
            this->gaintilde_01_valin_set(payload);

        if (TAG("gain~_obj-13") == objectId)
            this->gaintilde_02_valin_set(payload);

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
    case TAG("gain~_obj-6"):
        {
        return "gain~_obj-6";
        }
    case TAG("gain~_obj-13"):
        {
        return "gain~_obj-13";
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

    this->send_03_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->send_04_input_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->send_05_input_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->send_02_input_number_set(v);
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

void gaintilde_01_valin_set(number v) {
    this->gaintilde_01_value_set(v);
}

void gaintilde_02_valin_set(number v) {
    this->gaintilde_02_value_set(v);
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

    this->comb_tilde_01_feedForward_buffer = this->comb_tilde_01_feedForward_buffer->allocateIfNeeded();

    if (this->comb_tilde_01_feedForward_bufferobj->hasRequestedSize()) {
        if (this->comb_tilde_01_feedForward_bufferobj->wantsFill())
            this->zeroDataRef(this->comb_tilde_01_feedForward_bufferobj);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->comb_tilde_01_feedBack_buffer = this->comb_tilde_01_feedBack_buffer->allocateIfNeeded();

    if (this->comb_tilde_01_feedBack_bufferobj->hasRequestedSize()) {
        if (this->comb_tilde_01_feedBack_bufferobj->wantsFill())
            this->zeroDataRef(this->comb_tilde_01_feedBack_bufferobj);

        this->getEngine()->sendDataRefUpdated(2);
    }
}

void initializeObjects() {
    this->gaintilde_01_init();
    this->gaintilde_02_init();
    this->comb_tilde_01_feedForward_init();
    this->comb_tilde_01_feedBack_init();
    this->comb_tilde_01_init();
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

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void biquad_tilde_01_b1_set(number v) {
    this->biquad_tilde_01_b1 = v;
}

void receive_07_output_number_set(number v) {
    this->receive_07_output_number = v;
    this->biquad_tilde_01_b1_set(v);
}

void comb_tilde_01_fbGain_set(number v) {
    this->comb_tilde_01_fbGain = v;
}

void receive_10_output_number_set(number v) {
    this->receive_10_output_number = v;
    this->comb_tilde_01_fbGain_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_07_output_number_set(v);
    this->receive_10_output_number_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void send_03_input_number_set(number v) {
    this->send_03_input_number = v;
}

static number param_03_value_constrain(number v) {
    v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
    return v;
}

void comb_tilde_01_delayTime_set(number v) {
    this->comb_tilde_01_delayTime = v;
}

void receive_09_output_number_set(number v) {
    this->receive_09_output_number = v;
    this->comb_tilde_01_delayTime_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->receive_09_output_number_set(v);
}

static number param_04_value_constrain(number v) {
    v = (v > 2093 ? 2093 : (v < 32.703 ? 32.703 : v));
    return v;
}

void cycle_tilde_01_frequency_set(number v) {
    this->cycle_tilde_01_frequency = v;
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->cycle_tilde_01_frequency_set(v);
}

void cycle_tilde_02_frequency_set(number v) {
    this->cycle_tilde_02_frequency = v;
}

void receive_04_output_number_set(number v) {
    this->receive_04_output_number = v;
    this->cycle_tilde_02_frequency_set(v);
}

void send_05_input_number_set(number v) {
    this->send_05_input_number = v;
    this->receive_02_output_number_set(v);
    this->receive_04_output_number_set(v);
}

static number param_05_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void biquad_tilde_01_a1_set(number v) {
    this->biquad_tilde_01_a1 = v;
}

void receive_05_output_number_set(number v) {
    this->receive_05_output_number = v;
    this->biquad_tilde_01_a1_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_05_output_number_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void reson_tilde_01_resonanceValue_set(number v) {
    this->reson_tilde_01_resonanceValue = v;
}

void receive_06_output_number_set(number v) {
    this->receive_06_output_number = v;
    this->reson_tilde_01_resonanceValue_set(v);
}

void send_06_input_number_set(number v) {
    this->send_06_input_number = v;
    this->receive_06_output_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 20000 ? 20000 : (v < 0 ? 0 : v));
    return v;
}

void reson_tilde_01_centerFreq_set(number v) {
    this->reson_tilde_01_centerFreq = v;
}

void receive_03_output_number_set(number v) {
    this->receive_03_output_number = v;
    this->reson_tilde_01_centerFreq_set(v);
}

void send_07_input_number_set(number v) {
    this->send_07_input_number = v;
    this->receive_03_output_number_set(v);
}

static number param_08_value_constrain(number v) {
    v = (v > 157 ? 157 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_02_outval_set(number ) {}

void gaintilde_02_value_set(number v) {
    this->gaintilde_02_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-13"), v, this->_currentTime);
    this->gaintilde_02_outval_set(value);
}

void gaintilde_02_input_number_set(number v) {
    this->gaintilde_02_input_number = v;

    this->gaintilde_02_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void receive_08_output_number_set(number v) {
    this->receive_08_output_number = v;
    this->gaintilde_02_input_number_set(v);
}

void send_08_input_number_set(number v) {
    this->send_08_input_number = v;
    this->receive_08_output_number_set(v);
}

static number param_09_value_constrain(number v) {
    v = (v > 157 ? 157 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-6"), v, this->_currentTime);
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

void send_09_input_number_set(number v) {
    this->send_09_input_number = v;
    this->receive_01_output_number_set(v);
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

void reson_tilde_01_perform(
    const Sample * x,
    number centerFreq,
    number resonanceValue,
    SampleValue * out1,
    Index n
) {
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
        number __centerFreq = centerFreq;
        __centerFreq = rnbo_abs(__centerFreq);

        if (this->reson_tilde_01_d_next(__centerFreq) != 0 || this->reson_tilde_01_d2_next(resonanceValue) != 0) {
            number clippedResonance = (resonanceValue < 0. ? 0.01 : resonanceValue);
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

void cycle_tilde_02_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
    auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
    auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_02_phasei;
                }
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

void cycle_tilde_03_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    RNBO_UNUSED(frequency);
    auto __cycle_tilde_03_f2i = this->cycle_tilde_03_f2i;
    auto __cycle_tilde_03_buffer = this->cycle_tilde_03_buffer;
    auto __cycle_tilde_03_phasei = this->cycle_tilde_03_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_03_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_03_buffer[(Index)idx];
            number y1 = __cycle_tilde_03_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(0 * __cycle_tilde_03_f2i));
                __cycle_tilde_03_phasei = uint32_add(__cycle_tilde_03_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_03_phasei = __cycle_tilde_03_phasei;
}

void biquad_tilde_01_perform(
    const Sample * x,
    const Sample * a0,
    number a1,
    const Sample * a2,
    number b1,
    const Sample * b2,
    SampleValue * out1,
    Index n
) {
    auto __biquad_tilde_01_y2 = this->biquad_tilde_01_y2;
    auto __biquad_tilde_01_y1 = this->biquad_tilde_01_y1;
    auto __biquad_tilde_01_x2 = this->biquad_tilde_01_x2;
    auto __biquad_tilde_01_x1 = this->biquad_tilde_01_x1;
    Index i;

    for (i = 0; i < n; i++) {
        number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_01_x1 * a1 + __biquad_tilde_01_x2 * a2[(Index)i] - (__biquad_tilde_01_y1 * b1 + __biquad_tilde_01_y2 * b2[(Index)i]);
        __biquad_tilde_01_x2 = __biquad_tilde_01_x1;
        __biquad_tilde_01_x1 = x[(Index)i];
        __biquad_tilde_01_y2 = __biquad_tilde_01_y1;
        __biquad_tilde_01_y1 = tmp;
        out1[(Index)i] = tmp;
    }

    this->biquad_tilde_01_x1 = __biquad_tilde_01_x1;
    this->biquad_tilde_01_x2 = __biquad_tilde_01_x2;
    this->biquad_tilde_01_y1 = __biquad_tilde_01_y1;
    this->biquad_tilde_01_y2 = __biquad_tilde_01_y2;
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

void cycle_tilde_04_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    RNBO_UNUSED(frequency);
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
                uint32_t pincr = (uint32_t)(uint32_trunc(0 * __cycle_tilde_04_f2i));
                __cycle_tilde_04_phasei = uint32_add(__cycle_tilde_04_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_04_phasei = __cycle_tilde_04_phasei;
}

void cycle_tilde_05_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    RNBO_UNUSED(frequency);
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
                uint32_t pincr = (uint32_t)(uint32_trunc(0 * __cycle_tilde_05_f2i));
                __cycle_tilde_05_phasei = uint32_add(__cycle_tilde_05_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_05_phasei = __cycle_tilde_05_phasei;
}

void comb_tilde_01_perform(
    const Sample * x,
    number delayTime,
    const Sample * gain,
    const Sample * ffGain,
    number fbGain,
    SampleValue * out1,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        number __fbGain = fbGain;
        number __ffGain = ffGain[(Index)i];
        number __gain = gain[(Index)i];
        number __delayTime = delayTime;
        __delayTime = this->mstosamps(__delayTime);
        __delayTime = (__delayTime > this->sr ? this->sr : (__delayTime < 0 ? 0 : __delayTime));
        __gain = (__gain > 1 ? 1 : (__gain < 0 ? 0 : __gain));
        __ffGain = (__ffGain > 0.99 ? 0.99 : (__ffGain < 0 ? 0 : __ffGain));
        __fbGain = (__fbGain > 0.99 ? 0.99 : (__fbGain < 0 ? 0 : __fbGain));
        number tmp = x[(Index)i] * __gain;
        number ff = this->comb_tilde_01_feedForward_read(__delayTime, 0);
        number fb = this->comb_tilde_01_feedBack_read(__delayTime, 0);
        number ov = tmp + ff * __ffGain + fb * __fbGain;
        fixdenorm(ov);
        this->comb_tilde_01_feedForward_write(x[(Index)i]);
        this->comb_tilde_01_feedBack_write(ov);
        this->comb_tilde_01_feedForward_step();
        this->comb_tilde_01_feedBack_step();
        out1[(Index)i] = ov;
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

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
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

void biquad_tilde_01_reset() {
    this->biquad_tilde_01_x1 = 0;
    this->biquad_tilde_01_x2 = 0;
    this->biquad_tilde_01_y1 = 0;
    this->biquad_tilde_01_y2 = 0;
}

void biquad_tilde_01_dspsetup(bool force) {
    if ((bool)(this->biquad_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->biquad_tilde_01_reset();
    this->biquad_tilde_01_setupDone = true;
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

void comb_tilde_01_feedForward_step() {
    this->comb_tilde_01_feedForward_reader++;

    if (this->comb_tilde_01_feedForward_reader >= (int)(this->comb_tilde_01_feedForward_buffer->getSize()))
        this->comb_tilde_01_feedForward_reader = 0;
}

number comb_tilde_01_feedForward_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->comb_tilde_01_feedForward_buffer->getSize()) + this->comb_tilde_01_feedForward_reader - ((size > this->comb_tilde_01_feedForward__maxdelay ? this->comb_tilde_01_feedForward__maxdelay : (size < (this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer) ? this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->comb_tilde_01_feedForward_buffer->getSize()) + this->comb_tilde_01_feedForward_reader - ((size > this->comb_tilde_01_feedForward__maxdelay ? this->comb_tilde_01_feedForward__maxdelay : (size < (1 + this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer) ? 1 + this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->comb_tilde_01_feedForward_buffer->getSize()) + this->comb_tilde_01_feedForward_reader - ((size > this->comb_tilde_01_feedForward__maxdelay ? this->comb_tilde_01_feedForward__maxdelay : (size < (1 + this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer) ? 1 + this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->comb_tilde_01_feedForward_buffer->getSize()) + this->comb_tilde_01_feedForward_reader - ((size > this->comb_tilde_01_feedForward__maxdelay ? this->comb_tilde_01_feedForward__maxdelay : (size < (this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer) ? this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ), this->comb_tilde_01_feedForward_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
        ));
    }

    number r = (int)(this->comb_tilde_01_feedForward_buffer->getSize()) + this->comb_tilde_01_feedForward_reader - ((size > this->comb_tilde_01_feedForward__maxdelay ? this->comb_tilde_01_feedForward__maxdelay : (size < (this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer) ? this->comb_tilde_01_feedForward_reader != this->comb_tilde_01_feedForward_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->comb_tilde_01_feedForward_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedForward_wrap))
    );
}

void comb_tilde_01_feedForward_write(number v) {
    this->comb_tilde_01_feedForward_writer = this->comb_tilde_01_feedForward_reader;
    this->comb_tilde_01_feedForward_buffer[(Index)this->comb_tilde_01_feedForward_writer] = v;
}

number comb_tilde_01_feedForward_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->comb_tilde_01_feedForward__maxdelay : size);
    number val = this->comb_tilde_01_feedForward_read(effectiveSize, 0);
    this->comb_tilde_01_feedForward_write(v);
    this->comb_tilde_01_feedForward_step();
    return val;
}

array<Index, 2> comb_tilde_01_feedForward_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->comb_tilde_01_feedForward_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->comb_tilde_01_feedForward_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void comb_tilde_01_feedForward_init() {
    auto result = this->comb_tilde_01_feedForward_calcSizeInSamples();
    this->comb_tilde_01_feedForward__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->comb_tilde_01_feedForward_buffer->requestSize(requestedSizeInSamples, 1);
    this->comb_tilde_01_feedForward_wrap = requestedSizeInSamples - 1;
}

void comb_tilde_01_feedForward_clear() {
    this->comb_tilde_01_feedForward_buffer->setZero();
}

void comb_tilde_01_feedForward_reset() {
    auto result = this->comb_tilde_01_feedForward_calcSizeInSamples();
    this->comb_tilde_01_feedForward__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->comb_tilde_01_feedForward_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->comb_tilde_01_feedForward_buffer);
    this->comb_tilde_01_feedForward_wrap = this->comb_tilde_01_feedForward_buffer->getSize() - 1;
    this->comb_tilde_01_feedForward_clear();

    if (this->comb_tilde_01_feedForward_reader >= this->comb_tilde_01_feedForward__maxdelay || this->comb_tilde_01_feedForward_writer >= this->comb_tilde_01_feedForward__maxdelay) {
        this->comb_tilde_01_feedForward_reader = 0;
        this->comb_tilde_01_feedForward_writer = 0;
    }
}

void comb_tilde_01_feedForward_dspsetup() {
    this->comb_tilde_01_feedForward_reset();
}

number comb_tilde_01_feedForward_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 44100;
}

number comb_tilde_01_feedForward_size() {
    return this->comb_tilde_01_feedForward__maxdelay;
}

void comb_tilde_01_feedBack_step() {
    this->comb_tilde_01_feedBack_reader++;

    if (this->comb_tilde_01_feedBack_reader >= (int)(this->comb_tilde_01_feedBack_buffer->getSize()))
        this->comb_tilde_01_feedBack_reader = 0;
}

number comb_tilde_01_feedBack_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->comb_tilde_01_feedBack_buffer->getSize()) + this->comb_tilde_01_feedBack_reader - ((size > this->comb_tilde_01_feedBack__maxdelay ? this->comb_tilde_01_feedBack__maxdelay : (size < (this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer) ? this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->comb_tilde_01_feedBack_buffer->getSize()) + this->comb_tilde_01_feedBack_reader - ((size > this->comb_tilde_01_feedBack__maxdelay ? this->comb_tilde_01_feedBack__maxdelay : (size < (1 + this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer) ? 1 + this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->comb_tilde_01_feedBack_buffer->getSize()) + this->comb_tilde_01_feedBack_reader - ((size > this->comb_tilde_01_feedBack__maxdelay ? this->comb_tilde_01_feedBack__maxdelay : (size < (1 + this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer) ? 1 + this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->comb_tilde_01_feedBack_buffer->getSize()) + this->comb_tilde_01_feedBack_reader - ((size > this->comb_tilde_01_feedBack__maxdelay ? this->comb_tilde_01_feedBack__maxdelay : (size < (this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer) ? this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ), this->comb_tilde_01_feedBack_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
        ));
    }

    number r = (int)(this->comb_tilde_01_feedBack_buffer->getSize()) + this->comb_tilde_01_feedBack_reader - ((size > this->comb_tilde_01_feedBack__maxdelay ? this->comb_tilde_01_feedBack__maxdelay : (size < (this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer) ? this->comb_tilde_01_feedBack_reader != this->comb_tilde_01_feedBack_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->comb_tilde_01_feedBack_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->comb_tilde_01_feedBack_wrap))
    );
}

void comb_tilde_01_feedBack_write(number v) {
    this->comb_tilde_01_feedBack_writer = this->comb_tilde_01_feedBack_reader;
    this->comb_tilde_01_feedBack_buffer[(Index)this->comb_tilde_01_feedBack_writer] = v;
}

number comb_tilde_01_feedBack_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->comb_tilde_01_feedBack__maxdelay : size);
    number val = this->comb_tilde_01_feedBack_read(effectiveSize, 0);
    this->comb_tilde_01_feedBack_write(v);
    this->comb_tilde_01_feedBack_step();
    return val;
}

array<Index, 2> comb_tilde_01_feedBack_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->comb_tilde_01_feedBack_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->comb_tilde_01_feedBack_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void comb_tilde_01_feedBack_init() {
    auto result = this->comb_tilde_01_feedBack_calcSizeInSamples();
    this->comb_tilde_01_feedBack__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->comb_tilde_01_feedBack_buffer->requestSize(requestedSizeInSamples, 1);
    this->comb_tilde_01_feedBack_wrap = requestedSizeInSamples - 1;
}

void comb_tilde_01_feedBack_clear() {
    this->comb_tilde_01_feedBack_buffer->setZero();
}

void comb_tilde_01_feedBack_reset() {
    auto result = this->comb_tilde_01_feedBack_calcSizeInSamples();
    this->comb_tilde_01_feedBack__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->comb_tilde_01_feedBack_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->comb_tilde_01_feedBack_buffer);
    this->comb_tilde_01_feedBack_wrap = this->comb_tilde_01_feedBack_buffer->getSize() - 1;
    this->comb_tilde_01_feedBack_clear();

    if (this->comb_tilde_01_feedBack_reader >= this->comb_tilde_01_feedBack__maxdelay || this->comb_tilde_01_feedBack_writer >= this->comb_tilde_01_feedBack__maxdelay) {
        this->comb_tilde_01_feedBack_reader = 0;
        this->comb_tilde_01_feedBack_writer = 0;
    }
}

void comb_tilde_01_feedBack_dspsetup() {
    this->comb_tilde_01_feedBack_reset();
}

number comb_tilde_01_feedBack_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 44100;
}

number comb_tilde_01_feedBack_size() {
    return this->comb_tilde_01_feedBack__maxdelay;
}

void comb_tilde_01_init() {
    this->comb_tilde_01_feedForward_init();
    this->comb_tilde_01_feedBack_init();
}

void comb_tilde_01_clear() {
    this->comb_tilde_01_feedForward_clear();
    this->comb_tilde_01_feedBack_clear();
}

void comb_tilde_01_reset() {
    this->comb_tilde_01_init();
    this->comb_tilde_01_clear();
}

void comb_tilde_01_dspsetup(bool force) {
    if ((bool)(this->comb_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->comb_tilde_01_reset();
    this->comb_tilde_01_setupDone = true;
    this->comb_tilde_01_feedForward_dspsetup();
    this->comb_tilde_01_feedBack_dspsetup();
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
    param_01_value = 0;
    send_01_input_number = 0;
    send_02_input_number = 0;
    send_03_input_number = 0;
    param_02_value = 0;
    send_04_input_number = 0;
    param_03_value = 0;
    param_04_value = 0;
    param_05_value = 0;
    send_05_input_number = 0;
    send_06_input_number = 0;
    param_06_value = 0;
    send_07_input_number = 0;
    param_07_value = 0;
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    receive_01_output_number = 0;
    biquad_tilde_01_x = 0;
    biquad_tilde_01_a0 = 0;
    biquad_tilde_01_a1 = 0;
    biquad_tilde_01_a2 = 0;
    biquad_tilde_01_b1 = 0;
    biquad_tilde_01_b2 = 0;
    receive_02_output_number = 0;
    cycle_tilde_01_frequency = 0;
    cycle_tilde_01_phase_offset = 0;
    reson_tilde_01_x = 0;
    reson_tilde_01_centerFreq = 0;
    reson_tilde_01_resonanceValue = 0;
    receive_03_output_number = 0;
    receive_04_output_number = 0;
    cycle_tilde_02_frequency = 0;
    cycle_tilde_02_phase_offset = 0;
    receive_05_output_number = 0;
    receive_06_output_number = 0;
    cycle_tilde_03_frequency = 0;
    cycle_tilde_03_phase_offset = 0;
    receive_07_output_number = 0;
    gaintilde_02_input_number = 0;
    gaintilde_02_value = 0;
    gaintilde_02_interp = 10;
    receive_08_output_number = 0;
    receive_09_output_number = 0;
    comb_tilde_01_x = 0;
    comb_tilde_01_delayTime = 0;
    comb_tilde_01_gain = 0;
    comb_tilde_01_ffGain = 0;
    comb_tilde_01_fbGain = 0;
    cycle_tilde_04_frequency = 0;
    cycle_tilde_04_phase_offset = 0;
    cycle_tilde_05_frequency = 0;
    cycle_tilde_05_phase_offset = 0;
    receive_10_output_number = 0;
    send_08_input_number = 0;
    param_08_value = 0;
    send_09_input_number = 0;
    param_09_value = 0;
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
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
    biquad_tilde_01_x1 = 0;
    biquad_tilde_01_x2 = 0;
    biquad_tilde_01_y1 = 0;
    biquad_tilde_01_y2 = 0;
    biquad_tilde_01_setupDone = false;
    cycle_tilde_01_wrap = 0;
    cycle_tilde_01_ph_currentPhase = 0;
    cycle_tilde_01_ph_conv = 0;
    cycle_tilde_01_setupDone = false;
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
    cycle_tilde_03_wrap = 0;
    cycle_tilde_03_ph_currentPhase = 0;
    cycle_tilde_03_ph_conv = 0;
    cycle_tilde_03_setupDone = false;
    gaintilde_02_lastValue = 0;
    gaintilde_02_loginc = 1;
    gaintilde_02_zval = 0;
    gaintilde_02_ramp_d_prev = 0;
    gaintilde_02_ramp_prev = 0;
    gaintilde_02_ramp_index = 0;
    gaintilde_02_ramp_increment = 0;
    gaintilde_02_setupDone = false;
    comb_tilde_01_feedForward__maxdelay = 0;
    comb_tilde_01_feedForward_sizemode = 0;
    comb_tilde_01_feedForward_wrap = 0;
    comb_tilde_01_feedForward_reader = 0;
    comb_tilde_01_feedForward_writer = 0;
    comb_tilde_01_feedBack__maxdelay = 0;
    comb_tilde_01_feedBack_sizemode = 0;
    comb_tilde_01_feedBack_wrap = 0;
    comb_tilde_01_feedBack_reader = 0;
    comb_tilde_01_feedBack_writer = 0;
    comb_tilde_01_setupDone = false;
    cycle_tilde_04_wrap = 0;
    cycle_tilde_04_ph_currentPhase = 0;
    cycle_tilde_04_ph_conv = 0;
    cycle_tilde_04_setupDone = false;
    cycle_tilde_05_wrap = 0;
    cycle_tilde_05_ph_currentPhase = 0;
    cycle_tilde_05_ph_conv = 0;
    cycle_tilde_05_setupDone = false;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
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

    number param_01_value;
    number send_01_input_number;
    list send_01_input_list;
    number send_02_input_number;
    list send_02_input_list;
    number send_03_input_number;
    list send_03_input_list;
    number param_02_value;
    number send_04_input_number;
    list send_04_input_list;
    number param_03_value;
    number param_04_value;
    number param_05_value;
    number send_05_input_number;
    list send_05_input_list;
    number send_06_input_number;
    list send_06_input_list;
    number param_06_value;
    number send_07_input_number;
    list send_07_input_list;
    number param_07_value;
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number receive_01_output_number;
    list receive_01_output_list;
    number biquad_tilde_01_x;
    number biquad_tilde_01_a0;
    number biquad_tilde_01_a1;
    number biquad_tilde_01_a2;
    number biquad_tilde_01_b1;
    number biquad_tilde_01_b2;
    number receive_02_output_number;
    list receive_02_output_list;
    number cycle_tilde_01_frequency;
    number cycle_tilde_01_phase_offset;
    number reson_tilde_01_x;
    number reson_tilde_01_centerFreq;
    number reson_tilde_01_resonanceValue;
    number receive_03_output_number;
    list receive_03_output_list;
    number receive_04_output_number;
    list receive_04_output_list;
    number cycle_tilde_02_frequency;
    number cycle_tilde_02_phase_offset;
    number receive_05_output_number;
    list receive_05_output_list;
    number receive_06_output_number;
    list receive_06_output_list;
    number cycle_tilde_03_frequency;
    number cycle_tilde_03_phase_offset;
    number receive_07_output_number;
    list receive_07_output_list;
    number gaintilde_02_input_number;
    number gaintilde_02_value;
    number gaintilde_02_interp;
    number receive_08_output_number;
    list receive_08_output_list;
    number receive_09_output_number;
    list receive_09_output_list;
    number comb_tilde_01_x;
    number comb_tilde_01_delayTime;
    number comb_tilde_01_gain;
    number comb_tilde_01_ffGain;
    number comb_tilde_01_fbGain;
    number cycle_tilde_04_frequency;
    number cycle_tilde_04_phase_offset;
    number cycle_tilde_05_frequency;
    number cycle_tilde_05_phase_offset;
    number receive_10_output_number;
    list receive_10_output_list;
    number send_08_input_number;
    list send_08_input_list;
    number param_08_value;
    number send_09_input_number;
    list send_09_input_list;
    number param_09_value;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[5];
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
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
    number biquad_tilde_01_x1;
    number biquad_tilde_01_x2;
    number biquad_tilde_01_y1;
    number biquad_tilde_01_y2;
    bool biquad_tilde_01_setupDone;
    Float64BufferRef cycle_tilde_01_buffer;
    long cycle_tilde_01_wrap;
    uint32_t cycle_tilde_01_phasei;
    SampleValue cycle_tilde_01_f2i;
    number cycle_tilde_01_ph_currentPhase;
    number cycle_tilde_01_ph_conv;
    bool cycle_tilde_01_setupDone;
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
    Float64BufferRef cycle_tilde_03_buffer;
    long cycle_tilde_03_wrap;
    uint32_t cycle_tilde_03_phasei;
    SampleValue cycle_tilde_03_f2i;
    number cycle_tilde_03_ph_currentPhase;
    number cycle_tilde_03_ph_conv;
    bool cycle_tilde_03_setupDone;
    number gaintilde_02_lastValue;
    number gaintilde_02_loginc;
    number gaintilde_02_zval;
    number gaintilde_02_ramp_d_prev;
    number gaintilde_02_ramp_prev;
    number gaintilde_02_ramp_index;
    number gaintilde_02_ramp_increment;
    bool gaintilde_02_setupDone;
    Float64BufferRef comb_tilde_01_feedForward_buffer;
    Index comb_tilde_01_feedForward__maxdelay;
    Int comb_tilde_01_feedForward_sizemode;
    Index comb_tilde_01_feedForward_wrap;
    Int comb_tilde_01_feedForward_reader;
    Int comb_tilde_01_feedForward_writer;
    Float64BufferRef comb_tilde_01_feedBack_buffer;
    Index comb_tilde_01_feedBack__maxdelay;
    Int comb_tilde_01_feedBack_sizemode;
    Index comb_tilde_01_feedBack_wrap;
    Int comb_tilde_01_feedBack_reader;
    Int comb_tilde_01_feedBack_writer;
    bool comb_tilde_01_setupDone;
    Float64BufferRef cycle_tilde_04_buffer;
    long cycle_tilde_04_wrap;
    uint32_t cycle_tilde_04_phasei;
    SampleValue cycle_tilde_04_f2i;
    number cycle_tilde_04_ph_currentPhase;
    number cycle_tilde_04_ph_conv;
    bool cycle_tilde_04_setupDone;
    Float64BufferRef cycle_tilde_05_buffer;
    long cycle_tilde_05_wrap;
    uint32_t cycle_tilde_05_phasei;
    SampleValue cycle_tilde_05_f2i;
    number cycle_tilde_05_ph_currentPhase;
    number cycle_tilde_05_ph_conv;
    bool cycle_tilde_05_setupDone;
    number param_08_lastValue;
    number param_09_lastValue;
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
    DataRef comb_tilde_01_feedForward_bufferobj;
    DataRef comb_tilde_01_feedBack_bufferobj;
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

