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

class RNBOSubpatcher_2066 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_2066()
    {
    }
    
    ~RNBOSubpatcher_2066()
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
        getEngine()->flushClockEvents(this, 1935387534, false);
    }
    
    MillisecondTime currenttime() {
        return this->_currentTime;
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
        RNBO_UNUSED(numOutputs);
        RNBO_UNUSED(outputs);
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
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
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->metro_01_onTransportChanged(state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->metro_01_onBeatTimeChanged(beattime);
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
            this->metro_01_tick_bang();
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
            if (TAG("arpeggiator/toggle_obj-16") == objectId)
                this->toggle_01_valin_set(payload);
    
            if (TAG("arpeggiator/number_obj-97") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("arpeggiator/number_obj-21") == objectId)
                this->numberobj_02_valin_set(payload);
    
            if (TAG("arpeggiator/number_obj-64") == objectId)
                this->numberobj_03_valin_set(payload);
    
            if (TAG("arpeggiator/number_obj-12") == objectId)
                this->numberobj_04_valin_set(payload);
    
            if (TAG("arpeggiator/dial_obj-121") == objectId)
                this->dial_01_valin_set(payload);
    
            if (TAG("arpeggiator/number_obj-123") == objectId)
                this->numberobj_05_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("arpeggiator/number_obj-97") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("arpeggiator/number_obj-21") == objectId)
                this->numberobj_02_format_set(payload);
    
            if (TAG("arpeggiator/number_obj-64") == objectId)
                this->numberobj_03_format_set(payload);
    
            if (TAG("arpeggiator/number_obj-12") == objectId)
                this->numberobj_04_format_set(payload);
    
            if (TAG("arpeggiator/number_obj-123") == objectId)
                this->numberobj_05_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("arpeggiator/button_obj-102") == objectId)
                this->button_01_bangin_bang();
    
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
        case TAG("arpeggiator/toggle_obj-16"):
            {
            return "arpeggiator/toggle_obj-16";
            }
        case TAG("arpeggiator/number_obj-97"):
            {
            return "arpeggiator/number_obj-97";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("arpeggiator/number_obj-21"):
            {
            return "arpeggiator/number_obj-21";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("arpeggiator/button_obj-102"):
            {
            return "arpeggiator/button_obj-102";
            }
        case TAG("arpeggiator/number_obj-64"):
            {
            return "arpeggiator/number_obj-64";
            }
        case TAG("arpeggiator/number_obj-12"):
            {
            return "arpeggiator/number_obj-12";
            }
        case TAG("arpeggiator/dial_obj-121"):
            {
            return "arpeggiator/dial_obj-121";
            }
        case TAG("arpeggiator/number_obj-123"):
            {
            return "arpeggiator/number_obj-123";
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
    
    void toggle_01_valin_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void eventinlet_01_out1_bang_bang() {
        this->toggle_01_value_bang_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->toggle_01_value_number_set(converted);
        }
    }
    
    void metro_01_tick_bang() {
        this->metro_01_tickout_bang();
        this->getEngine()->flushClockEvents(this, 1935387534, false);;
    
        if ((bool)(this->metro_01_on)) {
            this->metro_01_last = this->currenttime();
    
            {
                this->metro_01_next = this->metro_01_last + this->metro_01_interval;
                this->getEngine()->scheduleClockEvent(this, 1935387534, this->metro_01_interval + this->_currentTime);;
            }
        }
    }
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void button_01_bangin_bang() {
        this->button_01_bangval_bang();
    }
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->switchobj_02_in1_bang_bang();
        this->numberobj_03_value_bang();
    }
    
    void eventinlet_03_out1_list_set(const list& v) {
        this->switchobj_02_in1_list_set(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_03_value_set(converted);
        }
    }
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->expr_05_in1_bang();
    }
    
    void eventinlet_04_out1_list_set(const list& v) {
        {
            if (v->length > 1)
                this->expr_05_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_05_in1_set(converted);
        }
    }
    
    void dial_01_valin_set(number v) {
        this->dial_01_value_set(v);
    }
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
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
        return 0;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
        this->numberobj_03_init();
        this->numberobj_04_init();
        this->numberobj_05_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
    
        if ((bool)(this->metro_01_on))
            this->metro_01_on_set(1);
    }
    
    void allocateDataRefs() {}
    
    void metro_01_on_set(number v) {
        this->metro_01_on = v;
        this->getEngine()->flushClockEvents(this, 1935387534, false);;
    
        if ((bool)(v)) {
            {
                this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
            }
        }
    }
    
    void toggle_01_output_set(number v) {
        this->metro_01_on_set(v);
    }
    
    void toggle_01_value_number_set(number v) {
        this->toggle_01_value_number_setter(v);
        v = this->toggle_01_value_number;
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("arpeggiator/toggle_obj-16"), v, this->_currentTime);
        this->toggle_01_output_set(v);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void switchobj_02_onoff_set(number v) {
        this->switchobj_02_onoff = v;
    }
    
    void numberobj_04_output_set(number v) {
        this->switchobj_02_onoff_set(v);
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
            TAG("arpeggiator/number_obj-12"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_04_output_set(localvalue);
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->numberobj_04_value_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
        this->expr_05_out1_set(this->expr_05_in1 + this->expr_05_in2);//#map:arpeggiator/+_obj-7:1
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->expr_05_in1_set(v);
    }
    
    void eventoutlet_02_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_16_out2_number_set(v);
    }
    
    void switchobj_02_out_number_set(number v) {
        this->eventoutlet_02_in1_number_set(v);
    }
    
    void switchobj_02_in1_number_set(number v) {
        if (this->switchobj_02_onoff == 1) {
            this->switchobj_02_out_number_set(v);
        }
    }
    
    void switchobj_02_in2_number_set(number v) {
        if (this->switchobj_02_onoff == 2) {
            this->switchobj_02_out_number_set(v);
        }
    }
    
    void switchobj_01_out_number_set(number v) {
        this->switchobj_02_in2_number_set(v);
    }
    
    void switchobj_01_in4_number_set(number v) {
        if (this->switchobj_01_onoff == 4) {
            this->switchobj_01_out_number_set(v);
        }
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->switchobj_01_in4_number_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
    
        this->expr_04_out1_set(
            (this->expr_04_in2 == 0 ? 0 : (this->expr_04_in2 == 0. ? 0. : this->expr_04_in1 / this->expr_04_in2))
        );//#map:arpeggiator//_obj-92:1
    }
    
    void switchobj_01_in3_number_set(number v) {
        if (this->switchobj_01_onoff == 3) {
            this->switchobj_01_out_number_set(v);
        }
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->switchobj_01_in3_number_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(this->expr_03_in1 * this->expr_03_in2);//#map:arpeggiator/*_obj-91:1
    }
    
    void switchobj_01_in2_number_set(number v) {
        if (this->switchobj_01_onoff == 2) {
            this->switchobj_01_out_number_set(v);
        }
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->switchobj_01_in2_number_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:arpeggiator/*_obj-90:1
    }
    
    void switchobj_01_in1_number_set(number v) {
        if (this->switchobj_01_onoff == 1) {
            this->switchobj_01_out_number_set(v);
        }
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->switchobj_01_in1_number_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(this->expr_01_in1 * this->expr_01_in2);//#map:arpeggiator/*_obj-89:1
    }
    
    void numberobj_03_output_set(number v) {
        this->expr_04_in1_set(v);
        this->expr_03_in1_set(v);
        this->expr_02_in1_set(v);
        this->expr_01_in1_set(v);
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
            TAG("arpeggiator/number_obj-64"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void eventinlet_03_out1_number_set(number v) {
        this->switchobj_02_in1_number_set(v);
        this->numberobj_03_value_set(v);
    }
    
    void metro_01_interval_set(number v) {
        this->metro_01_interval_setter(v);
        v = this->metro_01_interval;
    }
    
    void numberobj_02_output_set(number v) {
        this->metro_01_interval_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("arpeggiator/number_obj-21"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void toggle_01_value_bang_bang() {
        number val = (this->toggle_01_value_number == 1 ? 0 : 1);
        this->toggle_01_value_number_set(val);
    }
    
    void eventoutlet_01_in1_bang_bang() {
        ;
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_16_out1_bang_bang();
    }
    
    void button_01_output_bang() {
        this->eventoutlet_01_in1_bang_bang();
    }
    
    void button_01_bangval_bang() {
        this->getEngine()->sendBangMessage(TAG("bangout"), TAG("arpeggiator/button_obj-102"), this->_currentTime);;
        this->button_01_output_bang();
    }
    
    void switchobj_01_onoff_set(number v) {
        this->switchobj_01_onoff = v;
    }
    
    void numberobj_01_output_set(number v) {
        this->switchobj_01_onoff_set(v);
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
            TAG("arpeggiator/number_obj-97"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void counter_01_output_set(number v) {
        this->counter_01_output = v;
        this->numberobj_01_value_set(v);
    }
    
    void counter_01_overflow_bang_bang() {}
    
    static number counter_01_overflow_number_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void counter_01_overflow_number_set(number v) {
        v = this->counter_01_overflow_number_constrain(v);
        this->counter_01_overflow_number = v;
    }
    
    void counter_01_carry_set(number v) {
        this->counter_01_carry = v;
    }
    
    void counter_01_underflow_bang_bang() {}
    
    static number counter_01_underflow_number_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void counter_01_underflow_number_set(number v) {
        v = this->counter_01_underflow_number_constrain(v);
        this->counter_01_underflow_number = v;
    }
    
    void counter_01_input_bang() {
        this->counter_01_output_set(this->counter_01_count);
        this->counter_01_inc();
    
        if (this->counter_01_count > this->counter_01_maximum) {
            if (this->counter_01_direction == 2) {
                this->counter_01_phase = !(bool)(this->counter_01_phase);
                this->counter_01_count = this->counter_01_maximum;
                this->counter_01_inc();
            } else
                this->counter_01_count = this->counter_01_minimum;
    
            if ((bool)(!(bool)(this->counter_01_overflow_number))) {
                if (this->counter_01_carryflag == 1)
                    this->counter_01_overflow_bang_bang();
                else
                    this->counter_01_overflow_number_set(1);
            }
    
            this->counter_01_carry_set(this->counter_01_carry + 1);
        } else if ((bool)(this->counter_01_overflow_number) && this->counter_01_carryflag == 0)
            this->counter_01_overflow_number_set(0);
    
        if (this->counter_01_count < this->counter_01_minimum) {
            if (this->counter_01_direction == 2) {
                this->counter_01_phase = !(bool)(this->counter_01_phase);
                this->counter_01_count = this->counter_01_minimum;
                this->counter_01_inc();
            } else
                this->counter_01_count = this->counter_01_maximum;
    
            if ((bool)(!(bool)(this->counter_01_underflow_number))) {
                if (this->counter_01_carryflag == 1)
                    this->counter_01_underflow_bang_bang();
                else
                    this->counter_01_underflow_number_set(1);
            }
    
            this->counter_01_carry_set(this->counter_01_carry + 1);
        } else if ((bool)(this->counter_01_underflow_number) && this->counter_01_carryflag == 0)
            this->counter_01_underflow_number_set(0);
    }
    
    void metro_01_tickout_bang() {
        this->button_01_bangval_bang();
        this->counter_01_input_bang();
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("arpeggiator/number_obj-21"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventoutlet_02_in1_bang_bang() {
        ;
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_16_out2_bang_bang();
    }
    
    void switchobj_02_out_bang_bang() {
        this->eventoutlet_02_in1_bang_bang();
    }
    
    void switchobj_02_in1_bang_bang() {
        if (this->switchobj_02_onoff == 1) {
            this->switchobj_02_out_bang_bang();
        }
    }
    
    void numberobj_03_value_bang() {
        number v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("arpeggiator/number_obj-64"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void eventoutlet_02_in1_list_set(const list& v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_16_out2_list_set((list)v);
    }
    
    void switchobj_02_out_list_set(const list& v) {
        this->eventoutlet_02_in1_list_set(v);
    }
    
    void switchobj_02_in1_list_set(const list& v) {
        if (this->switchobj_02_onoff == 1) {
            this->switchobj_02_out_list_set(v);
        }
    }
    
    void expr_05_in1_bang() {
        this->expr_05_out1_set(this->expr_05_in1 + this->expr_05_in2);//#map:arpeggiator/+_obj-7:1
    }
    
    void expr_05_in2_set(number v) {
        this->expr_05_in2 = v;
    }
    
    void numberobj_05_output_set(number ) {}
    
    void numberobj_05_value_set(number v) {
        this->numberobj_05_value_setter(v);
        v = this->numberobj_05_value;
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("arpeggiator/number_obj-123"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void eventoutlet_03_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_16_out3_number_set(v);
    }
    
    void dial_01_output_set(number v) {
        this->numberobj_05_value_set(v);
        this->eventoutlet_03_in1_number_set(v);
    }
    
    void dial_01_value_set(number v) {
        this->dial_01_value = v;
        number value;
    
        {
            value = this->scale(v, 0, 128, 0, 0 + 1, 1) * 1;
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("arpeggiator/dial_obj-121"), v, this->_currentTime);
        this->dial_01_output_set(value);
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
    
    void metro_01_interval_setter(number v) {
        this->metro_01_interval = (v > 0 ? v : 0);
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
    
    void toggle_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->toggle_01_value_number;
    }
    
    void toggle_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->toggle_01_value_number_set(preset["value"]);
    }
    
    void counter_01_inc() {
        this->counter_01_count = ((bool)(this->counter_01_phase) ? this->counter_01_count + 1 : this->counter_01_count - 1);
    }
    
    void metro_01_onTransportChanged(number ) {}
    
    void metro_01_onBeatTimeChanged(number ) {}
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("arpeggiator/number_obj-97"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("arpeggiator/number_obj-21"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("arpeggiator/number_obj-64"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("arpeggiator/number_obj-12"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void dial_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->dial_01_value;
    }
    
    void dial_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->dial_01_value_set(preset["value"]);
    }
    
    void numberobj_05_init() {
        this->numberobj_05_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("arpeggiator/number_obj-123"), 1, this->_currentTime);
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
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
        toggle_01_value_number = 0;
        toggle_01_value_number_setter(toggle_01_value_number);
        counter_01_carryflag = 0;
        counter_01_direction = 0;
        counter_01_resetnext_number = 0;
        counter_01_resetnow_number = 0;
        counter_01_maximum = 4;
        counter_01_output = 0;
        counter_01_underflow_number = 0;
        counter_01_overflow_number = 0;
        counter_01_carry = 0;
        counter_01_minimum = 1;
        metro_01_on = 0;
        metro_01_interval = 200;
        metro_01_interval_setter(metro_01_interval);
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        expr_01_in1 = 0;
        expr_01_in2 = 1.25;
        expr_01_out1 = 0;
        expr_02_in1 = 0;
        expr_02_in2 = 1.5;
        expr_02_out1 = 0;
        switchobj_01_onoff = 0;
        expr_03_in1 = 0;
        expr_03_in2 = 2;
        expr_03_out1 = 0;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        expr_04_in1 = 0;
        expr_04_in2 = 2;
        expr_04_out1 = 0;
        switchobj_02_onoff = 0;
        expr_05_in1 = 0;
        expr_05_in2 = 1;
        expr_05_out1 = 0;
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        dial_01_value = 0;
        numberobj_05_value = 0;
        numberobj_05_value_setter(numberobj_05_value);
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
        toggle_01_lastValue = 0;
        counter_01_count = 1;
        counter_01_phase = true;
        metro_01_last = -1;
        metro_01_next = -1;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        dial_01_lastValue = 0;
        numberobj_05_currentFormat = 6;
        numberobj_05_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number toggle_01_value_number;
        Int counter_01_carryflag;
        number counter_01_direction;
        number counter_01_resetnext_number;
        number counter_01_resetnow_number;
        number counter_01_maximum;
        number counter_01_output;
        number counter_01_underflow_number;
        number counter_01_overflow_number;
        number counter_01_carry;
        number counter_01_minimum;
        number metro_01_on;
        number metro_01_interval;
        number numberobj_01_value;
        number numberobj_02_value;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number expr_02_in1;
        number expr_02_in2;
        number expr_02_out1;
        number switchobj_01_onoff;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number numberobj_03_value;
        number expr_04_in1;
        number expr_04_in2;
        number expr_04_out1;
        number switchobj_02_onoff;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        number numberobj_04_value;
        number dial_01_value;
        number numberobj_05_value;
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
        number toggle_01_lastValue;
        number counter_01_count;
        bool counter_01_phase;
        number metro_01_last;
        number metro_01_next;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        number dial_01_lastValue;
        Int numberobj_05_currentFormat;
        number numberobj_05_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_2067 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_2060 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2067;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_2051 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2060;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2051()
                        {
                        }
                        
                        ~RNBOSubpatcher_2051()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2060* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2060 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                        
                            this->cycle_tilde_01_perform(
                                this->cycle_tilde_01_frequency,
                                this->cycle_tilde_01_phase_offset,
                                out1,
                                this->dummyBuffer,
                                n
                            );
                        
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
                        
                            this->cycle_tilde_01_dspsetup(forceDSPSetup);
                        
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
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 0) {
                                this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_01_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
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
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_01_buffer->requestSize(16384, 1);
                            this->cycle_tilde_01_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
                        }
                        
                        void cycle_tilde_01_frequency_set(number v) {
                            this->cycle_tilde_01_frequency = v;
                        }
                        
                        void eventinlet_05_out1_number_set(number v) {
                            this->cycle_tilde_01_frequency_set(v);
                        }
                        
                        void eventinlet_05_out1_bang_bang() {}
                        
                        void cycle_tilde_01_phase_offset_set(number v) {
                            this->cycle_tilde_01_phase_offset = v;
                        }
                        
                        void eventinlet_05_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->cycle_tilde_01_phase_offset_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->cycle_tilde_01_frequency_set(converted);
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            cycle_tilde_01_frequency = 0;
                            cycle_tilde_01_phase_offset = 0;
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
                            cycle_tilde_01_wrap = 0;
                            cycle_tilde_01_ph_currentPhase = 0;
                            cycle_tilde_01_ph_conv = 0;
                            cycle_tilde_01_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number cycle_tilde_01_frequency;
                            number cycle_tilde_01_phase_offset;
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
                            Float64BufferRef cycle_tilde_01_buffer;
                            long cycle_tilde_01_wrap;
                            uint32_t cycle_tilde_01_phasei;
                            SampleValue cycle_tilde_01_f2i;
                            number cycle_tilde_01_ph_currentPhase;
                            number cycle_tilde_01_ph_conv;
                            bool cycle_tilde_01_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2052 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2060;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2052()
                        {
                        }
                        
                        ~RNBOSubpatcher_2052()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2060* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2060 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_01_perform(this->phasor_01_freq, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
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
                        
                            this->phasor_01_dspsetup(forceDSPSetup);
                        
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
                        
                        void phasor_01_freq_set(number v) {
                            this->phasor_01_freq = v;
                        }
                        
                        void eventinlet_06_out1_number_set(number v) {
                            this->phasor_01_freq_set(v);
                        }
                        
                        void eventinlet_06_out1_bang_bang() {}
                        
                        void phasor_01_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_01_sigbuf)) {
                                this->phasor_01_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_06_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_01_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_01_freq_set(converted);
                            }
                        }
                        
                        void phasor_01_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_01_ph_next(freq, -1);
                                this->phasor_01_sigbuf[(Index)i] = -1;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            phasor_01_freq = 0;
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
                            phasor_01_sigbuf = nullptr;
                            phasor_01_lastLockedPhase = 0;
                            phasor_01_conv = 0;
                            phasor_01_ph_currentPhase = 0;
                            phasor_01_ph_conv = 0;
                            phasor_01_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number phasor_01_freq;
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
                            signal phasor_01_sigbuf;
                            number phasor_01_lastLockedPhase;
                            number phasor_01_conv;
                            number phasor_01_ph_currentPhase;
                            number phasor_01_ph_conv;
                            bool phasor_01_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2053 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2060;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2053()
                        {
                        }
                        
                        ~RNBOSubpatcher_2053()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2060* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2060 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_02_perform(this->phasor_02_freq, this->signals[0], n);
                            this->triangle_tilde_01_perform(this->signals[0], this->triangle_tilde_01_duty, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 1; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->phasor_02_sigbuf = resizeSignal(this->phasor_02_sigbuf, this->maxvs, maxBlockSize);
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
                        
                            this->phasor_02_dspsetup(forceDSPSetup);
                        
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
                        
                        void phasor_02_freq_set(number v) {
                            this->phasor_02_freq = v;
                        }
                        
                        void eventinlet_07_out1_number_set(number v) {
                            this->phasor_02_freq_set(v);
                        }
                        
                        void eventinlet_07_out1_bang_bang() {}
                        
                        void phasor_02_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_02_sigbuf)) {
                                this->phasor_02_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_07_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_02_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_02_freq_set(converted);
                            }
                        }
                        
                        void phasor_02_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_02_ph_next(freq, -1);
                                this->phasor_02_sigbuf[(Index)i] = -1;
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            triangle_tilde_01_phase = 0;
                            triangle_tilde_01_duty = 0.5;
                            phasor_02_freq = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            phasor_02_sigbuf = nullptr;
                            phasor_02_lastLockedPhase = 0;
                            phasor_02_conv = 0;
                            phasor_02_ph_currentPhase = 0;
                            phasor_02_ph_conv = 0;
                            phasor_02_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number triangle_tilde_01_phase;
                            number triangle_tilde_01_duty;
                            number phasor_02_freq;
                            MillisecondTime _currentTime;
                            SampleIndex audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[1];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            signal phasor_02_sigbuf;
                            number phasor_02_lastLockedPhase;
                            number phasor_02_conv;
                            number phasor_02_ph_currentPhase;
                            number phasor_02_ph_conv;
                            bool phasor_02_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_2060()
            {
            }
            
            ~RNBOSubpatcher_2060()
            {
                delete this->p_01;
                delete this->p_02;
                delete this->p_03;
            }
            
            virtual RNBOSubpatcher_2067* getPatcher() const {
                return static_cast<RNBOSubpatcher_2067 *>(_parentPatcher);
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
                this->p_01_perform(this->signals[0], n);
                this->p_02_perform(this->signals[1], n);
                this->p_03_perform(this->signals[2], n);
            
                this->selector_01_perform(
                    this->selector_01_onoff,
                    this->zeroBuffer,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
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
                this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
            
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
                this->p_01 = new RNBOSubpatcher_2051();
                this->p_01->setEngineAndPatcher(this->getEngine(), this);
                this->p_01->initialize();
                this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
                this->p_02 = new RNBOSubpatcher_2052();
                this->p_02->setEngineAndPatcher(this->getEngine(), this);
                this->p_02->initialize();
                this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
                this->p_03 = new RNBOSubpatcher_2053();
                this->p_03->setEngineAndPatcher(this->getEngine(), this);
                this->p_03->initialize();
                this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "sin"));
                this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "phasor"));
                this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "triangle"));
            }
            
            void processTempoEvent(MillisecondTime time, Tempo tempo) {
                this->updateTime(time);
                this->p_01->processTempoEvent(time, tempo);
                this->p_02->processTempoEvent(time, tempo);
                this->p_03->processTempoEvent(time, tempo);
            }
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time);
                this->p_01->processTransportEvent(time, state);
                this->p_02->processTransportEvent(time, state);
                this->p_03->processTransportEvent(time, state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time);
                this->p_01->processBeatTimeEvent(time, beattime);
                this->p_02->processBeatTimeEvent(time, beattime);
                this->p_03->processBeatTimeEvent(time, beattime);
            }
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
                this->updateTime(time);
                this->p_01->processTimeSignatureEvent(time, numerator, denominator);
                this->p_02->processTimeSignatureEvent(time, numerator, denominator);
                this->p_03->processTimeSignatureEvent(time, numerator, denominator);
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        this->p_02->setParameterValue(index, v, time);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        this->p_03->setParameterValue(index, v, time);
            
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterValue(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterValue(index);
            
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
                return 0 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterName(index);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterName(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterName(index);
            
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterId(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterId(index);
            
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
            
                        index -= this->p_01->getNumParameters();
            
                        if (index < this->p_02->getNumParameters())
                            this->p_02->getParameterInfo(index, info);
            
                        index -= this->p_02->getNumParameters();
            
                        if (index < this->p_03->getNumParameters())
                            this->p_03->getParameterInfo(index, info);
            
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
            
                if (subpatcher == this->p_02)
                    return 0 + this->p_01->getNumParameters();
            
                if (subpatcher == this->p_03)
                    return 0 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
            
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->convertToNormalizedParameterValue(index, value);
            
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->convertFromNormalizedParameterValue(index, value);
            
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
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->constrainParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->constrainParameterValue(index, value);
            
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
                this->p_02->processNumMessage(tag, objectId, time, payload);
                this->p_03->processNumMessage(tag, objectId, time, payload);
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
                this->p_02->processListMessage(tag, objectId, time, payload);
                this->p_03->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processBangMessage(tag, objectId, time);
                this->p_02->processBangMessage(tag, objectId, time);
                this->p_03->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                auto subpatchResult_0 = this->p_01->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                auto subpatchResult_1 = this->p_02->resolveTag(tag);
            
                if (subpatchResult_1)
                    return subpatchResult_1;
            
                auto subpatchResult_2 = this->p_03->resolveTag(tag);
            
                if (subpatchResult_2)
                    return subpatchResult_2;
            
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
                this->p_02->processDataViewUpdate(index, time);
                this->p_03->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_09_out1_bang_bang() {
                this->p_03_in2_bang_bang();
                this->p_02_in2_bang_bang();
                this->p_01_in2_bang_bang();
            }
            
            void eventinlet_09_out1_list_set(const list& v) {
                this->p_03_in2_list_set(v);
                this->p_02_in2_list_set(v);
                this->p_01_in2_list_set(v);
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
                this->p_01->initializeObjects();
                this->p_02->initializeObjects();
                this->p_03->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_01->startup();
                this->p_02->startup();
                this->p_03->startup();
            }
            
            void allocateDataRefs() {
                this->p_01->allocateDataRefs();
                this->p_02->allocateDataRefs();
                this->p_03->allocateDataRefs();
            }
            
            void p_03_in2_number_set(number v) {
                this->p_03->updateTime(this->_currentTime);
                this->p_03->eventinlet_07_out1_number_set(v);
            }
            
            void p_02_in2_number_set(number v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_06_out1_number_set(v);
            }
            
            void p_01_in2_number_set(number v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_05_out1_number_set(v);
            }
            
            void eventinlet_09_out1_number_set(number v) {
                this->p_03_in2_number_set(v);
                this->p_02_in2_number_set(v);
                this->p_01_in2_number_set(v);
            }
            
            void selector_01_onoff_set(number v) {
                this->selector_01_onoff = v;
            }
            
            void eventinlet_08_out1_number_set(number v) {
                this->selector_01_onoff_set(v);
            }
            
            void eventinlet_08_out1_bang_bang() {}
            
            void eventinlet_08_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_01_onoff_set(converted);
                }
            }
            
            void p_03_in2_bang_bang() {
                this->p_03->updateTime(this->_currentTime);
                this->p_03->eventinlet_07_out1_bang_bang();
            }
            
            void p_02_in2_bang_bang() {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_06_out1_bang_bang();
            }
            
            void p_01_in2_bang_bang() {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_05_out1_bang_bang();
            }
            
            void p_03_in2_list_set(const list& v) {
                this->p_03->updateTime(this->_currentTime);
                this->p_03->eventinlet_07_out1_list_set(v);
            }
            
            void p_02_in2_list_set(const list& v) {
                this->p_02->updateTime(this->_currentTime);
                this->p_02->eventinlet_06_out1_list_set(v);
            }
            
            void p_01_in2_list_set(const list& v) {
                this->p_01->updateTime(this->_currentTime);
                this->p_01->eventinlet_05_out1_list_set(v);
            }
            
            void p_01_perform(SampleValue * out1, Index n) {
                // subpatcher: sin
                SampleArray<1> outs = {out1};
            
                this->p_01->process(nullptr, 0, outs, 1, n);
            }
            
            void p_02_perform(SampleValue * out1, Index n) {
                // subpatcher: phasor
                SampleArray<1> outs = {out1};
            
                this->p_02->process(nullptr, 0, outs, 1, n);
            }
            
            void p_03_perform(SampleValue * out1, Index n) {
                // subpatcher: triangle
                SampleArray<1> outs = {out1};
            
                this->p_03->process(nullptr, 0, outs, 1, n);
            }
            
            void selector_01_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
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
                selector_01_onoff = 1;
                p_01_target = 0;
                p_02_target = 0;
                p_03_target = 0;
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
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_01_onoff;
                number p_01_target;
                number p_02_target;
                number p_03_target;
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
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_2051* p_01;
                RNBOSubpatcher_2052* p_02;
                RNBOSubpatcher_2053* p_03;
            
    };
    
    class RNBOSubpatcher_2061 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2067;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_2054 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2061;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2054()
                        {
                        }
                        
                        ~RNBOSubpatcher_2054()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2061* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2061 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                        
                            this->cycle_tilde_02_perform(
                                this->cycle_tilde_02_frequency,
                                this->cycle_tilde_02_phase_offset,
                                out1,
                                this->dummyBuffer,
                                n
                            );
                        
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
                        
                            this->cycle_tilde_02_dspsetup(forceDSPSetup);
                        
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
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 0) {
                                this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_02_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
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
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_02_buffer->requestSize(16384, 1);
                            this->cycle_tilde_02_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
                        }
                        
                        void cycle_tilde_02_frequency_set(number v) {
                            this->cycle_tilde_02_frequency = v;
                        }
                        
                        void eventinlet_10_out1_number_set(number v) {
                            this->cycle_tilde_02_frequency_set(v);
                        }
                        
                        void eventinlet_10_out1_bang_bang() {}
                        
                        void cycle_tilde_02_phase_offset_set(number v) {
                            this->cycle_tilde_02_phase_offset = v;
                        }
                        
                        void eventinlet_10_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->cycle_tilde_02_phase_offset_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->cycle_tilde_02_frequency_set(converted);
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            cycle_tilde_02_frequency = 0;
                            cycle_tilde_02_phase_offset = 0;
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
                            cycle_tilde_02_wrap = 0;
                            cycle_tilde_02_ph_currentPhase = 0;
                            cycle_tilde_02_ph_conv = 0;
                            cycle_tilde_02_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number cycle_tilde_02_frequency;
                            number cycle_tilde_02_phase_offset;
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
                            Float64BufferRef cycle_tilde_02_buffer;
                            long cycle_tilde_02_wrap;
                            uint32_t cycle_tilde_02_phasei;
                            SampleValue cycle_tilde_02_f2i;
                            number cycle_tilde_02_ph_currentPhase;
                            number cycle_tilde_02_ph_conv;
                            bool cycle_tilde_02_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2055 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2061;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2055()
                        {
                        }
                        
                        ~RNBOSubpatcher_2055()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2061* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2061 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_03_perform(this->phasor_03_freq, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
                        
                            this->phasor_03_dspsetup(forceDSPSetup);
                        
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
                        
                        void phasor_03_freq_set(number v) {
                            this->phasor_03_freq = v;
                        }
                        
                        void eventinlet_11_out1_number_set(number v) {
                            this->phasor_03_freq_set(v);
                        }
                        
                        void eventinlet_11_out1_bang_bang() {}
                        
                        void phasor_03_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_03_sigbuf)) {
                                this->phasor_03_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_11_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_03_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_03_freq_set(converted);
                            }
                        }
                        
                        void phasor_03_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_03_ph_next(freq, -1);
                                this->phasor_03_sigbuf[(Index)i] = -1;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            phasor_03_freq = 0;
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
                        
                            number phasor_03_freq;
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
                            signal phasor_03_sigbuf;
                            number phasor_03_lastLockedPhase;
                            number phasor_03_conv;
                            number phasor_03_ph_currentPhase;
                            number phasor_03_ph_conv;
                            bool phasor_03_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2056 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2061;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2056()
                        {
                        }
                        
                        ~RNBOSubpatcher_2056()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2061* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2061 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_04_perform(this->phasor_04_freq, this->signals[0], n);
                            this->triangle_tilde_02_perform(this->signals[0], this->triangle_tilde_02_duty, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 1; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->phasor_04_sigbuf = resizeSignal(this->phasor_04_sigbuf, this->maxvs, maxBlockSize);
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
                        
                        void phasor_04_freq_set(number v) {
                            this->phasor_04_freq = v;
                        }
                        
                        void eventinlet_12_out1_number_set(number v) {
                            this->phasor_04_freq_set(v);
                        }
                        
                        void eventinlet_12_out1_bang_bang() {}
                        
                        void phasor_04_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_04_sigbuf)) {
                                this->phasor_04_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_12_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_04_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_04_freq_set(converted);
                            }
                        }
                        
                        void phasor_04_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_04_ph_next(freq, -1);
                                this->phasor_04_sigbuf[(Index)i] = -1;
                            }
                        }
                        
                        void triangle_tilde_02_perform(const Sample * phase, number duty, SampleValue * out1, Index n) {
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            triangle_tilde_02_phase = 0;
                            triangle_tilde_02_duty = 0.5;
                            phasor_04_freq = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            phasor_04_sigbuf = nullptr;
                            phasor_04_lastLockedPhase = 0;
                            phasor_04_conv = 0;
                            phasor_04_ph_currentPhase = 0;
                            phasor_04_ph_conv = 0;
                            phasor_04_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number triangle_tilde_02_phase;
                            number triangle_tilde_02_duty;
                            number phasor_04_freq;
                            MillisecondTime _currentTime;
                            SampleIndex audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[1];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            signal phasor_04_sigbuf;
                            number phasor_04_lastLockedPhase;
                            number phasor_04_conv;
                            number phasor_04_ph_currentPhase;
                            number phasor_04_ph_conv;
                            bool phasor_04_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_2061()
            {
            }
            
            ~RNBOSubpatcher_2061()
            {
                delete this->p_04;
                delete this->p_05;
                delete this->p_06;
            }
            
            virtual RNBOSubpatcher_2067* getPatcher() const {
                return static_cast<RNBOSubpatcher_2067 *>(_parentPatcher);
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
                this->p_04_perform(this->signals[0], n);
                this->p_05_perform(this->signals[1], n);
                this->p_06_perform(this->signals[2], n);
            
                this->selector_02_perform(
                    this->selector_02_onoff,
                    this->zeroBuffer,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
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
                this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
            
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
                this->p_04 = new RNBOSubpatcher_2054();
                this->p_04->setEngineAndPatcher(this->getEngine(), this);
                this->p_04->initialize();
                this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
                this->p_05 = new RNBOSubpatcher_2055();
                this->p_05->setEngineAndPatcher(this->getEngine(), this);
                this->p_05->initialize();
                this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
                this->p_06 = new RNBOSubpatcher_2056();
                this->p_06->setEngineAndPatcher(this->getEngine(), this);
                this->p_06->initialize();
                this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "sin"));
                this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "phasor"));
                this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "triangle"));
            }
            
            void processTempoEvent(MillisecondTime time, Tempo tempo) {
                this->updateTime(time);
                this->p_04->processTempoEvent(time, tempo);
                this->p_05->processTempoEvent(time, tempo);
                this->p_06->processTempoEvent(time, tempo);
            }
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time);
                this->p_04->processTransportEvent(time, state);
                this->p_05->processTransportEvent(time, state);
                this->p_06->processTransportEvent(time, state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time);
                this->p_04->processBeatTimeEvent(time, beattime);
                this->p_05->processBeatTimeEvent(time, beattime);
                this->p_06->processBeatTimeEvent(time, beattime);
            }
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
                this->updateTime(time);
                this->p_04->processTimeSignatureEvent(time, numerator, denominator);
                this->p_05->processTimeSignatureEvent(time, numerator, denominator);
                this->p_06->processTimeSignatureEvent(time, numerator, denominator);
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                RNBO_UNUSED(v);
                this->updateTime(time);
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_04->getNumParameters())
                        this->p_04->setParameterValue(index, v, time);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        this->p_05->setParameterValue(index, v, time);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        this->p_06->setParameterValue(index, v, time);
            
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
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterValue(index);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterValue(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterValue(index);
            
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
                return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterName(index);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterName(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterId(index);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterId(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterId(index);
            
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
            
                        if (index < this->p_04->getNumParameters())
                            this->p_04->getParameterInfo(index, info);
            
                        index -= this->p_04->getNumParameters();
            
                        if (index < this->p_05->getNumParameters())
                            this->p_05->getParameterInfo(index, info);
            
                        index -= this->p_05->getNumParameters();
            
                        if (index < this->p_06->getNumParameters())
                            this->p_06->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_04)
                    return 0;
            
                if (subpatcher == this->p_05)
                    return 0 + this->p_04->getNumParameters();
            
                if (subpatcher == this->p_06)
                    return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters();
            
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
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->convertToNormalizedParameterValue(index, value);
            
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
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->constrainParameterValue(index, value);
            
                    index -= this->p_04->getNumParameters();
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->constrainParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->constrainParameterValue(index, value);
            
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
                this->p_04->processNumMessage(tag, objectId, time, payload);
                this->p_05->processNumMessage(tag, objectId, time, payload);
                this->p_06->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_04->processListMessage(tag, objectId, time, payload);
                this->p_05->processListMessage(tag, objectId, time, payload);
                this->p_06->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_04->processBangMessage(tag, objectId, time);
                this->p_05->processBangMessage(tag, objectId, time);
                this->p_06->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                auto subpatchResult_0 = this->p_04->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                auto subpatchResult_1 = this->p_05->resolveTag(tag);
            
                if (subpatchResult_1)
                    return subpatchResult_1;
            
                auto subpatchResult_2 = this->p_06->resolveTag(tag);
            
                if (subpatchResult_2)
                    return subpatchResult_2;
            
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
                this->p_04->processDataViewUpdate(index, time);
                this->p_05->processDataViewUpdate(index, time);
                this->p_06->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_14_out1_bang_bang() {
                this->p_06_in2_bang_bang();
                this->p_05_in2_bang_bang();
                this->p_04_in2_bang_bang();
            }
            
            void eventinlet_14_out1_list_set(const list& v) {
                this->p_06_in2_list_set(v);
                this->p_05_in2_list_set(v);
                this->p_04_in2_list_set(v);
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
                this->p_04->initializeObjects();
                this->p_05->initializeObjects();
                this->p_06->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_04->startup();
                this->p_05->startup();
                this->p_06->startup();
            }
            
            void allocateDataRefs() {
                this->p_04->allocateDataRefs();
                this->p_05->allocateDataRefs();
                this->p_06->allocateDataRefs();
            }
            
            void p_06_in2_number_set(number v) {
                this->p_06->updateTime(this->_currentTime);
                this->p_06->eventinlet_12_out1_number_set(v);
            }
            
            void p_05_in2_number_set(number v) {
                this->p_05->updateTime(this->_currentTime);
                this->p_05->eventinlet_11_out1_number_set(v);
            }
            
            void p_04_in2_number_set(number v) {
                this->p_04->updateTime(this->_currentTime);
                this->p_04->eventinlet_10_out1_number_set(v);
            }
            
            void eventinlet_14_out1_number_set(number v) {
                this->p_06_in2_number_set(v);
                this->p_05_in2_number_set(v);
                this->p_04_in2_number_set(v);
            }
            
            void selector_02_onoff_set(number v) {
                this->selector_02_onoff = v;
            }
            
            void eventinlet_13_out1_number_set(number v) {
                this->selector_02_onoff_set(v);
            }
            
            void eventinlet_13_out1_bang_bang() {}
            
            void eventinlet_13_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_02_onoff_set(converted);
                }
            }
            
            void p_06_in2_bang_bang() {
                this->p_06->updateTime(this->_currentTime);
                this->p_06->eventinlet_12_out1_bang_bang();
            }
            
            void p_05_in2_bang_bang() {
                this->p_05->updateTime(this->_currentTime);
                this->p_05->eventinlet_11_out1_bang_bang();
            }
            
            void p_04_in2_bang_bang() {
                this->p_04->updateTime(this->_currentTime);
                this->p_04->eventinlet_10_out1_bang_bang();
            }
            
            void p_06_in2_list_set(const list& v) {
                this->p_06->updateTime(this->_currentTime);
                this->p_06->eventinlet_12_out1_list_set(v);
            }
            
            void p_05_in2_list_set(const list& v) {
                this->p_05->updateTime(this->_currentTime);
                this->p_05->eventinlet_11_out1_list_set(v);
            }
            
            void p_04_in2_list_set(const list& v) {
                this->p_04->updateTime(this->_currentTime);
                this->p_04->eventinlet_10_out1_list_set(v);
            }
            
            void p_04_perform(SampleValue * out1, Index n) {
                // subpatcher: sin
                SampleArray<1> outs = {out1};
            
                this->p_04->process(nullptr, 0, outs, 1, n);
            }
            
            void p_05_perform(SampleValue * out1, Index n) {
                // subpatcher: phasor
                SampleArray<1> outs = {out1};
            
                this->p_05->process(nullptr, 0, outs, 1, n);
            }
            
            void p_06_perform(SampleValue * out1, Index n) {
                // subpatcher: triangle
                SampleArray<1> outs = {out1};
            
                this->p_06->process(nullptr, 0, outs, 1, n);
            }
            
            void selector_02_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
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
                selector_02_onoff = 1;
                p_04_target = 0;
                p_05_target = 0;
                p_06_target = 0;
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
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_02_onoff;
                number p_04_target;
                number p_05_target;
                number p_06_target;
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
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_2054* p_04;
                RNBOSubpatcher_2055* p_05;
                RNBOSubpatcher_2056* p_06;
            
    };
    
    class RNBOSubpatcher_2062 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2067;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_2057 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2062;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2057()
                        {
                        }
                        
                        ~RNBOSubpatcher_2057()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2062* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2062 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                        
                            this->cycle_tilde_03_perform(
                                this->cycle_tilde_03_frequency,
                                this->cycle_tilde_03_phase_offset,
                                out1,
                                this->dummyBuffer,
                                n
                            );
                        
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
                        
                            this->cycle_tilde_03_dspsetup(forceDSPSetup);
                        
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
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 0) {
                                this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_03_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
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
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_03_buffer->requestSize(16384, 1);
                            this->cycle_tilde_03_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_03_buffer = this->cycle_tilde_03_buffer->allocateIfNeeded();
                        }
                        
                        void cycle_tilde_03_frequency_set(number v) {
                            this->cycle_tilde_03_frequency = v;
                        }
                        
                        void eventinlet_15_out1_number_set(number v) {
                            this->cycle_tilde_03_frequency_set(v);
                        }
                        
                        void eventinlet_15_out1_bang_bang() {}
                        
                        void cycle_tilde_03_phase_offset_set(number v) {
                            this->cycle_tilde_03_phase_offset = v;
                        }
                        
                        void eventinlet_15_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->cycle_tilde_03_phase_offset_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->cycle_tilde_03_frequency_set(converted);
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            cycle_tilde_03_frequency = 0;
                            cycle_tilde_03_phase_offset = 0;
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
                            cycle_tilde_03_wrap = 0;
                            cycle_tilde_03_ph_currentPhase = 0;
                            cycle_tilde_03_ph_conv = 0;
                            cycle_tilde_03_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number cycle_tilde_03_frequency;
                            number cycle_tilde_03_phase_offset;
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
                            Float64BufferRef cycle_tilde_03_buffer;
                            long cycle_tilde_03_wrap;
                            uint32_t cycle_tilde_03_phasei;
                            SampleValue cycle_tilde_03_f2i;
                            number cycle_tilde_03_ph_currentPhase;
                            number cycle_tilde_03_ph_conv;
                            bool cycle_tilde_03_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2058 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2062;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2058()
                        {
                        }
                        
                        ~RNBOSubpatcher_2058()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2062* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2062 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_05_perform(this->phasor_05_freq, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                this->phasor_05_sigbuf = resizeSignal(this->phasor_05_sigbuf, this->maxvs, maxBlockSize);
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
                        
                            this->phasor_05_dspsetup(forceDSPSetup);
                        
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
                        
                        void phasor_05_freq_set(number v) {
                            this->phasor_05_freq = v;
                        }
                        
                        void eventinlet_16_out1_number_set(number v) {
                            this->phasor_05_freq_set(v);
                        }
                        
                        void eventinlet_16_out1_bang_bang() {}
                        
                        void phasor_05_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_05_sigbuf)) {
                                this->phasor_05_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_16_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_05_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_05_freq_set(converted);
                            }
                        }
                        
                        void phasor_05_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_05_ph_next(freq, -1);
                                this->phasor_05_sigbuf[(Index)i] = -1;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            phasor_05_freq = 0;
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
                            phasor_05_sigbuf = nullptr;
                            phasor_05_lastLockedPhase = 0;
                            phasor_05_conv = 0;
                            phasor_05_ph_currentPhase = 0;
                            phasor_05_ph_conv = 0;
                            phasor_05_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number phasor_05_freq;
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
                            signal phasor_05_sigbuf;
                            number phasor_05_lastLockedPhase;
                            number phasor_05_conv;
                            number phasor_05_ph_currentPhase;
                            number phasor_05_ph_conv;
                            bool phasor_05_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_2059 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_2062;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_2059()
                        {
                        }
                        
                        ~RNBOSubpatcher_2059()
                        {
                        }
                        
                        virtual RNBOSubpatcher_2062* getPatcher() const {
                            return static_cast<RNBOSubpatcher_2062 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
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
                            this->phasor_06_perform(this->phasor_06_freq, this->signals[0], n);
                            this->triangle_tilde_03_perform(this->signals[0], this->triangle_tilde_03_duty, out1, n);
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 1; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->phasor_06_sigbuf = resizeSignal(this->phasor_06_sigbuf, this->maxvs, maxBlockSize);
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
                        
                        void phasor_06_freq_set(number v) {
                            this->phasor_06_freq = v;
                        }
                        
                        void eventinlet_17_out1_number_set(number v) {
                            this->phasor_06_freq_set(v);
                        }
                        
                        void eventinlet_17_out1_bang_bang() {}
                        
                        void phasor_06_phase_set(number v) {
                            if (v >= 0 && (bool)(this->phasor_06_sigbuf)) {
                                this->phasor_06_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                            }
                        }
                        
                        void eventinlet_17_out1_list_set(const list& v) {
                            {
                                if (v->length > 1)
                                    this->phasor_06_phase_set(v[1]);
                        
                                number converted = (v->length > 0 ? v[0] : 0);
                                this->phasor_06_freq_set(converted);
                            }
                        }
                        
                        void phasor_06_perform(number freq, SampleValue * out, Index n) {
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = this->phasor_06_ph_next(freq, -1);
                                this->phasor_06_sigbuf[(Index)i] = -1;
                            }
                        }
                        
                        void triangle_tilde_03_perform(const Sample * phase, number duty, SampleValue * out1, Index n) {
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
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
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
                            triangle_tilde_03_phase = 0;
                            triangle_tilde_03_duty = 0.5;
                            phasor_06_freq = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
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
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number triangle_tilde_03_phase;
                            number triangle_tilde_03_duty;
                            number phasor_06_freq;
                            MillisecondTime _currentTime;
                            SampleIndex audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[1];
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
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_2062()
            {
            }
            
            ~RNBOSubpatcher_2062()
            {
                delete this->p_07;
                delete this->p_08;
                delete this->p_09;
            }
            
            virtual RNBOSubpatcher_2067* getPatcher() const {
                return static_cast<RNBOSubpatcher_2067 *>(_parentPatcher);
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
                this->p_07_perform(this->signals[0], n);
                this->p_08_perform(this->signals[1], n);
                this->p_09_perform(this->signals[2], n);
            
                this->selector_03_perform(
                    this->selector_03_onoff,
                    this->zeroBuffer,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
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
                this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_08->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_09->prepareToProcess(sampleRate, maxBlockSize, force);
            
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
                this->p_07 = new RNBOSubpatcher_2057();
                this->p_07->setEngineAndPatcher(this->getEngine(), this);
                this->p_07->initialize();
                this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
                this->p_08 = new RNBOSubpatcher_2058();
                this->p_08->setEngineAndPatcher(this->getEngine(), this);
                this->p_08->initialize();
                this->p_08->setParameterOffset(this->getParameterOffset(this->p_08));
                this->p_09 = new RNBOSubpatcher_2059();
                this->p_09->setEngineAndPatcher(this->getEngine(), this);
                this->p_09->initialize();
                this->p_09->setParameterOffset(this->getParameterOffset(this->p_09));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "sin"));
                this->p_08->getPreset(getSubState(getSubState(preset, "__sps"), "phasor"));
                this->p_09->getPreset(getSubState(getSubState(preset, "__sps"), "triangle"));
            }
            
            void processTempoEvent(MillisecondTime time, Tempo tempo) {
                this->updateTime(time);
                this->p_07->processTempoEvent(time, tempo);
                this->p_08->processTempoEvent(time, tempo);
                this->p_09->processTempoEvent(time, tempo);
            }
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time);
                this->p_07->processTransportEvent(time, state);
                this->p_08->processTransportEvent(time, state);
                this->p_09->processTransportEvent(time, state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time);
                this->p_07->processBeatTimeEvent(time, beattime);
                this->p_08->processBeatTimeEvent(time, beattime);
                this->p_09->processBeatTimeEvent(time, beattime);
            }
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
                this->updateTime(time);
                this->p_07->processTimeSignatureEvent(time, numerator, denominator);
                this->p_08->processTimeSignatureEvent(time, numerator, denominator);
                this->p_09->processTimeSignatureEvent(time, numerator, denominator);
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                RNBO_UNUSED(v);
                this->updateTime(time);
            
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_07->getNumParameters())
                        this->p_07->setParameterValue(index, v, time);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        this->p_08->setParameterValue(index, v, time);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        this->p_09->setParameterValue(index, v, time);
            
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
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterValue(index);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->getParameterValue(index);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->getParameterValue(index);
            
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
                return 0 + this->p_07->getNumParameters() + this->p_08->getNumParameters() + this->p_09->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterName(index);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->getParameterName(index);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterId(index);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->getParameterId(index);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->getParameterId(index);
            
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
            
                        if (index < this->p_07->getNumParameters())
                            this->p_07->getParameterInfo(index, info);
            
                        index -= this->p_07->getNumParameters();
            
                        if (index < this->p_08->getNumParameters())
                            this->p_08->getParameterInfo(index, info);
            
                        index -= this->p_08->getNumParameters();
            
                        if (index < this->p_09->getNumParameters())
                            this->p_09->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_07)
                    return 0;
            
                if (subpatcher == this->p_08)
                    return 0 + this->p_07->getNumParameters();
            
                if (subpatcher == this->p_09)
                    return 0 + this->p_07->getNumParameters() + this->p_08->getNumParameters();
            
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
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->convertToNormalizedParameterValue(index, value);
            
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
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    index -= 0;
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->constrainParameterValue(index, value);
            
                    index -= this->p_07->getNumParameters();
            
                    if (index < this->p_08->getNumParameters())
                        return this->p_08->constrainParameterValue(index, value);
            
                    index -= this->p_08->getNumParameters();
            
                    if (index < this->p_09->getNumParameters())
                        return this->p_09->constrainParameterValue(index, value);
            
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
                this->p_07->processNumMessage(tag, objectId, time, payload);
                this->p_08->processNumMessage(tag, objectId, time, payload);
                this->p_09->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_07->processListMessage(tag, objectId, time, payload);
                this->p_08->processListMessage(tag, objectId, time, payload);
                this->p_09->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_07->processBangMessage(tag, objectId, time);
                this->p_08->processBangMessage(tag, objectId, time);
                this->p_09->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                auto subpatchResult_0 = this->p_07->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                auto subpatchResult_1 = this->p_08->resolveTag(tag);
            
                if (subpatchResult_1)
                    return subpatchResult_1;
            
                auto subpatchResult_2 = this->p_09->resolveTag(tag);
            
                if (subpatchResult_2)
                    return subpatchResult_2;
            
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
                this->p_07->processDataViewUpdate(index, time);
                this->p_08->processDataViewUpdate(index, time);
                this->p_09->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_19_out1_bang_bang() {
                this->p_09_in2_bang_bang();
                this->p_08_in2_bang_bang();
                this->p_07_in2_bang_bang();
            }
            
            void eventinlet_19_out1_list_set(const list& v) {
                this->p_09_in2_list_set(v);
                this->p_08_in2_list_set(v);
                this->p_07_in2_list_set(v);
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
                this->p_07->initializeObjects();
                this->p_08->initializeObjects();
                this->p_09->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_07->startup();
                this->p_08->startup();
                this->p_09->startup();
            }
            
            void allocateDataRefs() {
                this->p_07->allocateDataRefs();
                this->p_08->allocateDataRefs();
                this->p_09->allocateDataRefs();
            }
            
            void p_09_in2_number_set(number v) {
                this->p_09->updateTime(this->_currentTime);
                this->p_09->eventinlet_17_out1_number_set(v);
            }
            
            void p_08_in2_number_set(number v) {
                this->p_08->updateTime(this->_currentTime);
                this->p_08->eventinlet_16_out1_number_set(v);
            }
            
            void p_07_in2_number_set(number v) {
                this->p_07->updateTime(this->_currentTime);
                this->p_07->eventinlet_15_out1_number_set(v);
            }
            
            void eventinlet_19_out1_number_set(number v) {
                this->p_09_in2_number_set(v);
                this->p_08_in2_number_set(v);
                this->p_07_in2_number_set(v);
            }
            
            void selector_03_onoff_set(number v) {
                this->selector_03_onoff = v;
            }
            
            void eventinlet_18_out1_number_set(number v) {
                this->selector_03_onoff_set(v);
            }
            
            void eventinlet_18_out1_bang_bang() {}
            
            void eventinlet_18_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->selector_03_onoff_set(converted);
                }
            }
            
            void p_09_in2_bang_bang() {
                this->p_09->updateTime(this->_currentTime);
                this->p_09->eventinlet_17_out1_bang_bang();
            }
            
            void p_08_in2_bang_bang() {
                this->p_08->updateTime(this->_currentTime);
                this->p_08->eventinlet_16_out1_bang_bang();
            }
            
            void p_07_in2_bang_bang() {
                this->p_07->updateTime(this->_currentTime);
                this->p_07->eventinlet_15_out1_bang_bang();
            }
            
            void p_09_in2_list_set(const list& v) {
                this->p_09->updateTime(this->_currentTime);
                this->p_09->eventinlet_17_out1_list_set(v);
            }
            
            void p_08_in2_list_set(const list& v) {
                this->p_08->updateTime(this->_currentTime);
                this->p_08->eventinlet_16_out1_list_set(v);
            }
            
            void p_07_in2_list_set(const list& v) {
                this->p_07->updateTime(this->_currentTime);
                this->p_07->eventinlet_15_out1_list_set(v);
            }
            
            void p_07_perform(SampleValue * out1, Index n) {
                // subpatcher: sin
                SampleArray<1> outs = {out1};
            
                this->p_07->process(nullptr, 0, outs, 1, n);
            }
            
            void p_08_perform(SampleValue * out1, Index n) {
                // subpatcher: phasor
                SampleArray<1> outs = {out1};
            
                this->p_08->process(nullptr, 0, outs, 1, n);
            }
            
            void p_09_perform(SampleValue * out1, Index n) {
                // subpatcher: triangle
                SampleArray<1> outs = {out1};
            
                this->p_09->process(nullptr, 0, outs, 1, n);
            }
            
            void selector_03_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
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
                selector_03_onoff = 1;
                p_07_target = 0;
                p_08_target = 0;
                p_09_target = 0;
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
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_03_onoff;
                number p_07_target;
                number p_08_target;
                number p_09_target;
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
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_2057* p_07;
                RNBOSubpatcher_2058* p_08;
                RNBOSubpatcher_2059* p_09;
            
    };
    
    RNBOSubpatcher_2067()
    {
    }
    
    ~RNBOSubpatcher_2067()
    {
        delete this->p_10;
        delete this->p_11;
        delete this->p_12;
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
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->p_10_perform(this->signals[0], n);
        this->p_11_perform(this->signals[1], n);
        this->p_12_perform(this->signals[2], n);
        this->signaladder_01_perform(in1, this->signals[1], this->signals[2], this->signals[4], n);
        this->dspexpr_02_perform(this->signals[4], this->dspexpr_02_in2, this->signals[3], n);
        this->signaladder_02_perform(in1, this->signals[2], this->signals[6], n);
        this->dspexpr_03_perform(this->signals[6], this->dspexpr_03_in2, this->signals[5], n);
    
        this->signaladder_03_perform(
            in1,
            this->signals[1],
            this->signals[2],
            this->signals[0],
            this->signals[0],
            n
        );
    
        this->dspexpr_01_perform(this->signals[0], this->dspexpr_01_in2, this->signals[7], n);
    
        this->selector_04_perform(
            this->selector_04_onoff,
            in1,
            this->signals[5],
            this->signals[3],
            this->signals[7],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 8; i++) {
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
        this->p_10->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_11->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_12->prepareToProcess(sampleRate, maxBlockSize, force);
    
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
        this->p_10 = new RNBOSubpatcher_2060();
        this->p_10->setEngineAndPatcher(this->getEngine(), this);
        this->p_10->initialize();
        this->p_10->setParameterOffset(this->getParameterOffset(this->p_10));
        this->p_11 = new RNBOSubpatcher_2061();
        this->p_11->setEngineAndPatcher(this->getEngine(), this);
        this->p_11->initialize();
        this->p_11->setParameterOffset(this->getParameterOffset(this->p_11));
        this->p_12 = new RNBOSubpatcher_2062();
        this->p_12->setEngineAndPatcher(this->getEngine(), this);
        this->p_12->initialize();
        this->p_12->setParameterOffset(this->getParameterOffset(this->p_12));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_10->getPreset(getSubState(getSubState(preset, "__sps"), "generator"));
        this->p_11->getPreset(getSubState(getSubState(preset, "__sps"), "generator[1]"));
        this->p_12->getPreset(getSubState(getSubState(preset, "__sps"), "generator[2]"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_10->processTempoEvent(time, tempo);
        this->p_11->processTempoEvent(time, tempo);
        this->p_12->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_10->processTransportEvent(time, state);
        this->p_11->processTransportEvent(time, state);
        this->p_12->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_10->processBeatTimeEvent(time, beattime);
        this->p_11->processBeatTimeEvent(time, beattime);
        this->p_12->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_10->processTimeSignatureEvent(time, numerator, denominator);
        this->p_11->processTimeSignatureEvent(time, numerator, denominator);
        this->p_12->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        RNBO_UNUSED(v);
        this->updateTime(time);
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_10->getNumParameters())
                this->p_10->setParameterValue(index, v, time);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                this->p_11->setParameterValue(index, v, time);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                this->p_12->setParameterValue(index, v, time);
    
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
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterValue(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterValue(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterValue(index);
    
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
        return 0 + this->p_10->getNumParameters() + this->p_11->getNumParameters() + this->p_12->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterName(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterName(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterId(index);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->getParameterId(index);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->getParameterId(index);
    
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
    
                if (index < this->p_10->getNumParameters())
                    this->p_10->getParameterInfo(index, info);
    
                index -= this->p_10->getNumParameters();
    
                if (index < this->p_11->getNumParameters())
                    this->p_11->getParameterInfo(index, info);
    
                index -= this->p_11->getNumParameters();
    
                if (index < this->p_12->getNumParameters())
                    this->p_12->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_10)
            return 0;
    
        if (subpatcher == this->p_11)
            return 0 + this->p_10->getNumParameters();
    
        if (subpatcher == this->p_12)
            return 0 + this->p_10->getNumParameters() + this->p_11->getNumParameters();
    
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
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->convertToNormalizedParameterValue(index, value);
    
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
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->constrainParameterValue(index, value);
    
            index -= this->p_10->getNumParameters();
    
            if (index < this->p_11->getNumParameters())
                return this->p_11->constrainParameterValue(index, value);
    
            index -= this->p_11->getNumParameters();
    
            if (index < this->p_12->getNumParameters())
                return this->p_12->constrainParameterValue(index, value);
    
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
        this->p_10->processNumMessage(tag, objectId, time, payload);
        this->p_11->processNumMessage(tag, objectId, time, payload);
        this->p_12->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_10->processListMessage(tag, objectId, time, payload);
        this->p_11->processListMessage(tag, objectId, time, payload);
        this->p_12->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_10->processBangMessage(tag, objectId, time);
        this->p_11->processBangMessage(tag, objectId, time);
        this->p_12->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_10->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_11->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_12->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
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
        this->p_10->processDataViewUpdate(index, time);
        this->p_11->processDataViewUpdate(index, time);
        this->p_12->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void eventinlet_20_out1_bang_bang() {}
    
    void eventinlet_20_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_04_onoff_set(converted);
        }
    }
    
    void eventinlet_21_out1_bang_bang() {
        this->p_12_in1_bang_bang();
        this->p_11_in1_bang_bang();
        this->p_10_in1_bang_bang();
    }
    
    void eventinlet_21_out1_list_set(const list& v) {
        this->p_12_in1_list_set(v);
        this->p_11_in1_list_set(v);
        this->p_10_in1_list_set(v);
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
    
    void initializeObjects() {
        this->p_10->initializeObjects();
        this->p_11->initializeObjects();
        this->p_12->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_10->startup();
        this->p_11->startup();
        this->p_12->startup();
    }
    
    void allocateDataRefs() {
        this->p_10->allocateDataRefs();
        this->p_11->allocateDataRefs();
        this->p_12->allocateDataRefs();
    }
    
    void p_12_in2_number_set(number v) {
        this->p_12->updateTime(this->_currentTime);
        this->p_12->eventinlet_19_out1_number_set(v);
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->p_12_in2_number_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
        this->expr_08_out1_set(this->expr_08_in1 * this->expr_08_in2);//#map:shields/*_obj-13:1
    }
    
    void p_11_in2_number_set(number v) {
        this->p_11->updateTime(this->_currentTime);
        this->p_11->eventinlet_14_out1_number_set(v);
    }
    
    void expr_07_out1_set(number v) {
        this->expr_07_out1 = v;
        this->p_11_in2_number_set(this->expr_07_out1);
    }
    
    void expr_07_in1_set(number in1) {
        this->expr_07_in1 = in1;
        this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:shields/*_obj-12:1
    }
    
    void p_10_in2_number_set(number v) {
        this->p_10->updateTime(this->_currentTime);
        this->p_10->eventinlet_09_out1_number_set(v);
    }
    
    void expr_06_out1_set(number v) {
        this->expr_06_out1 = v;
        this->p_10_in2_number_set(this->expr_06_out1);
    }
    
    void expr_06_in1_set(number in1) {
        this->expr_06_in1 = in1;
        this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:shields/*_obj-11:1
    }
    
    void receive_01_output_number_set(number v) {
        this->receive_01_output_number = v;
        this->expr_08_in1_set(v);
        this->expr_07_in1_set(v);
        this->expr_06_in1_set(v);
    }
    
    void p_12_in1_number_set(number v) {
        this->p_12->updateTime(this->_currentTime);
        this->p_12->eventinlet_18_out1_number_set(v);
    }
    
    void p_11_in1_number_set(number v) {
        this->p_11->updateTime(this->_currentTime);
        this->p_11->eventinlet_13_out1_number_set(v);
    }
    
    void p_10_in1_number_set(number v) {
        this->p_10->updateTime(this->_currentTime);
        this->p_10->eventinlet_08_out1_number_set(v);
    }
    
    void eventinlet_21_out1_number_set(number v) {
        this->p_12_in1_number_set(v);
        this->p_11_in1_number_set(v);
        this->p_10_in1_number_set(v);
    }
    
    void selector_04_onoff_set(number v) {
        this->selector_04_onoff = v;
    }
    
    void eventinlet_20_out1_number_set(number v) {
        this->selector_04_onoff_set(v);
    }
    
    void expr_08_in1_bang() {
        this->expr_08_out1_set(this->expr_08_in1 * this->expr_08_in2);//#map:shields/*_obj-13:1
    }
    
    void expr_07_in1_bang() {
        this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:shields/*_obj-12:1
    }
    
    void expr_06_in1_bang() {
        this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:shields/*_obj-11:1
    }
    
    void receive_01_output_bang_bang() {
        this->expr_08_in1_bang();
        this->expr_07_in1_bang();
        this->expr_06_in1_bang();
    }
    
    void expr_08_in2_set(number v) {
        this->expr_08_in2 = v;
    }
    
    void expr_07_in2_set(number v) {
        this->expr_07_in2 = v;
    }
    
    void expr_06_in2_set(number v) {
        this->expr_06_in2 = v;
    }
    
    void receive_01_output_list_set(const list& v) {
        this->receive_01_output_list = jsCreateListCopy(v);
    
        {
            if (v->length > 1)
                this->expr_08_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_08_in1_set(converted);
        }
    
        {
            if (v->length > 1)
                this->expr_07_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_07_in1_set(converted);
        }
    
        {
            if (v->length > 1)
                this->expr_06_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_06_in1_set(converted);
        }
    }
    
    void p_12_in1_bang_bang() {
        this->p_12->updateTime(this->_currentTime);
        this->p_12->eventinlet_18_out1_bang_bang();
    }
    
    void p_11_in1_bang_bang() {
        this->p_11->updateTime(this->_currentTime);
        this->p_11->eventinlet_13_out1_bang_bang();
    }
    
    void p_10_in1_bang_bang() {
        this->p_10->updateTime(this->_currentTime);
        this->p_10->eventinlet_08_out1_bang_bang();
    }
    
    void p_12_in1_list_set(const list& v) {
        this->p_12->updateTime(this->_currentTime);
        this->p_12->eventinlet_18_out1_list_set(v);
    }
    
    void p_11_in1_list_set(const list& v) {
        this->p_11->updateTime(this->_currentTime);
        this->p_11->eventinlet_13_out1_list_set(v);
    }
    
    void p_10_in1_list_set(const list& v) {
        this->p_10->updateTime(this->_currentTime);
        this->p_10->eventinlet_08_out1_list_set(v);
    }
    
    void p_10_perform(SampleValue * out1, Index n) {
        // subpatcher: generator
        SampleArray<1> outs = {out1};
    
        this->p_10->process(nullptr, 0, outs, 1, n);
    }
    
    void p_11_perform(SampleValue * out1, Index n) {
        // subpatcher: generator
        SampleArray<1> outs = {out1};
    
        this->p_11->process(nullptr, 0, outs, 1, n);
    }
    
    void p_12_perform(SampleValue * out1, Index n) {
        // subpatcher: generator
        SampleArray<1> outs = {out1};
    
        this->p_12->process(nullptr, 0, outs, 1, n);
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
    
    void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] / (number)2;//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_02_perform(
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
    
    void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] / (number)2;//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i] + in4[(Index)i];
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] / (number)2;//#map:_###_obj_###_:1
        }
    }
    
    void selector_04_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
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
        selector_04_onoff = 1;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 2;
        p_10_target = 0;
        receive_01_output_number = 0;
        expr_06_in1 = 0;
        expr_06_in2 = 1.25;
        expr_06_out1 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 2;
        p_11_target = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 1.5;
        expr_07_out1 = 0;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 2;
        expr_08_in1 = 0;
        expr_08_in2 = 2;
        expr_08_out1 = 0;
        p_12_target = 0;
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
    
        number selector_04_onoff;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number p_10_target;
        number receive_01_output_number;
        list receive_01_output_list;
        number expr_06_in1;
        number expr_06_in2;
        number expr_06_out1;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number p_11_target;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number p_12_target;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[8];
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
        RNBOSubpatcher_2060* p_10;
        RNBOSubpatcher_2061* p_11;
        RNBOSubpatcher_2062* p_12;
    
};

class RNBOSubpatcher_2068 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_2068()
    {
    }
    
    ~RNBOSubpatcher_2068()
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
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    
        this->saw_tilde_01_perform(
            this->saw_tilde_01_frequency,
            this->saw_tilde_01_syncPhase,
            this->signals[0],
            this->dummyBuffer,
            n
        );
    
        this->dspexpr_04_perform(in1, this->signals[0], this->signals[1], n);
        this->selector_05_perform(this->selector_05_onoff, in1, this->signals[1], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
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
    
        this->saw_tilde_01_dspsetup(forceDSPSetup);
    
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
            if (TAG("thruster/number_obj-20") == objectId)
                this->numberobj_06_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("thruster/number_obj-20") == objectId)
                this->numberobj_06_format_set(payload);
    
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
        case TAG("thruster/number_obj-20"):
            {
            return "thruster/number_obj-20";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
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
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_22_out1_bang_bang() {
        this->numberobj_06_value_bang();
    }
    
    void eventinlet_22_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_06_value_set(converted);
        }
    }
    
    void eventinlet_23_out1_bang_bang() {}
    
    void eventinlet_23_out1_list_set(const list& v) {
        {
            if (v->length > 1)
                this->saw_tilde_01_syncPhase_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->saw_tilde_01_frequency_set(converted);
        }
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
    
    void initializeObjects() {
        this->numberobj_06_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void selector_05_onoff_set(number v) {
        this->selector_05_onoff = v;
    }
    
    void expr_09_out1_set(number v) {
        this->expr_09_out1 = v;
        this->selector_05_onoff_set(this->expr_09_out1);
    }
    
    void expr_09_in1_set(number in1) {
        this->expr_09_in1 = in1;
        this->expr_09_out1_set(this->expr_09_in1 + this->expr_09_in2);//#map:thruster/+_obj-2:1
    }
    
    void numberobj_06_output_set(number v) {
        this->expr_09_in1_set(v);
    }
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("thruster/number_obj-20"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void eventinlet_22_out1_number_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void saw_tilde_01_frequency_set(number v) {
        this->saw_tilde_01_frequency = v;
    }
    
    void eventinlet_23_out1_number_set(number v) {
        this->saw_tilde_01_frequency_set(v);
    }
    
    void numberobj_06_value_bang() {
        number v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("thruster/number_obj-20"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void saw_tilde_01_syncPhase_set(number v) {
        this->saw_tilde_01_syncPhase = v;
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
    
    void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void selector_05_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
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
    
    void numberobj_06_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_value = localvalue;
    }
    
    void numberobj_06_init() {
        this->numberobj_06_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("thruster/number_obj-20"), 1, this->_currentTime);
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
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
        selector_05_onoff = 1;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0;
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        expr_09_in1 = 0;
        expr_09_in2 = 1;
        expr_09_out1 = 0;
        saw_tilde_01_frequency = 8;
        saw_tilde_01_syncPhase = 0;
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
        numberobj_06_currentFormat = 6;
        numberobj_06_lastValue = 0;
        saw_tilde_01_t = 0;
        saw_tilde_01_lastSyncPhase = 0;
        saw_tilde_01_lastSyncDiff = 0;
        saw_tilde_01_didSync = false;
        saw_tilde_01_dcblocker_xm1 = 0;
        saw_tilde_01_dcblocker_ym1 = 0;
        saw_tilde_01_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number selector_05_onoff;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number numberobj_06_value;
        number expr_09_in1;
        number expr_09_in2;
        number expr_09_out1;
        number saw_tilde_01_frequency;
        number saw_tilde_01_syncPhase;
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
        Int numberobj_06_currentFormat;
        number numberobj_06_lastValue;
        number saw_tilde_01_t;
        number saw_tilde_01_lastSyncPhase;
        number saw_tilde_01_lastSyncDiff;
        bool saw_tilde_01_didSync;
        number saw_tilde_01_dcblocker_xm1;
        number saw_tilde_01_dcblocker_ym1;
        bool saw_tilde_01_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_2069 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_2063 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2069;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2063()
            {
            }
            
            ~RNBOSubpatcher_2063()
            {
            }
            
            virtual RNBOSubpatcher_2069* getPatcher() const {
                return static_cast<RNBOSubpatcher_2069 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
            
                this->cycle_tilde_04_perform(
                    this->cycle_tilde_04_frequency,
                    this->cycle_tilde_04_phase_offset,
                    out1,
                    this->dummyBuffer,
                    n
                );
            
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
            
                this->cycle_tilde_04_dspsetup(forceDSPSetup);
            
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
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->cycle_tilde_04_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                    this->cycle_tilde_04_bufferUpdated();
                }
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->cycle_tilde_04_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
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
            
            void allocateDataRefs() {
                this->cycle_tilde_04_buffer->requestSize(16384, 1);
                this->cycle_tilde_04_buffer->setSampleRate(this->sr);
                this->cycle_tilde_04_buffer = this->cycle_tilde_04_buffer->allocateIfNeeded();
            }
            
            void cycle_tilde_04_frequency_set(number v) {
                this->cycle_tilde_04_frequency = v;
            }
            
            void receive_02_output_number_set(number v) {
                this->receive_02_output_number = v;
                this->cycle_tilde_04_frequency_set(v);
            }
            
            void receive_02_output_bang_bang() {}
            
            void cycle_tilde_04_phase_offset_set(number v) {
                this->cycle_tilde_04_phase_offset = v;
            }
            
            void receive_02_output_list_set(const list& v) {
                this->receive_02_output_list = jsCreateListCopy(v);
            
                {
                    if (v->length > 1)
                        this->cycle_tilde_04_phase_offset_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->cycle_tilde_04_frequency_set(converted);
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
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                receive_02_output_number = 0;
                cycle_tilde_04_frequency = 0;
                cycle_tilde_04_phase_offset = 0;
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
                cycle_tilde_04_wrap = 0;
                cycle_tilde_04_ph_currentPhase = 0;
                cycle_tilde_04_ph_conv = 0;
                cycle_tilde_04_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number receive_02_output_number;
                list receive_02_output_list;
                number cycle_tilde_04_frequency;
                number cycle_tilde_04_phase_offset;
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
                Float64BufferRef cycle_tilde_04_buffer;
                long cycle_tilde_04_wrap;
                uint32_t cycle_tilde_04_phasei;
                SampleValue cycle_tilde_04_f2i;
                number cycle_tilde_04_ph_currentPhase;
                number cycle_tilde_04_ph_conv;
                bool cycle_tilde_04_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_2064 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2069;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2064()
            {
            }
            
            ~RNBOSubpatcher_2064()
            {
            }
            
            virtual RNBOSubpatcher_2069* getPatcher() const {
                return static_cast<RNBOSubpatcher_2069 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->phasor_07_perform(this->phasor_07_freq, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
            
            void phasor_07_freq_set(number v) {
                this->phasor_07_freq = v;
            }
            
            void receive_03_output_number_set(number v) {
                this->receive_03_output_number = v;
                this->phasor_07_freq_set(v);
            }
            
            void receive_03_output_bang_bang() {}
            
            void phasor_07_phase_set(number v) {
                if (v >= 0 && (bool)(this->phasor_07_sigbuf)) {
                    this->phasor_07_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                }
            }
            
            void receive_03_output_list_set(const list& v) {
                this->receive_03_output_list = jsCreateListCopy(v);
            
                {
                    if (v->length > 1)
                        this->phasor_07_phase_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->phasor_07_freq_set(converted);
                }
            }
            
            void phasor_07_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_07_ph_next(freq, -1);
                    this->phasor_07_sigbuf[(Index)i] = -1;
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
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
                receive_03_output_number = 0;
                phasor_07_freq = 0;
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
            
                number receive_03_output_number;
                list receive_03_output_list;
                number phasor_07_freq;
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
    
    class RNBOSubpatcher_2065 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_2069;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_2065()
            {
            }
            
            ~RNBOSubpatcher_2065()
            {
            }
            
            virtual RNBOSubpatcher_2069* getPatcher() const {
                return static_cast<RNBOSubpatcher_2069 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
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
                this->phasor_08_perform(this->phasor_08_freq, this->signals[0], n);
                this->triangle_tilde_04_perform(this->signals[0], this->triangle_tilde_04_duty, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 1; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->phasor_08_sigbuf = resizeSignal(this->phasor_08_sigbuf, this->maxvs, maxBlockSize);
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
            
                this->phasor_08_dspsetup(forceDSPSetup);
            
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
            
            void phasor_08_freq_set(number v) {
                this->phasor_08_freq = v;
            }
            
            void receive_04_output_number_set(number v) {
                this->receive_04_output_number = v;
                this->phasor_08_freq_set(v);
            }
            
            void receive_04_output_bang_bang() {}
            
            void phasor_08_phase_set(number v) {
                if (v >= 0 && (bool)(this->phasor_08_sigbuf)) {
                    this->phasor_08_sigbuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = v;
                }
            }
            
            void receive_04_output_list_set(const list& v) {
                this->receive_04_output_list = jsCreateListCopy(v);
            
                {
                    if (v->length > 1)
                        this->phasor_08_phase_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->phasor_08_freq_set(converted);
                }
            }
            
            void phasor_08_perform(number freq, SampleValue * out, Index n) {
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->phasor_08_ph_next(freq, -1);
                    this->phasor_08_sigbuf[(Index)i] = -1;
                }
            }
            
            void triangle_tilde_04_perform(const Sample * phase, number duty, SampleValue * out1, Index n) {
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
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number phasor_08_ph_next(number freq, number reset) {
                RNBO_UNUSED(reset);
                number pincr = freq * this->phasor_08_ph_conv;
            
                if (this->phasor_08_ph_currentPhase < 0.)
                    this->phasor_08_ph_currentPhase = 1. + this->phasor_08_ph_currentPhase;
            
                if (this->phasor_08_ph_currentPhase > 1.)
                    this->phasor_08_ph_currentPhase = this->phasor_08_ph_currentPhase - 1.;
            
                number tmp = this->phasor_08_ph_currentPhase;
                this->phasor_08_ph_currentPhase += pincr;
                return tmp;
            }
            
            void phasor_08_ph_reset() {
                this->phasor_08_ph_currentPhase = 0;
            }
            
            void phasor_08_ph_dspsetup() {
                this->phasor_08_ph_conv = (number)1 / this->sr;
            }
            
            void phasor_08_dspsetup(bool force) {
                if ((bool)(this->phasor_08_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->phasor_08_conv = (number)1 / this->samplerate();
                this->phasor_08_setupDone = true;
                this->phasor_08_ph_dspsetup();
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
                triangle_tilde_04_phase = 0;
                triangle_tilde_04_duty = 0.5;
                phasor_08_freq = 0;
                receive_04_output_number = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                phasor_08_sigbuf = nullptr;
                phasor_08_lastLockedPhase = 0;
                phasor_08_conv = 0;
                phasor_08_ph_currentPhase = 0;
                phasor_08_ph_conv = 0;
                phasor_08_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number triangle_tilde_04_phase;
                number triangle_tilde_04_duty;
                number phasor_08_freq;
                number receive_04_output_number;
                list receive_04_output_list;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[1];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                signal phasor_08_sigbuf;
                number phasor_08_lastLockedPhase;
                number phasor_08_conv;
                number phasor_08_ph_currentPhase;
                number phasor_08_ph_conv;
                bool phasor_08_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_2069()
    {
    }
    
    ~RNBOSubpatcher_2069()
    {
        delete this->p_13;
        delete this->p_14;
        delete this->p_15;
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
        this->p_13_perform(this->signals[0], n);
        this->p_14_perform(this->signals[1], n);
        this->p_15_perform(this->signals[2], n);
    
        this->selector_06_perform(
            this->selector_06_onoff,
            this->zeroBuffer,
            this->signals[0],
            this->signals[1],
            this->signals[2],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 3; i++) {
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
        this->p_13->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_14->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_15->prepareToProcess(sampleRate, maxBlockSize, force);
    
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
        this->p_13 = new RNBOSubpatcher_2063();
        this->p_13->setEngineAndPatcher(this->getEngine(), this);
        this->p_13->initialize();
        this->p_13->setParameterOffset(this->getParameterOffset(this->p_13));
        this->p_14 = new RNBOSubpatcher_2064();
        this->p_14->setEngineAndPatcher(this->getEngine(), this);
        this->p_14->initialize();
        this->p_14->setParameterOffset(this->getParameterOffset(this->p_14));
        this->p_15 = new RNBOSubpatcher_2065();
        this->p_15->setEngineAndPatcher(this->getEngine(), this);
        this->p_15->initialize();
        this->p_15->setParameterOffset(this->getParameterOffset(this->p_15));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_13->getPreset(getSubState(getSubState(preset, "__sps"), "sin"));
        this->p_14->getPreset(getSubState(getSubState(preset, "__sps"), "phasor"));
        this->p_15->getPreset(getSubState(getSubState(preset, "__sps"), "triangle"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_13->processTempoEvent(time, tempo);
        this->p_14->processTempoEvent(time, tempo);
        this->p_15->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_13->processTransportEvent(time, state);
        this->p_14->processTransportEvent(time, state);
        this->p_15->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_13->processBeatTimeEvent(time, beattime);
        this->p_14->processBeatTimeEvent(time, beattime);
        this->p_15->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_13->processTimeSignatureEvent(time, numerator, denominator);
        this->p_14->processTimeSignatureEvent(time, numerator, denominator);
        this->p_15->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        RNBO_UNUSED(v);
        this->updateTime(time);
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_13->getNumParameters())
                this->p_13->setParameterValue(index, v, time);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                this->p_14->setParameterValue(index, v, time);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                this->p_15->setParameterValue(index, v, time);
    
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
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterValue(index);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->getParameterValue(index);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->getParameterValue(index);
    
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
        return 0 + this->p_13->getNumParameters() + this->p_14->getNumParameters() + this->p_15->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterName(index);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->getParameterName(index);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->getParameterId(index);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->getParameterId(index);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->getParameterId(index);
    
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
    
                if (index < this->p_13->getNumParameters())
                    this->p_13->getParameterInfo(index, info);
    
                index -= this->p_13->getNumParameters();
    
                if (index < this->p_14->getNumParameters())
                    this->p_14->getParameterInfo(index, info);
    
                index -= this->p_14->getNumParameters();
    
                if (index < this->p_15->getNumParameters())
                    this->p_15->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_13)
            return 0;
    
        if (subpatcher == this->p_14)
            return 0 + this->p_13->getNumParameters();
    
        if (subpatcher == this->p_15)
            return 0 + this->p_13->getNumParameters() + this->p_14->getNumParameters();
    
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
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->convertToNormalizedParameterValue(index, value);
    
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
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_13->getNumParameters())
                return this->p_13->constrainParameterValue(index, value);
    
            index -= this->p_13->getNumParameters();
    
            if (index < this->p_14->getNumParameters())
                return this->p_14->constrainParameterValue(index, value);
    
            index -= this->p_14->getNumParameters();
    
            if (index < this->p_15->getNumParameters())
                return this->p_15->constrainParameterValue(index, value);
    
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
        this->p_13->processNumMessage(tag, objectId, time, payload);
        this->p_14->processNumMessage(tag, objectId, time, payload);
        this->p_15->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_13->processListMessage(tag, objectId, time, payload);
        this->p_14->processListMessage(tag, objectId, time, payload);
        this->p_15->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_13->processBangMessage(tag, objectId, time);
        this->p_14->processBangMessage(tag, objectId, time);
        this->p_15->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_13->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_14->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_15->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
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
        this->p_13->processDataViewUpdate(index, time);
        this->p_14->processDataViewUpdate(index, time);
        this->p_15->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void eventinlet_24_out1_bang_bang() {}
    
    void eventinlet_24_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_06_onoff_set(converted);
        }
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
        this->p_13->initializeObjects();
        this->p_14->initializeObjects();
        this->p_15->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_13->startup();
        this->p_14->startup();
        this->p_15->startup();
    }
    
    void allocateDataRefs() {
        this->p_13->allocateDataRefs();
        this->p_14->allocateDataRefs();
        this->p_15->allocateDataRefs();
    }
    
    void p_13_target_pitch_number_set(number v) {
        this->p_13->updateTime(this->_currentTime);
        this->p_13->receive_02_output_number_set(v);
    }
    
    void p_14_target_pitch_number_set(number v) {
        this->p_14->updateTime(this->_currentTime);
        this->p_14->receive_03_output_number_set(v);
    }
    
    void p_15_target_pitch_number_set(number v) {
        this->p_15->updateTime(this->_currentTime);
        this->p_15->receive_04_output_number_set(v);
    }
    
    void selector_06_onoff_set(number v) {
        this->selector_06_onoff = v;
    }
    
    void eventinlet_24_out1_number_set(number v) {
        this->selector_06_onoff_set(v);
    }
    
    void p_13_target_pitch_bang_bang() {
        this->p_13->updateTime(this->_currentTime);
        this->p_13->receive_02_output_bang_bang();
    }
    
    void p_14_target_pitch_bang_bang() {
        this->p_14->updateTime(this->_currentTime);
        this->p_14->receive_03_output_bang_bang();
    }
    
    void p_15_target_pitch_bang_bang() {
        this->p_15->updateTime(this->_currentTime);
        this->p_15->receive_04_output_bang_bang();
    }
    
    void p_13_target_pitch_list_set(const list& v) {
        this->p_13->updateTime(this->_currentTime);
        this->p_13->receive_02_output_list_set(v);
    }
    
    void p_14_target_pitch_list_set(const list& v) {
        this->p_14->updateTime(this->_currentTime);
        this->p_14->receive_03_output_list_set(v);
    }
    
    void p_15_target_pitch_list_set(const list& v) {
        this->p_15->updateTime(this->_currentTime);
        this->p_15->receive_04_output_list_set(v);
    }
    
    void p_13_perform(SampleValue * out1, Index n) {
        // subpatcher: sin
        SampleArray<1> outs = {out1};
    
        this->p_13->process(nullptr, 0, outs, 1, n);
    }
    
    void p_14_perform(SampleValue * out1, Index n) {
        // subpatcher: phasor
        SampleArray<1> outs = {out1};
    
        this->p_14->process(nullptr, 0, outs, 1, n);
    }
    
    void p_15_perform(SampleValue * out1, Index n) {
        // subpatcher: triangle
        SampleArray<1> outs = {out1};
    
        this->p_15->process(nullptr, 0, outs, 1, n);
    }
    
    void selector_06_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
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
        selector_06_onoff = 1;
        p_13_target = 0;
        p_14_target = 0;
        p_15_target = 0;
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
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number selector_06_onoff;
        number p_13_target;
        number p_14_target;
        number p_15_target;
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
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_2063* p_13;
        RNBOSubpatcher_2064* p_14;
        RNBOSubpatcher_2065* p_15;
    
};

class RNBOSubpatcher_2070 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_2070()
    {
    }
    
    ~RNBOSubpatcher_2070()
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
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    
        this->cycle_tilde_05_perform(
            this->cycle_tilde_05_frequency,
            this->cycle_tilde_05_phase_offset,
            this->signals[0],
            this->dummyBuffer,
            n
        );
    
        this->dspexpr_05_perform(in1, this->signals[0], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 1; i++) {
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
    
        this->cycle_tilde_05_dspsetup(forceDSPSetup);
    
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
        this->param_01_getPresetValue(getSubState(preset, "ringmod"));
    }
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
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
            return "ringmod";
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
            return "ringmod/ringmod";
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
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 0) {
            this->cycle_tilde_05_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->cycle_tilde_05_bufferUpdated();
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->cycle_tilde_05_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
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
    
        this->cycle_tilde_05_frequency_set(v);
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
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
    
        {
            this->scheduleParamInit(0, 0);
        }
    }
    
    void allocateDataRefs() {
        this->cycle_tilde_05_buffer->requestSize(16384, 1);
        this->cycle_tilde_05_buffer->setSampleRate(this->sr);
        this->cycle_tilde_05_buffer = this->cycle_tilde_05_buffer->allocateIfNeeded();
    }
    
    static number param_01_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void cycle_tilde_05_frequency_set(number v) {
        this->cycle_tilde_05_frequency = v;
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
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
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
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
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
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        cycle_tilde_05_frequency = 0;
        cycle_tilde_05_phase_offset = 0;
        param_01_value = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        cycle_tilde_05_wrap = 0;
        cycle_tilde_05_ph_currentPhase = 0;
        cycle_tilde_05_ph_conv = 0;
        cycle_tilde_05_setupDone = false;
        param_01_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number cycle_tilde_05_frequency;
        number cycle_tilde_05_phase_offset;
        number param_01_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[1];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float64BufferRef cycle_tilde_05_buffer;
        long cycle_tilde_05_wrap;
        uint32_t cycle_tilde_05_phasei;
        SampleValue cycle_tilde_05_f2i;
        number cycle_tilde_05_ph_currentPhase;
        number cycle_tilde_05_ph_conv;
        bool cycle_tilde_05_setupDone;
        number param_01_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_16;
    delete this->p_17;
    delete this->p_18;
    delete this->p_19;
    delete this->p_20;
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
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    this->p_16_perform(n);
    this->p_19_perform(this->signals[0], n);
    this->p_20_perform(this->signals[0], this->signals[1], n);
    this->p_18_perform(this->signals[1], this->signals[0], n);
    this->p_17_perform(this->signals[0], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 2; i++) {
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

    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_16->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_17->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_18->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_19->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_20->prepareToProcess(sampleRate, maxBlockSize, force);

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
    this->p_16->processDataViewUpdate(index, time);
    this->p_17->processDataViewUpdate(index, time);
    this->p_18->processDataViewUpdate(index, time);
    this->p_19->processDataViewUpdate(index, time);
    this->p_20->processDataViewUpdate(index, time);
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
    this->p_16 = new RNBOSubpatcher_2066();
    this->p_16->setEngineAndPatcher(this->getEngine(), this);
    this->p_16->initialize();
    this->p_16->setParameterOffset(this->getParameterOffset(this->p_16));
    this->p_17 = new RNBOSubpatcher_2067();
    this->p_17->setEngineAndPatcher(this->getEngine(), this);
    this->p_17->initialize();
    this->p_17->setParameterOffset(this->getParameterOffset(this->p_17));
    this->p_18 = new RNBOSubpatcher_2068();
    this->p_18->setEngineAndPatcher(this->getEngine(), this);
    this->p_18->initialize();
    this->p_18->setParameterOffset(this->getParameterOffset(this->p_18));
    this->p_19 = new RNBOSubpatcher_2069();
    this->p_19->setEngineAndPatcher(this->getEngine(), this);
    this->p_19->initialize();
    this->p_19->setParameterOffset(this->getParameterOffset(this->p_19));
    this->p_20 = new RNBOSubpatcher_2070();
    this->p_20->setEngineAndPatcher(this->getEngine(), this);
    this->p_20->initialize();
    this->p_20->setParameterOffset(this->getParameterOffset(this->p_20));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_02_getPresetValue(getSubState(preset, "arpstart"));
    this->param_03_getPresetValue(getSubState(preset, "arp"));
    this->param_04_getPresetValue(getSubState(preset, "pitch"));
    this->param_05_getPresetValue(getSubState(preset, "arpspeed"));
    this->param_06_getPresetValue(getSubState(preset, "source"));
    this->param_07_getPresetValue(getSubState(preset, "thruster"));
    this->param_08_getPresetValue(getSubState(preset, "shields"));
    this->param_09_getPresetValue(getSubState(preset, "thrusterspeed"));
    this->p_16->getPreset(getSubState(getSubState(preset, "__sps"), "arpeggiator"));
    this->p_17->getPreset(getSubState(getSubState(preset, "__sps"), "shields"));
    this->p_18->getPreset(getSubState(getSubState(preset, "__sps"), "thruster"));
    this->p_19->getPreset(getSubState(getSubState(preset, "__sps"), "generator"));
    this->p_20->getPreset(getSubState(getSubState(preset, "__sps"), "ringmod"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_02_setPresetValue(getSubState(preset, "arpstart"));
    this->param_03_setPresetValue(getSubState(preset, "arp"));
    this->param_04_setPresetValue(getSubState(preset, "pitch"));
    this->param_05_setPresetValue(getSubState(preset, "arpspeed"));
    this->param_06_setPresetValue(getSubState(preset, "source"));
    this->param_07_setPresetValue(getSubState(preset, "thruster"));
    this->param_08_setPresetValue(getSubState(preset, "shields"));
    this->param_09_setPresetValue(getSubState(preset, "thrusterspeed"));

    this->p_20->param_01_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "ringmod"), "ringmod")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_16->processTempoEvent(time, tempo);
        this->p_17->processTempoEvent(time, tempo);
        this->p_18->processTempoEvent(time, tempo);
        this->p_19->processTempoEvent(time, tempo);
        this->p_20->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_16->processTransportEvent(time, state);
        this->p_17->processTransportEvent(time, state);
        this->p_18->processTransportEvent(time, state);
        this->p_19->processTransportEvent(time, state);
        this->p_20->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_16->processBeatTimeEvent(time, beattime);
        this->p_17->processBeatTimeEvent(time, beattime);
        this->p_18->processBeatTimeEvent(time, beattime);
        this->p_19->processBeatTimeEvent(time, beattime);
        this->p_20->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_16->processTimeSignatureEvent(time, numerator, denominator);
        this->p_17->processTimeSignatureEvent(time, numerator, denominator);
        this->p_18->processTimeSignatureEvent(time, numerator, denominator);
        this->p_19->processTimeSignatureEvent(time, numerator, denominator);
        this->p_20->processTimeSignatureEvent(time, numerator, denominator);
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
    case 6:
        {
        this->param_08_value_set(v);
        break;
        }
    case 7:
        {
        this->param_09_value_set(v);
        break;
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            this->p_16->setParameterValue(index, v, time);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            this->p_17->setParameterValue(index, v, time);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            this->p_18->setParameterValue(index, v, time);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            this->p_19->setParameterValue(index, v, time);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            this->p_20->setParameterValue(index, v, time);

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
    case 6:
        {
        return this->param_08_value;
        }
    case 7:
        {
        return this->param_09_value;
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterValue(index);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->getParameterValue(index);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->getParameterValue(index);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->getParameterValue(index);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->getParameterValue(index);

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
    return 8 + this->p_16->getNumParameters() + this->p_17->getNumParameters() + this->p_18->getNumParameters() + this->p_19->getNumParameters() + this->p_20->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "arpstart";
        }
    case 1:
        {
        return "arp";
        }
    case 2:
        {
        return "pitch";
        }
    case 3:
        {
        return "arpspeed";
        }
    case 4:
        {
        return "source";
        }
    case 5:
        {
        return "thruster";
        }
    case 6:
        {
        return "shields";
        }
    case 7:
        {
        return "thrusterspeed";
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterName(index);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->getParameterName(index);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->getParameterName(index);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->getParameterName(index);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "arpstart";
        }
    case 1:
        {
        return "arp";
        }
    case 2:
        {
        return "pitch";
        }
    case 3:
        {
        return "arpspeed";
        }
    case 4:
        {
        return "source";
        }
    case 5:
        {
        return "thruster[1]";
        }
    case 6:
        {
        return "shields[1]";
        }
    case 7:
        {
        return "thrusterspeed";
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->getParameterId(index);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->getParameterId(index);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->getParameterId(index);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->getParameterId(index);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->getParameterId(index);

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
            info->steps = 2;
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
            info->max = 2093.005;
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
            info->min = 50;
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
            info->min = 1;
            info->max = 4;
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
            info->min = 1;
            info->max = 4;
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
            info->max = 15;
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
            index -= 8;

            if (index < this->p_16->getNumParameters())
                this->p_16->getParameterInfo(index, info);

            index -= this->p_16->getNumParameters();

            if (index < this->p_17->getNumParameters())
                this->p_17->getParameterInfo(index, info);

            index -= this->p_17->getNumParameters();

            if (index < this->p_18->getNumParameters())
                this->p_18->getParameterInfo(index, info);

            index -= this->p_18->getNumParameters();

            if (index < this->p_19->getNumParameters())
                this->p_19->getParameterInfo(index, info);

            index -= this->p_19->getNumParameters();

            if (index < this->p_20->getNumParameters())
                this->p_20->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_16)
        return 8;

    if (subpatcher == this->p_17)
        return 8 + this->p_16->getNumParameters();

    if (subpatcher == this->p_18)
        return 8 + this->p_16->getNumParameters() + this->p_17->getNumParameters();

    if (subpatcher == this->p_19)
        return 8 + this->p_16->getNumParameters() + this->p_17->getNumParameters() + this->p_18->getNumParameters();

    if (subpatcher == this->p_20)
        return 8 + this->p_16->getNumParameters() + this->p_17->getNumParameters() + this->p_18->getNumParameters() + this->p_19->getNumParameters();

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
    case 1:
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 4:
    case 6:
        {
        {
            value = (value < 1 ? 1 : (value > 4 ? 4 : value));
            ParameterValue normalizedValue = (value - 1) / (4 - 1);
            return normalizedValue;
        }
        }
    case 7:
        {
        {
            value = (value < 1 ? 1 : (value > 15 ? 15 : value));
            ParameterValue normalizedValue = (value - 1) / (15 - 1);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 50 ? 50 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 50) / (2000 - 50);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 32.703 ? 32.703 : (value > 2093.005 ? 2093.005 : value));
            ParameterValue normalizedValue = (value - 32.703) / (2093.005 - 32.703);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->convertToNormalizedParameterValue(index, value);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->convertToNormalizedParameterValue(index, value);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->convertToNormalizedParameterValue(index, value);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->convertToNormalizedParameterValue(index, value);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 1:
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 4:
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (4 - 1);
            }
        }
        }
    case 7:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (15 - 1);
            }
        }
        }
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 50 + value * (2000 - 50);
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 32.703 + value * (2093.005 - 32.703);
            }
        }
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->convertFromNormalizedParameterValue(index, value);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->convertFromNormalizedParameterValue(index, value);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->convertFromNormalizedParameterValue(index, value);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->convertFromNormalizedParameterValue(index, value);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->convertFromNormalizedParameterValue(index, value);

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
    case 6:
        {
        return this->param_08_value_constrain(value);
        }
    case 7:
        {
        return this->param_09_value_constrain(value);
        }
    default:
        {
        index -= 8;

        if (index < this->p_16->getNumParameters())
            return this->p_16->constrainParameterValue(index, value);

        index -= this->p_16->getNumParameters();

        if (index < this->p_17->getNumParameters())
            return this->p_17->constrainParameterValue(index, value);

        index -= this->p_17->getNumParameters();

        if (index < this->p_18->getNumParameters())
            return this->p_18->constrainParameterValue(index, value);

        index -= this->p_18->getNumParameters();

        if (index < this->p_19->getNumParameters())
            return this->p_19->constrainParameterValue(index, value);

        index -= this->p_19->getNumParameters();

        if (index < this->p_20->getNumParameters())
            return this->p_20->constrainParameterValue(index, value);

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
        if (TAG("number_obj-8") == objectId)
            this->numberobj_07_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-8") == objectId)
            this->numberobj_07_format_set(payload);

        break;
        }
    }

    this->p_16->processNumMessage(tag, objectId, time, payload);
    this->p_17->processNumMessage(tag, objectId, time, payload);
    this->p_18->processNumMessage(tag, objectId, time, payload);
    this->p_19->processNumMessage(tag, objectId, time, payload);
    this->p_20->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_16->processListMessage(tag, objectId, time, payload);
    this->p_17->processListMessage(tag, objectId, time, payload);
    this->p_18->processListMessage(tag, objectId, time, payload);
    this->p_19->processListMessage(tag, objectId, time, payload);
    this->p_20->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_16->processBangMessage(tag, objectId, time);
    this->p_17->processBangMessage(tag, objectId, time);
    this->p_18->processBangMessage(tag, objectId, time);
    this->p_19->processBangMessage(tag, objectId, time);
    this->p_20->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-8"):
        {
        return "number_obj-8";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    auto subpatchResult_0 = this->p_16->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_17->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    auto subpatchResult_2 = this->p_18->resolveTag(tag);

    if (subpatchResult_2)
        return subpatchResult_2;

    auto subpatchResult_3 = this->p_19->resolveTag(tag);

    if (subpatchResult_3)
        return subpatchResult_3;

    auto subpatchResult_4 = this->p_20->resolveTag(tag);

    if (subpatchResult_4)
        return subpatchResult_4;

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

    this->p_16_in1_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(1, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->p_16_in4_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(2, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->p_16_in3_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(3, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->p_16_in2_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(4, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->p_17_in2_number_set(v);
    this->p_19_in1_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(5, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->p_18_in2_number_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(6, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->p_17_in3_number_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(7, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->p_18_in3_number_set(v);
}

void numberobj_07_valin_set(number v) {
    this->numberobj_07_value_set(v);
}

void numberobj_07_format_set(number v) {
    this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
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
    this->p_16->allocateDataRefs();
    this->p_17->allocateDataRefs();
    this->p_18->allocateDataRefs();
    this->p_19->allocateDataRefs();
    this->p_20->allocateDataRefs();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->numberobj_07_init();
    this->p_16->initializeObjects();
    this->p_17->initializeObjects();
    this->p_18->initializeObjects();
    this->p_19->initializeObjects();
    this->p_20->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_16->startup();
    this->p_17->startup();
    this->p_18->startup();
    this->p_19->startup();
    this->p_20->startup();

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

static number param_02_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_16_in1_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->eventinlet_01_out1_number_set(v);
}

static number param_03_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_16_in4_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->eventinlet_04_out1_number_set(v);
}

static number param_04_value_constrain(number v) {
    v = (v > 2093.005 ? 2093.005 : (v < 32.703 ? 32.703 : v));
    return v;
}

void p_17_target_pitch_number_set(number v) {
    this->p_17->updateTime(this->_currentTime);
    this->p_17->receive_01_output_number_set(v);
}

void p_19_target_pitch_number_set(number v) {
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_13_target_pitch_number_set(v);
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_14_target_pitch_number_set(v);
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_15_target_pitch_number_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->p_17_target_pitch_number_set(v);
    this->p_19_target_pitch_number_set(v);
}

void p_16_out2_number_set(number v) {
    this->send_01_input_number_set(v);
}

void p_16_in3_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->eventinlet_03_out1_number_set(v);
}

static number param_05_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 50 ? 50 : v));
    return v;
}

void p_16_in2_number_set(number v) {
    this->p_16->updateTime(this->_currentTime);
    this->p_16->eventinlet_02_out1_number_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 4 ? 4 : (v < 1 ? 1 : v));
    return v;
}

void p_17_in2_number_set(number v) {
    this->p_17->updateTime(this->_currentTime);
    this->p_17->eventinlet_21_out1_number_set(v);
}

void p_19_in1_number_set(number v) {
    this->p_19->updateTime(this->_currentTime);
    this->p_19->eventinlet_24_out1_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_18_in2_number_set(number v) {
    this->p_18->updateTime(this->_currentTime);
    this->p_18->eventinlet_22_out1_number_set(v);
}

static number param_08_value_constrain(number v) {
    v = (v > 4 ? 4 : (v < 1 ? 1 : v));
    return v;
}

void p_17_in3_number_set(number v) {
    this->p_17->updateTime(this->_currentTime);
    this->p_17->eventinlet_20_out1_number_set(v);
}

static number param_09_value_constrain(number v) {
    v = (v > 15 ? 15 : (v < 1 ? 1 : v));
    return v;
}

void p_18_in3_number_set(number v) {
    this->p_18->updateTime(this->_currentTime);
    this->p_18->eventinlet_23_out1_number_set(v);
}

void numberobj_07_output_set(number v) {
    this->param_06_value_set(v);
}

void numberobj_07_value_set(number v) {
    this->numberobj_07_value_setter(v);
    v = this->numberobj_07_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 1) {
        localvalue = 1;
    }

    if ((bool)(true) && localvalue > 4) {
        localvalue = 4;
    }

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-8"), localvalue, this->_currentTime);
    this->numberobj_07_output_set(localvalue);
}

void param_04_value_bang() {
    number v = this->param_04_value;
    this->sendParameter(2, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->p_16_in3_number_set(v);
}

void p_16_out1_bang_bang() {
    this->param_04_value_bang();
}

void p_17_target_pitch_bang_bang() {
    this->p_17->updateTime(this->_currentTime);
    this->p_17->receive_01_output_bang_bang();
}

void p_19_target_pitch_bang_bang() {
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_13_target_pitch_bang_bang();
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_14_target_pitch_bang_bang();
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_15_target_pitch_bang_bang();
}

void send_01_input_bang_bang() {
    this->p_17_target_pitch_bang_bang();
    this->p_19_target_pitch_bang_bang();
}

void p_16_out2_bang_bang() {
    this->send_01_input_bang_bang();
}

void p_17_target_pitch_list_set(const list& v) {
    this->p_17->updateTime(this->_currentTime);
    this->p_17->receive_01_output_list_set(v);
}

void p_19_target_pitch_list_set(const list& v) {
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_13_target_pitch_list_set(v);
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_14_target_pitch_list_set(v);
    this->p_19->updateTime(this->_currentTime);
    this->p_19->p_15_target_pitch_list_set(v);
}

void send_01_input_list_set(const list& v) {
    this->send_01_input_list = jsCreateListCopy(v);
    this->p_17_target_pitch_list_set(v);
    this->p_19_target_pitch_list_set(v);
}

void p_16_out2_list_set(const list& v) {
    this->send_01_input_list_set(v);
}

void p_16_out3_number_set(number v) {
    this->param_03_value_set(v);
}

void p_16_perform(Index n) {
    // subpatcher: arpeggiator
    this->p_16->process(nullptr, 0, nullptr, 0, n);
}

void p_19_perform(SampleValue * out1, Index n) {
    // subpatcher: generator
    SampleArray<1> outs = {out1};

    this->p_19->process(nullptr, 0, outs, 1, n);
}

void p_20_perform(const SampleValue * in1, SampleValue * out1, Index n) {
    // subpatcher: ringmod
    ConstSampleArray<1> ins = {in1};

    SampleArray<1> outs = {out1};
    this->p_20->process(ins, 1, outs, 1, n);
}

void p_18_perform(const SampleValue * in1, SampleValue * out1, Index n) {
    // subpatcher: thruster
    ConstSampleArray<1> ins = {in1};

    SampleArray<1> outs = {out1};
    this->p_18->process(ins, 1, outs, 1, n);
}

void p_17_perform(const SampleValue * in1, SampleValue * out1, Index n) {
    // subpatcher: shields
    ConstSampleArray<1> ins = {in1};

    SampleArray<1> outs = {out1};
    this->p_17->process(ins, 1, outs, 1, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_07_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 1) {
        localvalue = 1;
    }

    if ((bool)(true) && localvalue > 4) {
        localvalue = 4;
    }

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_07_value = localvalue;
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

void numberobj_07_init() {
    this->numberobj_07_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-8"), 1, this->_currentTime);
}

void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_07_value;
}

void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_07_value_set(preset["value"]);
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
    param_02_value = 0;
    p_16_target = 0;
    send_01_input_number = 0;
    param_03_value = 0;
    param_04_value = 0;
    param_05_value = 0;
    numberobj_07_value = 0;
    numberobj_07_value_setter(numberobj_07_value);
    param_06_value = 0;
    p_17_target = 0;
    p_18_target = 0;
    p_19_target = 0;
    p_20_target = 0;
    param_07_value = 0;
    param_08_value = 0;
    param_09_value = 0;
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
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    numberobj_07_currentFormat = 6;
    numberobj_07_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
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

    number param_02_value;
    number p_16_target;
    number send_01_input_number;
    list send_01_input_list;
    number param_03_value;
    number param_04_value;
    number param_05_value;
    number numberobj_07_value;
    number param_06_value;
    number p_17_target;
    number p_18_target;
    number p_19_target;
    number p_20_target;
    number param_07_value;
    number param_08_value;
    number param_09_value;
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
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    Int numberobj_07_currentFormat;
    number numberobj_07_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
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
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_2066* p_16;
    RNBOSubpatcher_2067* p_17;
    RNBOSubpatcher_2068* p_18;
    RNBOSubpatcher_2069* p_19;
    RNBOSubpatcher_2070* p_20;

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

