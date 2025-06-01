#include "raw_material_eval.h"
#include "state.h"
#include "enums.h"

int RawMaterialEval::evaluate(const GameState& state)
{
    return (state.material(white) - state.material(black)) * 100;
}