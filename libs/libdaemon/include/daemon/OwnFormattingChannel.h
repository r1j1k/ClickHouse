#pragma once
#include <Interpreters/ExtendedLogChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Channel.h>
#include <Poco/FormattingChannel.h>


class OwnPatternFormatter;


namespace DB
{

class OwnFormattingChannel : public Poco::Channel, public ExtendedLogChannel
{
public:

    OwnFormattingChannel(const Poco::AutoPtr<OwnPatternFormatter> & pFormatter_)
            : pFormatter(pFormatter_) {}

    void setChannel(const Poco::AutoPtr<Poco::Channel> & pChannel_)
    {
        pChannel = pChannel_;
    }

    void setLevel(Poco::Message::Priority priority_)
    {
        priority = priority_;
    }

    void open() override
    {
        if (pChannel)
            pChannel->open();
    }

    void close() override
    {
        if (pChannel)
            pChannel->close();
    }

    void log(const Poco::Message & msg) override;
    void logExtended(const ExtendedLogMessage & msg) override;

    ~OwnFormattingChannel();

private:

    Poco::AutoPtr<OwnPatternFormatter> pFormatter;
    Poco::AutoPtr<Poco::Channel> pChannel;
    Poco::Message::Priority priority = Poco::Message::PRIO_TRACE;
};

}
