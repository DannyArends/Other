cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES("./source" "C:/Program Files/R/R-2.9.1/include")
LINK_DIRECTORIES("C:/Program Files/R/R-2.9.1/bin")
SET(EXECNAME rggQTL)
SET(TESTOUTPUT regressiontests)
SET(TESTINPUT input)

link_libraries (
  R
)

add_executable (${EXECNAME}
./source/error.cpp
./source/species.cpp
./source/population.cpp
./source/individuals.cpp
./source/markers.cpp
./source/cofactors.cpp
./source/traits.cpp

main.cpp
)

ENABLE_TESTING()
SET(EXECUTABLE "${EXECNAME}.exe")
ADD_TEST(startandhelp ${EXECUTABLE} -h)
ADD_TEST(inputfile ${EXECUTABLE} -f ${TESTINPUT}/RILarabidopsisIN.txt -o ${TESTOUTPUT}/test1.out)
ADD_TEST(inputfile_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test1.out ${TESTOUTPUT}/test1.original)
ADD_TEST(parameters_1 ${EXECUTABLE} -f ${TESTINPUT}/F2mouseIN.txt -m B -s C -a 0.10 -o ${TESTOUTPUT}/test2.out)
ADD_TEST(parameters_1_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test2.out ${TESTOUTPUT}/test2.original)
ADD_TEST(parameters_2 ${EXECUTABLE} -f ${TESTINPUT}/SNPhumanIN.txt -m B -s F -a 0.30 -o ${TESTOUTPUT}/test3.out)
ADD_TEST(parameters_2_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test3.out ${TESTOUTPUT}/test3.original)
ADD_TEST(parameters_3 ${EXECUTABLE} -f ${TESTINPUT}/SNPhumancomplexIN.txt -m F -s C -a 0.15 -o ${TESTOUTPUT}/test4.out)
ADD_TEST(parameters_3_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test4.out ${TESTOUTPUT}/test4.original)
ADD_TEST(parameters_4 ${EXECUTABLE} -f ${TESTINPUT}/EPIRILarabidopsisIN.txt -m F -s C -a 0.15 -o ${TESTOUTPUT}/test5.out)
ADD_TEST(parameters_4_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test5.out ${TESTOUTPUT}/test5.original)
ADD_TEST(parameters_5 ${EXECUTABLE} -f ${TESTINPUT}/BCmouseIN.txt -m F -s C -a 0.05 -o ${TESTOUTPUT}/test6.out)
ADD_TEST(parameters_5_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test6.out ${TESTOUTPUT}/test6.original)
ADD_TEST(parameters_F1 ${EXECUTABLE} -f ${TESTINPUT}/RILarabidopsisIN.txt -m K -s C -a 0.15 -o ${TESTOUTPUT}/test7.out)
ADD_TEST(parameters_F1_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test7.out ${TESTOUTPUT}/test7.original)
ADD_TEST(parameters_F2 ${EXECUTABLE} -f ${TESTINPUT}/RILarabidopsisIN.txt -m F -s C -a -0.15 -o ${TESTOUTPUT}/test8.out)
ADD_TEST(parameters_F2_cmp ${CMAKE_COMMAND} -E compare_files ${TESTOUTPUT}/test8.out ${TESTOUTPUT}/test8.original)
