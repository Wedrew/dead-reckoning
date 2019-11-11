#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Zero {
    
    /*
    * These values are automatically set according to their cmake variables.
    */

    std::string const BUILD_VERSION = "2019-10-14_22;10;46_prealpha_0.1";
    std::string const GAME_NAME = "ZerothOrder";
    std::string const ENGINE_NAME = "Melodic";
    std::string const WINDOW_NAME = "(Release)ZerothOrder_prealpha_0.1";
    std::string const LOG_FILE = "logs/2019-10-14_22;10;46_prealpha.txt";

    bool const ENABLE_VALIDATION_LAYERS = false;

    //#define BUILDVERSION 
    /* #undef HAVE_FEATURE_B */
    /* #undef HAVE_FEATURE_BITS */

}

#endif
