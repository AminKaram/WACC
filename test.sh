#!/bin/bash
#command line testing utility wor the wacc front-end.

VALID="$HOME/second_year/labs/wacc_examples/valid/"
SYNTAX="$HOME/second_year/labs/wacc_examples/invalid/syntaxErr/"
SEMANTIC="$HOME/second_year/labs/wacc_examples/invalid/semanticErr/"

make

echo "VALID TESTS "
for f in $(find "$VALID" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 0 ]; then
    echo "TEST FAILED: $f\n"
  fi
done

echo " SYNTAX TESTS"
echo ""
echo ""
echo ""
for f in $(find "$SYNTAX" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 100 ]; then
    echo "TEST FAILED: $f\n"
  fi
done

echo " SEMANTIC TESTS"
echo ""
echo ""
echo ""
for f in $(find "$SEMANTIC" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 200 ]; then
    echo "TEST FAILED: $f\n"
  fi
done


