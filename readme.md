# CE C/C++ Toolchain  
[Forked from [CE-Programming/toolchain](https://github.com/CE-Programming/toolchain)]

The CE Toolchain incorporates a variety of tools in order to build programs in C/C++ natively for the TI-84 Plus CE calculator series.

## Purpose of this fork
Restores the missing v11.3 build for some TI-84 Plus CE applications that requires them.
Example additional files include: i48stubs.src, inchar.src,...

## Getting Started

Visit the [CE Toolchain documentation](https://ce-programming.github.io/toolchain).
This site hosts all the information for working with the toolchain.

## Getting Help

You can join us on the `CE Programming` Discord server in the `#ez80-dev` channel: [Discord Chat Link](https://discord.gg/TRkN5UcUzs).\
If you prefer IRC, the chat is also bridged to the EFNet `#ez80-dev` channel (you can use a web client like [IRCCloud](https://www.irccloud.com/irc/efnet/channel/ez80-dev), if you don't want to use a local application).

Depending on how active the channel is you might not get a response.\
In that case, post your questions [here](https://github.com/CE-Programming/toolchain/discussions) or [here](https://github.com/CE-Programming/toolchain/issues), and we will get back to you as soon as possible.

## Building/Contributing

Documentation for contributing/building the toolchain can be found [here](https://ce-programming.github.io/toolchain/static/contributing.html).

**For v11.3:**
(The missing build on the original repo)

Facilitates and also contains patched libs for khiCAS TI84PCE Port.

For building: Download v11.3 tag from this fork, rename the folder to toolchain,
use the additional libs below and copy to toolchain/src/libc (credits to Bernard Parisse)
