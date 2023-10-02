# ProbNets
C++ Implementation of Baysian and Markov networks with jason import/export and graphviz based image export

This code was developed throughout my studies.
The Markov Networks implementation was done as part of the Autonomous System Research module of the Edinburgh Centre for Robotics (https://www.edinburgh-robotics.org) PhD program in 2016.
The produced paper and slides are also included in the repository.

The json import/export is done with JSON for modern C++ (https://github.com/nlohmann/json) and a git submodule is used to provide the single include file needed.
The GraphViz library will be needed along with it's include file gvc.h included in the include path (if using a linux distro probably installing the dev version of the graphviz library packet libgraphviz-dev will do)

I'm releasing this under the MIT license as it is very permissive. If you end up using it or some derived work I would apreciate a mention and a message letting me know. 

# Still to do
- Add code to create a sample for Markov Networks
