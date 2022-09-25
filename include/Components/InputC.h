#pragma once

enum class Command
{
    LEFT = 0,
    RIGHT,
    JUMP,
    STOP
};

struct InputC
{
    Command cmd;
};