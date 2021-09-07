#/bin/sh
PATH=$HOME/.local/bin:$PATH PYTHONPATH=$HOME/.local/lib/python3.8 make html
PATH=$HOME/.local/bin:$PATH PYTHONPATH=$HOME/.local/lib/python3.8 make latexpdf
cd _build/html && ln -s ../latex/BeagleBoard.pdf
