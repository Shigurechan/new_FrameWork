cd Editor
make

if [ $? = "1" ] ; then
        echo
        echo

        echo "              Compile Error"

        echo
        echo
    fi
    
cd ../Game
make

if [ $? = "1" ] ; then
        echo
        echo

        echo "              Compile Error"

        echo
        echo
    fi

