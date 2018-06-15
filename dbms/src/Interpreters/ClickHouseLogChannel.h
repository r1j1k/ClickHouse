#pragma once
#include <Interpreters/ExtendedLogChannel.h>
#include <Poco/Channel.h>
#include <Poco/AutoPtr.h>
#include <vector>


namespace DB
{

/// Poco::Channel used to implement passing of query logs to Client via TCP interface
class ClickHouseLogChannel : public Poco::Channel
{
public:
    ClickHouseLogChannel() = default;

    void log(const Poco::Message & msg) override;

    void addChannel(Poco::AutoPtr<Poco::Channel> & channel);

    ~ClickHouseLogChannel() = default;

private:

    using ChannelPtr = Poco::AutoPtr<Poco::Channel>;
    using ExtendedChannelPtrPair = std::pair<ChannelPtr, ExtendedLogChannel *>;
    std::vector<ExtendedChannelPtrPair> channels;
};

}
