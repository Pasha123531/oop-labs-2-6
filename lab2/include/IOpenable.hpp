#pragma once

class IOpenable {
public:
    virtual void open() = 0;
    virtual void close() = 0;

    virtual ~IOpenable() = default;
};