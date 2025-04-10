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

Index voice() {
    return this->_voiceIndex;
}

number random(number low, number high) {
    number range = high - low;
    return rand01() * range + low;
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
    this->noise_tilde_01_perform(this->signals[0], n);

    this->reson_tilde_01_perform(
        this->signals[0],
        this->reson_tilde_01_centerFreq,
        this->reson_tilde_01_resonanceValue,
        this->signals[1],
        n
    );

    this->adsr_01_perform(
        this->adsr_01_attack,
        this->adsr_01_decay,
        this->adsr_01_sustain,
        this->adsr_01_release,
        this->zeroBuffer,
        this->signals[0],
        n
    );

    this->dspexpr_01_perform(this->signals[1], this->signals[0], this->signals[2], n);
    this->gaintilde_01_perform(this->signals[2], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 3; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
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

    this->reson_tilde_01_dspsetup(forceDSPSetup);
    this->adsr_01_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
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
    this->param_01_getPresetValue(getSubState(preset, "bpfreq"));
    this->param_02_getPresetValue(getSubState(preset, "reson"));
    this->param_03_getPresetValue(getSubState(preset, "release"));
    this->param_04_getPresetValue(getSubState(preset, "attack"));
    this->param_05_getPresetValue(getSubState(preset, "adsr"));
    this->param_06_getPresetValue(getSubState(preset, "sustain"));
    this->param_07_getPresetValue(getSubState(preset, "decay"));
    this->param_08_getPresetValue(getSubState(preset, "gainctrl"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "bpfreq"));
    this->param_02_setPresetValue(getSubState(preset, "reson"));
    this->param_03_setPresetValue(getSubState(preset, "release"));
    this->param_04_setPresetValue(getSubState(preset, "attack"));
    this->param_05_setPresetValue(getSubState(preset, "adsr"));
    this->param_06_setPresetValue(getSubState(preset, "sustain"));
    this->param_07_setPresetValue(getSubState(preset, "decay"));
    this->param_08_setPresetValue(getSubState(preset, "gainctrl"));
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
    return 8;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "bpfreq";
        }
    case 1:
        {
        return "reson";
        }
    case 2:
        {
        return "release";
        }
    case 3:
        {
        return "attack";
        }
    case 4:
        {
        return "adsr";
        }
    case 5:
        {
        return "sustain";
        }
    case 6:
        {
        return "decay";
        }
    case 7:
        {
        return "gainctrl";
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
        return "bpfreq";
        }
    case 1:
        {
        return "reson";
        }
    case 2:
        {
        return "release";
        }
    case 3:
        {
        return "attack";
        }
    case 4:
        {
        return "adsr";
        }
    case 5:
        {
        return "sustain";
        }
    case 6:
        {
        return "decay";
        }
    case 7:
        {
        return "gainctrl";
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
        case 6:
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
    case 4:
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 7:
        {
        {
            value = (value < 0 ? 0 : (value > 157 ? 157 : value));
            ParameterValue normalizedValue = (value - 0) / (157 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 3:
    case 6:
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
    case 4:
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 7:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (157 - 0);
            }
        }
        }
    case 2:
    case 3:
    case 6:
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
        if (TAG("gain~_obj-29") == objectId)
            this->gaintilde_01_valin_set(payload);

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
    case TAG("gain~_obj-29"):
        {
        return "gain~_obj-29";
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

    this->send_02_input_number_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->send_01_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->send_05_input_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->send_03_input_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->send_04_input_number_set(v);
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

void gaintilde_01_valin_set(number v) {
    this->gaintilde_01_value_set(v);
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

void allocateDataRefs() {}

void initializeObjects() {
    this->noise_tilde_01_init();
    this->gaintilde_01_init();
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

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 20000 ? 20000 : (v < 0 ? 0 : v));
    return v;
}

void reson_tilde_01_centerFreq_set(number v) {
    this->reson_tilde_01_centerFreq = v;
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->reson_tilde_01_centerFreq_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_02_output_number_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void reson_tilde_01_resonanceValue_set(number v) {
    this->reson_tilde_01_resonanceValue = v;
}

void receive_05_output_number_set(number v) {
    this->receive_05_output_number = v;
    this->reson_tilde_01_resonanceValue_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_05_output_number_set(v);
}

static number param_03_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_release_set(number v) {
    this->adsr_01_release = v;
}

void receive_08_output_number_set(number v) {
    this->receive_08_output_number = v;
    this->adsr_01_release_set(v);
}

void send_05_input_number_set(number v) {
    this->send_05_input_number = v;
    this->receive_08_output_number_set(v);
}

static number param_04_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_attack_set(number v) {
    this->adsr_01_attack = v;
}

void receive_04_output_number_set(number v) {
    this->receive_04_output_number = v;
    this->adsr_01_attack_set(v);
}

void send_03_input_number_set(number v) {
    this->send_03_input_number = v;
    this->receive_04_output_number_set(v);
}

static number param_05_value_constrain(number v) {
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

void receive_03_output_number_set(number v) {
    this->receive_03_output_number = v;
    this->adsr_01_trigger_number_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->receive_03_output_number_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_sustain_set(number v) {
    this->adsr_01_sustain = v;
}

void receive_07_output_number_set(number v) {
    this->receive_07_output_number = v;
    this->adsr_01_sustain_set(v);
}

void send_06_input_number_set(number v) {
    this->send_06_input_number = v;
    this->receive_07_output_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_decay_set(number v) {
    this->adsr_01_decay = v;
}

void receive_06_output_number_set(number v) {
    this->receive_06_output_number = v;
    this->adsr_01_decay_set(v);
}

void send_07_input_number_set(number v) {
    this->send_07_input_number = v;
    this->receive_06_output_number_set(v);
}

static number param_08_value_constrain(number v) {
    v = (v > 157 ? 157 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-29"), v, this->_currentTime);
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

void send_08_input_number_set(number v) {
    this->send_08_input_number = v;
    this->receive_01_output_number_set(v);
}

void noise_tilde_01_perform(SampleValue * out1, Index n) {
    auto __noise_tilde_01_state = this->noise_tilde_01_state;
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = xoshiro_next(__noise_tilde_01_state);
    }
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

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
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

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
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

void noise_tilde_01_init() {
    this->noise_tilde_01_reset();
}

void noise_tilde_01_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_01_state
    );
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

void adsr_01_dspsetup(bool force) {
    if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_01_mspersamp = (number)1000 / this->sr;
    this->adsr_01_setupDone = true;
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
    param_02_value = 0;
    param_03_value = 0;
    send_02_input_number = 0;
    send_03_input_number = 0;
    param_04_value = 0;
    send_04_input_number = 0;
    param_05_value = 0;
    send_05_input_number = 0;
    send_06_input_number = 0;
    param_06_value = 0;
    send_07_input_number = 0;
    param_07_value = 0;
    param_08_value = 0;
    send_08_input_number = 0;
    receive_01_output_number = 0;
    reson_tilde_01_x = 0;
    reson_tilde_01_centerFreq = 0;
    reson_tilde_01_resonanceValue = 0;
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    receive_02_output_number = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    receive_03_output_number = 0;
    adsr_01_trigger_number = 0;
    adsr_01_attack = 0;
    adsr_01_decay = 0;
    adsr_01_sustain = 0;
    adsr_01_release = 0;
    adsr_01_legato = 0;
    receive_04_output_number = 0;
    receive_05_output_number = 0;
    receive_06_output_number = 0;
    receive_07_output_number = 0;
    receive_08_output_number = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
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
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
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
    number param_02_value;
    number param_03_value;
    number send_02_input_number;
    list send_02_input_list;
    number send_03_input_number;
    list send_03_input_list;
    number param_04_value;
    number send_04_input_number;
    list send_04_input_list;
    number param_05_value;
    number send_05_input_number;
    list send_05_input_list;
    number send_06_input_number;
    list send_06_input_list;
    number param_06_value;
    number send_07_input_number;
    list send_07_input_list;
    number param_07_value;
    number param_08_value;
    number send_08_input_number;
    list send_08_input_list;
    number receive_01_output_number;
    list receive_01_output_list;
    number reson_tilde_01_x;
    number reson_tilde_01_centerFreq;
    number reson_tilde_01_resonanceValue;
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number receive_02_output_number;
    list receive_02_output_list;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number receive_03_output_number;
    list receive_03_output_list;
    number adsr_01_trigger_number;
    number adsr_01_attack;
    number adsr_01_decay;
    number adsr_01_sustain;
    number adsr_01_release;
    number adsr_01_legato;
    number receive_04_output_number;
    list receive_04_output_list;
    number receive_05_output_number;
    list receive_05_output_list;
    number receive_06_output_number;
    list receive_06_output_list;
    number receive_07_output_number;
    list receive_07_output_list;
    number receive_08_output_number;
    list receive_08_output_list;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[3];
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
    UInt noise_tilde_01_state[4] = { };
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
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

