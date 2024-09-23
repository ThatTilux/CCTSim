#include <string>
#include <vector>
#include <constants.h>
#include "input_param_range_interface.h"
#include "input_layer_pitch.hh"
#include "output_criterion_interface.h"
#include "output_b_multipole.hh"
#include "output_a_multipole.hh"
#include "parameter_search.h"
#include "model_handler.h"
#include "json_range.hh"

int main()
{

    // Set path to model file
    std::string model_path = DATA_DIR_PATH + "Sextupole_prototype_ConnectV2_56_5mm_V5.json";
    CCTools::ModelHandler modelHandler(model_path);

    // Set input parameters
    std::vector<std::shared_ptr<InputParamRangeInterface>> inputs;

    InputLayerPitch pitch_outer("custom cct outer", {2.05}, "_outer");
    InputLayerPitch pitch_inner("custom cct inner", JsonRange::double_linear(2, 2.2, 10000), "_inner");

    inputs.push_back(std::make_shared<InputParamRangeInterface>(pitch_outer));
    inputs.push_back(std::make_shared<InputParamRangeInterface>(pitch_inner));

    // Set output parameters
    std::vector<std::shared_ptr<OutputCriterionInterface>> outputs;

    // Add all a_n
    for (size_t i = 1; i <= 10; i++)
    {
        outputs.push_back(std::make_shared<OutputAMultipole>(OutputAMultipole(i)));
    }
    // Add all b_n
    for (size_t i = 1; i <= 10; i++)
    {
        outputs.push_back(std::make_shared<OutputBMultipole>(OutputBMultipole(i)));
    }

    // Run grid search
    ParameterSearch search(inputs, outputs, modelHandler);
    search.run();

    return 0;
}