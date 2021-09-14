#/bin/bash
pushd PRUCookbook/docs && make
popd
PATH=$HOME/.local/bin:$PATH PYTHONPATH=$HOME/.local/lib/python3.8 make html
PATH=$HOME/.local/bin:$PATH PYTHONPATH=$HOME/.local/lib/python3.8 make latexpdf
pushd _build/html && ln -s ../latex/BeagleBoard.pdf
popd
