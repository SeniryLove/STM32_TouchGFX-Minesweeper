#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdlib.h>

class ModelListener;

#include <time.h>

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    int mineNumber;

    int rand_dd[99];
protected:
    ModelListener* modelListener;

};

#endif // MODEL_HPP
