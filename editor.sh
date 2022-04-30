cd Editor
make
if [ $? = "0" ] ; then
    
    ./Editor
    
    else
        echo
        echo

        echo "              Compile Error"

        echo
        echo
    fi
