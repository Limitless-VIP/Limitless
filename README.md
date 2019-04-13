![TittieCoin](https://github.com/tittiecoin/tittiecoin-2-0/blob/master/src/qt/res/images/dixicoin_logo_horizontal.png)
[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?&color=success)](https://github.com/Test-Coin/TestCoin/blob/master/LICENSE)

TittieCoin Core - About
=====================================

What is TittieCoin?
----------------

TittieCoin (TIT) is a digital currency created by a trusted group of
developers early Febuary 2014. TIT is currently being developed to be
the exclusive currency for Tittie Island, a vision that we are working towards.
The TIT technology enables instant payments to anyone, anywhere in the world, however,
the main real world use for TittieCoin will be for goods and services on Tittie island. 
Bitcoin led the way with this technology and was first released In November 2008,
a paper was posted on the internet under the name Satoshi Nakamotouses peer-to-peer
technology to operate with no central authority: managing transactions and issuing
money are carried out collectively by the network. TittieCoin Core is the name of
open source software which enables the use of TIT the currency. 

TittieCoin v2.0 development was inspired by the PIVX model, a fork of PIVX with a few changes
differing primarily by having a decreased block generation time, increased maximum number of coins, 
different hashing algorithm phi1612, and a slightly modified GUI.
TittieCoin also proudly boasts Dark Gravity Wave 3 an open source difficulty-adjusting algorithm
for Bitcoin-based cryptocurrencies that was first used in Darkcoin/Dash and has since
been adopted by other digital currencies.

For more information, as well as an immediately useable, binary version of
the TittieCoin Core software, see https://tittiecoin.com/, or read the
[original whitepaper](https://tittiecoin.com/tittiecoin.pdf).

License
-------

TIttieCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/tittiecoin/tittiecoin-2-0/tags) are created
regularly to indicate new official, stable release versions of Bitcoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer channel at Discord should be used to discuss complicated or controversial changes before
working on a patch set. Developer Discord can be found https://discord.gg/57bcjwB at #Tittiecoin

Credit: Bitcoin Developers, Litecoin Developers and Dash Developers.

Build Process tittiecoind
-------------------------

Building tittiecoind is very easy and stright forward.

Use the autogen script to prepare the build environment. *Note these commands are not run in the src directoty*

    ./autogen.sh
    ./configure
    make

**Windows - v2.4 Update**
-------------------------
1. Download the new wallet for your machine form `https://tittiecoin.com/wallet`
2. if your wallet is running please exit the v2.1 wallet. 
3. Open the zipped folder and pull tittiecoin-qt.exe to the desktop
4. Run the wallet! (Avast or other antivirus might go crazy, don't worry this is normal. We already submitted the new version.

**Mac - v2.4 Update**
-------------------------
1. Download the new wallet for your machine form https://tittiecoin.com/wallet
2. if your wallet is running please exit the v2.1 wallet. 
3. Open the zipped folder and pull tittiecoin-core.dmg to the desktop
4. Run the wallet!
