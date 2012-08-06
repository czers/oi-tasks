TESTS_IN=`ls $3 | grep \.in$ | sort -V`
echo `pwd`
for t in $TESTS_IN
do
    ./$1 <$t >1.out
    ./$2 <$t >2.out
    RES=`diff 1.out 2.out`
    if [ $? -ne 0 ]
    then
        echo FAIL:$t
    else
        echo OK:$t
    fi
done
rm 1.out 2.out