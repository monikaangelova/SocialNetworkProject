#pragma once
class Unique
{
protected:
    static unsigned globalId;

public:
    static unsigned genetateId();
    static void setGlobalId(unsigned id);
};

