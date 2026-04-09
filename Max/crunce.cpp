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
    getEngine()->flushClockEvents(this, -1468824490, false);
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

    this->saw_tilde_01_perform(
        this->saw_tilde_01_frequency,
        this->saw_tilde_01_syncPhase,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_01_perform(this->signals[0], this->signals[1], n);

    this->cycle_tilde_01_perform(
        this->cycle_tilde_01_frequency,
        this->cycle_tilde_01_phase_offset,
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gaintilde_04_perform(this->signals[0], this->signals[2], n);

    this->adsr_01_perform(
        this->adsr_01_attack,
        this->adsr_01_decay,
        this->adsr_01_sustain,
        this->adsr_01_release,
        this->zeroBuffer,
        this->signals[0],
        n
    );

    this->phasor_01_perform(this->phasor_01_freq, this->signals[3], n);
    this->gaintilde_05_perform(this->signals[3], this->signals[4], n);
    this->phasor_02_perform(this->phasor_02_freq, this->signals[3], n);
    this->gaintilde_06_perform(this->signals[3], this->signals[5], n);

    this->cycle_tilde_02_perform(
        this->cycle_tilde_02_frequency,
        this->cycle_tilde_02_phase_offset,
        this->signals[3],
        this->dummyBuffer,
        n
    );

    this->signalsend_01_perform(this->signals[3], this->signals[6], n);
    this->signalreceive_02_perform(this->signals[6], this->signals[3], n);

    this->cycle_tilde_03_perform(
        this->cycle_tilde_03_frequency,
        this->cycle_tilde_03_phase_offset,
        this->signals[6],
        this->dummyBuffer,
        n
    );

    this->signalsend_02_perform(this->signals[6], this->signals[7], n);
    this->signalreceive_01_perform(this->signals[7], this->signals[6], n);
    this->dspexpr_02_perform(this->signals[6], this->dspexpr_02_in2, this->signals[7], n);

    this->saw_tilde_02_perform(
        this->signals[7],
        this->saw_tilde_02_syncPhase,
        this->signals[6],
        this->dummyBuffer,
        n
    );

    this->gaintilde_02_perform(this->signals[6], this->signals[7], n);
    this->phasor_03_perform(this->phasor_03_freq, this->signals[6], n);
    this->signalsend_03_perform(this->signals[6], this->signals[8], n);
    this->signalreceive_03_perform(this->signals[8], this->signals[6], n);
    this->dspexpr_05_perform(this->dspexpr_05_in1, this->signals[6], this->signals[8], n);

    this->saw_tilde_03_perform(
        this->signals[8],
        this->saw_tilde_03_syncPhase,
        this->signals[6],
        this->dummyBuffer,
        n
    );

    this->gaintilde_03_perform(this->signals[6], this->signals[8], n);
    this->dspexpr_04_perform(this->signals[7], this->signals[8], this->signals[6], n);
    this->dspexpr_03_perform(this->signals[6], this->signals[3], this->signals[8], n);

    this->signaladder_01_perform(
        this->signals[1],
        this->signals[2],
        this->signals[8],
        this->signals[4],
        this->signals[5],
        this->signals[5],
        n
    );

    this->dspexpr_01_perform(this->signals[5], this->signals[0], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 9; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
        this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
        this->phasor_02_sigbuf = resizeSignal(this->phasor_02_sigbuf, this->maxvs, maxBlockSize);
        this->phasor_03_sigbuf = resizeSignal(this->phasor_03_sigbuf, this->maxvs, maxBlockSize);
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

    this->saw_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_04_dspsetup(forceDSPSetup);
    this->adsr_01_dspsetup(forceDSPSetup);
    this->phasor_01_dspsetup(forceDSPSetup);
    this->gaintilde_05_dspsetup(forceDSPSetup);
    this->phasor_02_dspsetup(forceDSPSetup);
    this->gaintilde_06_dspsetup(forceDSPSetup);
    this->cycle_tilde_02_dspsetup(forceDSPSetup);
    this->cycle_tilde_03_dspsetup(forceDSPSetup);
    this->saw_tilde_02_dspsetup(forceDSPSetup);
    this->gaintilde_02_dspsetup(forceDSPSetup);
    this->phasor_03_dspsetup(forceDSPSetup);
    this->saw_tilde_03_dspsetup(forceDSPSetup);
    this->gaintilde_03_dspsetup(forceDSPSetup);
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
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
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

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_01_bufferUpdated();
        this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_02_bufferUpdated();
        this->cycle_tilde_03_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_03_bufferUpdated();
    }
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_03_buffer = new Float64Buffer(this->RNBODefaultSinus);
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
    this->param_02_getPresetValue(getSubState(preset, "adsr"));
    this->param_03_getPresetValue(getSubState(preset, "attack"));
    this->param_04_getPresetValue(getSubState(preset, "decay"));
    this->param_05_getPresetValue(getSubState(preset, "sustain"));
    this->param_06_getPresetValue(getSubState(preset, "release"));
    this->param_07_getPresetValue(getSubState(preset, "amfreq"));
    this->param_08_getPresetValue(getSubState(preset, "fmfreq"));
    this->param_09_getPresetValue(getSubState(preset, "fm2freq"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "freq"));
    this->param_02_setPresetValue(getSubState(preset, "adsr"));
    this->param_03_setPresetValue(getSubState(preset, "attack"));
    this->param_04_setPresetValue(getSubState(preset, "decay"));
    this->param_05_setPresetValue(getSubState(preset, "sustain"));
    this->param_06_setPresetValue(getSubState(preset, "release"));
    this->param_07_setPresetValue(getSubState(preset, "amfreq"));
    this->param_08_setPresetValue(getSubState(preset, "fmfreq"));
    this->param_09_setPresetValue(getSubState(preset, "fm2freq"));
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
        return "freq";
        }
    case 1:
        {
        return "adsr";
        }
    case 2:
        {
        return "attack";
        }
    case 3:
        {
        return "decay";
        }
    case 4:
        {
        return "sustain";
        }
    case 5:
        {
        return "release";
        }
    case 6:
        {
        return "amfreq";
        }
    case 7:
        {
        return "fmfreq";
        }
    case 8:
        {
        return "fm2freq";
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
        return "adsr";
        }
    case 2:
        {
        return "attack";
        }
    case 3:
        {
        return "decay";
        }
    case 4:
        {
        return "sustain";
        }
    case 5:
        {
        return "release";
        }
    case 6:
        {
        return "amfreq";
        }
    case 7:
        {
        return "fmfreq";
        }
    case 8:
        {
        return "fm2freq";
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
        case 3:
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
        case 4:
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
        case 5:
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
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 1;
            info->max = 20;
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
            info->min = 1;
            info->max = 20;
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
            info->min = 1;
            info->max = 20;
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
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 3:
    case 4:
    case 5:
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
    case 6:
    case 7:
    case 8:
        {
        {
            value = (value < 1 ? 1 : (value > 20 ? 20 : value));
            ParameterValue normalizedValue = (value - 1) / (20 - 1);
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
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 2:
    case 3:
    case 4:
    case 5:
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
    case 6:
    case 7:
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (20 - 1);
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

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -1468824490:
        {
        this->adsr_01_mute_bang();
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
        if (TAG("gain~_obj-15") == objectId)
            this->gaintilde_01_valin_set(payload);

        if (TAG("gain~_obj-19") == objectId)
            this->gaintilde_02_valin_set(payload);

        if (TAG("gain~_obj-20") == objectId)
            this->gaintilde_03_valin_set(payload);

        if (TAG("gain~_obj-27") == objectId)
            this->gaintilde_04_valin_set(payload);

        if (TAG("gain~_obj-58") == objectId)
            this->gaintilde_05_valin_set(payload);

        if (TAG("gain~_obj-63") == objectId)
            this->gaintilde_06_valin_set(payload);

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
    case TAG("gain~_obj-15"):
        {
        return "gain~_obj-15";
        }
    case TAG("gain~_obj-19"):
        {
        return "gain~_obj-19";
        }
    case TAG("gain~_obj-20"):
        {
        return "gain~_obj-20";
        }
    case TAG("gain~_obj-27"):
        {
        return "gain~_obj-27";
        }
    case TAG("gain~_obj-58"):
        {
        return "gain~_obj-58";
        }
    case TAG("gain~_obj-63"):
        {
        return "gain~_obj-63";
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

    this->adsr_01_trigger_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->adsr_01_attack_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->adsr_01_decay_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->adsr_01_sustain_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->adsr_01_release_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->cycle_tilde_02_frequency_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->cycle_tilde_03_frequency_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->phasor_03_freq_set(v);
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

void adsr_01_mute_bang() {}

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
    this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
    this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
    this->cycle_tilde_03_buffer = this->cycle_tilde_03_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->gaintilde_01_init();
    this->gaintilde_02_init();
    this->gaintilde_03_init();
    this->gaintilde_04_init();
    this->gaintilde_05_init();
    this->gaintilde_06_init();
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
    v = (v > 20000 ? 20000 : (v < 0 ? 0 : v));
    return v;
}

void saw_tilde_01_frequency_set(number v) {
    this->saw_tilde_01_frequency = v;
}

void receive_01_output_number_set(number v) {
    this->receive_01_output_number = v;
    this->saw_tilde_01_frequency_set(v);
}

void dspexpr_02_in2_set(number v) {
    this->dspexpr_02_in2 = v;
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->dspexpr_02_in2_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;
    this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:+_obj-18:1
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->expr_01_in1_set(v);
}

void dspexpr_05_in1_set(number v) {
    this->dspexpr_05_in1 = v;
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->dspexpr_05_in1_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 - this->expr_02_in2);//#map:-_obj-21:1
}

void receive_03_output_number_set(number v) {
    this->receive_03_output_number = v;
    this->expr_02_in1_set(v);
}

void cycle_tilde_01_frequency_set(number v) {
    this->cycle_tilde_01_frequency = v;
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->cycle_tilde_01_frequency_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;

    this->expr_03_out1_set(
        (this->expr_03_in2 == 0 ? 0 : (this->expr_03_in2 == 0. ? 0. : this->expr_03_in1 / this->expr_03_in2))
    );//#map:/_obj-26:1
}

void receive_04_output_number_set(number v) {
    this->receive_04_output_number = v;
    this->expr_03_in1_set(v);
}

void phasor_01_freq_set(number v) {
    this->phasor_01_freq = v;
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->phasor_01_freq_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;

    this->expr_04_out1_set(
        (this->expr_04_in2 == 0 ? 0 : (this->expr_04_in2 == 0. ? 0. : this->expr_04_in1 / this->expr_04_in2))
    );//#map:/_obj-59:1
}

void receive_05_output_number_set(number v) {
    this->receive_05_output_number = v;
    this->expr_04_in1_set(v);
}

void phasor_02_freq_set(number v) {
    this->phasor_02_freq = v;
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->phasor_02_freq_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;

    this->expr_05_out1_set(
        (this->expr_05_in2 == 0 ? 0 : (this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 / this->expr_05_in2))
    );//#map:/_obj-64:1
}

void receive_06_output_number_set(number v) {
    this->receive_06_output_number = v;
    this->expr_05_in1_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_01_output_number_set(v);
    this->receive_02_output_number_set(v);
    this->receive_03_output_number_set(v);
    this->receive_04_output_number_set(v);
    this->receive_05_output_number_set(v);
    this->receive_06_output_number_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_trigger_number_set(number v) {
    this->adsr_01_trigger_number = v;

    if (v != 0)
        this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
        this->adsr_01_triggerValueBuf[(Index)i] = v;
    }
}

static number param_03_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_attack_set(number v) {
    this->adsr_01_attack = v;
}

static number param_04_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_decay_set(number v) {
    this->adsr_01_decay = v;
}

static number param_05_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_sustain_set(number v) {
    this->adsr_01_sustain = v;
}

static number param_06_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_release_set(number v) {
    this->adsr_01_release = v;
}

static number param_07_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 1 ? 1 : v));
    return v;
}

void cycle_tilde_02_frequency_set(number v) {
    this->cycle_tilde_02_frequency = v;
}

static number param_08_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 1 ? 1 : v));
    return v;
}

void cycle_tilde_03_frequency_set(number v) {
    this->cycle_tilde_03_frequency = v;
}

static number param_09_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 1 ? 1 : v));
    return v;
}

void phasor_03_freq_set(number v) {
    this->phasor_03_freq = v;
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-15"), v, this->_currentTime);
    this->gaintilde_01_outval_set(value);
}

void gaintilde_02_outval_set(number ) {}

void gaintilde_02_value_set(number v) {
    this->gaintilde_02_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-19"), v, this->_currentTime);
    this->gaintilde_02_outval_set(value);
}

void gaintilde_03_outval_set(number ) {}

void gaintilde_03_value_set(number v) {
    this->gaintilde_03_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-20"), v, this->_currentTime);
    this->gaintilde_03_outval_set(value);
}

void gaintilde_04_outval_set(number ) {}

void gaintilde_04_value_set(number v) {
    this->gaintilde_04_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-27"), v, this->_currentTime);
    this->gaintilde_04_outval_set(value);
}

void gaintilde_05_outval_set(number ) {}

void gaintilde_05_value_set(number v) {
    this->gaintilde_05_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-58"), v, this->_currentTime);
    this->gaintilde_05_outval_set(value);
}

void gaintilde_06_outval_set(number ) {}

void gaintilde_06_value_set(number v) {
    this->gaintilde_06_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-63"), v, this->_currentTime);
    this->gaintilde_06_outval_set(value);
}

void saw_tilde_01_perform(
    number frequency,
    number syncPhase,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(syncPhase);
    auto __saw_tilde_01_didSync = this->saw_tilde_01_didSync;
    auto __saw_tilde_01_lastSyncDiff = this->saw_tilde_01_lastSyncDiff;
    auto __saw_tilde_01_lastSyncPhase = this->saw_tilde_01_lastSyncPhase;
    auto __saw_tilde_01_t = this->saw_tilde_01_t;
    Index i;

    for (i = 0; i < n; i++) {
        number dt = frequency / this->samplerate();
        number t1 = __saw_tilde_01_t + 0.5;
        t1 -= trunc(t1);
        number y = 2 * t1 - 1;

        if (dt != 0.0) {
            number syncDiff = 0 - __saw_tilde_01_lastSyncPhase;
            __saw_tilde_01_lastSyncPhase = 0;
            __saw_tilde_01_lastSyncDiff = syncDiff;
            number lookahead = 0 + syncDiff;

            if (t1 < dt) {
                number d = t1 / dt;
                y -= d + d - d * d - 1;
            } else if (t1 + dt > 1) {
                number d = (t1 - 1) / dt;
                y -= d + d + d * d + 1;
            } else if ((bool)(__saw_tilde_01_didSync)) {
                y = 0;
                __saw_tilde_01_didSync = false;
            } else if (lookahead > 1) {
                y *= 0.5;
                __saw_tilde_01_t = 0;
                __saw_tilde_01_didSync = true;
            }

            __saw_tilde_01_t += dt;

            if (dt > 0) {
                while (__saw_tilde_01_t >= 1) {
                    __saw_tilde_01_t -= 1;
                }
            } else {
                while (__saw_tilde_01_t <= 0) {
                    __saw_tilde_01_t += 1;
                }
            }
        }

        y = this->saw_tilde_01_dcblocker_next(y, 0.9997);
        out1[(Index)i] = 0.5 * y;
        out2[(Index)i] = __saw_tilde_01_t;
    }

    this->saw_tilde_01_t = __saw_tilde_01_t;
    this->saw_tilde_01_lastSyncPhase = __saw_tilde_01_lastSyncPhase;
    this->saw_tilde_01_lastSyncDiff = __saw_tilde_01_lastSyncDiff;
    this->saw_tilde_01_didSync = __saw_tilde_01_didSync;
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
        number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
        number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
        number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
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
                __adsr_01_outval = __adsr_01_amplitude * sustain;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
            }
        } else if (__adsr_01_phase == 3) {
            __adsr_01_outval = __adsr_01_amplitude * sustain;
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
            -1468824490,
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

void phasor_01_perform(number freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_01_ph_next(freq, -1);
        this->phasor_01_sigbuf[(Index)i] = -1;
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

void phasor_02_perform(number freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_02_ph_next(freq, -1);
        this->phasor_02_sigbuf[(Index)i] = -1;
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

void signalsend_01_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_02_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void cycle_tilde_03_perform(
    number frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
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

void signalsend_02_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_01_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void saw_tilde_02_perform(
    const Sample * frequency,
    number syncPhase,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(syncPhase);
    auto __saw_tilde_02_didSync = this->saw_tilde_02_didSync;
    auto __saw_tilde_02_lastSyncDiff = this->saw_tilde_02_lastSyncDiff;
    auto __saw_tilde_02_lastSyncPhase = this->saw_tilde_02_lastSyncPhase;
    auto __saw_tilde_02_t = this->saw_tilde_02_t;
    Index i;

    for (i = 0; i < n; i++) {
        number dt = frequency[(Index)i] / this->samplerate();
        number t1 = __saw_tilde_02_t + 0.5;
        t1 -= trunc(t1);
        number y = 2 * t1 - 1;

        if (dt != 0.0) {
            number syncDiff = 0 - __saw_tilde_02_lastSyncPhase;
            __saw_tilde_02_lastSyncPhase = 0;
            __saw_tilde_02_lastSyncDiff = syncDiff;
            number lookahead = 0 + syncDiff;

            if (t1 < dt) {
                number d = t1 / dt;
                y -= d + d - d * d - 1;
            } else if (t1 + dt > 1) {
                number d = (t1 - 1) / dt;
                y -= d + d + d * d + 1;
            } else if ((bool)(__saw_tilde_02_didSync)) {
                y = 0;
                __saw_tilde_02_didSync = false;
            } else if (lookahead > 1) {
                y *= 0.5;
                __saw_tilde_02_t = 0;
                __saw_tilde_02_didSync = true;
            }

            __saw_tilde_02_t += dt;

            if (dt > 0) {
                while (__saw_tilde_02_t >= 1) {
                    __saw_tilde_02_t -= 1;
                }
            } else {
                while (__saw_tilde_02_t <= 0) {
                    __saw_tilde_02_t += 1;
                }
            }
        }

        y = this->saw_tilde_02_dcblocker_next(y, 0.9997);
        out1[(Index)i] = 0.5 * y;
        out2[(Index)i] = __saw_tilde_02_t;
    }

    this->saw_tilde_02_t = __saw_tilde_02_t;
    this->saw_tilde_02_lastSyncPhase = __saw_tilde_02_lastSyncPhase;
    this->saw_tilde_02_lastSyncDiff = __saw_tilde_02_lastSyncDiff;
    this->saw_tilde_02_didSync = __saw_tilde_02_didSync;
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

void phasor_03_perform(number freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_03_ph_next(freq, -1);
        this->phasor_03_sigbuf[(Index)i] = -1;
    }
}

void signalsend_03_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_03_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_05_perform(number in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1 * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void saw_tilde_03_perform(
    const Sample * frequency,
    number syncPhase,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(syncPhase);
    auto __saw_tilde_03_didSync = this->saw_tilde_03_didSync;
    auto __saw_tilde_03_lastSyncDiff = this->saw_tilde_03_lastSyncDiff;
    auto __saw_tilde_03_lastSyncPhase = this->saw_tilde_03_lastSyncPhase;
    auto __saw_tilde_03_t = this->saw_tilde_03_t;
    Index i;

    for (i = 0; i < n; i++) {
        number dt = frequency[(Index)i] / this->samplerate();
        number t1 = __saw_tilde_03_t + 0.5;
        t1 -= trunc(t1);
        number y = 2 * t1 - 1;

        if (dt != 0.0) {
            number syncDiff = 0 - __saw_tilde_03_lastSyncPhase;
            __saw_tilde_03_lastSyncPhase = 0;
            __saw_tilde_03_lastSyncDiff = syncDiff;
            number lookahead = 0 + syncDiff;

            if (t1 < dt) {
                number d = t1 / dt;
                y -= d + d - d * d - 1;
            } else if (t1 + dt > 1) {
                number d = (t1 - 1) / dt;
                y -= d + d + d * d + 1;
            } else if ((bool)(__saw_tilde_03_didSync)) {
                y = 0;
                __saw_tilde_03_didSync = false;
            } else if (lookahead > 1) {
                y *= 0.5;
                __saw_tilde_03_t = 0;
                __saw_tilde_03_didSync = true;
            }

            __saw_tilde_03_t += dt;

            if (dt > 0) {
                while (__saw_tilde_03_t >= 1) {
                    __saw_tilde_03_t -= 1;
                }
            } else {
                while (__saw_tilde_03_t <= 0) {
                    __saw_tilde_03_t += 1;
                }
            }
        }

        y = this->saw_tilde_03_dcblocker_next(y, 0.9997);
        out1[(Index)i] = 0.5 * y;
        out2[(Index)i] = __saw_tilde_03_t;
    }

    this->saw_tilde_03_t = __saw_tilde_03_t;
    this->saw_tilde_03_lastSyncPhase = __saw_tilde_03_lastSyncPhase;
    this->saw_tilde_03_lastSyncDiff = __saw_tilde_03_lastSyncDiff;
    this->saw_tilde_03_didSync = __saw_tilde_03_didSync;
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

void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
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

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
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

number saw_tilde_01_dcblocker_next(number x, number gain) {
    number y = x - this->saw_tilde_01_dcblocker_xm1 + this->saw_tilde_01_dcblocker_ym1 * gain;
    this->saw_tilde_01_dcblocker_xm1 = x;
    this->saw_tilde_01_dcblocker_ym1 = y;
    return y;
}

void saw_tilde_01_dcblocker_reset() {
    this->saw_tilde_01_dcblocker_xm1 = 0;
    this->saw_tilde_01_dcblocker_ym1 = 0;
}

void saw_tilde_01_dcblocker_dspsetup() {
    this->saw_tilde_01_dcblocker_reset();
}

void saw_tilde_01_dspsetup(bool force) {
    if ((bool)(this->saw_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->saw_tilde_01_setupDone = true;
    this->saw_tilde_01_dcblocker_dspsetup();
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

number saw_tilde_02_dcblocker_next(number x, number gain) {
    number y = x - this->saw_tilde_02_dcblocker_xm1 + this->saw_tilde_02_dcblocker_ym1 * gain;
    this->saw_tilde_02_dcblocker_xm1 = x;
    this->saw_tilde_02_dcblocker_ym1 = y;
    return y;
}

void saw_tilde_02_dcblocker_reset() {
    this->saw_tilde_02_dcblocker_xm1 = 0;
    this->saw_tilde_02_dcblocker_ym1 = 0;
}

void saw_tilde_02_dcblocker_dspsetup() {
    this->saw_tilde_02_dcblocker_reset();
}

void saw_tilde_02_dspsetup(bool force) {
    if ((bool)(this->saw_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->saw_tilde_02_setupDone = true;
    this->saw_tilde_02_dcblocker_dspsetup();
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

number saw_tilde_03_dcblocker_next(number x, number gain) {
    number y = x - this->saw_tilde_03_dcblocker_xm1 + this->saw_tilde_03_dcblocker_ym1 * gain;
    this->saw_tilde_03_dcblocker_xm1 = x;
    this->saw_tilde_03_dcblocker_ym1 = y;
    return y;
}

void saw_tilde_03_dcblocker_reset() {
    this->saw_tilde_03_dcblocker_xm1 = 0;
    this->saw_tilde_03_dcblocker_ym1 = 0;
}

void saw_tilde_03_dcblocker_dspsetup() {
    this->saw_tilde_03_dcblocker_reset();
}

void saw_tilde_03_dspsetup(bool force) {
    if ((bool)(this->saw_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->saw_tilde_03_setupDone = true;
    this->saw_tilde_03_dcblocker_dspsetup();
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

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void adsr_01_dspsetup(bool force) {
    if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_01_mspersamp = (number)1000 / this->sr;
    this->adsr_01_setupDone = true;
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

number phasor_01_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_01_ph_conv;

    if (this->phasor_01_ph_currentPhase < 0.)
        this->phasor_01_ph_currentPhase = 1. + this->phasor_01_ph_currentPhase;

    if (this->phasor_01_ph_currentPhase > 1.)
        this->phasor_01_ph_currentPhase = this->phasor_01_ph_currentPhase - 1.;

    number tmp = this->phasor_01_ph_currentPhase;
    this->phasor_01_ph_currentPhase += pincr;
    return tmp;
}

void phasor_01_ph_reset() {
    this->phasor_01_ph_currentPhase = 0;
}

void phasor_01_ph_dspsetup() {
    this->phasor_01_ph_conv = (number)1 / this->sr;
}

void phasor_01_dspsetup(bool force) {
    if ((bool)(this->phasor_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_01_conv = (number)1 / this->samplerate();
    this->phasor_01_setupDone = true;
    this->phasor_01_ph_dspsetup();
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
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

number phasor_02_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_02_ph_conv;

    if (this->phasor_02_ph_currentPhase < 0.)
        this->phasor_02_ph_currentPhase = 1. + this->phasor_02_ph_currentPhase;

    if (this->phasor_02_ph_currentPhase > 1.)
        this->phasor_02_ph_currentPhase = this->phasor_02_ph_currentPhase - 1.;

    number tmp = this->phasor_02_ph_currentPhase;
    this->phasor_02_ph_currentPhase += pincr;
    return tmp;
}

void phasor_02_ph_reset() {
    this->phasor_02_ph_currentPhase = 0;
}

void phasor_02_ph_dspsetup() {
    this->phasor_02_ph_conv = (number)1 / this->sr;
}

void phasor_02_dspsetup(bool force) {
    if ((bool)(this->phasor_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_02_conv = (number)1 / this->samplerate();
    this->phasor_02_setupDone = true;
    this->phasor_02_ph_dspsetup();
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
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

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
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

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

number phasor_03_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_03_ph_conv;

    if (this->phasor_03_ph_currentPhase < 0.)
        this->phasor_03_ph_currentPhase = 1. + this->phasor_03_ph_currentPhase;

    if (this->phasor_03_ph_currentPhase > 1.)
        this->phasor_03_ph_currentPhase = this->phasor_03_ph_currentPhase - 1.;

    number tmp = this->phasor_03_ph_currentPhase;
    this->phasor_03_ph_currentPhase += pincr;
    return tmp;
}

void phasor_03_ph_reset() {
    this->phasor_03_ph_currentPhase = 0;
}

void phasor_03_ph_dspsetup() {
    this->phasor_03_ph_conv = (number)1 / this->sr;
}

void phasor_03_dspsetup(bool force) {
    if ((bool)(this->phasor_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_03_conv = (number)1 / this->samplerate();
    this->phasor_03_setupDone = true;
    this->phasor_03_ph_dspsetup();
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
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    receive_01_output_number = 0;
    saw_tilde_01_frequency = 0;
    saw_tilde_01_syncPhase = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    gaintilde_02_input_number = 0;
    gaintilde_02_value = 0;
    gaintilde_02_interp = 10;
    receive_02_output_number = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    expr_01_in1 = 0;
    expr_01_in2 = 5;
    expr_01_out1 = 0;
    saw_tilde_02_frequency = 0;
    saw_tilde_02_syncPhase = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    gaintilde_03_input_number = 0;
    gaintilde_03_value = 0;
    gaintilde_03_interp = 10;
    saw_tilde_03_frequency = 0;
    saw_tilde_03_syncPhase = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0;
    expr_02_in1 = 0;
    expr_02_in2 = 6;
    expr_02_out1 = 0;
    receive_03_output_number = 0;
    gaintilde_04_input_number = 0;
    gaintilde_04_value = 0;
    gaintilde_04_interp = 10;
    expr_03_in1 = 0;
    expr_03_in2 = 4;
    expr_03_out1 = 0;
    receive_04_output_number = 0;
    cycle_tilde_01_frequency = 0;
    cycle_tilde_01_phase_offset = 0;
    param_02_value = 0;
    adsr_01_trigger_number = 0;
    adsr_01_attack = 0;
    adsr_01_decay = 0;
    adsr_01_sustain = 0;
    adsr_01_release = 0;
    adsr_01_legato = 0;
    param_03_value = 0;
    param_04_value = 0;
    param_05_value = 0;
    gaintilde_05_input_number = 0;
    gaintilde_05_value = 0;
    gaintilde_05_interp = 10;
    expr_04_in1 = 0;
    expr_04_in2 = 4;
    expr_04_out1 = 0;
    receive_05_output_number = 0;
    phasor_01_freq = 0;
    param_06_value = 0;
    gaintilde_06_input_number = 0;
    gaintilde_06_value = 0;
    gaintilde_06_interp = 10;
    expr_05_in1 = 0;
    expr_05_in2 = 2;
    expr_05_out1 = 0;
    receive_06_output_number = 0;
    phasor_02_freq = 0;
    param_07_value = 0;
    cycle_tilde_02_frequency = 0;
    cycle_tilde_02_phase_offset = 0;
    param_08_value = 0;
    cycle_tilde_03_frequency = 0;
    cycle_tilde_03_phase_offset = 0;
    param_09_value = 0;
    phasor_03_freq = 0;
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
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_01_lastValue = 0;
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
    saw_tilde_01_t = 0;
    saw_tilde_01_lastSyncPhase = 0;
    saw_tilde_01_lastSyncDiff = 0;
    saw_tilde_01_didSync = false;
    saw_tilde_01_dcblocker_xm1 = 0;
    saw_tilde_01_dcblocker_ym1 = 0;
    saw_tilde_01_setupDone = false;
    gaintilde_02_lastValue = 0;
    gaintilde_02_loginc = 1;
    gaintilde_02_zval = 0;
    gaintilde_02_ramp_d_prev = 0;
    gaintilde_02_ramp_prev = 0;
    gaintilde_02_ramp_index = 0;
    gaintilde_02_ramp_increment = 0;
    gaintilde_02_setupDone = false;
    saw_tilde_02_t = 0;
    saw_tilde_02_lastSyncPhase = 0;
    saw_tilde_02_lastSyncDiff = 0;
    saw_tilde_02_didSync = false;
    saw_tilde_02_dcblocker_xm1 = 0;
    saw_tilde_02_dcblocker_ym1 = 0;
    saw_tilde_02_setupDone = false;
    gaintilde_03_lastValue = 0;
    gaintilde_03_loginc = 1;
    gaintilde_03_zval = 0;
    gaintilde_03_ramp_d_prev = 0;
    gaintilde_03_ramp_prev = 0;
    gaintilde_03_ramp_index = 0;
    gaintilde_03_ramp_increment = 0;
    gaintilde_03_setupDone = false;
    saw_tilde_03_t = 0;
    saw_tilde_03_lastSyncPhase = 0;
    saw_tilde_03_lastSyncDiff = 0;
    saw_tilde_03_didSync = false;
    saw_tilde_03_dcblocker_xm1 = 0;
    saw_tilde_03_dcblocker_ym1 = 0;
    saw_tilde_03_setupDone = false;
    gaintilde_04_lastValue = 0;
    gaintilde_04_loginc = 1;
    gaintilde_04_zval = 0;
    gaintilde_04_ramp_d_prev = 0;
    gaintilde_04_ramp_prev = 0;
    gaintilde_04_ramp_index = 0;
    gaintilde_04_ramp_increment = 0;
    gaintilde_04_setupDone = false;
    cycle_tilde_01_wrap = 0;
    cycle_tilde_01_ph_currentPhase = 0;
    cycle_tilde_01_ph_conv = 0;
    cycle_tilde_01_setupDone = false;
    param_02_lastValue = 0;
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
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    gaintilde_05_lastValue = 0;
    gaintilde_05_loginc = 1;
    gaintilde_05_zval = 0;
    gaintilde_05_ramp_d_prev = 0;
    gaintilde_05_ramp_prev = 0;
    gaintilde_05_ramp_index = 0;
    gaintilde_05_ramp_increment = 0;
    gaintilde_05_setupDone = false;
    phasor_01_sigbuf = nullptr;
    phasor_01_lastLockedPhase = 0;
    phasor_01_conv = 0;
    phasor_01_ph_currentPhase = 0;
    phasor_01_ph_conv = 0;
    phasor_01_setupDone = false;
    param_06_lastValue = 0;
    gaintilde_06_lastValue = 0;
    gaintilde_06_loginc = 1;
    gaintilde_06_zval = 0;
    gaintilde_06_ramp_d_prev = 0;
    gaintilde_06_ramp_prev = 0;
    gaintilde_06_ramp_index = 0;
    gaintilde_06_ramp_increment = 0;
    gaintilde_06_setupDone = false;
    phasor_02_sigbuf = nullptr;
    phasor_02_lastLockedPhase = 0;
    phasor_02_conv = 0;
    phasor_02_ph_currentPhase = 0;
    phasor_02_ph_conv = 0;
    phasor_02_setupDone = false;
    param_07_lastValue = 0;
    cycle_tilde_02_wrap = 0;
    cycle_tilde_02_ph_currentPhase = 0;
    cycle_tilde_02_ph_conv = 0;
    cycle_tilde_02_setupDone = false;
    param_08_lastValue = 0;
    cycle_tilde_03_wrap = 0;
    cycle_tilde_03_ph_currentPhase = 0;
    cycle_tilde_03_ph_conv = 0;
    cycle_tilde_03_setupDone = false;
    param_09_lastValue = 0;
    phasor_03_sigbuf = nullptr;
    phasor_03_lastLockedPhase = 0;
    phasor_03_conv = 0;
    phasor_03_ph_currentPhase = 0;
    phasor_03_ph_conv = 0;
    phasor_03_setupDone = false;
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
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number receive_01_output_number;
    list receive_01_output_list;
    number saw_tilde_01_frequency;
    number saw_tilde_01_syncPhase;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number gaintilde_02_input_number;
    number gaintilde_02_value;
    number gaintilde_02_interp;
    number receive_02_output_number;
    list receive_02_output_list;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    number saw_tilde_02_frequency;
    number saw_tilde_02_syncPhase;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number gaintilde_03_input_number;
    number gaintilde_03_value;
    number gaintilde_03_interp;
    number saw_tilde_03_frequency;
    number saw_tilde_03_syncPhase;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number receive_03_output_number;
    list receive_03_output_list;
    number gaintilde_04_input_number;
    number gaintilde_04_value;
    number gaintilde_04_interp;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number receive_04_output_number;
    list receive_04_output_list;
    number cycle_tilde_01_frequency;
    number cycle_tilde_01_phase_offset;
    number param_02_value;
    number adsr_01_trigger_number;
    number adsr_01_attack;
    number adsr_01_decay;
    number adsr_01_sustain;
    number adsr_01_release;
    number adsr_01_legato;
    number param_03_value;
    number param_04_value;
    number param_05_value;
    number gaintilde_05_input_number;
    number gaintilde_05_value;
    number gaintilde_05_interp;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number receive_05_output_number;
    list receive_05_output_list;
    number phasor_01_freq;
    number param_06_value;
    number gaintilde_06_input_number;
    number gaintilde_06_value;
    number gaintilde_06_interp;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number receive_06_output_number;
    list receive_06_output_list;
    number phasor_02_freq;
    number param_07_value;
    number cycle_tilde_02_frequency;
    number cycle_tilde_02_phase_offset;
    number param_08_value;
    number cycle_tilde_03_frequency;
    number cycle_tilde_03_phase_offset;
    number param_09_value;
    number phasor_03_freq;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[9];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
    number saw_tilde_01_t;
    number saw_tilde_01_lastSyncPhase;
    number saw_tilde_01_lastSyncDiff;
    bool saw_tilde_01_didSync;
    number saw_tilde_01_dcblocker_xm1;
    number saw_tilde_01_dcblocker_ym1;
    bool saw_tilde_01_setupDone;
    number gaintilde_02_lastValue;
    number gaintilde_02_loginc;
    number gaintilde_02_zval;
    number gaintilde_02_ramp_d_prev;
    number gaintilde_02_ramp_prev;
    number gaintilde_02_ramp_index;
    number gaintilde_02_ramp_increment;
    bool gaintilde_02_setupDone;
    number saw_tilde_02_t;
    number saw_tilde_02_lastSyncPhase;
    number saw_tilde_02_lastSyncDiff;
    bool saw_tilde_02_didSync;
    number saw_tilde_02_dcblocker_xm1;
    number saw_tilde_02_dcblocker_ym1;
    bool saw_tilde_02_setupDone;
    number gaintilde_03_lastValue;
    number gaintilde_03_loginc;
    number gaintilde_03_zval;
    number gaintilde_03_ramp_d_prev;
    number gaintilde_03_ramp_prev;
    number gaintilde_03_ramp_index;
    number gaintilde_03_ramp_increment;
    bool gaintilde_03_setupDone;
    number saw_tilde_03_t;
    number saw_tilde_03_lastSyncPhase;
    number saw_tilde_03_lastSyncDiff;
    bool saw_tilde_03_didSync;
    number saw_tilde_03_dcblocker_xm1;
    number saw_tilde_03_dcblocker_ym1;
    bool saw_tilde_03_setupDone;
    number gaintilde_04_lastValue;
    number gaintilde_04_loginc;
    number gaintilde_04_zval;
    number gaintilde_04_ramp_d_prev;
    number gaintilde_04_ramp_prev;
    number gaintilde_04_ramp_index;
    number gaintilde_04_ramp_increment;
    bool gaintilde_04_setupDone;
    Float64BufferRef cycle_tilde_01_buffer;
    long cycle_tilde_01_wrap;
    uint32_t cycle_tilde_01_phasei;
    SampleValue cycle_tilde_01_f2i;
    number cycle_tilde_01_ph_currentPhase;
    number cycle_tilde_01_ph_conv;
    bool cycle_tilde_01_setupDone;
    number param_02_lastValue;
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
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number gaintilde_05_lastValue;
    number gaintilde_05_loginc;
    number gaintilde_05_zval;
    number gaintilde_05_ramp_d_prev;
    number gaintilde_05_ramp_prev;
    number gaintilde_05_ramp_index;
    number gaintilde_05_ramp_increment;
    bool gaintilde_05_setupDone;
    signal phasor_01_sigbuf;
    number phasor_01_lastLockedPhase;
    number phasor_01_conv;
    number phasor_01_ph_currentPhase;
    number phasor_01_ph_conv;
    bool phasor_01_setupDone;
    number param_06_lastValue;
    number gaintilde_06_lastValue;
    number gaintilde_06_loginc;
    number gaintilde_06_zval;
    number gaintilde_06_ramp_d_prev;
    number gaintilde_06_ramp_prev;
    number gaintilde_06_ramp_index;
    number gaintilde_06_ramp_increment;
    bool gaintilde_06_setupDone;
    signal phasor_02_sigbuf;
    number phasor_02_lastLockedPhase;
    number phasor_02_conv;
    number phasor_02_ph_currentPhase;
    number phasor_02_ph_conv;
    bool phasor_02_setupDone;
    number param_07_lastValue;
    Float64BufferRef cycle_tilde_02_buffer;
    long cycle_tilde_02_wrap;
    uint32_t cycle_tilde_02_phasei;
    SampleValue cycle_tilde_02_f2i;
    number cycle_tilde_02_ph_currentPhase;
    number cycle_tilde_02_ph_conv;
    bool cycle_tilde_02_setupDone;
    number param_08_lastValue;
    Float64BufferRef cycle_tilde_03_buffer;
    long cycle_tilde_03_wrap;
    uint32_t cycle_tilde_03_phasei;
    SampleValue cycle_tilde_03_f2i;
    number cycle_tilde_03_ph_currentPhase;
    number cycle_tilde_03_ph_conv;
    bool cycle_tilde_03_setupDone;
    number param_09_lastValue;
    signal phasor_03_sigbuf;
    number phasor_03_lastLockedPhase;
    number phasor_03_conv;
    number phasor_03_ph_currentPhase;
    number phasor_03_ph_conv;
    bool phasor_03_setupDone;
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

