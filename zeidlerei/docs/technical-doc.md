# Technical documentation

The purpose of **Zeidlerei** is to simulate unconventional models like networks of evolutionary processors (NEPs) and P systems.

The current release is an alpha version zeidlerei-0.1. A binary version for Windows can be found in `release` folder.

## Components

![Class diagram](https://github.com/snowbag/zeidlerei/blob/demo_environment/zeidlerei/docs/figures/class_diagram.png)

### Word
The base component of the simulator is 'word' which is currently a simple string, but later we could use unordered list of symbols or even pictures as words. It has one complex function: calculateEditDistance that calculates the Levenshtein distance between two words. This implementation is from [Wikipedia](http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B). 

### Multiset
A multiset of words is actually a map with words as keys and integers as counters. A word must be in the multiset at least once to have a key.

There are some basic functionalities defined: you can add a word (with any positive counter), remove a word (same), remove everything, and add all words from an other multiset. You can also get the current size of the multiset (even the number of unique elements).

### Rules
Rules are made of a left and a right hand side (e.g. `a->b` means that an `a` is rewritten to `b` in the word). The left hand side of insertion rules is default lambda (empty symbol) and the right hand side of deletion rules is also default lambda. This way insertion rules are a substitution rule, where "nothing" is replaced by "something" and deletion rules replace "something" with "nothing".

A rule can be applied if the left hand side is found in the given word. This way insertion rules are always applicable. Deletion and substitution are more restricted.

A rule is also have a position where it is applied. A left substitution rule `a->b` can be applied on `ab`, but not on `ba`. The `any` positioned rules are not yet integrated in the simulator. 

The result of rule application is a vector of words as there are rules that can be applied in more than one way. For example if we have a deletion rule for `a`, the word `aba` can become `ba` or `ab` in one step.

### Filters
Filters have only one main function: `apply(Word)`. This returns if the given word can be sent (output filter)/received (input filter) or not. There is a general filter, `FreeFilter` which allows every word. The others are `LengthFilter` for word lengths, `RegexFilter` for the format of words and `PermitForbidFilter` also for the format.

`LengthFilter` has a comparison type (less than, equals or greater than) and an integer as parameters. This way we can separate words by their lengths.

`RegexFilter` uses the `regex` from the C++ standard library. If the expression matches the word, it is allowed in the communication.

`PermitForbidFilter` has not been included in the binary yet.

### HaltingConditions
Halting Conditions are calculated on the network after every step and persist if they become true. There are three types: MaximumSteps, NonEmptyNode, SameConfiguration.

`MaximumSteps` simply counts the number of executed steps.

`NonEmptyNode` gets a Processor reference in its constructor and checks it after every step if the content of it is the empty multiset.

`SameConfiguration` stores two configurations: one for communication and one for evolution. After every step it changes which configuration to check: after initialization it stores an evolutionary configuration, then a communication, then an evolutionary again, etc.

### Processor
Processors can evolve their words, collect their output for communication, send it and receive words from their neighbours. 

The evolution take multiple steps: first we gather those words that have applicable rules and then apply the rules in every possible way. This way we can get many new words. On the other hand, we keep those words that were not appropriate for any rules and add them to the new words. We drop those words that were used in at least one rule application (unless they are created again from an other word).

The communication is triggered from outside, they do not check if their words are sent to their neighbours or to others, that is the task of the simulator:
- firstly, it asks the processors to gather the words that go through their output filters,
- then sends the words from one neighbour to the other.

This two steps is necessary, because we do not want to send a newly gained word immediately, therefore we have to separate the "old" words from the "new" ones.

The processors also do not check if the evolve and communication functions are altering steps.

Processor class has a `Configuration` defined that stores the id of the processor and a snapshot of its content.


### Clustering
Clustering is in the experimental phase of the simulator. We are able to create clusters from the content of a processor and then according to these groups we can send those elements that create the smallest cluster. In the future we want to have rules that combine words inside a cluster or words between clusters, and also other filtering methods like sending those words that are too far from the others.

There are two types of clustering implemented based on edit distance. First is k-means which randomly select k clustroids and then add the other points to the closest cluster. In the next turn we calculate in these clusters a new clustroid: which word is the closest to the others. Then again add all other points to the closest cluster. We repeat this until the maximum number of steps is reached or the clustroids do not change. *(As we cannot have an average point in this method, it is actually a k-medoid clustering.)*

The other is a hierarchical bottom up clustering. In the first step all words are a separate cluster. Then in every step we merge the two closest cluster. This closeness can be calculated by many methods (closest/furthest points of the clusters), we use the method of calculating the distance between the clustroids. We repeat these merging until the desired number of clusters is present (or we reach the maximum number of steps).

### Network
Network is a simple structure for storing Processors and Edges. It does not have any complex functions: we can list the processors, the neighbours of a processor or check if an edge is present.

Like the processor, the configuration of a Network can be exported as well. It contains the Configuration of all nodes in the network.

### Simulator

Simulator is the soul of this software: it controls the execution of steps to be in order and handles the halting conditions, checking if any of them become true after every step.

There are two execution modes: one normal and one with logging all steps. The latter is slower, because it stores a snapshot after every step (which type of step was executed, what was the configuration of the network), but it makes the simulation traceable.

### XmlNetworkConverter

The XML configuration is partially based on [1]. It uses TinyXML-2 that is a C++ XML parser. In the User documentation you can find the proper description of a NEP.

This is the most complex class in the software, because it has to build the whole system based on XML tags. It has some basic error checking, but it can be improved with better exception messages.

### Tests

There are unit tests defined for multisets, rules, filters, processors, networks and simulators. These tests provide that after some refactoring the functionalities remain the same: they check the basic functions of these classes.

## References
[1] E. del  Rosal. *Real  life  applications  of  bio-inspired  computing  models: EAP and NEPs.* PhD thesis, 2013.
