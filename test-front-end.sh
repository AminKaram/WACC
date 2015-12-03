#!/bin/bash
#command line testing utility wor the wacc front-end.

VALID="$HOME/second_year/labs/wacc_examples/valid/"
SYNTAX="$HOME/second_year/labs/wacc_examples/invalid/syntaxErr/"
SEMANTIC="$HOME/second_year/labs/wacc_examples/invalid/semanticErr/"

VFAIL=0
SYFAIL=0
SEFAIL=0

make

echo "VALID TESTS "
echo ""
echo ""
echo ""
for f in $(find "$VALID" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 0 ]; then
    echo ""
    echo "TEST FAILED: $f"
    echo ""
    ((VFAIL++))
  fi
done
echo "VALID TESTS $((172-$VFAIL))/172"
echo""
echo""
echo""

echo "SYNTAX TESTS"
echo ""
echo ""
echo ""
for f in $(find "$SYNTAX" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 100 ]; then
    echo ""
    echo "TEST FAILED: $f"
    echo ""
    ((SYFAIL++))
  fi
done
echo""
echo""
echo""

echo "SYNTAX TESTS $((46-$SYFAIL))/46"

echo""
echo""
echo""

echo "SEMANTIC TESTS"

echo ""
echo ""
echo ""
for f in $(find "$SEMANTIC" -name '*.wacc')
do
  /bin/bash ./compile $f
  if [ $? -ne 200 ]; then
    echo ""
    echo "TEST FAILED: $f"
    echo ""
    ((SEFAIL++))
  fi
done
echo""
echo""
echo""
echo "SEMANTIC TESTS $((45-$SEFAIL))/45"

