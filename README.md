Tealcoin Core integration/staging tree
=====================================

https://tealcoin-project.io

Copyright (c) 2018 Tealcoin Core Developers

What is Tealcoin?
----------------

Tealcoin is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. Tealcoin uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Tealcoin Core is the name of open source
software which enables the use of this currency.

Tealcoin started in March 2018 as a variant of Litecoin using Scrypt as the Proof-of-Work (PoW) hash algorithm.

- Max Money 20,000,000
- Total Supply 126,140,000
- Subsidy halves every 12,614,000 blocks which will occur approximately every 2 years.
- Block time change to 5 seconds
- Re-targeting every 48 blocks approximately every 4 minutes.
- 5 coins reward
- Make with a very low mining difficulty

For more information, as well as an immediately useable, binary version of
the Tealcoin Core software, see [https://tealcoin-project.io](https://tealcoin-project.io).

License
-------

Tealcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Tealcoin periodically.

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.
