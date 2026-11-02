include("/home/lusa/octapedal/build/Desktop_Qt_6_11_1_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/octapedal-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtmultimedia")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/lusa/octapedal/build/Desktop_Qt_6_11_1_Debug/octapedal"
    GENERATE_QT_CONF
)
