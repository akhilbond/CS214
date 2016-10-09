gcc -Wall -O -o Assign Assign.c
if [ $? == 0 ]; then
  ########################
  #      Test Cases      #
  ########################

  # Empty/Missing Argument
  ./Assign

  # The first assignment sheet test case
  ./Assign "thing stuff otherstuff blarp"

  # The second assignment sheet test case
  #gdb -ex=r --args ./Assign "thing1stuff3otherstuff,blarp" #DEBUG
  ./Assign "thing1stuff3otherstuff,blarp"

  # Test characters with non-space character
  ./Assign "la-dee-da"

  # Test with multiple non-alpha characters
  ./Assign "do-re-me fa =so   la ------ tee do"

  # Test with capitals and lowercase
  ./Assign "- WORLD hello world--HELLO 123WoRlD"

  #Test beginning with non alphabetic
  ./Assign "- hello world"

  #Test Ending with non-alphabetic
  ./Assign "hello there world--"

  #Test multiple non-alpha beginnings
  ./Assign "-----hello there humans"

  #Test multiple non-alpha endings
  ./Assign "we have come peacefully  ---123123"

  # Test Empty input String
  ./Assign ""

  # Test all non-alphabetic standard keyboard input
  ./Assign "\`1234567890-=~!@#$%$^&*()_+,./\\][';<>?|}{\":"



  which valgrind
  if [ $? == 0 ]; then

    #########################################################
    # Test for memeory leaks among just a couple test cases #
    #########################################################
    echo "Testing for memory leaks with valgrind"

    #Test multiple non-alpha endings
    valgrind --leak-check=yes ./Assign "we have come peacefully  ---123123"

    # Some lorem ipsum
    valgrind --leak-check=yes ./Assign "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

    # Test all non-alphabetic standard keyboard input
    valgrind --leak-check=yes ./Assign "\`1234567890-=~!@#$%$^&*()_+,./\\][';<>?|}{\":"
xsss
