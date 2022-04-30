cd Game 
make
if [ $? = "0" ] ; then
    
    ./Game
    
    else
        echo
        echo

        echo "              Compile Error"

        echo
        echo
    fi
