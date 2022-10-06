#include <iostream>

#include "NotMario/NotMario.h"

#include <Physics/Utils/BodyAllocator.h>

int main()
{
    NotMario game;

    game.OnInit();
    game.Run();

    p2d::BodyAllocator list {3};

    return 0;
}
