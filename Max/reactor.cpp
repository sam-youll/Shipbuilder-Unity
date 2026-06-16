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

class RNBOSubpatcher_254 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_254()
    {
    }
    
    ~RNBOSubpatcher_254()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 848255507, false);
        getEngine()->flushClockEvents(this, -1468824490, false);
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
    
        this->gaintilde_02_perform(this->signals[0], this->signals[1], n);
    
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
    
        this->gaintilde_04_perform(this->signals[2], this->signals[3], n);
    
        this->adsr_01_perform(
            this->adsr_01_attack,
            this->adsr_01_decay,
            this->adsr_01_sustain,
            this->adsr_01_release,
            this->zeroBuffer,
            this->signals[2],
            n
        );
    
        this->dspexpr_02_perform(this->signals[2], this->dspexpr_02_in2, this->signals[4], n);
    
        this->cycle_tilde_04_perform(
            this->cycle_tilde_04_frequency,
            this->cycle_tilde_04_phase_offset,
            this->signals[5],
            this->dummyBuffer,
            n
        );
    
        this->gaintilde_05_perform(this->signals[5], this->signals[6], n);
        this->phasor_01_perform(this->phasor_01_freq, this->signals[5], n);
        this->gaintilde_06_perform(this->signals[5], this->signals[7], n);
        this->phasor_02_perform(this->phasor_02_freq, this->signals[5], n);
        this->gaintilde_07_perform(this->signals[5], this->signals[8], n);
        this->phasor_03_perform(this->phasor_03_freq, this->signals[5], n);
        this->gaintilde_08_perform(this->signals[5], this->signals[9], n);
    
        this->signaladder_02_perform(
            this->signals[7],
            this->signals[8],
            this->signals[1],
            this->signals[9],
            this->signals[6],
            this->signals[3],
            this->signals[3],
            n
        );
    
        this->limi_02_perform(this->signals[3], this->signals[5], n);
        this->delaytilde_01_perform(this->signals[0], this->signals[5], this->signals[6], n);
        this->signaladder_03_perform(this->signals[6], this->signals[5], this->signals[9], n);
        this->gaintilde_01_perform(this->signals[9], this->signals[0], n);
        this->signaladder_04_perform(this->signals[6], this->signals[5], this->signals[5], n);
        this->dspexpr_01_perform(this->signals[5], this->signals[2], this->signals[9], n);
        this->gaintilde_03_perform(this->signals[9], this->signals[2], n);
        this->signaladder_05_perform(this->signals[0], this->signals[2], this->signals[2], n);
    
        this->lores_01_perform(
            this->signals[4],
            this->lores_01_resonance,
            this->signals[2],
            this->signals[9],
            n
        );
    
        this->limi_01_perform(this->signals[9], out1, n);
        this->stackprotect_perform(n);
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
            this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
            this->phasor_02_sigbuf = resizeSignal(this->phasor_02_sigbuf, this->maxvs, maxBlockSize);
            this->phasor_03_sigbuf = resizeSignal(this->phasor_03_sigbuf, this->maxvs, maxBlockSize);
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
        this->gaintilde_02_dspsetup(forceDSPSetup);
        this->cycle_tilde_02_dspsetup(forceDSPSetup);
        this->cycle_tilde_03_dspsetup(forceDSPSetup);
        this->gaintilde_04_dspsetup(forceDSPSetup);
        this->adsr_01_dspsetup(forceDSPSetup);
        this->cycle_tilde_04_dspsetup(forceDSPSetup);
        this->gaintilde_05_dspsetup(forceDSPSetup);
        this->phasor_01_dspsetup(forceDSPSetup);
        this->gaintilde_06_dspsetup(forceDSPSetup);
        this->phasor_02_dspsetup(forceDSPSetup);
        this->gaintilde_07_dspsetup(forceDSPSetup);
        this->phasor_03_dspsetup(forceDSPSetup);
        this->gaintilde_08_dspsetup(forceDSPSetup);
        this->limi_02_dspsetup(forceDSPSetup);
        this->delaytilde_01_dspsetup(forceDSPSetup);
        this->gaintilde_01_dspsetup(forceDSPSetup);
        this->gaintilde_03_dspsetup(forceDSPSetup);
        this->lores_01_dspsetup(forceDSPSetup);
        this->limi_01_dspsetup(forceDSPSetup);
    
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
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
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
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case 848255507:
            {
            this->line_01_tick_set(value);
            break;
            }
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
            if (TAG("subbass/gain~_obj-76") == objectId)
                this->gaintilde_01_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-3") == objectId)
                this->gaintilde_02_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-75") == objectId)
                this->gaintilde_03_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-10") == objectId)
                this->gaintilde_04_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-20") == objectId)
                this->gaintilde_05_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-41") == objectId)
                this->gaintilde_06_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-34") == objectId)
                this->gaintilde_07_valin_set(payload);
    
            if (TAG("subbass/gain~_obj-27") == objectId)
                this->gaintilde_08_valin_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("subbass/message_obj-81") == objectId)
                this->message_01_listin_number_set(payload);
    
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
            if (TAG("subbass/message_obj-81") == objectId)
                this->message_01_listin_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("subbass/message_obj-81") == objectId)
                this->message_01_listin_bang_bang();
    
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
        case TAG("subbass/gain~_obj-76"):
            {
            return "subbass/gain~_obj-76";
            }
        case TAG("subbass/gain~_obj-3"):
            {
            return "subbass/gain~_obj-3";
            }
        case TAG("subbass/gain~_obj-75"):
            {
            return "subbass/gain~_obj-75";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("subbass/message_obj-81"):
            {
            return "subbass/message_obj-81";
            }
        case TAG("subbass/gain~_obj-10"):
            {
            return "subbass/gain~_obj-10";
            }
        case TAG("subbass/gain~_obj-20"):
            {
            return "subbass/gain~_obj-20";
            }
        case TAG("subbass/gain~_obj-41"):
            {
            return "subbass/gain~_obj-41";
            }
        case TAG("subbass/gain~_obj-34"):
            {
            return "subbass/gain~_obj-34";
            }
        case TAG("subbass/gain~_obj-27"):
            {
            return "subbass/gain~_obj-27";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 1:
            {
            return addressOf(this->delaytilde_01_del_bufferobj);
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
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void zeroDataRef(DataRef& ref) {
        ref->setZero();
    }
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 0) {
            this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_01_bufferUpdated();
            this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_02_bufferUpdated();
            this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_03_bufferUpdated();
            this->cycle_tilde_04_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_04_bufferUpdated();
        }
    
        if (index == 1) {
            this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
        }
    }
    
    void initialize() {
        this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr, "buffer~");
        this->assign_defaults();
        this->setState();
        this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->cycle_tilde_04_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->delaytilde_01_del_bufferobj->setIndex(1);
        this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    }
    
    protected:
    
    void gaintilde_01_valin_set(number v) {
        this->gaintilde_01_value_set(v);
    }
    
    void gaintilde_02_valin_set(number v) {
        this->gaintilde_02_value_set(v);
    }
    
    void gaintilde_03_valin_set(number v) {
        this->gaintilde_03_value_set(v);
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
    
    void gaintilde_04_valin_set(number v) {
        this->gaintilde_04_value_set(v);
    }
    
    void line_01_tick_set(number v) {
        this->line_01_output_set(v);
    
        if ((bool)(this->line_01_isFinished(v))) {
            this->line_01_slope = 0;
            this->line_01_startValue = v;
            this->line_01_startPendingRamp();
        } else {
            this->line_01_scheduleNext();
        }
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
    
    void initializeObjects() {
        this->gaintilde_01_init();
        this->gaintilde_02_init();
        this->gaintilde_03_init();
        this->message_01_init();
        this->delaytilde_01_del_init();
        this->gaintilde_04_init();
        this->gaintilde_05_init();
        this->gaintilde_06_init();
        this->gaintilde_07_init();
        this->gaintilde_08_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->cycle_tilde_01_buffer->requestSize(16384, 1);
        this->cycle_tilde_01_buffer->setSampleRate(this->sr);
        this->cycle_tilde_02_buffer->requestSize(16384, 1);
        this->cycle_tilde_02_buffer->setSampleRate(this->sr);
        this->cycle_tilde_03_buffer->requestSize(16384, 1);
        this->cycle_tilde_03_buffer->setSampleRate(this->sr);
        this->cycle_tilde_04_buffer->requestSize(16384, 1);
        this->cycle_tilde_04_buffer->setSampleRate(this->sr);
        this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
        this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
        this->cycle_tilde_03_buffer = this->cycle_tilde_03_buffer->allocateIfNeeded();
        this->cycle_tilde_04_buffer = this->cycle_tilde_04_buffer->allocateIfNeeded();
        this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();
    
        if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
            if (this->delaytilde_01_del_bufferobj->wantsFill())
                this->zeroDataRef(this->delaytilde_01_del_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(1);
        }
    }
    
    void gaintilde_03_outval_set(number ) {}
    
    void gaintilde_03_value_set(number v) {
        this->gaintilde_03_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-75"), v, this->_currentTime);
        this->gaintilde_03_outval_set(value);
    }
    
    void gaintilde_03_input_number_set(number v) {
        this->gaintilde_03_input_number = v;
    
        this->gaintilde_03_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void gaintilde_01_outval_set(number ) {}
    
    void gaintilde_01_value_set(number v) {
        this->gaintilde_01_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-76"), v, this->_currentTime);
        this->gaintilde_01_outval_set(value);
    }
    
    void gaintilde_01_input_number_set(number v) {
        this->gaintilde_01_input_number = v;
    
        this->gaintilde_01_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->gaintilde_01_input_number_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(this->expr_01_in1 - this->expr_01_in2);//#map:subbass/-_obj-79:1
    }
    
    void expr_01_in2_set(number v) {
        this->expr_01_in2 = v;
    }
    
    void message_01_out_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gaintilde_03_input_number_set(converted);
        }
    
        {
            if (v->length > 1)
                this->expr_01_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_01_in1_set(converted);
        }
    }
    
    void message_01_trigger_bang() {
        this->message_01_out_set(this->message_01_set);
    }
    
    void receive_03_output_number_set(number v) {
        this->receive_03_output_number = v;
        this->message_01_trigger_bang();
    }
    
    void adsr_01_trigger_number_set(number v) {
        this->adsr_01_trigger_number = v;
    
        if (v != 0)
            this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
    
        for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
            this->adsr_01_triggerValueBuf[(Index)i] = v;
        }
    }
    
    void receive_05_output_number_set(number v) {
        this->receive_05_output_number = v;
        this->adsr_01_trigger_number_set(v);
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
        );//#map:subbass//_obj-6:1
    }
    
    void receive_02_output_number_set(number v) {
        this->receive_02_output_number = v;
        this->expr_03_in1_set(v);
    }
    
    void cycle_tilde_03_frequency_set(number v) {
        this->cycle_tilde_03_frequency = v;
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->cycle_tilde_03_frequency_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
        this->expr_05_out1_set(this->expr_05_in1 + this->expr_05_in2);//#map:subbass/+_obj-12:1
    }
    
    void expr_06_out1_set(number v) {
        this->expr_06_out1 = v;
        this->expr_05_in1_set(this->expr_06_out1);
    }
    
    void expr_06_in1_set(number in1) {
        this->expr_06_in1 = in1;
    
        this->expr_06_out1_set(
            (this->expr_06_in2 == 0 ? 0 : (this->expr_06_in2 == 0. ? 0. : this->expr_06_in1 / this->expr_06_in2))
        );//#map:subbass//_obj-8:1
    }
    
    void receive_06_output_number_set(number v) {
        this->receive_06_output_number = v;
        this->expr_06_in1_set(v);
    }
    
    void cycle_tilde_04_frequency_set(number v) {
        this->cycle_tilde_04_frequency = v;
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->cycle_tilde_04_frequency_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
        this->expr_08_out1_set(this->expr_08_in1 - this->expr_08_in2);//#map:subbass/-_obj-17:1
    }
    
    void expr_09_out1_set(number v) {
        this->expr_09_out1 = v;
        this->expr_08_in1_set(this->expr_09_out1);
    }
    
    void expr_09_in1_set(number in1) {
        this->expr_09_in1 = in1;
    
        this->expr_09_out1_set(
            (this->expr_09_in2 == 0 ? 0 : (this->expr_09_in2 == 0. ? 0. : this->expr_09_in1 / this->expr_09_in2))
        );//#map:subbass//_obj-18:1
    }
    
    void receive_08_output_number_set(number v) {
        this->receive_08_output_number = v;
        this->expr_09_in1_set(v);
    }
    
    void phasor_01_freq_set(number v) {
        this->phasor_01_freq = v;
    }
    
    void expr_11_out1_set(number v) {
        this->expr_11_out1 = v;
        this->phasor_01_freq_set(this->expr_11_out1);
    }
    
    void expr_11_in1_set(number in1) {
        this->expr_11_in1 = in1;
    
        this->expr_11_out1_set(
            (this->expr_11_in2 == 0 ? 0 : (this->expr_11_in2 == 0. ? 0. : this->expr_11_in1 / this->expr_11_in2))
        );//#map:subbass//_obj-39:1
    }
    
    void receive_10_output_number_set(number v) {
        this->receive_10_output_number = v;
        this->expr_11_in1_set(v);
    }
    
    void phasor_02_freq_set(number v) {
        this->phasor_02_freq = v;
    }
    
    void expr_13_out1_set(number v) {
        this->expr_13_out1 = v;
        this->phasor_02_freq_set(this->expr_13_out1);
    }
    
    void expr_13_in1_set(number in1) {
        this->expr_13_in1 = in1;
        this->expr_13_out1_set(this->expr_13_in1 + this->expr_13_in2);//#map:subbass/+_obj-31:1
    }
    
    void expr_14_out1_set(number v) {
        this->expr_14_out1 = v;
        this->expr_13_in1_set(this->expr_14_out1);
    }
    
    void expr_14_in1_set(number in1) {
        this->expr_14_in1 = in1;
    
        this->expr_14_out1_set(
            (this->expr_14_in2 == 0 ? 0 : (this->expr_14_in2 == 0. ? 0. : this->expr_14_in1 / this->expr_14_in2))
        );//#map:subbass//_obj-32:1
    }
    
    void receive_12_output_number_set(number v) {
        this->receive_12_output_number = v;
        this->expr_14_in1_set(v);
    }
    
    void phasor_03_freq_set(number v) {
        this->phasor_03_freq = v;
    }
    
    void expr_16_out1_set(number v) {
        this->expr_16_out1 = v;
        this->phasor_03_freq_set(this->expr_16_out1);
    }
    
    void expr_16_in1_set(number in1) {
        this->expr_16_in1 = in1;
        this->expr_16_out1_set(this->expr_16_in1 - this->expr_16_in2);//#map:subbass/-_obj-24:1
    }
    
    void expr_17_out1_set(number v) {
        this->expr_17_out1 = v;
        this->expr_16_in1_set(this->expr_17_out1);
    }
    
    void expr_17_in1_set(number in1) {
        this->expr_17_in1 = in1;
    
        this->expr_17_out1_set(
            (this->expr_17_in2 == 0 ? 0 : (this->expr_17_in2 == 0. ? 0. : this->expr_17_in1 / this->expr_17_in2))
        );//#map:subbass//_obj-25:1
    }
    
    void receive_14_output_number_set(number v) {
        this->receive_14_output_number = v;
        this->expr_17_in1_set(v);
    }
    
    void gaintilde_02_outval_set(number ) {}
    
    void gaintilde_02_value_set(number v) {
        this->gaintilde_02_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-3"), v, this->_currentTime);
        this->gaintilde_02_outval_set(value);
    }
    
    void gaintilde_02_input_number_set(number v) {
        this->gaintilde_02_input_number = v;
    
        this->gaintilde_02_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->gaintilde_02_input_number_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:subbass/+_obj-85:1
    }
    
    void receive_01_output_number_set(number v) {
        this->receive_01_output_number = v;
        this->expr_02_in1_set(v);
    }
    
    void gaintilde_04_outval_set(number ) {}
    
    void gaintilde_04_value_set(number v) {
        this->gaintilde_04_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-10"), v, this->_currentTime);
        this->gaintilde_04_outval_set(value);
    }
    
    void gaintilde_04_input_number_set(number v) {
        this->gaintilde_04_input_number = v;
    
        this->gaintilde_04_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->gaintilde_04_input_number_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
        this->expr_04_out1_set(this->expr_04_in1 - this->expr_04_in2);//#map:subbass/-_obj-14:1
    }
    
    void receive_04_output_number_set(number v) {
        this->receive_04_output_number = v;
        this->expr_04_in1_set(v);
    }
    
    void gaintilde_05_outval_set(number ) {}
    
    void gaintilde_05_value_set(number v) {
        this->gaintilde_05_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-20"), v, this->_currentTime);
        this->gaintilde_05_outval_set(value);
    }
    
    void gaintilde_05_input_number_set(number v) {
        this->gaintilde_05_input_number = v;
    
        this->gaintilde_05_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_07_out1_set(number v) {
        this->expr_07_out1 = v;
        this->gaintilde_05_input_number_set(this->expr_07_out1);
    }
    
    void expr_07_in1_set(number in1) {
        this->expr_07_in1 = in1;
        this->expr_07_out1_set(this->expr_07_in1 - this->expr_07_in2);//#map:subbass/-_obj-52:1
    }
    
    void receive_07_output_number_set(number v) {
        this->receive_07_output_number = v;
        this->expr_07_in1_set(v);
    }
    
    void gaintilde_06_outval_set(number ) {}
    
    void gaintilde_06_value_set(number v) {
        this->gaintilde_06_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-41"), v, this->_currentTime);
        this->gaintilde_06_outval_set(value);
    }
    
    void expr_10_out1_set(number v) {
        this->expr_10_out1 = v;
        this->gaintilde_06_value_set(this->expr_10_out1);
    }
    
    void expr_10_in1_set(number in1) {
        this->expr_10_in1 = in1;
        this->expr_10_out1_set(this->expr_10_in1 - this->expr_10_in2);//#map:subbass/-_obj-60:1
    }
    
    void receive_09_output_number_set(number v) {
        this->receive_09_output_number = v;
        this->expr_10_in1_set(v);
    }
    
    void gaintilde_07_outval_set(number ) {}
    
    void gaintilde_07_value_set(number v) {
        this->gaintilde_07_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-34"), v, this->_currentTime);
        this->gaintilde_07_outval_set(value);
    }
    
    void gaintilde_07_input_number_set(number v) {
        this->gaintilde_07_input_number = v;
    
        this->gaintilde_07_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_12_out1_set(number v) {
        this->expr_12_out1 = v;
        this->gaintilde_07_input_number_set(this->expr_12_out1);
    }
    
    void expr_12_in1_set(number in1) {
        this->expr_12_in1 = in1;
        this->expr_12_out1_set(this->expr_12_in1 - this->expr_12_in2);//#map:subbass/-_obj-29:1
    }
    
    void receive_11_output_number_set(number v) {
        this->receive_11_output_number = v;
        this->expr_12_in1_set(v);
    }
    
    void gaintilde_08_outval_set(number ) {}
    
    void gaintilde_08_value_set(number v) {
        this->gaintilde_08_value = v;
        number value;
        value = this->scale(v, 0, 157, 0, 158 - 1, 1);
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("subbass/gain~_obj-27"), v, this->_currentTime);
        this->gaintilde_08_outval_set(value);
    }
    
    void gaintilde_08_input_number_set(number v) {
        this->gaintilde_08_input_number = v;
    
        this->gaintilde_08_value_set(
            this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
        );
    }
    
    void expr_15_out1_set(number v) {
        this->expr_15_out1 = v;
        this->gaintilde_08_input_number_set(this->expr_15_out1);
    }
    
    void expr_15_in1_set(number in1) {
        this->expr_15_in1 = in1;
        this->expr_15_out1_set(this->expr_15_in1 - this->expr_15_in2);//#map:subbass/-_obj-22:1
    }
    
    void receive_13_output_number_set(number v) {
        this->receive_13_output_number = v;
        this->expr_15_in1_set(v);
    }
    
    void message_01_set_set(const list& v) {
        this->message_01_set = jsCreateListCopy(v);
        this->getEngine()->sendListMessage(TAG("listout"), TAG("subbass/message_obj-81"), v, this->_currentTime);
    }
    
    void adsr_01_attack_set(number v) {
        this->adsr_01_attack = v;
    }
    
    void line_01_output_set(number v) {
        this->line_01_output = v;
        this->adsr_01_attack_set(v);
    }
    
    static number line_01_time_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void line_01_time_set(number v) {
        v = this->line_01_time_constrain(v);
        this->line_01_time = v;
    }
    
    void line_01_end_bang() {}
    
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
    
    void cycle_tilde_02_perform(
        number frequency,
        number phase_offset,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        RNBO_UNUSED(phase_offset);
        RNBO_UNUSED(frequency);
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
                    uint32_t pincr = (uint32_t)(uint32_trunc(5 * __cycle_tilde_02_f2i));
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
        RNBO_UNUSED(release);
        RNBO_UNUSED(sustain);
        RNBO_UNUSED(decay);
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
    
    void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * 500;//#map:_###_obj_###_:1
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
    
    void phasor_01_perform(number freq, SampleValue * out, Index n) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->phasor_01_ph_next(freq, -1);
            this->phasor_01_sigbuf[(Index)i] = -1;
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
    
    void phasor_02_perform(number freq, SampleValue * out, Index n) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->phasor_02_ph_next(freq, -1);
            this->phasor_02_sigbuf[(Index)i] = -1;
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
    
    void phasor_03_perform(number freq, SampleValue * out, Index n) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->phasor_03_ph_next(freq, -1);
            this->phasor_03_sigbuf[(Index)i] = -1;
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
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        const SampleValue * in5,
        const SampleValue * in6,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i] + in4[(Index)i] + in5[(Index)i] + in6[(Index)i];
        }
    }
    
    void limi_02_perform(const SampleValue * input1, SampleValue * output1, Index n) {
        RNBO_UNUSED(output1);
        RNBO_UNUSED(input1);
        auto __limi_02_lookaheadInv = this->limi_02_lookaheadInv;
        auto __limi_02_threshold = this->limi_02_threshold;
        auto __limi_02_lookahead = this->limi_02_lookahead;
        auto __limi_02_recover = this->limi_02_recover;
        auto __limi_02_last = this->limi_02_last;
        auto __limi_02_postamp = this->limi_02_postamp;
        auto __limi_02_lookaheadIndex = this->limi_02_lookaheadIndex;
        auto __limi_02_preamp = this->limi_02_preamp;
        auto __limi_02_dcblock = this->limi_02_dcblock;
        auto __limi_02_bypass = this->limi_02_bypass;
        ConstSampleArray<1> input = {input1};
        SampleArray<1> output = {output1};
    
        if ((bool)(__limi_02_bypass)) {
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
                    v = ((bool)(__limi_02_dcblock) ? this->limi_02_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                    v *= __limi_02_preamp;
                    this->limi_02_lookaheadBuffers[(Index)j][__limi_02_lookaheadIndex] = v * __limi_02_postamp;
                    v = rnbo_fabs(v);
    
                    if (v > hotSample)
                        hotSample = v;
                }
    
                {
                    if (__limi_02_last > 0.01)
                        v = __limi_02_last + __limi_02_recover * __limi_02_last;
                    else
                        v = __limi_02_last + __limi_02_recover;
                }
    
                if (v > 1)
                    v = 1;
    
                this->limi_02_gainBuffer[__limi_02_lookaheadIndex] = v;
                int lookaheadPlayback = (int)(__limi_02_lookaheadIndex - (int)(__limi_02_lookahead));
    
                if (lookaheadPlayback < 0)
                    lookaheadPlayback += (int)(__limi_02_lookahead);
    
                if (hotSample * v > __limi_02_threshold) {
                    number newgain;
                    number curgain = __limi_02_threshold / hotSample;
                    number inc = __limi_02_threshold - curgain;
                    number acc = 0.0;
                    number flag = 0;
    
                    for (Index j = 0; flag == 0 && j < (Index)(__limi_02_lookahead); j++) {
                        int k = (int)(__limi_02_lookaheadIndex - (int)(j));
    
                        if (k < 0)
                            k += (int)(__limi_02_lookahead);
    
                        {
                            newgain = curgain + inc * (acc * acc);
                        }
    
                        if (newgain < this->limi_02_gainBuffer[(Index)k])
                            this->limi_02_gainBuffer[(Index)k] = newgain;
                        else
                            flag = 1;
    
                        acc = acc + __limi_02_lookaheadInv;
                    }
                }
    
                for (Index j = 0; j < 1; j++) {
                    output[(Index)j][(Index)i] = this->limi_02_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_02_gainBuffer[(Index)lookaheadPlayback];
                }
    
                __limi_02_last = this->limi_02_gainBuffer[__limi_02_lookaheadIndex];
                __limi_02_lookaheadIndex++;
    
                if (__limi_02_lookaheadIndex >= __limi_02_lookahead)
                    __limi_02_lookaheadIndex = 0;
            }
        }
    
        this->limi_02_lookaheadIndex = __limi_02_lookaheadIndex;
        this->limi_02_last = __limi_02_last;
    }
    
    void delaytilde_01_perform(
        const Sample * delay,
        const SampleValue * input,
        SampleValue * output,
        Index n
    ) {
        auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
        auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
        auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
        auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;
    
        for (Index i = 0; i < n; i++) {
            if (__delaytilde_01_lastDelay == -1) {
                __delaytilde_01_lastDelay = delay[(Index)i];
            }
    
            if (__delaytilde_01_ramp > 0) {
                number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
                __delaytilde_01_ramp--;
            } else {
                number effectiveDelay = delay[(Index)i];
    
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
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
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
    
    void signaladder_04_perform(
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
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
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
    
    void signaladder_05_perform(
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
    
    void lores_01_perform(
        const Sample * cutoff,
        number resonance,
        const SampleValue * input,
        SampleValue * out,
        Index n
    ) {
        RNBO_UNUSED(resonance);
        auto __lores_01_y_2 = this->lores_01_y_2;
        auto __lores_01_y_1 = this->lores_01_y_1;
        auto __lores_01_x_0 = this->lores_01_x_0;
        auto __lores_01_b_0 = this->lores_01_b_0;
        auto __lores_01_a_1 = this->lores_01_a_1;
        auto __lores_01_a_2 = this->lores_01_a_2;
        auto __lores_01_last_freq_calc = this->lores_01_last_freq_calc;
        auto __lores_01_last_res_calc = this->lores_01_last_res_calc;
        auto __lores_01_last_frequency = this->lores_01_last_frequency;
        auto __lores_01_last_resonance = this->lores_01_last_resonance;
    
        for (Index i = 0; i < n; i++) {
            if (0 != __lores_01_last_resonance || cutoff[(Index)i] != __lores_01_last_frequency) {
                __lores_01_last_res_calc = rnbo_exp(0 * 0.125) * 0.882497;
                __lores_01_last_freq_calc = rnbo_cos(2.0 * pi01() / this->sr * cutoff[(Index)i]);
                __lores_01_last_resonance = 0;
                __lores_01_last_frequency = cutoff[(Index)i];
            }
    
            number res_temp = __lores_01_last_res_calc;
            number freq_temp = __lores_01_last_freq_calc;
            __lores_01_a_2 = res_temp * res_temp;
            __lores_01_a_1 = -2.0 * res_temp * freq_temp;
            __lores_01_b_0 = 1.0 + __lores_01_a_1 + __lores_01_a_2;
            __lores_01_x_0 = input[(Index)i];
            number y_0 = __lores_01_x_0 * __lores_01_b_0 - __lores_01_y_1 * __lores_01_a_1 - __lores_01_y_2 * __lores_01_a_2;
            __lores_01_y_2 = __lores_01_y_1;
            __lores_01_y_1 = y_0;
            out[(Index)i] = y_0;
        }
    
        this->lores_01_last_resonance = __lores_01_last_resonance;
        this->lores_01_last_frequency = __lores_01_last_frequency;
        this->lores_01_last_res_calc = __lores_01_last_res_calc;
        this->lores_01_last_freq_calc = __lores_01_last_freq_calc;
        this->lores_01_a_2 = __lores_01_a_2;
        this->lores_01_a_1 = __lores_01_a_1;
        this->lores_01_b_0 = __lores_01_b_0;
        this->lores_01_x_0 = __lores_01_x_0;
        this->lores_01_y_1 = __lores_01_y_1;
        this->lores_01_y_2 = __lores_01_y_2;
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
    
    void lores_01_resonance_setter(number v) {
        if (v < 0.0) {
            v = 0.0;
        } else if (v >= 1.0) {
            v = 1.0 - 1E-20;
        }
    
        this->lores_01_resonance = v;
    }
    
    void limi_02_lookahead_setter(number v) {
        this->limi_02_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
        this->limi_02_lookaheadInv = (number)1 / this->limi_02_lookahead;
    }
    
    void limi_02_preamp_setter(number v) {
        this->limi_02_preamp = rnbo_pow(10., v * 0.05);
    }
    
    void limi_02_postamp_setter(number v) {
        this->limi_02_postamp = rnbo_pow(10., v * 0.05);
    }
    
    void limi_02_threshold_setter(number v) {
        this->limi_02_threshold = rnbo_pow(10., v * 0.05);
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
    
    void lores_01_reset() {
        this->lores_01_y_1 = 0;
        this->lores_01_y_2 = 0;
        this->lores_01_last_resonance = 0;
        this->lores_01_last_frequency = 0;
        this->lores_01_last_res_calc = 0;
        this->lores_01_last_freq_calc = 0;
    }
    
    void lores_01_dspsetup(bool force) {
        if ((bool)(this->lores_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->lores_01_reset();
        this->lores_01_setupDone = true;
    }
    
    number limi_02_dc1_next(number x, number gain) {
        number y = x - this->limi_02_dc1_xm1 + this->limi_02_dc1_ym1 * gain;
        this->limi_02_dc1_xm1 = x;
        this->limi_02_dc1_ym1 = y;
        return y;
    }
    
    void limi_02_dc1_reset() {
        this->limi_02_dc1_xm1 = 0;
        this->limi_02_dc1_ym1 = 0;
    }
    
    void limi_02_dc1_dspsetup() {
        this->limi_02_dc1_reset();
    }
    
    number limi_02_dc_next(Index i, number x, number gain) {
        switch ((int)i) {
        default:
            {
            return this->limi_02_dc1_next(x, gain);
            }
        }
    
        return 0;
    }
    
    void limi_02_dc_reset(Index i) {
        switch ((int)i) {
        default:
            {
            return this->limi_02_dc1_reset();
            }
        }
    }
    
    void limi_02_dc_dspsetup(Index i) {
        switch ((int)i) {
        default:
            {
            return this->limi_02_dc1_dspsetup();
            }
        }
    }
    
    void limi_02_reset() {
        this->limi_02_recover = (number)1000 / (this->limi_02_release * this->samplerate());
    
        {
            this->limi_02_recover *= 0.707;
        }
    }
    
    void limi_02_dspsetup(bool force) {
        if ((bool)(this->limi_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->limi_02_reset();
        this->limi_02_setupDone = true;
        this->limi_02_dc1_dspsetup();
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
    
    void message_01_init() {
        this->message_01_set_set({149});
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
        return samplerate;
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
    
    void adsr_01_dspsetup(bool force) {
        if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->adsr_01_mspersamp = (number)1000 / this->sr;
        this->adsr_01_setupDone = true;
    }
    
    bool line_01_isFinished(number value) {
        return value == this->line_01_currentTarget && this->currenttime() - this->line_01_startTime >= this->line_01__time;
    }
    
    number line_01_valueAtTime(number time) {
        return this->line_01_startValue + this->line_01_slope * (time - this->line_01_startTime);
    }
    
    void line_01_scheduleNext() {
        auto currentTime = this->currenttime();
        number nextTime = currentTime + this->line_01_grain;
        number nextValue;
    
        if (nextTime - this->line_01_startTime >= this->line_01__time || this->line_01_grain == 0) {
            nextTime = this->line_01_startTime + this->line_01__time;
            nextValue = this->line_01_currentTarget;
        } else {
            nextValue = this->line_01_valueAtTime(nextTime);
        }
    
        this->getEngine()->scheduleClockEventWithValue(this, 848255507, nextTime - currentTime + this->_currentTime, nextValue);;
    }
    
    void line_01_startRamp(number target, MillisecondTime time) {
        auto currentTime = this->currenttime();
        this->line_01_startValue = this->line_01_valueAtTime(currentTime);
        this->line_01_startTime = currentTime;
        this->line_01_currentTarget = target;
        this->getEngine()->flushClockEvents(this, 848255507, false);;
        number rise = target - this->line_01_startValue;
        this->line_01_slope = rise / time;
        this->line_01_scheduleNext();
    }
    
    void line_01_startPendingRamp() {
        if (this->line_01_pendingRamps->length < 2) {
            this->line_01_pendingRamps->length = 0;
            this->line_01__time = 0;
            this->line_01_time_set(0);
            this->line_01_end_bang();
            return;
        }
    
        if (this->line_01_pendingRamps->length > 1) {
            number target = this->line_01_pendingRamps->shift();
            this->line_01__time = this->line_01_pendingRamps->shift();
            this->line_01__time = (this->line_01__time < 0 ? 0 : this->line_01__time);
            this->line_01_startRamp(target, this->line_01__time);
        }
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
        this->gaintilde_06_zval = 2 * rnbo_exp(-((158 - 1) * this->gaintilde_06_loginc));
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
        this->gaintilde_07_zval = 2 * rnbo_exp(-((158 - 1) * this->gaintilde_07_loginc));
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
        this->gaintilde_08_zval = 2 * rnbo_exp(-((158 - 1) * this->gaintilde_08_loginc));
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
        receive_01_output_number = 0;
        expr_01_in1 = 0;
        expr_01_in2 = 10;
        expr_01_out1 = 0;
        expr_02_in1 = 0;
        expr_02_in2 = 20;
        expr_02_out1 = 0;
        gaintilde_01_input_number = 0;
        gaintilde_01_value = 0;
        gaintilde_01_interp = 10;
        limi_01_bypass = 0;
        limi_01_dcblock = 0;
        limi_01_lookahead = 100;
        limi_01_lookahead_setter(limi_01_lookahead);
        limi_01_preamp = 0;
        limi_01_preamp_setter(limi_01_preamp);
        limi_01_postamp = 0;
        limi_01_postamp_setter(limi_01_postamp);
        limi_01_threshold = 0;
        limi_01_threshold_setter(limi_01_threshold);
        limi_01_release = 1000;
        lores_01_cutoff = 0;
        lores_01_resonance = 0;
        lores_01_resonance_setter(lores_01_resonance);
        limi_02_bypass = 0;
        limi_02_dcblock = 0;
        limi_02_lookahead = 100;
        limi_02_lookahead_setter(limi_02_lookahead);
        limi_02_preamp = 0;
        limi_02_preamp_setter(limi_02_preamp);
        limi_02_postamp = 0;
        limi_02_postamp_setter(limi_02_postamp);
        limi_02_threshold = 0;
        limi_02_threshold_setter(limi_02_threshold);
        limi_02_release = 1000;
        expr_03_in1 = 0;
        expr_03_in2 = 8;
        expr_03_out1 = 0;
        receive_02_output_number = 0;
        gaintilde_02_input_number = 0;
        gaintilde_02_value = 0;
        gaintilde_02_interp = 10;
        cycle_tilde_01_frequency = 0;
        cycle_tilde_01_phase_offset = 0;
        gaintilde_03_input_number = 0;
        gaintilde_03_value = 0;
        gaintilde_03_interp = 10;
        receive_03_output_number = 0;
        delaytilde_01_delay = 0;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        expr_04_in1 = 0;
        expr_04_in2 = 25;
        expr_04_out1 = 0;
        receive_04_output_number = 0;
        cycle_tilde_02_frequency = 5;
        cycle_tilde_02_phase_offset = 0;
        receive_05_output_number = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 500;
        expr_05_in1 = 0;
        expr_05_in2 = 2;
        expr_05_out1 = 0;
        expr_06_in1 = 0;
        expr_06_in2 = 8;
        expr_06_out1 = 0;
        receive_06_output_number = 0;
        gaintilde_04_input_number = 0;
        gaintilde_04_value = 0;
        gaintilde_04_interp = 10;
        cycle_tilde_03_frequency = 0;
        cycle_tilde_03_phase_offset = 0;
        adsr_01_trigger_number = 0;
        adsr_01_attack = 0;
        adsr_01_decay = 300;
        adsr_01_sustain = 0;
        adsr_01_release = 0;
        adsr_01_legato = 0;
        line_01_time = 0;
        line_01_grain = 10;
        line_01_output = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 25;
        expr_07_out1 = 0;
        receive_07_output_number = 0;
        expr_08_in1 = 0;
        expr_08_in2 = 2;
        expr_08_out1 = 0;
        expr_09_in1 = 0;
        expr_09_in2 = 8;
        expr_09_out1 = 0;
        receive_08_output_number = 0;
        cycle_tilde_04_frequency = 0;
        cycle_tilde_04_phase_offset = 0;
        gaintilde_05_input_number = 0;
        gaintilde_05_value = 0;
        gaintilde_05_interp = 10;
        receive_09_output_number = 0;
        expr_10_in1 = 0;
        expr_10_in2 = 25;
        expr_10_out1 = 0;
        gaintilde_06_input_number = 0;
        gaintilde_06_value = 0;
        gaintilde_06_interp = 10;
        expr_11_in1 = 0;
        expr_11_in2 = 8;
        expr_11_out1 = 0;
        receive_10_output_number = 0;
        phasor_01_freq = 0;
        expr_12_in1 = 0;
        expr_12_in2 = 50;
        expr_12_out1 = 0;
        receive_11_output_number = 0;
        expr_13_in1 = 0;
        expr_13_in2 = 2;
        expr_13_out1 = 0;
        expr_14_in1 = 0;
        expr_14_in2 = 8;
        expr_14_out1 = 0;
        receive_12_output_number = 0;
        phasor_02_freq = 0;
        gaintilde_07_input_number = 0;
        gaintilde_07_value = 0;
        gaintilde_07_interp = 10;
        expr_15_in1 = 0;
        expr_15_in2 = 50;
        expr_15_out1 = 0;
        receive_13_output_number = 0;
        expr_16_in1 = 0;
        expr_16_in2 = 2;
        expr_16_out1 = 0;
        expr_17_in1 = 0;
        expr_17_in2 = 8;
        expr_17_out1 = 0;
        receive_14_output_number = 0;
        gaintilde_08_input_number = 0;
        gaintilde_08_value = 0;
        gaintilde_08_interp = 10;
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
        signals[9] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        gaintilde_01_lastValue = 0;
        gaintilde_01_loginc = 1;
        gaintilde_01_zval = 0;
        gaintilde_01_ramp_d_prev = 0;
        gaintilde_01_ramp_prev = 0;
        gaintilde_01_ramp_index = 0;
        gaintilde_01_ramp_increment = 0;
        gaintilde_01_setupDone = false;
        limi_01_last = 0;
        limi_01_lookaheadIndex = 0;
        limi_01_recover = 0;
        limi_01_lookaheadInv = 0;
        limi_01_dc1_xm1 = 0;
        limi_01_dc1_ym1 = 0;
        limi_01_setupDone = false;
        lores_01_setupDone = false;
        limi_02_last = 0;
        limi_02_lookaheadIndex = 0;
        limi_02_recover = 0;
        limi_02_lookaheadInv = 0;
        limi_02_dc1_xm1 = 0;
        limi_02_dc1_ym1 = 0;
        limi_02_setupDone = false;
        gaintilde_02_lastValue = 0;
        gaintilde_02_loginc = 1;
        gaintilde_02_zval = 0;
        gaintilde_02_ramp_d_prev = 0;
        gaintilde_02_ramp_prev = 0;
        gaintilde_02_ramp_index = 0;
        gaintilde_02_ramp_increment = 0;
        gaintilde_02_setupDone = false;
        cycle_tilde_01_wrap = 0;
        cycle_tilde_01_ph_currentPhase = 0;
        cycle_tilde_01_ph_conv = 0;
        cycle_tilde_01_setupDone = false;
        gaintilde_03_lastValue = 0;
        gaintilde_03_loginc = 1;
        gaintilde_03_zval = 0;
        gaintilde_03_ramp_d_prev = 0;
        gaintilde_03_ramp_prev = 0;
        gaintilde_03_ramp_index = 0;
        gaintilde_03_ramp_increment = 0;
        gaintilde_03_setupDone = false;
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
        cycle_tilde_02_wrap = 0;
        cycle_tilde_02_ph_currentPhase = 0;
        cycle_tilde_02_ph_conv = 0;
        cycle_tilde_02_setupDone = false;
        gaintilde_04_lastValue = 0;
        gaintilde_04_loginc = 1;
        gaintilde_04_zval = 0;
        gaintilde_04_ramp_d_prev = 0;
        gaintilde_04_ramp_prev = 0;
        gaintilde_04_ramp_index = 0;
        gaintilde_04_ramp_increment = 0;
        gaintilde_04_setupDone = false;
        cycle_tilde_03_wrap = 0;
        cycle_tilde_03_ph_currentPhase = 0;
        cycle_tilde_03_ph_conv = 0;
        cycle_tilde_03_setupDone = false;
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
        line_01_startTime = 0;
        line_01_startValue = 20;
        line_01_currentTarget = 0;
        line_01_slope = 0;
        line_01__time = 0;
        cycle_tilde_04_wrap = 0;
        cycle_tilde_04_ph_currentPhase = 0;
        cycle_tilde_04_ph_conv = 0;
        cycle_tilde_04_setupDone = false;
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
        phasor_01_sigbuf = nullptr;
        phasor_01_lastLockedPhase = 0;
        phasor_01_conv = 0;
        phasor_01_ph_currentPhase = 0;
        phasor_01_ph_conv = 0;
        phasor_01_setupDone = false;
        phasor_02_sigbuf = nullptr;
        phasor_02_lastLockedPhase = 0;
        phasor_02_conv = 0;
        phasor_02_ph_currentPhase = 0;
        phasor_02_ph_conv = 0;
        phasor_02_setupDone = false;
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
        phasor_03_sigbuf = nullptr;
        phasor_03_lastLockedPhase = 0;
        phasor_03_conv = 0;
        phasor_03_ph_currentPhase = 0;
        phasor_03_ph_conv = 0;
        phasor_03_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number receive_01_output_number;
        list receive_01_output_list;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number expr_02_in1;
        number expr_02_in2;
        number expr_02_out1;
        number gaintilde_01_input_number;
        number gaintilde_01_value;
        number gaintilde_01_interp;
        number limi_01_bypass;
        number limi_01_dcblock;
        number limi_01_lookahead;
        number limi_01_preamp;
        number limi_01_postamp;
        number limi_01_threshold;
        number limi_01_release;
        number lores_01_cutoff;
        number lores_01_resonance;
        number limi_02_bypass;
        number limi_02_dcblock;
        number limi_02_lookahead;
        number limi_02_preamp;
        number limi_02_postamp;
        number limi_02_threshold;
        number limi_02_release;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number receive_02_output_number;
        list receive_02_output_list;
        number gaintilde_02_input_number;
        number gaintilde_02_value;
        number gaintilde_02_interp;
        number cycle_tilde_01_frequency;
        number cycle_tilde_01_phase_offset;
        number gaintilde_03_input_number;
        number gaintilde_03_value;
        number gaintilde_03_interp;
        list message_01_set;
        number receive_03_output_number;
        list receive_03_output_list;
        number delaytilde_01_delay;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number expr_04_in1;
        number expr_04_in2;
        number expr_04_out1;
        number receive_04_output_number;
        list receive_04_output_list;
        number cycle_tilde_02_frequency;
        number cycle_tilde_02_phase_offset;
        number receive_05_output_number;
        list receive_05_output_list;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        number expr_06_in1;
        number expr_06_in2;
        number expr_06_out1;
        number receive_06_output_number;
        list receive_06_output_list;
        number gaintilde_04_input_number;
        number gaintilde_04_value;
        number gaintilde_04_interp;
        number cycle_tilde_03_frequency;
        number cycle_tilde_03_phase_offset;
        number adsr_01_trigger_number;
        number adsr_01_attack;
        number adsr_01_decay;
        number adsr_01_sustain;
        number adsr_01_release;
        number adsr_01_legato;
        list line_01_target;
        number line_01_time;
        number line_01_grain;
        number line_01_output;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number receive_07_output_number;
        list receive_07_output_list;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number expr_09_in1;
        number expr_09_in2;
        number expr_09_out1;
        number receive_08_output_number;
        list receive_08_output_list;
        number cycle_tilde_04_frequency;
        number cycle_tilde_04_phase_offset;
        number gaintilde_05_input_number;
        number gaintilde_05_value;
        number gaintilde_05_interp;
        number receive_09_output_number;
        list receive_09_output_list;
        number expr_10_in1;
        number expr_10_in2;
        number expr_10_out1;
        number gaintilde_06_input_number;
        number gaintilde_06_value;
        number gaintilde_06_interp;
        number expr_11_in1;
        number expr_11_in2;
        number expr_11_out1;
        number receive_10_output_number;
        list receive_10_output_list;
        number phasor_01_freq;
        number expr_12_in1;
        number expr_12_in2;
        number expr_12_out1;
        number receive_11_output_number;
        list receive_11_output_list;
        number expr_13_in1;
        number expr_13_in2;
        number expr_13_out1;
        number expr_14_in1;
        number expr_14_in2;
        number expr_14_out1;
        number receive_12_output_number;
        list receive_12_output_list;
        number phasor_02_freq;
        number gaintilde_07_input_number;
        number gaintilde_07_value;
        number gaintilde_07_interp;
        number expr_15_in1;
        number expr_15_in2;
        number expr_15_out1;
        number receive_13_output_number;
        list receive_13_output_list;
        number expr_16_in1;
        number expr_16_in2;
        number expr_16_out1;
        number expr_17_in1;
        number expr_17_in2;
        number expr_17_out1;
        number receive_14_output_number;
        list receive_14_output_list;
        number gaintilde_08_input_number;
        number gaintilde_08_value;
        number gaintilde_08_interp;
        number phasor_03_freq;
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
        number gaintilde_01_lastValue;
        number gaintilde_01_loginc;
        number gaintilde_01_zval;
        number gaintilde_01_ramp_d_prev;
        number gaintilde_01_ramp_prev;
        number gaintilde_01_ramp_index;
        number gaintilde_01_ramp_increment;
        bool gaintilde_01_setupDone;
        SampleValue limi_01_lookaheadBuffers[1][512] = { };
        SampleValue limi_01_gainBuffer[512] = { };
        number limi_01_last;
        int limi_01_lookaheadIndex;
        number limi_01_recover;
        number limi_01_lookaheadInv;
        number limi_01_dc1_xm1;
        number limi_01_dc1_ym1;
        bool limi_01_setupDone;
        number lores_01_b_0;
        number lores_01_a_1;
        number lores_01_a_2;
        number lores_01_x_0;
        number lores_01_y_1;
        number lores_01_y_2;
        number lores_01_last_resonance;
        number lores_01_last_frequency;
        number lores_01_last_res_calc;
        number lores_01_last_freq_calc;
        bool lores_01_setupDone;
        SampleValue limi_02_lookaheadBuffers[1][512] = { };
        SampleValue limi_02_gainBuffer[512] = { };
        number limi_02_last;
        int limi_02_lookaheadIndex;
        number limi_02_recover;
        number limi_02_lookaheadInv;
        number limi_02_dc1_xm1;
        number limi_02_dc1_ym1;
        bool limi_02_setupDone;
        number gaintilde_02_lastValue;
        number gaintilde_02_loginc;
        number gaintilde_02_zval;
        number gaintilde_02_ramp_d_prev;
        number gaintilde_02_ramp_prev;
        number gaintilde_02_ramp_index;
        number gaintilde_02_ramp_increment;
        bool gaintilde_02_setupDone;
        Float64BufferRef cycle_tilde_01_buffer;
        long cycle_tilde_01_wrap;
        uint32_t cycle_tilde_01_phasei;
        SampleValue cycle_tilde_01_f2i;
        number cycle_tilde_01_ph_currentPhase;
        number cycle_tilde_01_ph_conv;
        bool cycle_tilde_01_setupDone;
        number gaintilde_03_lastValue;
        number gaintilde_03_loginc;
        number gaintilde_03_zval;
        number gaintilde_03_ramp_d_prev;
        number gaintilde_03_ramp_prev;
        number gaintilde_03_ramp_index;
        number gaintilde_03_ramp_increment;
        bool gaintilde_03_setupDone;
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
        Float64BufferRef cycle_tilde_02_buffer;
        long cycle_tilde_02_wrap;
        uint32_t cycle_tilde_02_phasei;
        SampleValue cycle_tilde_02_f2i;
        number cycle_tilde_02_ph_currentPhase;
        number cycle_tilde_02_ph_conv;
        bool cycle_tilde_02_setupDone;
        number gaintilde_04_lastValue;
        number gaintilde_04_loginc;
        number gaintilde_04_zval;
        number gaintilde_04_ramp_d_prev;
        number gaintilde_04_ramp_prev;
        number gaintilde_04_ramp_index;
        number gaintilde_04_ramp_increment;
        bool gaintilde_04_setupDone;
        Float64BufferRef cycle_tilde_03_buffer;
        long cycle_tilde_03_wrap;
        uint32_t cycle_tilde_03_phasei;
        SampleValue cycle_tilde_03_f2i;
        number cycle_tilde_03_ph_currentPhase;
        number cycle_tilde_03_ph_conv;
        bool cycle_tilde_03_setupDone;
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
        number line_01_startTime;
        number line_01_startValue;
        number line_01_currentTarget;
        number line_01_slope;
        number line_01__time;
        list line_01_pendingRamps;
        Float64BufferRef cycle_tilde_04_buffer;
        long cycle_tilde_04_wrap;
        uint32_t cycle_tilde_04_phasei;
        SampleValue cycle_tilde_04_f2i;
        number cycle_tilde_04_ph_currentPhase;
        number cycle_tilde_04_ph_conv;
        bool cycle_tilde_04_setupDone;
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
        signal phasor_01_sigbuf;
        number phasor_01_lastLockedPhase;
        number phasor_01_conv;
        number phasor_01_ph_currentPhase;
        number phasor_01_ph_conv;
        bool phasor_01_setupDone;
        signal phasor_02_sigbuf;
        number phasor_02_lastLockedPhase;
        number phasor_02_conv;
        number phasor_02_ph_currentPhase;
        number phasor_02_ph_conv;
        bool phasor_02_setupDone;
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
        signal phasor_03_sigbuf;
        number phasor_03_lastLockedPhase;
        number phasor_03_conv;
        number phasor_03_ph_currentPhase;
        number phasor_03_ph_conv;
        bool phasor_03_setupDone;
        number stackprotect_count;
        DataRef delaytilde_01_del_bufferobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_255 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_241 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_255;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_241()
            {
            }
            
            ~RNBOSubpatcher_241()
            {
            }
            
            virtual RNBOSubpatcher_255* getPatcher() const {
                return static_cast<RNBOSubpatcher_255 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -1615565300, false);
                getEngine()->flushClockEvents(this, 1935387534, false);
                getEngine()->flushClockEvents(this, -1987572531, false);
                getEngine()->flushClockEvents(this, -1096817259, false);
                getEngine()->flushClockEvents(this, -1468824490, false);
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
            
            number samplerate() {
                return this->sr;
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
                this->phasor_04_perform(this->phasor_04_freq, this->signals[0], n);
            
                this->adsr_02_perform(
                    this->adsr_02_attack,
                    this->adsr_02_decay,
                    this->adsr_02_sustain,
                    this->adsr_02_release,
                    this->zeroBuffer,
                    this->signals[1],
                    n
                );
            
                this->dspexpr_03_perform(this->signals[0], this->signals[1], this->signals[2], n);
                this->phasor_05_perform(this->phasor_05_freq, this->signals[1], n);
            
                this->adsr_03_perform(
                    this->adsr_03_attack,
                    this->adsr_03_decay,
                    this->adsr_03_sustain,
                    this->adsr_03_release,
                    this->zeroBuffer,
                    this->signals[0],
                    n
                );
            
                this->dspexpr_04_perform(this->signals[1], this->signals[0], this->signals[3], n);
                this->signaladder_06_perform(this->signals[3], this->signals[2], this->signals[2], n);
            
                this->reson_tilde_01_perform(
                    this->signals[2],
                    this->reson_tilde_01_centerFreq,
                    this->reson_tilde_01_resonanceValue,
                    this->signals[0],
                    n
                );
            
                this->gaintilde_09_perform(this->signals[0], this->signals[3], n);
                this->delaytilde_02_perform(this->delaytilde_02_delay, this->signals[0], this->signals[1], n);
                this->gaintilde_10_perform(this->signals[1], this->signals[0], n);
                this->signaladder_07_perform(this->signals[3], this->signals[0], this->signals[0], n);
            
                this->allpass_tilde_01_perform(
                    this->signals[0],
                    this->allpass_tilde_01_delayTime,
                    this->allpass_tilde_01_gain,
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 4; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->phasor_04_sigbuf = resizeSignal(this->phasor_04_sigbuf, this->maxvs, maxBlockSize);
                    this->adsr_02_triggerBuf = resizeSignal(this->adsr_02_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_02_triggerValueBuf = resizeSignal(this->adsr_02_triggerValueBuf, this->maxvs, maxBlockSize);
                    this->phasor_05_sigbuf = resizeSignal(this->phasor_05_sigbuf, this->maxvs, maxBlockSize);
                    this->adsr_03_triggerBuf = resizeSignal(this->adsr_03_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_03_triggerValueBuf = resizeSignal(this->adsr_03_triggerValueBuf, this->maxvs, maxBlockSize);
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
            
                this->phasor_04_dspsetup(forceDSPSetup);
                this->adsr_02_dspsetup(forceDSPSetup);
                this->phasor_05_dspsetup(forceDSPSetup);
                this->adsr_03_dspsetup(forceDSPSetup);
                this->reson_tilde_01_dspsetup(forceDSPSetup);
                this->gaintilde_09_dspsetup(forceDSPSetup);
                this->delaytilde_02_dspsetup(forceDSPSetup);
                this->gaintilde_10_dspsetup(forceDSPSetup);
                this->allpass_tilde_01_dspsetup(forceDSPSetup);
            
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
                this->param_01_getPresetValue(getSubState(preset, "t"));
            }
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time);
                this->metro_01_onTransportChanged(state);
                this->metro_02_onTransportChanged(state);
                this->metro_03_onTransportChanged(state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time);
                this->metro_01_onBeatTimeChanged(beattime);
                this->metro_02_onBeatTimeChanged(beattime);
                this->metro_03_onBeatTimeChanged(beattime);
            }
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_01_value_set(v);
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
                return 1;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "t";
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
                    return "sparkles/bloops/t";
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
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
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
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            return 0 + value * (1 - 0);
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -1615565300:
                    {
                    this->metro_01_tick_bang();
                    break;
                    }
                case 1935387534:
                    {
                    this->metro_02_tick_bang();
                    break;
                    }
                case -1987572531:
                    {
                    this->metro_03_tick_bang();
                    break;
                    }
                case -1096817259:
                    {
                    this->adsr_02_mute_bang();
                    break;
                    }
                case -1468824490:
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
                    if (TAG("sparkles/bloops/toggle_obj-30") == objectId)
                        this->toggle_01_valin_set(payload);
            
                    if (TAG("sparkles/bloops/gain~_obj-72") == objectId)
                        this->gaintilde_09_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-62") == objectId)
                        this->numberobj_01_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-9") == objectId)
                        this->numberobj_02_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-65") == objectId)
                        this->numberobj_03_valin_set(payload);
            
                    if (TAG("sparkles/bloops/gain~_obj-71") == objectId)
                        this->gaintilde_10_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-50") == objectId)
                        this->numberobj_04_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-54") == objectId)
                        this->numberobj_05_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-8") == objectId)
                        this->numberobj_06_valin_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-46") == objectId)
                        this->numberobj_07_valin_set(payload);
            
                    break;
                    }
                case TAG("format"):
                    {
                    if (TAG("sparkles/bloops/number_obj-62") == objectId)
                        this->numberobj_01_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-9") == objectId)
                        this->numberobj_02_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-65") == objectId)
                        this->numberobj_03_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-50") == objectId)
                        this->numberobj_04_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-54") == objectId)
                        this->numberobj_05_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-8") == objectId)
                        this->numberobj_06_format_set(payload);
            
                    if (TAG("sparkles/bloops/number_obj-46") == objectId)
                        this->numberobj_07_format_set(payload);
            
                    break;
                    }
                case TAG("listin"):
                    {
                    if (TAG("sparkles/bloops/message_obj-60") == objectId)
                        this->message_02_listin_number_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-61") == objectId)
                        this->message_03_listin_number_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-52") == objectId)
                        this->message_04_listin_number_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-57") == objectId)
                        this->message_05_listin_number_set(payload);
            
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
                    if (TAG("sparkles/bloops/message_obj-60") == objectId)
                        this->message_02_listin_list_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-61") == objectId)
                        this->message_03_listin_list_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-52") == objectId)
                        this->message_04_listin_list_set(payload);
            
                    if (TAG("sparkles/bloops/message_obj-57") == objectId)
                        this->message_05_listin_list_set(payload);
            
                    break;
                    }
                }
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("listin"):
                    {
                    if (TAG("sparkles/bloops/message_obj-60") == objectId)
                        this->message_02_listin_bang_bang();
            
                    if (TAG("sparkles/bloops/message_obj-61") == objectId)
                        this->message_03_listin_bang_bang();
            
                    if (TAG("sparkles/bloops/message_obj-52") == objectId)
                        this->message_04_listin_bang_bang();
            
                    if (TAG("sparkles/bloops/message_obj-57") == objectId)
                        this->message_05_listin_bang_bang();
            
                    break;
                    }
                case TAG("bangin"):
                    {
                    if (TAG("sparkles/bloops/button_obj-32") == objectId)
                        this->button_01_bangin_bang();
            
                    if (TAG("sparkles/bloops/button_obj-69") == objectId)
                        this->button_02_bangin_bang();
            
                    if (TAG("sparkles/bloops/button_obj-42") == objectId)
                        this->button_03_bangin_bang();
            
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
                case TAG("sparkles/bloops/toggle_obj-30"):
                    {
                    return "sparkles/bloops/toggle_obj-30";
                    }
                case TAG("sparkles/bloops/gain~_obj-72"):
                    {
                    return "sparkles/bloops/gain~_obj-72";
                    }
                case TAG("sparkles/bloops/number_obj-62"):
                    {
                    return "sparkles/bloops/number_obj-62";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("listout"):
                    {
                    return "listout";
                    }
                case TAG("sparkles/bloops/message_obj-60"):
                    {
                    return "sparkles/bloops/message_obj-60";
                    }
                case TAG("sparkles/bloops/number_obj-9"):
                    {
                    return "sparkles/bloops/number_obj-9";
                    }
                case TAG("sparkles/bloops/number_obj-65"):
                    {
                    return "sparkles/bloops/number_obj-65";
                    }
                case TAG("bangout"):
                    {
                    return "bangout";
                    }
                case TAG("sparkles/bloops/button_obj-32"):
                    {
                    return "sparkles/bloops/button_obj-32";
                    }
                case TAG("sparkles/bloops/gain~_obj-71"):
                    {
                    return "sparkles/bloops/gain~_obj-71";
                    }
                case TAG("sparkles/bloops/button_obj-69"):
                    {
                    return "sparkles/bloops/button_obj-69";
                    }
                case TAG("sparkles/bloops/message_obj-61"):
                    {
                    return "sparkles/bloops/message_obj-61";
                    }
                case TAG("sparkles/bloops/number_obj-50"):
                    {
                    return "sparkles/bloops/number_obj-50";
                    }
                case TAG("sparkles/bloops/message_obj-52"):
                    {
                    return "sparkles/bloops/message_obj-52";
                    }
                case TAG("sparkles/bloops/number_obj-54"):
                    {
                    return "sparkles/bloops/number_obj-54";
                    }
                case TAG("sparkles/bloops/button_obj-42"):
                    {
                    return "sparkles/bloops/button_obj-42";
                    }
                case TAG("sparkles/bloops/number_obj-8"):
                    {
                    return "sparkles/bloops/number_obj-8";
                    }
                case TAG("sparkles/bloops/number_obj-46"):
                    {
                    return "sparkles/bloops/number_obj-46";
                    }
                case TAG("sparkles/bloops/message_obj-57"):
                    {
                    return "sparkles/bloops/message_obj-57";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("format"):
                    {
                    return "format";
                    }
                case TAG("listin"):
                    {
                    return "listin";
                    }
                case TAG("bangin"):
                    {
                    return "bangin";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                case 1:
                    {
                    return addressOf(this->allpass_tilde_01_feedForward_bufferobj);
                    break;
                    }
                case 2:
                    {
                    return addressOf(this->allpass_tilde_01_feedBack_bufferobj);
                    break;
                    }
                case 3:
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
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void zeroDataRef(DataRef& ref) {
                ref->setZero();
            }
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 1) {
                    this->allpass_tilde_01_feedForward_buffer = new Float64Buffer(this->allpass_tilde_01_feedForward_bufferobj);
                }
            
                if (index == 2) {
                    this->allpass_tilde_01_feedBack_buffer = new Float64Buffer(this->allpass_tilde_01_feedBack_bufferobj);
                }
            
                if (index == 3) {
                    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
                }
            }
            
            void initialize() {
                this->allpass_tilde_01_feedForward_bufferobj = initDataRef("allpass_tilde_01_feedForward_bufferobj", true, nullptr, "buffer~");
                this->allpass_tilde_01_feedBack_bufferobj = initDataRef("allpass_tilde_01_feedBack_bufferobj", true, nullptr, "buffer~");
                this->delaytilde_02_del_bufferobj = initDataRef("delaytilde_02_del_bufferobj", true, nullptr, "buffer~");
                this->assign_defaults();
                this->setState();
                this->allpass_tilde_01_feedForward_bufferobj->setIndex(1);
                this->allpass_tilde_01_feedForward_buffer = new Float64Buffer(this->allpass_tilde_01_feedForward_bufferobj);
                this->allpass_tilde_01_feedBack_bufferobj->setIndex(2);
                this->allpass_tilde_01_feedBack_buffer = new Float64Buffer(this->allpass_tilde_01_feedBack_bufferobj);
                this->delaytilde_02_del_bufferobj->setIndex(3);
                this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
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
                this->toggle_01_value_number_set(v);
            }
            
            void toggle_01_valin_set(number v) {
                this->toggle_01_value_number_set(v);
            }
            
            void gaintilde_09_valin_set(number v) {
                this->gaintilde_09_value_set(v);
            }
            
            void numberobj_01_valin_set(number v) {
                this->numberobj_01_value_set(v);
            }
            
            void numberobj_01_format_set(number v) {
                this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
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
            
            void numberobj_02_valin_set(number v) {
                this->numberobj_02_value_set(v);
            }
            
            void numberobj_02_format_set(number v) {
                this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void numberobj_03_valin_set(number v) {
                this->numberobj_03_value_set(v);
            }
            
            void numberobj_03_format_set(number v) {
                this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void button_01_bangin_bang() {
                this->button_01_bangval_bang();
            }
            
            void metro_01_tick_bang() {
                this->metro_01_tickout_bang();
                this->getEngine()->flushClockEvents(this, -1615565300, false);;
            
                if ((bool)(this->metro_01_on)) {
                    this->metro_01_last = this->currenttime();
            
                    {
                        this->metro_01_next = this->metro_01_last + this->metro_01_interval;
                        this->getEngine()->scheduleClockEvent(this, -1615565300, this->metro_01_interval + this->_currentTime);;
                    }
                }
            }
            
            void gaintilde_10_valin_set(number v) {
                this->gaintilde_10_value_set(v);
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
            
            void message_03_listin_list_set(const list& v) {
                this->message_03_set_set(v);
            }
            
            void message_03_listin_number_set(number v) {
                this->message_03_set_set(v);
            }
            
            void message_03_listin_bang_bang() {
                this->message_03_trigger_bang();
            }
            
            void numberobj_04_valin_set(number v) {
                this->numberobj_04_value_set(v);
            }
            
            void numberobj_04_format_set(number v) {
                this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void message_04_listin_list_set(const list& v) {
                this->message_04_set_set(v);
            }
            
            void message_04_listin_number_set(number v) {
                this->message_04_set_set(v);
            }
            
            void message_04_listin_bang_bang() {
                this->message_04_trigger_bang();
            }
            
            void numberobj_05_valin_set(number v) {
                this->numberobj_05_value_set(v);
            }
            
            void numberobj_05_format_set(number v) {
                this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void button_03_bangin_bang() {
                this->button_03_bangval_bang();
            }
            
            void metro_03_tick_bang() {
                this->metro_03_tickout_bang();
                this->getEngine()->flushClockEvents(this, -1987572531, false);;
            
                if ((bool)(this->metro_03_on)) {
                    this->metro_03_last = this->currenttime();
            
                    {
                        this->metro_03_next = this->metro_03_last + this->metro_03_interval;
                        this->getEngine()->scheduleClockEvent(this, -1987572531, this->metro_03_interval + this->_currentTime);;
                    }
                }
            }
            
            void numberobj_06_valin_set(number v) {
                this->numberobj_06_value_set(v);
            }
            
            void numberobj_06_format_set(number v) {
                this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void numberobj_07_valin_set(number v) {
                this->numberobj_07_value_set(v);
            }
            
            void numberobj_07_format_set(number v) {
                this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void message_05_listin_list_set(const list& v) {
                this->message_05_set_set(v);
            }
            
            void message_05_listin_number_set(number v) {
                this->message_05_set_set(v);
            }
            
            void message_05_listin_bang_bang() {
                this->message_05_trigger_bang();
            }
            
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
            
            void initializeObjects() {
                this->gaintilde_09_init();
                this->numberobj_01_init();
                this->message_02_init();
                this->allpass_tilde_01_feedForward_init();
                this->allpass_tilde_01_feedBack_init();
                this->allpass_tilde_01_init();
                this->numberobj_02_init();
                this->numberobj_03_init();
                this->random_01_nz_init();
                this->delaytilde_02_del_init();
                this->gaintilde_10_init();
                this->message_03_init();
                this->numberobj_04_init();
                this->message_04_init();
                this->numberobj_05_init();
                this->random_02_nz_init();
                this->numberobj_06_init();
                this->numberobj_07_init();
                this->message_05_init();
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
            
                if ((bool)(this->metro_03_on))
                    this->metro_03_on_set(1);
            
                {
                    this->scheduleParamInit(0, 0);
                }
            }
            
            void allocateDataRefs() {
                this->allpass_tilde_01_feedForward_buffer = this->allpass_tilde_01_feedForward_buffer->allocateIfNeeded();
            
                if (this->allpass_tilde_01_feedForward_bufferobj->hasRequestedSize()) {
                    if (this->allpass_tilde_01_feedForward_bufferobj->wantsFill())
                        this->zeroDataRef(this->allpass_tilde_01_feedForward_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(1);
                }
            
                this->allpass_tilde_01_feedBack_buffer = this->allpass_tilde_01_feedBack_buffer->allocateIfNeeded();
            
                if (this->allpass_tilde_01_feedBack_bufferobj->hasRequestedSize()) {
                    if (this->allpass_tilde_01_feedBack_bufferobj->wantsFill())
                        this->zeroDataRef(this->allpass_tilde_01_feedBack_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(2);
                }
            
                this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();
            
                if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
                    if (this->delaytilde_02_del_bufferobj->wantsFill())
                        this->zeroDataRef(this->delaytilde_02_del_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(3);
                }
            }
            
            void quantize_01_quantum_set(number v) {
                this->quantize_01_quantum = v;
            }
            
            void receive_15_output_number_set(number v) {
                this->receive_15_output_number = v;
                this->quantize_01_quantum_set(v);
            }
            
            void quantize_02_quantum_set(number v) {
                this->quantize_02_quantum = v;
            }
            
            void receive_18_output_number_set(number v) {
                this->receive_18_output_number = v;
                this->quantize_02_quantum_set(v);
            }
            
            void expr_18_in2_set(number v) {
                this->expr_18_in2 = v;
            }
            
            void numberobj_03_output_set(number v) {
                this->expr_18_in2_set(v);
            }
            
            void numberobj_03_value_set(number v) {
                this->numberobj_03_value_setter(v);
                v = this->numberobj_03_value;
                number localvalue = v;
            
                if (this->numberobj_03_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-65"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_03_output_set(localvalue);
            }
            
            void receive_16_output_number_set(number v) {
                this->receive_16_output_number = v;
                this->numberobj_03_value_set(v);
            }
            
            void expr_21_in2_set(number v) {
                this->expr_21_in2 = v;
            }
            
            void numberobj_07_output_set(number v) {
                this->expr_21_in2_set(v);
            }
            
            void numberobj_07_value_set(number v) {
                this->numberobj_07_value_setter(v);
                v = this->numberobj_07_value;
                number localvalue = v;
            
                if (this->numberobj_07_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-46"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_07_output_set(localvalue);
            }
            
            void receive_19_output_number_set(number v) {
                this->receive_19_output_number = v;
                this->numberobj_07_value_set(v);
            }
            
            void gaintilde_10_outval_set(number ) {}
            
            void gaintilde_10_value_set(number v) {
                this->gaintilde_10_value = v;
                number value;
                value = this->scale(v, 0, 157, 0, 158 - 1, 1);
                this->getEngine()->sendNumMessage(TAG("valout"), TAG("sparkles/bloops/gain~_obj-71"), v, this->_currentTime);
                this->gaintilde_10_outval_set(value);
            }
            
            void gaintilde_10_input_number_set(number v) {
                this->gaintilde_10_input_number = v;
            
                this->gaintilde_10_value_set(
                    this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
                );
            }
            
            void gaintilde_09_outval_set(number ) {}
            
            void gaintilde_09_value_set(number v) {
                this->gaintilde_09_value = v;
                number value;
                value = this->scale(v, 0, 157, 0, 158 - 1, 1);
                this->getEngine()->sendNumMessage(TAG("valout"), TAG("sparkles/bloops/gain~_obj-72"), v, this->_currentTime);
                this->gaintilde_09_outval_set(value);
            }
            
            void gaintilde_09_input_number_set(number v) {
                this->gaintilde_09_input_number = v;
            
                this->gaintilde_09_value_set(
                    this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
                );
            }
            
            void receive_17_output_number_set(number v) {
                this->receive_17_output_number = v;
                this->gaintilde_10_input_number_set(v);
                this->gaintilde_09_input_number_set(v);
            }
            
            static number param_01_value_constrain(number v) {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void send_01_input_number_set(number v) {
                this->send_01_input_number = v;
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_01_source_t_number_set(v);
            }
            
            void metro_03_on_set(number v) {
                this->metro_03_on = v;
                this->getEngine()->flushClockEvents(this, -1987572531, false);;
            
                if ((bool)(v)) {
                    {
                        this->getEngine()->scheduleClockEvent(this, -1987572531, 0 + this->_currentTime);;
                    }
                }
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
                this->getEngine()->flushClockEvents(this, -1615565300, false);;
            
                if ((bool)(v)) {
                    {
                        this->getEngine()->scheduleClockEvent(this, -1615565300, 0 + this->_currentTime);;
                    }
                }
            }
            
            void toggle_01_output_set(number v) {
                this->metro_03_on_set(v);
                this->metro_02_on_set(v);
                this->metro_01_on_set(v);
            }
            
            void toggle_01_value_number_set(number v) {
                this->toggle_01_value_number_setter(v);
                v = this->toggle_01_value_number;
                this->getEngine()->sendNumMessage(TAG("valout"), TAG("sparkles/bloops/toggle_obj-30"), v, this->_currentTime);
                this->toggle_01_output_set(v);
            }
            
            void metro_01_interval_set(number v) {
                this->metro_01_interval_setter(v);
                v = this->metro_01_interval;
            }
            
            void expr_18_out1_set(number v) {
                this->expr_18_out1 = v;
                this->metro_01_interval_set(this->expr_18_out1);
            }
            
            void expr_18_in1_set(number in1) {
                this->expr_18_in1 = in1;
            
                this->expr_18_out1_set(
                    (this->expr_18_in2 == 0 ? 0 : (this->expr_18_in2 == 0. ? 0. : this->expr_18_in1 / this->expr_18_in2))
                );//#map:sparkles/bloops//_obj-63:1
            }
            
            void numberobj_01_output_set(number v) {
                this->expr_18_in1_set(v);
            }
            
            void numberobj_01_value_set(number v) {
                this->numberobj_01_value_setter(v);
                v = this->numberobj_01_value;
                number localvalue = v;
            
                if (this->numberobj_01_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-62"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_01_output_set(localvalue);
            }
            
            void message_02_set_set(const list& v) {
                this->message_02_set = jsCreateListCopy(v);
            
                this->getEngine()->sendListMessage(
                    TAG("listout"),
                    TAG("sparkles/bloops/message_obj-60"),
                    v,
                    this->_currentTime
                );
            }
            
            void message_02_out_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->numberobj_01_value_set(converted);
                }
            }
            
            void message_02_trigger_bang() {
                this->message_02_out_set(this->message_02_set);
            }
            
            void numberobj_02_output_set(number ) {}
            
            void numberobj_02_value_set(number v) {
                this->numberobj_02_value_setter(v);
                v = this->numberobj_02_value;
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-9"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_02_output_set(localvalue);
            }
            
            void adsr_02_trigger_number_set(number v) {
                this->adsr_02_trigger_number = v;
            
                if (v != 0)
                    this->adsr_02_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
            
                for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
                    this->adsr_02_triggerValueBuf[(Index)i] = v;
                }
            }
            
            void message_03_out_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_02_trigger_number_set(converted);
                }
            }
            
            void message_03_trigger_bang() {
                this->message_03_out_set(this->message_03_set);
            }
            
            void phasor_04_freq_set(number v) {
                this->phasor_04_freq = v;
            }
            
            void quantize_01_out1_set(number v) {
                this->phasor_04_freq_set(v);
                this->numberobj_02_value_set(v);
            }
            
            void quantize_01_value_set(number value) {
                this->quantize_01_value = value;
                auto quantum = this->quantize_01_quantum;
            
                {
                    this->quantize_01_out1_set(rnbo_floor(value * quantum + 0.5) / quantum);
                    return;
                }
            }
            
            void expr_19_out1_set(number v) {
                this->expr_19_out1 = v;
                this->quantize_01_value_set(this->expr_19_out1);
            }
            
            void expr_19_in1_set(number in1) {
                this->expr_19_in1 = in1;
                this->expr_19_out1_set(this->expr_19_in1 + this->expr_19_in2);//#map:sparkles/bloops/+_obj-21:1
            }
            
            void random_01_result_set(number v) {
                this->expr_19_in1_set(v);
            }
            
            void random_01_trigger_bang() {
                {
                    this->random_01_result_set(this->random(0, this->random_01_limit));
                }
            }
            
            void button_01_output_bang() {
                this->message_03_trigger_bang();
                this->random_01_trigger_bang();
            }
            
            void button_01_bangval_bang() {
                this->getEngine()->sendBangMessage(TAG("bangout"), TAG("sparkles/bloops/button_obj-32"), this->_currentTime);;
                this->button_01_output_bang();
            }
            
            void metro_01_tickout_bang() {
                this->button_01_bangval_bang();
            }
            
            void metro_03_interval_set(number v) {
                this->metro_03_interval_setter(v);
                v = this->metro_03_interval;
            }
            
            void expr_21_out1_set(number v) {
                this->expr_21_out1 = v;
                this->metro_03_interval_set(this->expr_21_out1);
            }
            
            void expr_21_in1_set(number in1) {
                this->expr_21_in1 = in1;
            
                this->expr_21_out1_set(
                    (this->expr_21_in2 == 0 ? 0 : (this->expr_21_in2 == 0. ? 0. : this->expr_21_in1 / this->expr_21_in2))
                );//#map:sparkles/bloops//_obj-48:1
            }
            
            void numberobj_04_output_set(number v) {
                this->expr_21_in1_set(v);
            }
            
            void numberobj_04_value_set(number v) {
                this->numberobj_04_value_setter(v);
                v = this->numberobj_04_value;
                number localvalue = v;
            
                if (this->numberobj_04_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-50"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_04_output_set(localvalue);
            }
            
            void message_04_out_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->numberobj_04_value_set(converted);
                }
            }
            
            void message_04_trigger_bang() {
                this->message_04_out_set(this->message_04_set);
            }
            
            void button_02_output_bang() {
                this->message_04_trigger_bang();
                this->message_02_trigger_bang();
            }
            
            void button_02_bangval_bang() {
                this->getEngine()->sendBangMessage(TAG("bangout"), TAG("sparkles/bloops/button_obj-69"), this->_currentTime);;
                this->button_02_output_bang();
            }
            
            void metro_02_tickout_bang() {
                this->button_02_bangval_bang();
            }
            
            void message_03_set_set(const list& v) {
                this->message_03_set = jsCreateListCopy(v);
            
                this->getEngine()->sendListMessage(
                    TAG("listout"),
                    TAG("sparkles/bloops/message_obj-61"),
                    v,
                    this->_currentTime
                );
            }
            
            void message_04_set_set(const list& v) {
                this->message_04_set = jsCreateListCopy(v);
            
                this->getEngine()->sendListMessage(
                    TAG("listout"),
                    TAG("sparkles/bloops/message_obj-52"),
                    v,
                    this->_currentTime
                );
            }
            
            void numberobj_06_output_set(number ) {}
            
            void numberobj_06_value_set(number v) {
                this->numberobj_06_value_setter(v);
                v = this->numberobj_06_value;
                number localvalue = v;
            
                if (this->numberobj_06_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-8"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_06_output_set(localvalue);
            }
            
            void phasor_05_freq_set(number v) {
                this->phasor_05_freq = v;
            }
            
            void quantize_02_out1_set(number v) {
                this->numberobj_06_value_set(v);
                this->phasor_05_freq_set(v);
            }
            
            void quantize_02_value_set(number value) {
                this->quantize_02_value = value;
                auto quantum = this->quantize_02_quantum;
            
                {
                    this->quantize_02_out1_set(rnbo_floor(value * quantum + 0.5) / quantum);
                    return;
                }
            }
            
            void expr_20_out1_set(number v) {
                this->expr_20_out1 = v;
                this->quantize_02_value_set(this->expr_20_out1);
            }
            
            void expr_20_in1_set(number in1) {
                this->expr_20_in1 = in1;
                this->expr_20_out1_set(this->expr_20_in1 + this->expr_20_in2);//#map:sparkles/bloops/+_obj-20:1
            }
            
            void numberobj_05_output_set(number v) {
                this->expr_20_in1_set(v);
            }
            
            void numberobj_05_value_set(number v) {
                this->numberobj_05_value_setter(v);
                v = this->numberobj_05_value;
                number localvalue = v;
            
                if (this->numberobj_05_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("sparkles/bloops/number_obj-54"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_05_output_set(localvalue);
            }
            
            void adsr_03_trigger_number_set(number v) {
                this->adsr_03_trigger_number = v;
            
                if (v != 0)
                    this->adsr_03_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
            
                for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
                    this->adsr_03_triggerValueBuf[(Index)i] = v;
                }
            }
            
            void message_05_out_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_03_trigger_number_set(converted);
                }
            }
            
            void message_05_trigger_bang() {
                this->message_05_out_set(this->message_05_set);
            }
            
            void random_02_result_set(number v) {
                this->numberobj_05_value_set(v);
            }
            
            void random_02_trigger_bang() {
                {
                    this->random_02_result_set(this->random(0, this->random_02_limit));
                }
            }
            
            void button_03_output_bang() {
                this->message_05_trigger_bang();
                this->random_02_trigger_bang();
            }
            
            void button_03_bangval_bang() {
                this->getEngine()->sendBangMessage(TAG("bangout"), TAG("sparkles/bloops/button_obj-42"), this->_currentTime);;
                this->button_03_output_bang();
            }
            
            void metro_03_tickout_bang() {
                this->button_03_bangval_bang();
            }
            
            void message_05_set_set(const list& v) {
                this->message_05_set = jsCreateListCopy(v);
            
                this->getEngine()->sendListMessage(
                    TAG("listout"),
                    TAG("sparkles/bloops/message_obj-57"),
                    v,
                    this->_currentTime
                );
            }
            
            void phasor_04_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_04_ph_next(freq, -1);
                    this->phasor_04_sigbuf[(Index)i] = -1;
                }
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
                RNBO_UNUSED(release);
                RNBO_UNUSED(sustain);
                RNBO_UNUSED(decay);
                RNBO_UNUSED(attack);
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
                    number clampedattack = (15 > __adsr_02_mspersamp ? 15 : __adsr_02_mspersamp);
                    number clampeddecay = (300 > __adsr_02_mspersamp ? 300 : __adsr_02_mspersamp);
                    number clampedrelease = (0 > __adsr_02_mspersamp ? 0 : __adsr_02_mspersamp);
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
                            __adsr_02_outval = __adsr_02_amplitude * 0;
                        } else {
                            __adsr_02_outval = __adsr_02_amplitude * 0 + (__adsr_02_amplitude - __adsr_02_amplitude * 0) * (1. - __adsr_02_time / clampeddecay);
                        }
                    } else if (__adsr_02_phase == 3) {
                        __adsr_02_outval = __adsr_02_amplitude * 0;
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
                        -1096817259,
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
            
            void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void phasor_05_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_05_ph_next(freq, -1);
                    this->phasor_05_sigbuf[(Index)i] = -1;
                }
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
                        -1468824490,
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
            
            void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_06_perform(
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
                    number __centerFreq = 8000;
                    __centerFreq = rnbo_abs(__centerFreq);
            
                    if (this->reson_tilde_01_d_next(__centerFreq) != 0 || this->reson_tilde_01_d2_next(20) != 0) {
                        number clippedResonance = 20;
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
            
            void signaladder_07_perform(
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
            
            void allpass_tilde_01_perform(
                const Sample * x,
                number delayTime,
                number gain,
                SampleValue * out1,
                Index n
            ) {
                RNBO_UNUSED(gain);
                RNBO_UNUSED(delayTime);
                Index i;
            
                for (i = 0; i < n; i++) {
                    number __gain = 0.5;
                    auto delayTimeinSamps = this->mstosamps(500);
                    delayTimeinSamps = (delayTimeinSamps > 44100 ? 44100 : (delayTimeinSamps < 0 ? 0 : delayTimeinSamps));
                    __gain = (__gain > 0.99 ? 0.99 : (__gain < 0 ? 0 : __gain));
                    number ff = this->allpass_tilde_01_feedForward_read(delayTimeinSamps, 0);
                    number fb = this->allpass_tilde_01_feedBack_read(delayTimeinSamps, 0);
                    number ov = ff + (x[(Index)i] - fb) * (__gain * -1.0);
                    fixdenorm(ov);
                    this->allpass_tilde_01_feedForward_write(x[(Index)i]);
                    this->allpass_tilde_01_feedBack_write(ov);
                    this->allpass_tilde_01_feedForward_step();
                    this->allpass_tilde_01_feedBack_step();
                    out1[(Index)i] = ov;
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void toggle_01_value_number_setter(number v) {
                this->toggle_01_value_number = (v != 0 ? 1 : 0);
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
            
            void numberobj_03_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_03_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_03_value = localvalue;
            }
            
            void random_01_limit_setter(number v) {
                if (v >= 0)
                    this->random_01_limit = v;
            }
            
            void metro_01_interval_setter(number v) {
                this->metro_01_interval = (v > 0 ? v : 0);
            }
            
            void metro_02_interval_setter(number v) {
                this->metro_02_interval = (v > 0 ? v : 0);
            }
            
            void numberobj_04_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_04_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_04_value = localvalue;
            }
            
            void numberobj_05_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_05_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_05_value = localvalue;
            }
            
            void random_02_limit_setter(number v) {
                if (v >= 0)
                    this->random_02_limit = v;
            }
            
            void metro_03_interval_setter(number v) {
                this->metro_03_interval = (v > 0 ? v : 0);
            }
            
            void numberobj_06_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_06_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_06_value = localvalue;
            }
            
            void numberobj_07_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_07_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_07_value = localvalue;
            }
            
            void param_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_01_value;
            }
            
            void param_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_01_value_set(preset["value"]);
            }
            
            void toggle_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->toggle_01_value_number;
            }
            
            void toggle_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->toggle_01_value_number_set(preset["value"]);
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
            
            void numberobj_01_init() {
                this->numberobj_01_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-62"), 1, this->_currentTime);
            }
            
            void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_01_value;
            }
            
            void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_01_value_set(preset["value"]);
            }
            
            void message_02_init() {
                this->message_02_set_set({32000});
            }
            
            void allpass_tilde_01_feedForward_step() {
                this->allpass_tilde_01_feedForward_reader++;
            
                if (this->allpass_tilde_01_feedForward_reader >= (int)(this->allpass_tilde_01_feedForward_buffer->getSize()))
                    this->allpass_tilde_01_feedForward_reader = 0;
            }
            
            number allpass_tilde_01_feedForward_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->allpass_tilde_01_feedForward_buffer->getSize()) + this->allpass_tilde_01_feedForward_reader - ((size > this->allpass_tilde_01_feedForward__maxdelay ? this->allpass_tilde_01_feedForward__maxdelay : (size < (this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer) ? this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->allpass_tilde_01_feedForward_buffer->getSize()) + this->allpass_tilde_01_feedForward_reader - ((size > this->allpass_tilde_01_feedForward__maxdelay ? this->allpass_tilde_01_feedForward__maxdelay : (size < (1 + this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer) ? 1 + this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->allpass_tilde_01_feedForward_buffer->getSize()) + this->allpass_tilde_01_feedForward_reader - ((size > this->allpass_tilde_01_feedForward__maxdelay ? this->allpass_tilde_01_feedForward__maxdelay : (size < (1 + this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer) ? 1 + this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->allpass_tilde_01_feedForward_buffer->getSize()) + this->allpass_tilde_01_feedForward_reader - ((size > this->allpass_tilde_01_feedForward__maxdelay ? this->allpass_tilde_01_feedForward__maxdelay : (size < (this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer) ? this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ), this->allpass_tilde_01_feedForward_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                    ));
                }
            
                number r = (int)(this->allpass_tilde_01_feedForward_buffer->getSize()) + this->allpass_tilde_01_feedForward_reader - ((size > this->allpass_tilde_01_feedForward__maxdelay ? this->allpass_tilde_01_feedForward__maxdelay : (size < (this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer) ? this->allpass_tilde_01_feedForward_reader != this->allpass_tilde_01_feedForward_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->allpass_tilde_01_feedForward_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedForward_wrap))
                );
            }
            
            void allpass_tilde_01_feedForward_write(number v) {
                this->allpass_tilde_01_feedForward_writer = this->allpass_tilde_01_feedForward_reader;
                this->allpass_tilde_01_feedForward_buffer[(Index)this->allpass_tilde_01_feedForward_writer] = v;
            }
            
            number allpass_tilde_01_feedForward_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->allpass_tilde_01_feedForward__maxdelay : size);
                number val = this->allpass_tilde_01_feedForward_read(effectiveSize, 0);
                this->allpass_tilde_01_feedForward_write(v);
                this->allpass_tilde_01_feedForward_step();
                return val;
            }
            
            array<Index, 2> allpass_tilde_01_feedForward_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->allpass_tilde_01_feedForward_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->allpass_tilde_01_feedForward_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void allpass_tilde_01_feedForward_init() {
                auto result = this->allpass_tilde_01_feedForward_calcSizeInSamples();
                this->allpass_tilde_01_feedForward__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->allpass_tilde_01_feedForward_buffer->requestSize(requestedSizeInSamples, 1);
                this->allpass_tilde_01_feedForward_wrap = requestedSizeInSamples - 1;
            }
            
            void allpass_tilde_01_feedForward_clear() {
                this->allpass_tilde_01_feedForward_buffer->setZero();
            }
            
            void allpass_tilde_01_feedForward_reset() {
                auto result = this->allpass_tilde_01_feedForward_calcSizeInSamples();
                this->allpass_tilde_01_feedForward__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->allpass_tilde_01_feedForward_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->allpass_tilde_01_feedForward_buffer);
                this->allpass_tilde_01_feedForward_wrap = this->allpass_tilde_01_feedForward_buffer->getSize() - 1;
                this->allpass_tilde_01_feedForward_clear();
            
                if (this->allpass_tilde_01_feedForward_reader >= this->allpass_tilde_01_feedForward__maxdelay || this->allpass_tilde_01_feedForward_writer >= this->allpass_tilde_01_feedForward__maxdelay) {
                    this->allpass_tilde_01_feedForward_reader = 0;
                    this->allpass_tilde_01_feedForward_writer = 0;
                }
            }
            
            void allpass_tilde_01_feedForward_dspsetup() {
                this->allpass_tilde_01_feedForward_reset();
            }
            
            number allpass_tilde_01_feedForward_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                RNBO_UNUSED(samplerate);
                return 44100;
            }
            
            number allpass_tilde_01_feedForward_size() {
                return this->allpass_tilde_01_feedForward__maxdelay;
            }
            
            void allpass_tilde_01_feedBack_step() {
                this->allpass_tilde_01_feedBack_reader++;
            
                if (this->allpass_tilde_01_feedBack_reader >= (int)(this->allpass_tilde_01_feedBack_buffer->getSize()))
                    this->allpass_tilde_01_feedBack_reader = 0;
            }
            
            number allpass_tilde_01_feedBack_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->allpass_tilde_01_feedBack_buffer->getSize()) + this->allpass_tilde_01_feedBack_reader - ((size > this->allpass_tilde_01_feedBack__maxdelay ? this->allpass_tilde_01_feedBack__maxdelay : (size < (this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer) ? this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->allpass_tilde_01_feedBack_buffer->getSize()) + this->allpass_tilde_01_feedBack_reader - ((size > this->allpass_tilde_01_feedBack__maxdelay ? this->allpass_tilde_01_feedBack__maxdelay : (size < (1 + this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer) ? 1 + this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->allpass_tilde_01_feedBack_buffer->getSize()) + this->allpass_tilde_01_feedBack_reader - ((size > this->allpass_tilde_01_feedBack__maxdelay ? this->allpass_tilde_01_feedBack__maxdelay : (size < (1 + this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer) ? 1 + this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->allpass_tilde_01_feedBack_buffer->getSize()) + this->allpass_tilde_01_feedBack_reader - ((size > this->allpass_tilde_01_feedBack__maxdelay ? this->allpass_tilde_01_feedBack__maxdelay : (size < (this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer) ? this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ), this->allpass_tilde_01_feedBack_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                    ));
                }
            
                number r = (int)(this->allpass_tilde_01_feedBack_buffer->getSize()) + this->allpass_tilde_01_feedBack_reader - ((size > this->allpass_tilde_01_feedBack__maxdelay ? this->allpass_tilde_01_feedBack__maxdelay : (size < (this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer) ? this->allpass_tilde_01_feedBack_reader != this->allpass_tilde_01_feedBack_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->allpass_tilde_01_feedBack_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->allpass_tilde_01_feedBack_wrap))
                );
            }
            
            void allpass_tilde_01_feedBack_write(number v) {
                this->allpass_tilde_01_feedBack_writer = this->allpass_tilde_01_feedBack_reader;
                this->allpass_tilde_01_feedBack_buffer[(Index)this->allpass_tilde_01_feedBack_writer] = v;
            }
            
            number allpass_tilde_01_feedBack_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->allpass_tilde_01_feedBack__maxdelay : size);
                number val = this->allpass_tilde_01_feedBack_read(effectiveSize, 0);
                this->allpass_tilde_01_feedBack_write(v);
                this->allpass_tilde_01_feedBack_step();
                return val;
            }
            
            array<Index, 2> allpass_tilde_01_feedBack_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->allpass_tilde_01_feedBack_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->allpass_tilde_01_feedBack_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void allpass_tilde_01_feedBack_init() {
                auto result = this->allpass_tilde_01_feedBack_calcSizeInSamples();
                this->allpass_tilde_01_feedBack__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->allpass_tilde_01_feedBack_buffer->requestSize(requestedSizeInSamples, 1);
                this->allpass_tilde_01_feedBack_wrap = requestedSizeInSamples - 1;
            }
            
            void allpass_tilde_01_feedBack_clear() {
                this->allpass_tilde_01_feedBack_buffer->setZero();
            }
            
            void allpass_tilde_01_feedBack_reset() {
                auto result = this->allpass_tilde_01_feedBack_calcSizeInSamples();
                this->allpass_tilde_01_feedBack__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->allpass_tilde_01_feedBack_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->allpass_tilde_01_feedBack_buffer);
                this->allpass_tilde_01_feedBack_wrap = this->allpass_tilde_01_feedBack_buffer->getSize() - 1;
                this->allpass_tilde_01_feedBack_clear();
            
                if (this->allpass_tilde_01_feedBack_reader >= this->allpass_tilde_01_feedBack__maxdelay || this->allpass_tilde_01_feedBack_writer >= this->allpass_tilde_01_feedBack__maxdelay) {
                    this->allpass_tilde_01_feedBack_reader = 0;
                    this->allpass_tilde_01_feedBack_writer = 0;
                }
            }
            
            void allpass_tilde_01_feedBack_dspsetup() {
                this->allpass_tilde_01_feedBack_reset();
            }
            
            number allpass_tilde_01_feedBack_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                RNBO_UNUSED(samplerate);
                return 44100;
            }
            
            number allpass_tilde_01_feedBack_size() {
                return this->allpass_tilde_01_feedBack__maxdelay;
            }
            
            void allpass_tilde_01_init() {
                this->allpass_tilde_01_feedForward_init();
                this->allpass_tilde_01_feedBack_init();
            }
            
            void allpass_tilde_01_clear() {
                this->allpass_tilde_01_feedForward_clear();
                this->allpass_tilde_01_feedBack_clear();
            }
            
            void allpass_tilde_01_reset() {
                this->allpass_tilde_01_init();
                this->allpass_tilde_01_clear();
            }
            
            void allpass_tilde_01_dspsetup(bool force) {
                if ((bool)(this->allpass_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->allpass_tilde_01_reset();
                this->allpass_tilde_01_setupDone = true;
                this->allpass_tilde_01_feedForward_dspsetup();
                this->allpass_tilde_01_feedBack_dspsetup();
            }
            
            void numberobj_02_init() {
                this->numberobj_02_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-9"), 1, this->_currentTime);
            }
            
            void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_02_value;
            }
            
            void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_02_value_set(preset["value"]);
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
            
            void numberobj_03_init() {
                this->numberobj_03_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-65"), 1, this->_currentTime);
            }
            
            void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_03_value;
            }
            
            void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_03_value_set(preset["value"]);
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
            
            number phasor_04_ph_next(number freq, number reset) {
                RNBO_UNUSED(reset);
                number pincr = freq * this->phasor_04_ph_conv;
            
                if (this->phasor_04_ph_currentPhase < 0.)
                    this->phasor_04_ph_currentPhase = 1. + this->phasor_04_ph_currentPhase;
            
                if (this->phasor_04_ph_currentPhase > 1.)
                    this->phasor_04_ph_currentPhase = this->phasor_04_ph_currentPhase - 1.;
            
                number tmp = this->phasor_04_ph_currentPhase;
                this->phasor_04_ph_currentPhase += pincr;
                return tmp;
            }
            
            void phasor_04_ph_reset() {
                this->phasor_04_ph_currentPhase = 0;
            }
            
            void phasor_04_ph_dspsetup() {
                this->phasor_04_ph_conv = (number)1 / this->sr;
            }
            
            void phasor_04_dspsetup(bool force) {
                if ((bool)(this->phasor_04_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->phasor_04_conv = (number)1 / this->samplerate();
                this->phasor_04_setupDone = true;
                this->phasor_04_ph_dspsetup();
            }
            
            void metro_01_onTransportChanged(number ) {}
            
            void metro_01_onBeatTimeChanged(number ) {}
            
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
                return 5000;
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
            
            void metro_02_onTransportChanged(number ) {}
            
            void metro_02_onBeatTimeChanged(number ) {}
            
            void adsr_02_dspsetup(bool force) {
                if ((bool)(this->adsr_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_02_mspersamp = (number)1000 / this->sr;
                this->adsr_02_setupDone = true;
            }
            
            void message_03_init() {
                this->message_03_set_set({1});
            }
            
            void numberobj_04_init() {
                this->numberobj_04_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-50"), 1, this->_currentTime);
            }
            
            void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_04_value;
            }
            
            void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_04_value_set(preset["value"]);
            }
            
            void message_04_init() {
                this->message_04_set_set({16000});
            }
            
            number phasor_05_ph_next(number freq, number reset) {
                RNBO_UNUSED(reset);
                number pincr = freq * this->phasor_05_ph_conv;
            
                if (this->phasor_05_ph_currentPhase < 0.)
                    this->phasor_05_ph_currentPhase = 1. + this->phasor_05_ph_currentPhase;
            
                if (this->phasor_05_ph_currentPhase > 1.)
                    this->phasor_05_ph_currentPhase = this->phasor_05_ph_currentPhase - 1.;
            
                number tmp = this->phasor_05_ph_currentPhase;
                this->phasor_05_ph_currentPhase += pincr;
                return tmp;
            }
            
            void phasor_05_ph_reset() {
                this->phasor_05_ph_currentPhase = 0;
            }
            
            void phasor_05_ph_dspsetup() {
                this->phasor_05_ph_conv = (number)1 / this->sr;
            }
            
            void phasor_05_dspsetup(bool force) {
                if ((bool)(this->phasor_05_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->phasor_05_conv = (number)1 / this->samplerate();
                this->phasor_05_setupDone = true;
                this->phasor_05_ph_dspsetup();
            }
            
            void numberobj_05_init() {
                this->numberobj_05_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-54"), 1, this->_currentTime);
            }
            
            void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_05_value;
            }
            
            void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_05_value_set(preset["value"]);
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
            
            void metro_03_onTransportChanged(number ) {}
            
            void metro_03_onBeatTimeChanged(number ) {}
            
            void numberobj_06_init() {
                this->numberobj_06_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-8"), 1, this->_currentTime);
            }
            
            void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_06_value;
            }
            
            void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_06_value_set(preset["value"]);
            }
            
            void numberobj_07_init() {
                this->numberobj_07_currentFormat = 6;
                this->getEngine()->sendNumMessage(TAG("setup"), TAG("sparkles/bloops/number_obj-46"), 1, this->_currentTime);
            }
            
            void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_07_value;
            }
            
            void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_07_value_set(preset["value"]);
            }
            
            void message_05_init() {
                this->message_05_set_set({1});
            }
            
            void adsr_03_dspsetup(bool force) {
                if ((bool)(this->adsr_03_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_03_mspersamp = (number)1000 / this->sr;
                this->adsr_03_setupDone = true;
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
                param_01_value = 1;
                toggle_01_value_number = 0;
                toggle_01_value_number_setter(toggle_01_value_number);
                gaintilde_09_input_number = 0;
                gaintilde_09_value = 0;
                gaintilde_09_interp = 10;
                numberobj_01_value = 0;
                numberobj_01_value_setter(numberobj_01_value);
                quantize_01_value = 0;
                quantize_01_quantum = 1;
                send_01_input_number = 0;
                receive_15_output_number = 0;
                allpass_tilde_01_x = 0;
                allpass_tilde_01_delayTime = 500;
                allpass_tilde_01_gain = 0.5;
                numberobj_02_value = 0;
                numberobj_02_value_setter(numberobj_02_value);
                expr_18_in1 = 0;
                expr_18_in2 = 0;
                expr_18_out1 = 0;
                reson_tilde_01_x = 0;
                reson_tilde_01_centerFreq = 8000;
                reson_tilde_01_resonanceValue = 20;
                receive_16_output_number = 0;
                numberobj_03_value = 0;
                numberobj_03_value_setter(numberobj_03_value);
                expr_19_in1 = 0;
                expr_19_in2 = 8000;
                expr_19_out1 = 0;
                random_01_limit = 8000;
                random_01_limit_setter(random_01_limit);
                random_01_seed = 0;
                phasor_04_freq = 0;
                metro_01_on = 0;
                metro_01_interval = 500;
                metro_01_interval_setter(metro_01_interval);
                delaytilde_02_delay = 0;
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0;
                gaintilde_10_input_number = 0;
                gaintilde_10_value = 0;
                gaintilde_10_interp = 10;
                metro_02_on = 0;
                metro_02_interval = 10;
                metro_02_interval_setter(metro_02_interval);
                adsr_02_trigger_number = 0;
                adsr_02_attack = 15;
                adsr_02_decay = 300;
                adsr_02_sustain = 0;
                adsr_02_release = 0;
                adsr_02_legato = 0;
                receive_17_output_number = 0;
                numberobj_04_value = 0;
                numberobj_04_value_setter(numberobj_04_value);
                expr_20_in1 = 0;
                expr_20_in2 = 8000;
                expr_20_out1 = 0;
                dspexpr_04_in1 = 0;
                dspexpr_04_in2 = 0;
                quantize_02_value = 0;
                quantize_02_quantum = 1;
                phasor_05_freq = 0;
                numberobj_05_value = 0;
                numberobj_05_value_setter(numberobj_05_value);
                expr_21_in1 = 0;
                expr_21_in2 = 0;
                expr_21_out1 = 0;
                random_02_limit = 8000;
                random_02_limit_setter(random_02_limit);
                random_02_seed = 0;
                receive_18_output_number = 0;
                metro_03_on = 0;
                metro_03_interval = 500;
                metro_03_interval_setter(metro_03_interval);
                numberobj_06_value = 0;
                numberobj_06_value_setter(numberobj_06_value);
                receive_19_output_number = 0;
                numberobj_07_value = 0;
                numberobj_07_value_setter(numberobj_07_value);
                adsr_03_trigger_number = 0;
                adsr_03_attack = 20;
                adsr_03_decay = 50;
                adsr_03_sustain = 0;
                adsr_03_release = 0;
                adsr_03_legato = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                param_01_lastValue = 0;
                toggle_01_lastValue = 0;
                gaintilde_09_lastValue = 0;
                gaintilde_09_loginc = 1;
                gaintilde_09_zval = 0;
                gaintilde_09_ramp_d_prev = 0;
                gaintilde_09_ramp_prev = 0;
                gaintilde_09_ramp_index = 0;
                gaintilde_09_ramp_increment = 0;
                gaintilde_09_setupDone = false;
                numberobj_01_currentFormat = 6;
                numberobj_01_lastValue = 0;
                allpass_tilde_01_feedForward__maxdelay = 0;
                allpass_tilde_01_feedForward_sizemode = 0;
                allpass_tilde_01_feedForward_wrap = 0;
                allpass_tilde_01_feedForward_reader = 0;
                allpass_tilde_01_feedForward_writer = 0;
                allpass_tilde_01_feedBack__maxdelay = 0;
                allpass_tilde_01_feedBack_sizemode = 0;
                allpass_tilde_01_feedBack_wrap = 0;
                allpass_tilde_01_feedBack_reader = 0;
                allpass_tilde_01_feedBack_writer = 0;
                allpass_tilde_01_setupDone = false;
                numberobj_02_currentFormat = 6;
                numberobj_02_lastValue = 0;
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
                numberobj_03_currentFormat = 6;
                numberobj_03_lastValue = 0;
                phasor_04_sigbuf = nullptr;
                phasor_04_lastLockedPhase = 0;
                phasor_04_conv = 0;
                phasor_04_ph_currentPhase = 0;
                phasor_04_ph_conv = 0;
                phasor_04_setupDone = false;
                metro_01_last = -1;
                metro_01_next = -1;
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
                gaintilde_10_lastValue = 0;
                gaintilde_10_loginc = 1;
                gaintilde_10_zval = 0;
                gaintilde_10_ramp_d_prev = 0;
                gaintilde_10_ramp_prev = 0;
                gaintilde_10_ramp_index = 0;
                gaintilde_10_ramp_increment = 0;
                gaintilde_10_setupDone = false;
                metro_02_last = -1;
                metro_02_next = -1;
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
                numberobj_04_currentFormat = 6;
                numberobj_04_lastValue = 0;
                phasor_05_sigbuf = nullptr;
                phasor_05_lastLockedPhase = 0;
                phasor_05_conv = 0;
                phasor_05_ph_currentPhase = 0;
                phasor_05_ph_conv = 0;
                phasor_05_setupDone = false;
                numberobj_05_currentFormat = 6;
                numberobj_05_lastValue = 0;
                metro_03_last = -1;
                metro_03_next = -1;
                numberobj_06_currentFormat = 6;
                numberobj_06_lastValue = 0;
                numberobj_07_currentFormat = 6;
                numberobj_07_lastValue = 0;
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
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number param_01_value;
                number toggle_01_value_number;
                number gaintilde_09_input_number;
                number gaintilde_09_value;
                number gaintilde_09_interp;
                number numberobj_01_value;
                number quantize_01_value;
                number quantize_01_quantum;
                list message_02_set;
                number send_01_input_number;
                list send_01_input_list;
                number receive_15_output_number;
                list receive_15_output_list;
                number allpass_tilde_01_x;
                number allpass_tilde_01_delayTime;
                number allpass_tilde_01_gain;
                number numberobj_02_value;
                number expr_18_in1;
                number expr_18_in2;
                number expr_18_out1;
                number reson_tilde_01_x;
                number reson_tilde_01_centerFreq;
                number reson_tilde_01_resonanceValue;
                number receive_16_output_number;
                list receive_16_output_list;
                number numberobj_03_value;
                number expr_19_in1;
                number expr_19_in2;
                number expr_19_out1;
                number random_01_limit;
                number random_01_seed;
                number phasor_04_freq;
                number metro_01_on;
                number metro_01_interval;
                number delaytilde_02_delay;
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number gaintilde_10_input_number;
                number gaintilde_10_value;
                number gaintilde_10_interp;
                number metro_02_on;
                number metro_02_interval;
                number adsr_02_trigger_number;
                number adsr_02_attack;
                number adsr_02_decay;
                number adsr_02_sustain;
                number adsr_02_release;
                number adsr_02_legato;
                list message_03_set;
                number receive_17_output_number;
                list receive_17_output_list;
                number numberobj_04_value;
                number expr_20_in1;
                number expr_20_in2;
                number expr_20_out1;
                list message_04_set;
                number dspexpr_04_in1;
                number dspexpr_04_in2;
                number quantize_02_value;
                number quantize_02_quantum;
                number phasor_05_freq;
                number numberobj_05_value;
                number expr_21_in1;
                number expr_21_in2;
                number expr_21_out1;
                number random_02_limit;
                number random_02_seed;
                number receive_18_output_number;
                list receive_18_output_list;
                number metro_03_on;
                number metro_03_interval;
                number numberobj_06_value;
                number receive_19_output_number;
                list receive_19_output_list;
                number numberobj_07_value;
                list message_05_set;
                number adsr_03_trigger_number;
                number adsr_03_attack;
                number adsr_03_decay;
                number adsr_03_sustain;
                number adsr_03_release;
                number adsr_03_legato;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[4];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number param_01_lastValue;
                number toggle_01_lastValue;
                number gaintilde_09_lastValue;
                number gaintilde_09_loginc;
                number gaintilde_09_zval;
                number gaintilde_09_ramp_d_prev;
                number gaintilde_09_ramp_prev;
                number gaintilde_09_ramp_index;
                number gaintilde_09_ramp_increment;
                bool gaintilde_09_setupDone;
                Int numberobj_01_currentFormat;
                number numberobj_01_lastValue;
                Float64BufferRef allpass_tilde_01_feedForward_buffer;
                Index allpass_tilde_01_feedForward__maxdelay;
                Int allpass_tilde_01_feedForward_sizemode;
                Index allpass_tilde_01_feedForward_wrap;
                Int allpass_tilde_01_feedForward_reader;
                Int allpass_tilde_01_feedForward_writer;
                Float64BufferRef allpass_tilde_01_feedBack_buffer;
                Index allpass_tilde_01_feedBack__maxdelay;
                Int allpass_tilde_01_feedBack_sizemode;
                Index allpass_tilde_01_feedBack_wrap;
                Int allpass_tilde_01_feedBack_reader;
                Int allpass_tilde_01_feedBack_writer;
                bool allpass_tilde_01_setupDone;
                Int numberobj_02_currentFormat;
                number numberobj_02_lastValue;
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
                Int numberobj_03_currentFormat;
                number numberobj_03_lastValue;
                UInt random_01_nz_state[4] = { };
                signal phasor_04_sigbuf;
                number phasor_04_lastLockedPhase;
                number phasor_04_conv;
                number phasor_04_ph_currentPhase;
                number phasor_04_ph_conv;
                bool phasor_04_setupDone;
                number metro_01_last;
                number metro_01_next;
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
                number gaintilde_10_lastValue;
                number gaintilde_10_loginc;
                number gaintilde_10_zval;
                number gaintilde_10_ramp_d_prev;
                number gaintilde_10_ramp_prev;
                number gaintilde_10_ramp_index;
                number gaintilde_10_ramp_increment;
                bool gaintilde_10_setupDone;
                number metro_02_last;
                number metro_02_next;
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
                Int numberobj_04_currentFormat;
                number numberobj_04_lastValue;
                signal phasor_05_sigbuf;
                number phasor_05_lastLockedPhase;
                number phasor_05_conv;
                number phasor_05_ph_currentPhase;
                number phasor_05_ph_conv;
                bool phasor_05_setupDone;
                Int numberobj_05_currentFormat;
                number numberobj_05_lastValue;
                UInt random_02_nz_state[4] = { };
                number metro_03_last;
                number metro_03_next;
                Int numberobj_06_currentFormat;
                number numberobj_06_lastValue;
                Int numberobj_07_currentFormat;
                number numberobj_07_lastValue;
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
                number stackprotect_count;
                DataRef allpass_tilde_01_feedForward_bufferobj;
                DataRef allpass_tilde_01_feedBack_bufferobj;
                DataRef delaytilde_02_del_bufferobj;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_255()
    {
    }
    
    ~RNBOSubpatcher_255()
    {
        delete this->p_01;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
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
        this->p_01_perform(out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
    
        RNBO_UNUSED(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    
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
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_241();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "bloops"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_01->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_01->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_01->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        RNBO_UNUSED(v);
        this->updateTime(time);
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
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
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
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
        return 0 + this->p_01->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            default:
                {
                index -= 0;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 0;
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        return nullptr;
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
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_01->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
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
    
    void initializeObjects() {
        this->p_01->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
    }
    
    void p_01_target_freq_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->receive_15_output_number_set(v);
        this->p_01->updateTime(this->_currentTime);
        this->p_01->receive_18_output_number_set(v);
    }
    
    void p_01_target_conversion_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->receive_16_output_number_set(v);
        this->p_01->updateTime(this->_currentTime);
        this->p_01->receive_19_output_number_set(v);
    }
    
    void p_01_target_power_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->receive_17_output_number_set(v);
    }
    
    void p_01_source_t_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_15_source_t_number_set(v);
    }
    
    void p_01_perform(SampleValue * out1, Index n) {
        // subpatcher: bloops
        SampleArray<1> outs = {out1};
    
        this->p_01->process(nullptr, 0, outs, 1, n);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
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
        p_01_target = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number p_01_target;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_241* p_01;
    
};

class RNBOSubpatcher_256 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_242 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_242()
            {
            }
            
            ~RNBOSubpatcher_242()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_01_perform(this->intnum_tilde_01_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_01_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_01_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_01_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_243 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_243()
            {
            }
            
            ~RNBOSubpatcher_243()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, 1935387534, false);
                getEngine()->flushClockEvents(this, -1468824490, false);
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
            
            Index vectorsize() {
                return this->vs;
            }
            
            MillisecondTime currenttime() {
                return this->_currentTime;
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
                this->phasor_06_perform(this->phasor_06_freq, this->signals[0], n);
            
                this->adsr_04_perform(
                    this->adsr_04_attack,
                    this->adsr_04_decay,
                    this->adsr_04_sustain,
                    this->adsr_04_release,
                    this->zeroBuffer,
                    this->signals[1],
                    n
                );
            
                this->dspexpr_05_perform(this->signals[0], this->signals[1], this->signals[2], n);
                this->gaintilde_11_perform(this->signals[2], out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->phasor_06_sigbuf = resizeSignal(this->phasor_06_sigbuf, this->maxvs, maxBlockSize);
                    this->adsr_04_triggerBuf = resizeSignal(this->adsr_04_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_04_triggerValueBuf = resizeSignal(this->adsr_04_triggerValueBuf, this->maxvs, maxBlockSize);
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
            
                this->phasor_06_dspsetup(forceDSPSetup);
                this->adsr_04_dspsetup(forceDSPSetup);
                this->gaintilde_11_dspsetup(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time);
                this->metro_04_onTransportChanged(state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time);
                this->metro_04_onBeatTimeChanged(beattime);
            }
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case 1935387534:
                    {
                    this->metro_04_tick_bang();
                    break;
                    }
                case -1468824490:
                    {
                    this->adsr_04_mute_bang();
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
                    if (TAG("constellation[1]/aries/gain~_obj-6") == objectId)
                        this->gaintilde_11_valin_set(payload);
            
                    if (TAG("constellation[1]/aries/toggle_obj-13") == objectId)
                        this->toggle_02_valin_set(payload);
            
                    break;
                    }
                case TAG("listin"):
                    {
                    if (TAG("constellation[1]/aries/message_obj-18") == objectId)
                        this->message_06_listin_number_set(payload);
            
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
                    if (TAG("constellation[1]/aries/message_obj-18") == objectId)
                        this->message_06_listin_list_set(payload);
            
                    break;
                    }
                }
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("listin"):
                    {
                    if (TAG("constellation[1]/aries/message_obj-18") == objectId)
                        this->message_06_listin_bang_bang();
            
                    break;
                    }
                case TAG("bangin"):
                    {
                    if (TAG("constellation[1]/aries/button_obj-16") == objectId)
                        this->button_04_bangin_bang();
            
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
                case TAG("constellation[1]/aries/gain~_obj-6"):
                    {
                    return "constellation[1]/aries/gain~_obj-6";
                    }
                case TAG("listout"):
                    {
                    return "listout";
                    }
                case TAG("constellation[1]/aries/message_obj-18"):
                    {
                    return "constellation[1]/aries/message_obj-18";
                    }
                case TAG("constellation[1]/aries/toggle_obj-13"):
                    {
                    return "constellation[1]/aries/toggle_obj-13";
                    }
                case TAG("bangout"):
                    {
                    return "bangout";
                    }
                case TAG("constellation[1]/aries/button_obj-16"):
                    {
                    return "constellation[1]/aries/button_obj-16";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("listin"):
                    {
                    return "listin";
                    }
                case TAG("bangin"):
                    {
                    return "bangin";
                    }
                }
            
                return nullptr;
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
            }
            
            protected:
            
            void gaintilde_11_valin_set(number v) {
                this->gaintilde_11_value_set(v);
            }
            
            void message_06_listin_list_set(const list& v) {
                this->message_06_set_set(v);
            }
            
            void message_06_listin_number_set(number v) {
                this->message_06_set_set(v);
            }
            
            void message_06_listin_bang_bang() {
                this->message_06_trigger_bang();
            }
            
            void toggle_02_valin_set(number v) {
                this->toggle_02_value_number_set(v);
            }
            
            void metro_04_tick_bang() {
                this->metro_04_tickout_bang();
                this->getEngine()->flushClockEvents(this, 1935387534, false);;
            
                if ((bool)(this->metro_04_on)) {
                    this->metro_04_last = this->currenttime();
            
                    {
                        this->metro_04_next = this->metro_04_last + this->metro_04_interval;
                        this->getEngine()->scheduleClockEvent(this, 1935387534, this->metro_04_interval + this->_currentTime);;
                    }
                }
            }
            
            void button_04_bangin_bang() {
                this->button_04_bangval_bang();
            }
            
            void adsr_04_mute_bang() {}
            
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
            
            void initializeObjects() {
                this->gaintilde_11_init();
                this->message_06_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                if ((bool)(this->metro_04_on))
                    this->metro_04_on_set(1);
            }
            
            void allocateDataRefs() {}
            
            void metro_04_on_set(number v) {
                this->metro_04_on = v;
                this->getEngine()->flushClockEvents(this, 1935387534, false);;
            
                if ((bool)(v)) {
                    {
                        this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
                    }
                }
            }
            
            void toggle_02_output_set(number v) {
                this->metro_04_on_set(v);
            }
            
            void toggle_02_value_number_set(number v) {
                this->toggle_02_value_number_setter(v);
                v = this->toggle_02_value_number;
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("constellation[1]/aries/toggle_obj-13"),
                    v,
                    this->_currentTime
                );
            
                this->toggle_02_output_set(v);
            }
            
            void receive_22_output_number_set(number v) {
                this->receive_22_output_number = v;
                this->toggle_02_value_number_set(v);
            }
            
            void phasor_06_freq_set(number v) {
                this->phasor_06_freq = v;
            }
            
            void expr_22_out1_set(number v) {
                this->expr_22_out1 = v;
                this->phasor_06_freq_set(this->expr_22_out1);
            }
            
            void expr_22_in1_set(number in1) {
                this->expr_22_in1 = in1;
            
                this->expr_22_out1_set(
                    (this->expr_22_in2 == 0 ? 0 : (this->expr_22_in2 == 0. ? 0. : this->expr_22_in1 / this->expr_22_in2))
                );//#map:constellation[1]/aries//_obj-4:1
            }
            
            void receive_20_output_number_set(number v) {
                this->receive_20_output_number = v;
                this->expr_22_in1_set(v);
            }
            
            void gaintilde_11_outval_set(number ) {}
            
            void gaintilde_11_value_set(number v) {
                this->gaintilde_11_value = v;
                number value;
                value = this->scale(v, 0, 157, 0, 158 - 1, 1);
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("constellation[1]/aries/gain~_obj-6"),
                    v,
                    this->_currentTime
                );
            
                this->gaintilde_11_outval_set(value);
            }
            
            void gaintilde_11_input_number_set(number v) {
                this->gaintilde_11_input_number = v;
            
                this->gaintilde_11_value_set(
                    this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
                );
            }
            
            void expr_23_out1_set(number v) {
                this->expr_23_out1 = v;
                this->gaintilde_11_input_number_set(this->expr_23_out1);
            }
            
            void expr_23_in1_set(number in1) {
                this->expr_23_in1 = in1;
                this->expr_23_out1_set(this->expr_23_in1 - this->expr_23_in2);//#map:constellation[1]/aries/-_obj-20:1
            }
            
            void receive_21_output_number_set(number v) {
                this->receive_21_output_number = v;
                this->expr_23_in1_set(v);
            }
            
            void message_06_set_set(const list& v) {
                this->message_06_set = jsCreateListCopy(v);
            
                this->getEngine()->sendListMessage(
                    TAG("listout"),
                    TAG("constellation[1]/aries/message_obj-18"),
                    v,
                    this->_currentTime
                );
            }
            
            void adsr_04_trigger_number_set(number v) {
                this->adsr_04_trigger_number = v;
            
                if (v != 0)
                    this->adsr_04_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
            
                for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
                    this->adsr_04_triggerValueBuf[(Index)i] = v;
                }
            }
            
            void message_06_out_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->adsr_04_trigger_number_set(converted);
                }
            }
            
            void message_06_trigger_bang() {
                this->message_06_out_set(this->message_06_set);
            }
            
            void button_04_output_bang() {
                this->message_06_trigger_bang();
            }
            
            void button_04_bangval_bang() {
                this->getEngine()->sendBangMessage(
                    TAG("bangout"),
                    TAG("constellation[1]/aries/button_obj-16"),
                    this->_currentTime
                );;
            
                this->button_04_output_bang();
            }
            
            void metro_04_tickout_bang() {
                this->button_04_bangval_bang();
            }
            
            void phasor_06_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_06_ph_next(freq, -1);
                    this->phasor_06_sigbuf[(Index)i] = -1;
                }
            }
            
            void adsr_04_perform(
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
                auto __adsr_04_trigger_number = this->adsr_04_trigger_number;
                auto __adsr_04_time = this->adsr_04_time;
                auto __adsr_04_amplitude = this->adsr_04_amplitude;
                auto __adsr_04_outval = this->adsr_04_outval;
                auto __adsr_04_startingpoint = this->adsr_04_startingpoint;
                auto __adsr_04_phase = this->adsr_04_phase;
                auto __adsr_04_legato = this->adsr_04_legato;
                auto __adsr_04_lastTriggerVal = this->adsr_04_lastTriggerVal;
                auto __adsr_04_mspersamp = this->adsr_04_mspersamp;
                bool bangMute = false;
            
                for (Index i = 0; i < n; i++) {
                    number clampedattack = (1000 > __adsr_04_mspersamp ? 1000 : __adsr_04_mspersamp);
                    number clampeddecay = (3000 > __adsr_04_mspersamp ? 3000 : __adsr_04_mspersamp);
                    number clampedrelease = (0 > __adsr_04_mspersamp ? 0 : __adsr_04_mspersamp);
                    number currentTriggerVal = this->adsr_04_triggerValueBuf[(Index)i];
            
                    if ((__adsr_04_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_04_triggerBuf[(Index)i] == 1) {
                        if ((bool)(__adsr_04_legato)) {
                            if (__adsr_04_phase != 0) {
                                __adsr_04_startingpoint = __adsr_04_outval;
                            } else {
                                __adsr_04_startingpoint = 0;
                            }
                        } else {
                            __adsr_04_startingpoint = 0;
                        }
            
                        __adsr_04_amplitude = currentTriggerVal;
                        __adsr_04_phase = 1;
                        __adsr_04_time = 0.0;
                        bangMute = false;
                    } else if (__adsr_04_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                        if (__adsr_04_phase != 4 && __adsr_04_phase != 0) {
                            __adsr_04_phase = 4;
                            __adsr_04_amplitude = __adsr_04_outval;
                            __adsr_04_time = 0.0;
                        }
                    }
            
                    __adsr_04_time += __adsr_04_mspersamp;
            
                    if (__adsr_04_phase == 0) {
                        __adsr_04_outval = 0;
                    } else if (__adsr_04_phase == 1) {
                        if (__adsr_04_time > clampedattack) {
                            __adsr_04_time -= clampedattack;
                            __adsr_04_phase = 2;
                            __adsr_04_outval = __adsr_04_amplitude;
                        } else {
                            __adsr_04_outval = (__adsr_04_amplitude - __adsr_04_startingpoint) * __adsr_04_time / clampedattack + __adsr_04_startingpoint;
                        }
                    } else if (__adsr_04_phase == 2) {
                        if (__adsr_04_time > clampeddecay) {
                            __adsr_04_time -= clampeddecay;
                            __adsr_04_phase = 3;
                            __adsr_04_outval = __adsr_04_amplitude * 0;
                        } else {
                            __adsr_04_outval = __adsr_04_amplitude * 0 + (__adsr_04_amplitude - __adsr_04_amplitude * 0) * (1. - __adsr_04_time / clampeddecay);
                        }
                    } else if (__adsr_04_phase == 3) {
                        __adsr_04_outval = __adsr_04_amplitude * 0;
                    } else if (__adsr_04_phase == 4) {
                        if (__adsr_04_time > clampedrelease) {
                            __adsr_04_time = 0;
                            __adsr_04_phase = 0;
                            __adsr_04_outval = 0;
                            __adsr_04_amplitude = 0;
                            bangMute = true;
                        } else {
                            __adsr_04_outval = __adsr_04_amplitude * (1.0 - __adsr_04_time / clampedrelease);
                        }
                    }
            
                    out[(Index)i] = __adsr_04_outval;
                    this->adsr_04_triggerBuf[(Index)i] = 0;
                    this->adsr_04_triggerValueBuf[(Index)i] = __adsr_04_trigger_number;
                    __adsr_04_lastTriggerVal = currentTriggerVal;
                }
            
                if ((bool)(bangMute)) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1468824490,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            
                this->adsr_04_lastTriggerVal = __adsr_04_lastTriggerVal;
                this->adsr_04_phase = __adsr_04_phase;
                this->adsr_04_startingpoint = __adsr_04_startingpoint;
                this->adsr_04_outval = __adsr_04_outval;
                this->adsr_04_amplitude = __adsr_04_amplitude;
                this->adsr_04_time = __adsr_04_time;
            }
            
            void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
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
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void toggle_02_value_number_setter(number v) {
                this->toggle_02_value_number = (v != 0 ? 1 : 0);
            }
            
            void metro_04_interval_setter(number v) {
                this->metro_04_interval = (v > 0 ? v : 0);
            }
            
            number phasor_06_ph_next(number freq, number reset) {
                RNBO_UNUSED(reset);
                number pincr = freq * this->phasor_06_ph_conv;
            
                if (this->phasor_06_ph_currentPhase < 0.)
                    this->phasor_06_ph_currentPhase = 1. + this->phasor_06_ph_currentPhase;
            
                if (this->phasor_06_ph_currentPhase > 1.)
                    this->phasor_06_ph_currentPhase = this->phasor_06_ph_currentPhase - 1.;
            
                number tmp = this->phasor_06_ph_currentPhase;
                this->phasor_06_ph_currentPhase += pincr;
                return tmp;
            }
            
            void phasor_06_ph_reset() {
                this->phasor_06_ph_currentPhase = 0;
            }
            
            void phasor_06_ph_dspsetup() {
                this->phasor_06_ph_conv = (number)1 / this->sr;
            }
            
            void phasor_06_dspsetup(bool force) {
                if ((bool)(this->phasor_06_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->phasor_06_conv = (number)1 / this->samplerate();
                this->phasor_06_setupDone = true;
                this->phasor_06_ph_dspsetup();
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
            
            void message_06_init() {
                this->message_06_set_set({1});
            }
            
            void adsr_04_dspsetup(bool force) {
                if ((bool)(this->adsr_04_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_04_mspersamp = (number)1000 / this->sr;
                this->adsr_04_setupDone = true;
            }
            
            void toggle_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->toggle_02_value_number;
            }
            
            void toggle_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->toggle_02_value_number_set(preset["value"]);
            }
            
            void metro_04_onTransportChanged(number ) {}
            
            void metro_04_onBeatTimeChanged(number ) {}
            
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
                receive_20_output_number = 0;
                phasor_06_freq = 0;
                expr_22_in1 = 0;
                expr_22_in2 = 16;
                expr_22_out1 = 0;
                dspexpr_05_in1 = 0;
                dspexpr_05_in2 = 0;
                gaintilde_11_input_number = 0;
                gaintilde_11_value = 0;
                gaintilde_11_interp = 10;
                expr_23_in1 = 0;
                expr_23_in2 = 10;
                expr_23_out1 = 0;
                receive_21_output_number = 0;
                adsr_04_trigger_number = 0;
                adsr_04_attack = 1000;
                adsr_04_decay = 3000;
                adsr_04_sustain = 0;
                adsr_04_release = 0;
                adsr_04_legato = 0;
                toggle_02_value_number = 0;
                toggle_02_value_number_setter(toggle_02_value_number);
                metro_04_on = 0;
                metro_04_interval = 6000;
                metro_04_interval_setter(metro_04_interval);
                receive_22_output_number = 0;
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
                phasor_06_sigbuf = nullptr;
                phasor_06_lastLockedPhase = 0;
                phasor_06_conv = 0;
                phasor_06_ph_currentPhase = 0;
                phasor_06_ph_conv = 0;
                phasor_06_setupDone = false;
                gaintilde_11_lastValue = 0;
                gaintilde_11_loginc = 1;
                gaintilde_11_zval = 0;
                gaintilde_11_ramp_d_prev = 0;
                gaintilde_11_ramp_prev = 0;
                gaintilde_11_ramp_index = 0;
                gaintilde_11_ramp_increment = 0;
                gaintilde_11_setupDone = false;
                adsr_04_phase = 3;
                adsr_04_mspersamp = 0;
                adsr_04_time = 0;
                adsr_04_lastTriggerVal = 0;
                adsr_04_amplitude = 0;
                adsr_04_outval = 0;
                adsr_04_startingpoint = 0;
                adsr_04_triggerBuf = nullptr;
                adsr_04_triggerValueBuf = nullptr;
                adsr_04_setupDone = false;
                toggle_02_lastValue = 0;
                metro_04_last = -1;
                metro_04_next = -1;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number receive_20_output_number;
                list receive_20_output_list;
                number phasor_06_freq;
                number expr_22_in1;
                number expr_22_in2;
                number expr_22_out1;
                number dspexpr_05_in1;
                number dspexpr_05_in2;
                number gaintilde_11_input_number;
                number gaintilde_11_value;
                number gaintilde_11_interp;
                number expr_23_in1;
                number expr_23_in2;
                number expr_23_out1;
                number receive_21_output_number;
                list receive_21_output_list;
                list message_06_set;
                number adsr_04_trigger_number;
                number adsr_04_attack;
                number adsr_04_decay;
                number adsr_04_sustain;
                number adsr_04_release;
                number adsr_04_legato;
                number toggle_02_value_number;
                number metro_04_on;
                number metro_04_interval;
                number receive_22_output_number;
                list receive_22_output_list;
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
                signal phasor_06_sigbuf;
                number phasor_06_lastLockedPhase;
                number phasor_06_conv;
                number phasor_06_ph_currentPhase;
                number phasor_06_ph_conv;
                bool phasor_06_setupDone;
                number gaintilde_11_lastValue;
                number gaintilde_11_loginc;
                number gaintilde_11_zval;
                number gaintilde_11_ramp_d_prev;
                number gaintilde_11_ramp_prev;
                number gaintilde_11_ramp_index;
                number gaintilde_11_ramp_increment;
                bool gaintilde_11_setupDone;
                Int adsr_04_phase;
                number adsr_04_mspersamp;
                number adsr_04_time;
                number adsr_04_lastTriggerVal;
                number adsr_04_amplitude;
                number adsr_04_outval;
                number adsr_04_startingpoint;
                signal adsr_04_triggerBuf;
                signal adsr_04_triggerValueBuf;
                bool adsr_04_setupDone;
                number toggle_02_lastValue;
                number metro_04_last;
                number metro_04_next;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_244 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_244()
            {
            }
            
            ~RNBOSubpatcher_244()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_02_perform(this->intnum_tilde_02_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_02_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_02_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_02_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_245 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_245()
            {
            }
            
            ~RNBOSubpatcher_245()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
            
            number wrap(number x, number low, number high) {
                number lo;
                number hi;
            
                if (low == high)
                    return low;
            
                if (low > high) {
                    hi = low;
                    lo = high;
                } else {
                    lo = low;
                    hi = high;
                }
            
                number range = hi - lo;
            
                if (x >= lo && x < hi)
                    return x;
            
                if (range <= 0.000000001)
                    return lo;
            
                long numWraps = (long)(trunc((x - lo) / range));
                numWraps = numWraps - ((x < lo ? 1 : 0));
                number result = x - range * numWraps;
            
                if (result >= hi)
                    return result - range;
                else
                    return result;
            }
            
            number samplerate() {
                return this->sr;
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
                this->phasor_07_perform(this->phasor_07_freq, this->signals[0], n);
                this->triangle_tilde_01_perform(this->signals[0], this->triangle_tilde_01_duty, this->signals[1], n);
                this->gaintilde_12_perform(this->signals[1], out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 2; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->phasor_07_sigbuf = resizeSignal(this->phasor_07_sigbuf, this->maxvs, maxBlockSize);
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
            
                this->phasor_07_dspsetup(forceDSPSetup);
                this->gaintilde_12_dspsetup(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
                    if (TAG("constellation[1]/taurus/gain~_obj-7") == objectId)
                        this->gaintilde_12_valin_set(payload);
            
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
                case TAG("constellation[1]/taurus/gain~_obj-7"):
                    {
                    return "constellation[1]/taurus/gain~_obj-7";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                }
            
                return nullptr;
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
            }
            
            protected:
            
            void gaintilde_12_valin_set(number v) {
                this->gaintilde_12_value_set(v);
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
            
            void initializeObjects() {
                this->gaintilde_12_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void phasor_07_freq_set(number v) {
                this->phasor_07_freq = v;
            }
            
            void expr_24_out1_set(number v) {
                this->expr_24_out1 = v;
                this->phasor_07_freq_set(this->expr_24_out1);
            }
            
            void expr_24_in1_set(number in1) {
                this->expr_24_in1 = in1;
            
                this->expr_24_out1_set(
                    (this->expr_24_in2 == 0 ? 0 : (this->expr_24_in2 == 0. ? 0. : this->expr_24_in1 / this->expr_24_in2))
                );//#map:constellation[1]/taurus//_obj-2:1
            }
            
            void receive_23_output_number_set(number v) {
                this->receive_23_output_number = v;
                this->expr_24_in1_set(v);
            }
            
            void gaintilde_12_outval_set(number ) {}
            
            void gaintilde_12_value_set(number v) {
                this->gaintilde_12_value = v;
                number value;
                value = this->scale(v, 0, 157, 0, 158 - 1, 1);
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("constellation[1]/taurus/gain~_obj-7"),
                    v,
                    this->_currentTime
                );
            
                this->gaintilde_12_outval_set(value);
            }
            
            void phasor_07_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_07_ph_next(freq, -1);
                    this->phasor_07_sigbuf[(Index)i] = -1;
                }
            }
            
            void triangle_tilde_01_perform(const Sample * phase, number duty, SampleValue * out1, Index n) {
                RNBO_UNUSED(duty);
                Index i;
            
                for (i = 0; i < n; i++) {
                    number p1 = 0.5;
                    auto wrappedPhase = this->wrap(phase[(Index)i], 0., 1.);
                    p1 = (p1 > 1. ? 1. : (p1 < 0. ? 0. : p1));
            
                    if (wrappedPhase < p1) {
                        out1[(Index)i] = wrappedPhase / p1;
                        continue;
                    } else {
                        out1[(Index)i] = (p1 == 1. ? wrappedPhase : 1. - (wrappedPhase - p1) / (1. - p1));
                        continue;
                    }
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
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
            
            number phasor_07_ph_next(number freq, number reset) {
                RNBO_UNUSED(reset);
                number pincr = freq * this->phasor_07_ph_conv;
            
                if (this->phasor_07_ph_currentPhase < 0.)
                    this->phasor_07_ph_currentPhase = 1. + this->phasor_07_ph_currentPhase;
            
                if (this->phasor_07_ph_currentPhase > 1.)
                    this->phasor_07_ph_currentPhase = this->phasor_07_ph_currentPhase - 1.;
            
                number tmp = this->phasor_07_ph_currentPhase;
                this->phasor_07_ph_currentPhase += pincr;
                return tmp;
            }
            
            void phasor_07_ph_reset() {
                this->phasor_07_ph_currentPhase = 0;
            }
            
            void phasor_07_ph_dspsetup() {
                this->phasor_07_ph_conv = (number)1 / this->sr;
            }
            
            void phasor_07_dspsetup(bool force) {
                if ((bool)(this->phasor_07_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->phasor_07_conv = (number)1 / this->samplerate();
                this->phasor_07_setupDone = true;
                this->phasor_07_ph_dspsetup();
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
                gaintilde_12_input_number = 0;
                gaintilde_12_value = 0;
                gaintilde_12_interp = 10;
                receive_23_output_number = 0;
                triangle_tilde_01_phase = 0;
                triangle_tilde_01_duty = 0.5;
                phasor_07_freq = 0;
                expr_24_in1 = 0;
                expr_24_in2 = 16;
                expr_24_out1 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gaintilde_12_lastValue = 0;
                gaintilde_12_loginc = 1;
                gaintilde_12_zval = 0;
                gaintilde_12_ramp_d_prev = 0;
                gaintilde_12_ramp_prev = 0;
                gaintilde_12_ramp_index = 0;
                gaintilde_12_ramp_increment = 0;
                gaintilde_12_setupDone = false;
                phasor_07_sigbuf = nullptr;
                phasor_07_lastLockedPhase = 0;
                phasor_07_conv = 0;
                phasor_07_ph_currentPhase = 0;
                phasor_07_ph_conv = 0;
                phasor_07_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number gaintilde_12_input_number;
                number gaintilde_12_value;
                number gaintilde_12_interp;
                number receive_23_output_number;
                list receive_23_output_list;
                number triangle_tilde_01_phase;
                number triangle_tilde_01_duty;
                number phasor_07_freq;
                number expr_24_in1;
                number expr_24_in2;
                number expr_24_out1;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[2];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gaintilde_12_lastValue;
                number gaintilde_12_loginc;
                number gaintilde_12_zval;
                number gaintilde_12_ramp_d_prev;
                number gaintilde_12_ramp_prev;
                number gaintilde_12_ramp_index;
                number gaintilde_12_ramp_increment;
                bool gaintilde_12_setupDone;
                signal phasor_07_sigbuf;
                number phasor_07_lastLockedPhase;
                number phasor_07_conv;
                number phasor_07_ph_currentPhase;
                number phasor_07_ph_conv;
                bool phasor_07_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_246 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_246()
            {
            }
            
            ~RNBOSubpatcher_246()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_03_perform(this->intnum_tilde_03_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_03_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_03_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_03_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_247 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_247()
            {
            }
            
            ~RNBOSubpatcher_247()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_04_perform(this->intnum_tilde_04_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_04_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_04_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_04_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_248 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_248()
            {
            }
            
            ~RNBOSubpatcher_248()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_05_perform(this->intnum_tilde_05_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_05_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_05_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_05_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_249 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_249()
            {
            }
            
            ~RNBOSubpatcher_249()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_06_perform(this->intnum_tilde_06_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_06_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_06_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_06_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_250 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_250()
            {
            }
            
            ~RNBOSubpatcher_250()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_07_perform(this->intnum_tilde_07_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_07_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_07_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_07_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_251 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_251()
            {
            }
            
            ~RNBOSubpatcher_251()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_08_perform(this->intnum_tilde_08_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_08_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_08_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_08_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_252 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_252()
            {
            }
            
            ~RNBOSubpatcher_252()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_09_perform(this->intnum_tilde_09_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_09_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_09_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_09_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_253 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_256;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_253()
            {
            }
            
            ~RNBOSubpatcher_253()
            {
            }
            
            virtual RNBOSubpatcher_256* getPatcher() const {
                return static_cast<RNBOSubpatcher_256 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->intnum_tilde_10_perform(this->intnum_tilde_10_value, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
                RNBO_UNUSED(forceDSPSetup);
            
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
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
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
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
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
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
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
            }
            
            protected:
            
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
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void intnum_tilde_10_perform(number value, SampleValue * out1, Index n) {
                RNBO_UNUSED(value);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = trunc(0);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                intnum_tilde_10_value = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number intnum_tilde_10_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_256()
    {
    }
    
    ~RNBOSubpatcher_256()
    {
        delete this->p_02;
        delete this->p_03;
        delete this->p_04;
        delete this->p_05;
        delete this->p_06;
        delete this->p_07;
        delete this->p_08;
        delete this->p_09;
        delete this->p_10;
        delete this->p_11;
        delete this->p_12;
        delete this->p_13;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
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
        this->p_02_perform(this->signals[0], n);
        this->p_03_perform(this->signals[1], n);
        this->p_04_perform(this->signals[2], n);
        this->p_05_perform(this->signals[3], n);
        this->p_06_perform(this->signals[4], n);
        this->p_07_perform(this->signals[5], n);
        this->p_08_perform(this->signals[6], n);
        this->p_09_perform(this->signals[7], n);
        this->p_10_perform(this->signals[8], n);
        this->p_11_perform(this->signals[9], n);
        this->p_12_perform(this->signals[10], n);
        this->p_13_perform(this->signals[11], n);
    
        this->selector_01_perform(
            this->selector_01_onoff,
            this->signals[1],
            this->signals[3],
            this->signals[5],
            this->signals[7],
            this->signals[9],
            this->signals[11],
            this->signals[0],
            this->signals[2],
            this->signals[4],
            this->signals[6],
            this->signals[8],
            this->signals[10],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 12; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
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
    
        RNBO_UNUSED(forceDSPSetup);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_08->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_09->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_10->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_11->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_12->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_13->prepareToProcess(sampleRate, maxBlockSize, force);
    
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
    
    void setState() {
        this->p_02 = new RNBOSubpatcher_242();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_243();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
        this->p_04 = new RNBOSubpatcher_244();
        this->p_04->setEngineAndPatcher(this->getEngine(), this);
        this->p_04->initialize();
        this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
        this->p_05 = new RNBOSubpatcher_245();
        this->p_05->setEngineAndPatcher(this->getEngine(), this);
        this->p_05->initialize();
        this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
        this->p_06 = new RNBOSubpatcher_246();
        this->p_06->setEngineAndPatcher(this->getEngine(), this);
        this->p_06->initialize();
        this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
        this->p_07 = new RNBOSubpatcher_247();
        this->p_07->setEngineAndPatcher(this->getEngine(), this);
        this->p_07->initialize();
        this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
        this->p_08 = new RNBOSubpatcher_248();
        this->p_08->setEngineAndPatcher(this->getEngine(), this);
        this->p_08->initialize();
        this->p_08->setParameterOffset(this->getParameterOffset(this->p_08));
        this->p_09 = new RNBOSubpatcher_249();
        this->p_09->setEngineAndPatcher(this->getEngine(), this);
        this->p_09->initialize();
        this->p_09->setParameterOffset(this->getParameterOffset(this->p_09));
        this->p_10 = new RNBOSubpatcher_250();
        this->p_10->setEngineAndPatcher(this->getEngine(), this);
        this->p_10->initialize();
        this->p_10->setParameterOffset(this->getParameterOffset(this->p_10));
        this->p_11 = new RNBOSubpatcher_251();
        this->p_11->setEngineAndPatcher(this->getEngine(), this);
        this->p_11->initialize();
        this->p_11->setParameterOffset(this->getParameterOffset(this->p_11));
        this->p_12 = new RNBOSubpatcher_252();
        this->p_12->setEngineAndPatcher(this->getEngine(), this);
        this->p_12->initialize();
        this->p_12->setParameterOffset(this->getParameterOffset(this->p_12));
        this->p_13 = new RNBOSubpatcher_253();
        this->p_13->setEngineAndPatcher(this->getEngine(), this);
        this->p_13->initialize();
        this->p_13->setParameterOffset(this->getParameterOffset(this->p_13));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "libra"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "aries"));
        this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "scorpio"));
        this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "taurus"));
        this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "sagittarius"));
        this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "gemini"));
        this->p_08->getPreset(getSubState(getSubState(preset, "__sps"), "capricorn"));
        this->p_09->getPreset(getSubState(getSubState(preset, "__sps"), "cancer"));
        this->p_10->getPreset(getSubState(getSubState(preset, "__sps"), "aquarius"));
        this->p_11->getPreset(getSubState(getSubState(preset, "__sps"), "leo"));
        this->p_12->getPreset(getSubState(getSubState(preset, "__sps"), "pisces"));
        this->p_13->getPreset(getSubState(getSubState(preset, "__sps"), "virgo"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
        this->p_04->processTempoEvent(time, tempo);
        this->p_05->processTempoEvent(time, tempo);
        this->p_06->processTempoEvent(time, tempo);
        this->p_07->processTempoEvent(time, tempo);
        this->p_08->processTempoEvent(time, tempo);
        this->p_09->processTempoEvent(time, tempo);
        this->p_10->processTempoEvent(time, tempo);
        this->p_11->processTempoEvent(time, tempo);
        this->p_12->processTempoEvent(time, tempo);
        this->p_13->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
        this->p_04->processTransportEvent(time, state);
        this->p_05->processTransportEvent(time, state);
        this->p_06->processTransportEvent(time, state);
        this->p_07->processTransportEvent(time, state);
        this->p_08->processTransportEvent(time, state);
        this->p_09->processTransportEvent(time, state);
        this->p_10->processTransportEvent(time, state);
        this->p_11->processTransportEvent(time, state);
        this->p_12->processTransportEvent(time, state);
        this->p_13->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
        this->p_04->processBeatTimeEvent(time, beattime);
        this->p_05->processBeatTimeEvent(time, beattime);
        this->p_06->processBeatTimeEvent(time, beattime);
        this->p_07->processBeatTimeEvent(time, beattime);
        this->p_08->processBeatTimeEvent(time, beattime);
        this->p_09->processBeatTimeEvent(time, beattime);
        this->p_10->processBeatTimeEvent(time, beattime);
        this->p_11->processBeatTimeEvent(time, beattime);
        this->p_12->processBeatTimeEvent(time, beattime);
        this->p_13->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
        this->p_04->processTimeSignatureEvent(time, numerator, denominator);
        this->p_05->processTimeSignatureEvent(time, numerator, denominator);
        this->p_06->processTimeSignatureEvent(time, numerator, denominator);
        this->p_07->processTimeSignatureEvent(time, numerator, denominator);
        this->p_08->processTimeSignatureEvent(time, numerator, denominator);
        this->p_09->processTimeSignatureEvent(time, numerator, denominator);
        this->p_10->processTimeSignatureEvent(time, numerator, denominator);
        this->p_11->processTimeSignatureEvent(time, numerator, denominator);
        this->p_12->processTimeSignatureEvent(time, numerator, denominator);
        this->p_13->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        RNBO_UNUSED(v);
        this->updateTime(time);
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                this->p_04->setParameterValue(index, v, time);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                this->p_05->setParameterValue(index, v, time);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                this->p_06->setParameterValue(index, v, time);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                this->p_07->setParameterValue(index, v, time);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                this->p_08->setParameterValue(index, v, time);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                this->p_09->setParameterValue(index, v, time);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                this->p_10->setParameterValue(index, v, time);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                this->p_11->setParameterValue(index, v, time);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                this->p_12->setParameterValue(index, v, time);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                this->p_13->setParameterValue(index, v, time);
    
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
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterValue(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterValue(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterValue(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterValue(index);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterValue(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterValue(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterValue(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterValue(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterValue(index);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterValue(index);
    
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
        return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters() + this->p_10->getNumParameters() + this->p_11->getNumParameters() + this->p_12->getNumParameters() + this->p_13->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterName(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterName(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterName(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterName(index);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterName(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterName(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterName(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterName(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterName(index);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterId(index);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->getParameterId(index);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->getParameterId(index);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->getParameterId(index);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterId(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterId(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterId(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterId(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterId(index);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            default:
                {
                index -= 0;
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                index -= this->p_03->getNumParameters();
    
                if (index < this->p_04->getNumParameters())
                    this->p_04->getParameterInfo(index, info);
    
                index -= this->p_04->getNumParameters();
    
                if (index < this->p_05->getNumParameters())
                    this->p_05->getParameterInfo(index, info);
    
                index -= this->p_05->getNumParameters();
    
                if (index < this->p_06->getNumParameters())
                    this->p_06->getParameterInfo(index, info);
    
                index -= this->p_06->getNumParameters();
    
                if (index < this->p_07->getNumParameters())
                    this->p_07->getParameterInfo(index, info);
    
                index -= this->p_07->getNumParameters();
    
                if (index < this->p_08->getNumParameters())
                    this->p_08->getParameterInfo(index, info);
    
                index -= this->p_08->getNumParameters();
    
                if (index < this->p_09->getNumParameters())
                    this->p_09->getParameterInfo(index, info);
    
                index -= this->p_09->getNumParameters();
    
                if (index < this->p_10->getNumParameters())
                    this->p_10->getParameterInfo(index, info);
    
                index -= this->p_10->getNumParameters();
    
                if (index < this->p_11->getNumParameters())
                    this->p_11->getParameterInfo(index, info);
    
                index -= this->p_11->getNumParameters();
    
                if (index < this->p_12->getNumParameters())
                    this->p_12->getParameterInfo(index, info);
    
                index -= this->p_12->getNumParameters();
    
                if (index < this->p_13->getNumParameters())
                    this->p_13->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_02)
            return 0;
    
        if (subpatcher == this->p_03)
            return 0 + this->p_02->getNumParameters();
    
        if (subpatcher == this->p_04)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    
        if (subpatcher == this->p_05)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();
    
        if (subpatcher == this->p_06)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters();
    
        if (subpatcher == this->p_07)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();
    
        if (subpatcher == this->p_08)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();
    
        if (subpatcher == this->p_09)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters();
    
        if (subpatcher == this->p_10)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters();
    
        if (subpatcher == this->p_11)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters() + this->p_10->getNumParameters();
    
        if (subpatcher == this->p_12)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters() + this->p_10->getNumParameters() + this->p_11->getNumParameters();
    
        if (subpatcher == this->p_13)
            return 0 + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters() + this->p_10->getNumParameters() + this->p_11->getNumParameters() + this->p_12->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->constrainParameterValue(index, value);
    
            index -= this->p_04->getNumParameters();
    
            if (index < this->p_05->getNumParameters())
                return this->p_05->constrainParameterValue(index, value);
    
            index -= this->p_05->getNumParameters();
    
            if (index < this->p_06->getNumParameters())
                return this->p_06->constrainParameterValue(index, value);
    
            index -= this->p_06->getNumParameters();
    
            if (index < this->p_07->getNumParameters())
                return this->p_07->constrainParameterValue(index, value);
    
            index -= this->p_07->getNumParameters();
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->constrainParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->constrainParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->constrainParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->constrainParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->constrainParameterValue(index, value);
    
            index -= this->p_12->getNumParameters();
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
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
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
        this->p_04->processNumMessage(tag, objectId, time, payload);
        this->p_05->processNumMessage(tag, objectId, time, payload);
        this->p_06->processNumMessage(tag, objectId, time, payload);
        this->p_07->processNumMessage(tag, objectId, time, payload);
        this->p_08->processNumMessage(tag, objectId, time, payload);
        this->p_09->processNumMessage(tag, objectId, time, payload);
        this->p_10->processNumMessage(tag, objectId, time, payload);
        this->p_11->processNumMessage(tag, objectId, time, payload);
        this->p_12->processNumMessage(tag, objectId, time, payload);
        this->p_13->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
        this->p_04->processListMessage(tag, objectId, time, payload);
        this->p_05->processListMessage(tag, objectId, time, payload);
        this->p_06->processListMessage(tag, objectId, time, payload);
        this->p_07->processListMessage(tag, objectId, time, payload);
        this->p_08->processListMessage(tag, objectId, time, payload);
        this->p_09->processListMessage(tag, objectId, time, payload);
        this->p_10->processListMessage(tag, objectId, time, payload);
        this->p_11->processListMessage(tag, objectId, time, payload);
        this->p_12->processListMessage(tag, objectId, time, payload);
        this->p_13->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
        this->p_04->processBangMessage(tag, objectId, time);
        this->p_05->processBangMessage(tag, objectId, time);
        this->p_06->processBangMessage(tag, objectId, time);
        this->p_07->processBangMessage(tag, objectId, time);
        this->p_08->processBangMessage(tag, objectId, time);
        this->p_09->processBangMessage(tag, objectId, time);
        this->p_10->processBangMessage(tag, objectId, time);
        this->p_11->processBangMessage(tag, objectId, time);
        this->p_12->processBangMessage(tag, objectId, time);
        this->p_13->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_04->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        auto subpatchResult_3 = this->p_05->resolveTag(tag);
    
        if (subpatchResult_3)
            return subpatchResult_3;
    
        auto subpatchResult_4 = this->p_06->resolveTag(tag);
    
        if (subpatchResult_4)
            return subpatchResult_4;
    
        auto subpatchResult_5 = this->p_07->resolveTag(tag);
    
        if (subpatchResult_5)
            return subpatchResult_5;
    
        auto subpatchResult_6 = this->p_08->resolveTag(tag);
    
        if (subpatchResult_6)
            return subpatchResult_6;
    
        auto subpatchResult_7 = this->p_09->resolveTag(tag);
    
        if (subpatchResult_7)
            return subpatchResult_7;
    
        auto subpatchResult_8 = this->p_10->resolveTag(tag);
    
        if (subpatchResult_8)
            return subpatchResult_8;
    
        auto subpatchResult_9 = this->p_11->resolveTag(tag);
    
        if (subpatchResult_9)
            return subpatchResult_9;
    
        auto subpatchResult_10 = this->p_12->resolveTag(tag);
    
        if (subpatchResult_10)
            return subpatchResult_10;
    
        auto subpatchResult_11 = this->p_13->resolveTag(tag);
    
        if (subpatchResult_11)
            return subpatchResult_11;
    
        return nullptr;
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
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
        this->p_04->processDataViewUpdate(index, time);
        this->p_05->processDataViewUpdate(index, time);
        this->p_06->processDataViewUpdate(index, time);
        this->p_07->processDataViewUpdate(index, time);
        this->p_08->processDataViewUpdate(index, time);
        this->p_09->processDataViewUpdate(index, time);
        this->p_10->processDataViewUpdate(index, time);
        this->p_11->processDataViewUpdate(index, time);
        this->p_12->processDataViewUpdate(index, time);
        this->p_13->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
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
    
    void initializeObjects() {
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
        this->p_04->initializeObjects();
        this->p_05->initializeObjects();
        this->p_06->initializeObjects();
        this->p_07->initializeObjects();
        this->p_08->initializeObjects();
        this->p_09->initializeObjects();
        this->p_10->initializeObjects();
        this->p_11->initializeObjects();
        this->p_12->initializeObjects();
        this->p_13->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_02->startup();
        this->p_03->startup();
        this->p_04->startup();
        this->p_05->startup();
        this->p_06->startup();
        this->p_07->startup();
        this->p_08->startup();
        this->p_09->startup();
        this->p_10->startup();
        this->p_11->startup();
        this->p_12->startup();
        this->p_13->startup();
    }
    
    void allocateDataRefs() {
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->p_04->allocateDataRefs();
        this->p_05->allocateDataRefs();
        this->p_06->allocateDataRefs();
        this->p_07->allocateDataRefs();
        this->p_08->allocateDataRefs();
        this->p_09->allocateDataRefs();
        this->p_10->allocateDataRefs();
        this->p_11->allocateDataRefs();
        this->p_12->allocateDataRefs();
        this->p_13->allocateDataRefs();
    }
    
    void p_03_target_t_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->receive_22_output_number_set(v);
    }
    
    void p_03_target_freq_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->receive_20_output_number_set(v);
    }
    
    void p_05_target_freq_number_set(number v) {
        this->p_05->updateTime(this->_currentTime);
        this->p_05->receive_23_output_number_set(v);
    }
    
    void selector_01_onoff_set(number v) {
        this->selector_01_onoff = v;
    }
    
    void receive_24_output_number_set(number v) {
        this->receive_24_output_number = v;
        this->selector_01_onoff_set(v);
    }
    
    void p_03_target_power_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->receive_21_output_number_set(v);
    }
    
    void p_02_perform(SampleValue * out1, Index n) {
        // subpatcher: libra
        SampleArray<1> outs = {out1};
    
        this->p_02->process(nullptr, 0, outs, 1, n);
    }
    
    void p_03_perform(SampleValue * out1, Index n) {
        // subpatcher: aries
        SampleArray<1> outs = {out1};
    
        this->p_03->process(nullptr, 0, outs, 1, n);
    }
    
    void p_04_perform(SampleValue * out1, Index n) {
        // subpatcher: scorpio
        SampleArray<1> outs = {out1};
    
        this->p_04->process(nullptr, 0, outs, 1, n);
    }
    
    void p_05_perform(SampleValue * out1, Index n) {
        // subpatcher: taurus
        SampleArray<1> outs = {out1};
    
        this->p_05->process(nullptr, 0, outs, 1, n);
    }
    
    void p_06_perform(SampleValue * out1, Index n) {
        // subpatcher: sagittarius
        SampleArray<1> outs = {out1};
    
        this->p_06->process(nullptr, 0, outs, 1, n);
    }
    
    void p_07_perform(SampleValue * out1, Index n) {
        // subpatcher: gemini
        SampleArray<1> outs = {out1};
    
        this->p_07->process(nullptr, 0, outs, 1, n);
    }
    
    void p_08_perform(SampleValue * out1, Index n) {
        // subpatcher: capricorn
        SampleArray<1> outs = {out1};
    
        this->p_08->process(nullptr, 0, outs, 1, n);
    }
    
    void p_09_perform(SampleValue * out1, Index n) {
        // subpatcher: cancer
        SampleArray<1> outs = {out1};
    
        this->p_09->process(nullptr, 0, outs, 1, n);
    }
    
    void p_10_perform(SampleValue * out1, Index n) {
        // subpatcher: aquarius
        SampleArray<1> outs = {out1};
    
        this->p_10->process(nullptr, 0, outs, 1, n);
    }
    
    void p_11_perform(SampleValue * out1, Index n) {
        // subpatcher: leo
        SampleArray<1> outs = {out1};
    
        this->p_11->process(nullptr, 0, outs, 1, n);
    }
    
    void p_12_perform(SampleValue * out1, Index n) {
        // subpatcher: pisces
        SampleArray<1> outs = {out1};
    
        this->p_12->process(nullptr, 0, outs, 1, n);
    }
    
    void p_13_perform(SampleValue * out1, Index n) {
        // subpatcher: virgo
        SampleArray<1> outs = {out1};
    
        this->p_13->process(nullptr, 0, outs, 1, n);
    }
    
    void selector_01_perform(
        number onoff,
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
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else if (onoff >= 3 && onoff < 4)
                out[(Index)i] = in3[(Index)i];
            else if (onoff >= 4 && onoff < 5)
                out[(Index)i] = in4[(Index)i];
            else if (onoff >= 5 && onoff < 6)
                out[(Index)i] = in5[(Index)i];
            else if (onoff >= 6 && onoff < 7)
                out[(Index)i] = in6[(Index)i];
            else if (onoff >= 7 && onoff < 8)
                out[(Index)i] = in7[(Index)i];
            else if (onoff >= 8 && onoff < 9)
                out[(Index)i] = in8[(Index)i];
            else if (onoff >= 9 && onoff < 10)
                out[(Index)i] = in9[(Index)i];
            else if (onoff >= 10 && onoff < 11)
                out[(Index)i] = in10[(Index)i];
            else if (onoff >= 11 && onoff < 12)
                out[(Index)i] = in11[(Index)i];
            else if (onoff >= 12 && onoff < 13)
                out[(Index)i] = in12[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
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
        p_02_target = 0;
        p_03_target = 0;
        p_04_target = 0;
        p_05_target = 0;
        receive_24_output_number = 0;
        p_06_target = 0;
        p_07_target = 0;
        selector_01_onoff = 1;
        p_08_target = 0;
        p_09_target = 0;
        p_10_target = 0;
        p_11_target = 0;
        p_12_target = 0;
        p_13_target = 0;
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
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number p_02_target;
        number p_03_target;
        number p_04_target;
        number p_05_target;
        number receive_24_output_number;
        list receive_24_output_list;
        number p_06_target;
        number p_07_target;
        number selector_01_onoff;
        number p_08_target;
        number p_09_target;
        number p_10_target;
        number p_11_target;
        number p_12_target;
        number p_13_target;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[12];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_242* p_02;
        RNBOSubpatcher_243* p_03;
        RNBOSubpatcher_244* p_04;
        RNBOSubpatcher_245* p_05;
        RNBOSubpatcher_246* p_06;
        RNBOSubpatcher_247* p_07;
        RNBOSubpatcher_248* p_08;
        RNBOSubpatcher_249* p_09;
        RNBOSubpatcher_250* p_10;
        RNBOSubpatcher_251* p_11;
        RNBOSubpatcher_252* p_12;
        RNBOSubpatcher_253* p_13;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_14;
    delete this->p_15;
    delete this->p_16;
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
    this->p_14_perform(this->signals[0], n);
    this->p_15_perform(this->signals[1], n);
    this->p_16_perform(this->signals[2], n);
    this->signaladder_01_perform(this->signals[2], this->signals[1], this->signals[0], this->signals[0], n);
    this->gaintilde_13_perform(this->signals[0], this->signals[3], n);
    this->limi_03_perform(this->signals[3], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 4; i++) {
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

    this->gaintilde_13_dspsetup(forceDSPSetup);
    this->limi_03_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_14->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_15->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_16->prepareToProcess(sampleRate, maxBlockSize, force);

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
    this->p_14->processDataViewUpdate(index, time);
    this->p_15->processDataViewUpdate(index, time);
    this->p_16->processDataViewUpdate(index, time);
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
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

void setState() {
    this->p_14 = new RNBOSubpatcher_254();
    this->p_14->setEngineAndPatcher(this->getEngine(), this);
    this->p_14->initialize();
    this->p_14->setParameterOffset(this->getParameterOffset(this->p_14));
    this->p_15 = new RNBOSubpatcher_255();
    this->p_15->setEngineAndPatcher(this->getEngine(), this);
    this->p_15->initialize();
    this->p_15->setParameterOffset(this->getParameterOffset(this->p_15));
    this->p_16 = new RNBOSubpatcher_256();
    this->p_16->setEngineAndPatcher(this->getEngine(), this);
    this->p_16->initialize();
    this->p_16->setParameterOffset(this->getParameterOffset(this->p_16));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_02_getPresetValue(getSubState(preset, "t"));
    this->param_03_getPresetValue(getSubState(preset, "adsr"));
    this->param_04_getPresetValue(getSubState(preset, "freq"));
    this->param_05_getPresetValue(getSubState(preset, "constellation"));
    this->param_06_getPresetValue(getSubState(preset, "conversion"));
    this->param_07_getPresetValue(getSubState(preset, "power"));
    this->p_14->getPreset(getSubState(getSubState(preset, "__sps"), "subbass"));
    this->p_15->getPreset(getSubState(getSubState(preset, "__sps"), "sparkles"));
    this->p_16->getPreset(getSubState(getSubState(preset, "__sps"), "constellation[1]"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_02_setPresetValue(getSubState(preset, "t"));
    this->param_03_setPresetValue(getSubState(preset, "adsr"));
    this->param_04_setPresetValue(getSubState(preset, "freq"));
    this->param_05_setPresetValue(getSubState(preset, "constellation"));
    this->param_06_setPresetValue(getSubState(preset, "conversion"));
    this->param_07_setPresetValue(getSubState(preset, "power"));

    this->p_15->p_01->param_01_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(preset, "__sps"), "sparkles"), "__sps"), "bloops"), "t")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_14->processTempoEvent(time, tempo);
        this->p_15->processTempoEvent(time, tempo);
        this->p_16->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_14->processTransportEvent(time, state);
        this->p_15->processTransportEvent(time, state);
        this->p_16->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_14->processBeatTimeEvent(time, beattime);
        this->p_15->processBeatTimeEvent(time, beattime);
        this->p_16->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_14->processTimeSignatureEvent(time, numerator, denominator);
        this->p_15->processTimeSignatureEvent(time, numerator, denominator);
        this->p_16->processTimeSignatureEvent(time, numerator, denominator);
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_02_value_set(v);
        break;
        }
    case 1:
        {
        this->param_03_value_set(v);
        break;
        }
    case 2:
        {
        this->param_04_value_set(v);
        break;
        }
    case 3:
        {
        this->param_05_value_set(v);
        break;
        }
    case 4:
        {
        this->param_06_value_set(v);
        break;
        }
    case 5:
        {
        this->param_07_value_set(v);
        break;
        }
    default:
        {
        index -= 6;

        if (index < this->p_14->getNumParameters())
            this->p_14->setParameterValue(index, v, time);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            this->p_15->setParameterValue(index, v, time);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            this->p_16->setParameterValue(index, v, time);

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
        return this->param_02_value;
        }
    case 1:
        {
        return this->param_03_value;
        }
    case 2:
        {
        return this->param_04_value;
        }
    case 3:
        {
        return this->param_05_value;
        }
    case 4:
        {
        return this->param_06_value;
        }
    case 5:
        {
        return this->param_07_value;
        }
    default:
        {
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->getParameterValue(index);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->getParameterValue(index);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterValue(index);

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
    return 6 + this->p_14->getNumParameters() + this->p_15->getNumParameters() + this->p_16->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "t";
        }
    case 1:
        {
        return "adsr";
        }
    case 2:
        {
        return "freq";
        }
    case 3:
        {
        return "constellation";
        }
    case 4:
        {
        return "conversion";
        }
    case 5:
        {
        return "power";
        }
    default:
        {
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->getParameterName(index);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->getParameterName(index);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "t";
        }
    case 1:
        {
        return "adsr";
        }
    case 2:
        {
        return "freq";
        }
    case 3:
        {
        return "constellation";
        }
    case 4:
        {
        return "conversion";
        }
    case 5:
        {
        return "power";
        }
    default:
        {
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->getParameterId(index);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->getParameterId(index);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterId(index);

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
            info->initialValue = 0;
            info->min = 1;
            info->max = 12;
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
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 120;
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
        default:
            {
            index -= 6;

            if (index < this->p_14->getNumParameters())
                this->p_14->getParameterInfo(index, info);

            index -= this->p_14->getNumParameters();

            if (index < this->p_15->getNumParameters())
                this->p_15->getParameterInfo(index, info);

            index -= this->p_15->getNumParameters();

            if (index < this->p_16->getNumParameters())
                this->p_16->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_14)
        return 6;

    if (subpatcher == this->p_15)
        return 6 + this->p_14->getNumParameters();

    if (subpatcher == this->p_16)
        return 6 + this->p_14->getNumParameters() + this->p_15->getNumParameters();

    return 0;
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
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 120 ? 120 : value));
            ParameterValue normalizedValue = (value - 0) / (120 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 1 ? 1 : (value > 12 ? 12 : value));
            ParameterValue normalizedValue = (value - 1) / (12 - 1);
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
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->convertToNormalizedParameterValue(index, value);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->convertToNormalizedParameterValue(index, value);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (120 - 0);
            }
        }
        }
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (12 - 1);
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
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->convertFromNormalizedParameterValue(index, value);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->convertFromNormalizedParameterValue(index, value);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_02_value_constrain(value);
        }
    case 1:
        {
        return this->param_03_value_constrain(value);
        }
    case 2:
        {
        return this->param_04_value_constrain(value);
        }
    case 3:
        {
        return this->param_05_value_constrain(value);
        }
    case 4:
        {
        return this->param_06_value_constrain(value);
        }
    case 5:
        {
        return this->param_07_value_constrain(value);
        }
    default:
        {
        index -= 6;

        if (index < this->p_14->getNumParameters())
            return this->p_14->constrainParameterValue(index, value);

        index -= this->p_14->getNumParameters();

        if (index < this->p_15->getNumParameters())
            return this->p_15->constrainParameterValue(index, value);

        index -= this->p_15->getNumParameters();

        if (index < this->p_16->getNumParameters())
            return this->p_16->constrainParameterValue(index, value);

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
    case TAG("listin"):
        {
        if (TAG("message_obj-26") == objectId)
            this->message_07_listin_number_set(payload);

        break;
        }
    case TAG("valin"):
        {
        if (TAG("gain~_obj-18") == objectId)
            this->gaintilde_13_valin_set(payload);

        break;
        }
    }

    this->p_14->processNumMessage(tag, objectId, time, payload);
    this->p_15->processNumMessage(tag, objectId, time, payload);
    this->p_16->processNumMessage(tag, objectId, time, payload);
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
        if (TAG("message_obj-26") == objectId)
            this->message_07_listin_list_set(payload);

        break;
        }
    }

    this->p_14->processListMessage(tag, objectId, time, payload);
    this->p_15->processListMessage(tag, objectId, time, payload);
    this->p_16->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-26") == objectId)
            this->message_07_listin_bang_bang();

        break;
        }
    }

    this->p_14->processBangMessage(tag, objectId, time);
    this->p_15->processBangMessage(tag, objectId, time);
    this->p_16->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-26"):
        {
        return "message_obj-26";
        }
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("gain~_obj-18"):
        {
        return "gain~_obj-18";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    }

    auto subpatchResult_0 = this->p_14->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_15->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    auto subpatchResult_2 = this->p_16->resolveTag(tag);

    if (subpatchResult_2)
        return subpatchResult_2;

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

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(0, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->send_02_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(1, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->send_03_input_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(2, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->send_04_input_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(3, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->send_05_input_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(4, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->send_06_input_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(5, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->send_07_input_number_set(v);
}

void message_07_listin_list_set(const list& v) {
    this->message_07_set_set(v);
}

void message_07_listin_number_set(number v) {
    this->message_07_set_set(v);
}

void message_07_listin_bang_bang() {
    this->message_07_trigger_bang();
}

void gaintilde_13_valin_set(number v) {
    this->gaintilde_13_value_set(v);
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
    this->p_14->allocateDataRefs();
    this->p_15->allocateDataRefs();
    this->p_16->allocateDataRefs();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->message_07_init();
    this->gaintilde_13_init();
    this->p_14->initializeObjects();
    this->p_15->initializeObjects();
    this->p_16->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_14->startup();
    this->p_15->startup();
    this->p_16->startup();

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

    this->processParamInitEvents();
}

static number param_02_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gaintilde_13_outval_set(number ) {}

void gaintilde_13_value_set(number v) {
    this->gaintilde_13_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-18"), v, this->_currentTime);
    this->gaintilde_13_outval_set(value);
}

void gaintilde_13_input_number_set(number v) {
    this->gaintilde_13_input_number = v;

    this->gaintilde_13_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void message_07_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gaintilde_13_input_number_set(converted);
    }
}

void message_07_trigger_bang() {
    this->message_07_out_set(this->message_07_set);
}

void receive_25_output_number_set(number v) {
    this->receive_25_output_number = v;
    this->message_07_trigger_bang();
}

void p_14_target_t_number_set(number v) {
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_03_output_number_set(v);
}

void p_16_target_t_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->p_03_target_t_number_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_25_output_number_set(v);
    this->p_14_target_t_number_set(v);
    this->p_16_target_t_number_set(v);
}

static number param_03_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_14_target_adsr_number_set(number v) {
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_05_output_number_set(v);
}

void send_03_input_number_set(number v) {
    this->send_03_input_number = v;
    this->p_14_target_adsr_number_set(v);
}

static number param_04_value_constrain(number v) {
    v = (v > 2093 ? 2093 : (v < 32.703 ? 32.703 : v));
    return v;
}

void p_14_target_freq_number_set(number v) {
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_02_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_06_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_08_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_10_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_12_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_14_output_number_set(v);
}

void p_15_target_freq_number_set(number v) {
    this->p_15->updateTime(this->_currentTime);
    this->p_15->p_01_target_freq_number_set(v);
}

void p_16_target_freq_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->p_03_target_freq_number_set(v);
    this->p_16->updateTime(this->_currentTime);
    this->p_16->p_05_target_freq_number_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->p_14_target_freq_number_set(v);
    this->p_15_target_freq_number_set(v);
    this->p_16_target_freq_number_set(v);
}

static number param_05_value_constrain(number v) {
    v = (v > 12 ? 12 : (v < 1 ? 1 : v));
    return v;
}

void p_16_target_constellation_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->receive_24_output_number_set(v);
}

void send_05_input_number_set(number v) {
    this->send_05_input_number = v;
    this->p_16_target_constellation_number_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_15_target_conversion_number_set(number v) {
    this->p_15->updateTime(this->_currentTime);
    this->p_15->p_01_target_conversion_number_set(v);
}

void send_06_input_number_set(number v) {
    this->send_06_input_number = v;
    this->p_15_target_conversion_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 120 ? 120 : (v < 0 ? 0 : v));
    return v;
}

void p_14_target_power_number_set(number v) {
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_01_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_04_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_07_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_09_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_11_output_number_set(v);
    this->p_14->updateTime(this->_currentTime);
    this->p_14->receive_13_output_number_set(v);
}

void p_15_target_power_number_set(number v) {
    this->p_15->updateTime(this->_currentTime);
    this->p_15->p_01_target_power_number_set(v);
}

void p_16_target_power_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->p_03_target_power_number_set(v);
}

void send_07_input_number_set(number v) {
    this->send_07_input_number = v;
    this->p_14_target_power_number_set(v);
    this->p_15_target_power_number_set(v);
    this->p_16_target_power_number_set(v);
}

void message_07_set_set(const list& v) {
    this->message_07_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-26"), v, this->_currentTime);
}

void p_15_source_t_number_set(number v) {
    this->receive_25_output_number_set(v);
    this->p_14_target_t_number_set(v);
    this->p_16_target_t_number_set(v);
}

void p_14_perform(SampleValue * out1, Index n) {
    // subpatcher: subbass
    SampleArray<1> outs = {out1};

    this->p_14->process(nullptr, 0, outs, 1, n);
}

void p_15_perform(SampleValue * out1, Index n) {
    // subpatcher: sparkles
    SampleArray<1> outs = {out1};

    this->p_15->process(nullptr, 0, outs, 1, n);
}

void p_16_perform(SampleValue * out1, Index n) {
    // subpatcher: constellation
    SampleArray<1> outs = {out1};

    this->p_16->process(nullptr, 0, outs, 1, n);
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i];
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

void limi_03_perform(const SampleValue * input1, SampleValue * output1, Index n) {
    RNBO_UNUSED(output1);
    RNBO_UNUSED(input1);
    auto __limi_03_lookaheadInv = this->limi_03_lookaheadInv;
    auto __limi_03_threshold = this->limi_03_threshold;
    auto __limi_03_lookahead = this->limi_03_lookahead;
    auto __limi_03_recover = this->limi_03_recover;
    auto __limi_03_last = this->limi_03_last;
    auto __limi_03_postamp = this->limi_03_postamp;
    auto __limi_03_lookaheadIndex = this->limi_03_lookaheadIndex;
    auto __limi_03_preamp = this->limi_03_preamp;
    auto __limi_03_dcblock = this->limi_03_dcblock;
    auto __limi_03_bypass = this->limi_03_bypass;
    ConstSampleArray<1> input = {input1};
    SampleArray<1> output = {output1};

    if ((bool)(__limi_03_bypass)) {
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
                v = ((bool)(__limi_03_dcblock) ? this->limi_03_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                v *= __limi_03_preamp;
                this->limi_03_lookaheadBuffers[(Index)j][__limi_03_lookaheadIndex] = v * __limi_03_postamp;
                v = rnbo_fabs(v);

                if (v > hotSample)
                    hotSample = v;
            }

            {
                if (__limi_03_last > 0.01)
                    v = __limi_03_last + __limi_03_recover * __limi_03_last;
                else
                    v = __limi_03_last + __limi_03_recover;
            }

            if (v > 1)
                v = 1;

            this->limi_03_gainBuffer[__limi_03_lookaheadIndex] = v;
            int lookaheadPlayback = (int)(__limi_03_lookaheadIndex - (int)(__limi_03_lookahead));

            if (lookaheadPlayback < 0)
                lookaheadPlayback += (int)(__limi_03_lookahead);

            if (hotSample * v > __limi_03_threshold) {
                number newgain;
                number curgain = __limi_03_threshold / hotSample;
                number inc = __limi_03_threshold - curgain;
                number acc = 0.0;
                number flag = 0;

                for (Index j = 0; flag == 0 && j < (Index)(__limi_03_lookahead); j++) {
                    int k = (int)(__limi_03_lookaheadIndex - (int)(j));

                    if (k < 0)
                        k += (int)(__limi_03_lookahead);

                    {
                        newgain = curgain + inc * (acc * acc);
                    }

                    if (newgain < this->limi_03_gainBuffer[(Index)k])
                        this->limi_03_gainBuffer[(Index)k] = newgain;
                    else
                        flag = 1;

                    acc = acc + __limi_03_lookaheadInv;
                }
            }

            for (Index j = 0; j < 1; j++) {
                output[(Index)j][(Index)i] = this->limi_03_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_03_gainBuffer[(Index)lookaheadPlayback];
            }

            __limi_03_last = this->limi_03_gainBuffer[__limi_03_lookaheadIndex];
            __limi_03_lookaheadIndex++;

            if (__limi_03_lookaheadIndex >= __limi_03_lookahead)
                __limi_03_lookaheadIndex = 0;
        }
    }

    this->limi_03_lookaheadIndex = __limi_03_lookaheadIndex;
    this->limi_03_last = __limi_03_last;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void limi_03_lookahead_setter(number v) {
    this->limi_03_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
    this->limi_03_lookaheadInv = (number)1 / this->limi_03_lookahead;
}

void limi_03_preamp_setter(number v) {
    this->limi_03_preamp = rnbo_pow(10., v * 0.05);
}

void limi_03_postamp_setter(number v) {
    this->limi_03_postamp = rnbo_pow(10., v * 0.05);
}

void limi_03_threshold_setter(number v) {
    this->limi_03_threshold = rnbo_pow(10., v * 0.05);
}

void message_07_init() {
    this->message_07_set_set({100});
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

number limi_03_dc1_next(number x, number gain) {
    number y = x - this->limi_03_dc1_xm1 + this->limi_03_dc1_ym1 * gain;
    this->limi_03_dc1_xm1 = x;
    this->limi_03_dc1_ym1 = y;
    return y;
}

void limi_03_dc1_reset() {
    this->limi_03_dc1_xm1 = 0;
    this->limi_03_dc1_ym1 = 0;
}

void limi_03_dc1_dspsetup() {
    this->limi_03_dc1_reset();
}

number limi_03_dc_next(Index i, number x, number gain) {
    switch ((int)i) {
    default:
        {
        return this->limi_03_dc1_next(x, gain);
        }
    }

    return 0;
}

void limi_03_dc_reset(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_03_dc1_reset();
        }
    }
}

void limi_03_dc_dspsetup(Index i) {
    switch ((int)i) {
    default:
        {
        return this->limi_03_dc1_dspsetup();
        }
    }
}

void limi_03_reset() {
    this->limi_03_recover = (number)1000 / (this->limi_03_release * this->samplerate());

    {
        this->limi_03_recover *= 0.707;
    }
}

void limi_03_dspsetup(bool force) {
    if ((bool)(this->limi_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->limi_03_reset();
    this->limi_03_setupDone = true;
    this->limi_03_dc1_dspsetup();
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
    receive_25_output_number = 0;
    p_14_target = 0;
    gaintilde_13_input_number = 0;
    gaintilde_13_value = 0;
    gaintilde_13_interp = 10;
    param_02_value = 0;
    p_15_target = 0;
    send_02_input_number = 0;
    send_03_input_number = 0;
    param_03_value = 0;
    limi_03_bypass = 0;
    limi_03_dcblock = 0;
    limi_03_lookahead = 100;
    limi_03_lookahead_setter(limi_03_lookahead);
    limi_03_preamp = 0;
    limi_03_preamp_setter(limi_03_preamp);
    limi_03_postamp = 0;
    limi_03_postamp_setter(limi_03_postamp);
    limi_03_threshold = 0;
    limi_03_threshold_setter(limi_03_threshold);
    limi_03_release = 1000;
    p_16_target = 0;
    send_04_input_number = 0;
    param_04_value = 0;
    send_05_input_number = 0;
    param_05_value = 0;
    send_06_input_number = 0;
    param_06_value = 0;
    send_07_input_number = 0;
    param_07_value = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    gaintilde_13_lastValue = 0;
    gaintilde_13_loginc = 1;
    gaintilde_13_zval = 0;
    gaintilde_13_ramp_d_prev = 0;
    gaintilde_13_ramp_prev = 0;
    gaintilde_13_ramp_index = 0;
    gaintilde_13_ramp_increment = 0;
    gaintilde_13_setupDone = false;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    limi_03_last = 0;
    limi_03_lookaheadIndex = 0;
    limi_03_recover = 0;
    limi_03_lookaheadInv = 0;
    limi_03_dc1_xm1 = 0;
    limi_03_dc1_ym1 = 0;
    limi_03_setupDone = false;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
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

    number receive_25_output_number;
    list receive_25_output_list;
    list message_07_set;
    number p_14_target;
    number gaintilde_13_input_number;
    number gaintilde_13_value;
    number gaintilde_13_interp;
    number param_02_value;
    number p_15_target;
    number send_02_input_number;
    list send_02_input_list;
    number send_03_input_number;
    list send_03_input_list;
    number param_03_value;
    number limi_03_bypass;
    number limi_03_dcblock;
    number limi_03_lookahead;
    number limi_03_preamp;
    number limi_03_postamp;
    number limi_03_threshold;
    number limi_03_release;
    number p_16_target;
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
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[4];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number gaintilde_13_lastValue;
    number gaintilde_13_loginc;
    number gaintilde_13_zval;
    number gaintilde_13_ramp_d_prev;
    number gaintilde_13_ramp_prev;
    number gaintilde_13_ramp_index;
    number gaintilde_13_ramp_increment;
    bool gaintilde_13_setupDone;
    number param_02_lastValue;
    number param_03_lastValue;
    SampleValue limi_03_lookaheadBuffers[1][512] = { };
    SampleValue limi_03_gainBuffer[512] = { };
    number limi_03_last;
    int limi_03_lookaheadIndex;
    number limi_03_recover;
    number limi_03_lookaheadInv;
    number limi_03_dc1_xm1;
    number limi_03_dc1_ym1;
    bool limi_03_setupDone;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
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
    RNBOSubpatcher_254* p_14;
    RNBOSubpatcher_255* p_15;
    RNBOSubpatcher_256* p_16;

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

