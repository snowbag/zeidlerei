# User documentation

The purpose of **Zeidlerei** is to simulate unconventional models like networks of evolutionary processors (NEPs) and P systems.

The current release is an alpha version zeidlerei-0.1. A binary version for Windows can be found in `release` folder.

## Components

Currently Zeidlerei is a simulator for NEPs. This means that you can create:
- evolutionary processors with
-- evolutionary rules (insertion, deletion, substitution with the position of left and right),
-- input and output filters (no filter, length filter, regular expression filter and permitting/forbidding context) and
-- clustering method (the smallest cluster is chosen for communication),
- you can create undirected edges between them and
- you can create multiple halting conditions for the simulation (maximum number of steps, two consecutive configurations are the same, an output node becomes non empty).

## How to use

You can specify a NEP and a configuration in an XML format. Only NEP is required as in the NEP definition there is an initial configuration described. Then you can run your simulation with `zeidlerei-0.1` using this command:

```> ./zeidlerei-0.1 nep.xml```

This will print the halting configuration to the standard output after the simulation is executed (meaning a halting condition became true).

You can also use some options and flags:
| Options | Parameter | Description |
|--------|-----------|-------------|
|-c | filename | existing configuration file in XML format; the simulation will start from the last configuration described in this file |
|&#8209;&#8209;outputall | | prints the configuration of all steps (not just the halting step)
|-o | filename | an output file for the halting configuration if &#8209;&#8209;outputall is not set; for the configuration of all steps, if &#8209;&#8209;outputall is set; if the file already exists, it is overwritten |
|-s| string | if an output file is set, this string will be used as string separator (default: `,`)

Example usage of all options:
```> ./zeidlerei-0.1 nep.xml -c conf.xml -o result.xml -s ';' --outputall```

**Keep in mind that if your simulation has many steps, printing every configuration will have a large effect on the run time.**

If any of the XML files is not valid, you can get an error code from our external component, TinyXML. Here are some common errors:
| Error code | Definition |
|------------:|------------|
| 3 | file not found |
| 4 | file could not be opened |
| 5 | file read error |
| 7 | error while parsing attribute (e.g. no value) |
| 13 | empty document |
| 14 | mismatched element (a closing tag is missing)|


## XML description of a NEP
The elements are defined between `<network></network>`tags. There are three required parts:
- processors `<processors></processors>`
- graph `<graph></graph>`
- halting conditions `<halting-conditions></halting-conditions>`

*Processors*
For all processors you can define a word-separator character, which will be used to split the axioms. The default character is comma(`,`). This character is an attribute of the processors tag: `<processors word-separator=";">`

A processor has a description between `<node id="..."></node>`. An identifier can be any string (even only numbers). A node also can have an initial content defined in the `content` attribute. This must be a list of words, separated by the word separator defined in the `processors` tag (default is comma). If the `content` is not defined, the processor is initially empty.

The rules of a processor must be of the same type (insertion, deletion or substitution), but the rules can have different positions (left, right, any). The rules are listed between `<rules type="[insertion|deletion|substitution]"></rules>` with the following format: `<rule position="[left|right|any]" from="..." to="..." />`.  Insertion rules do not have `from"` defined and deletion rules do not have "to" defined (as it is lambda). The `from` and `to` attributes can be characters or strings.

The input and output filter of a processor can be a length filter (with a rule of "<integer", "=integer" or ">integer"), a regular expression filter (with a rule of a valid C++ regular expression) or a free filter (sends all words). The definition of an inputfilter is the following: `<inputfilter type="[length|regex|free]" rule="[[<|=|>]int|regex]" />`. The filters are not required tags, if you do not define them, the default is free filter. For free filter you do not have to specify any rules.

An other optional property of  a processor is a clustering method. If you use clustering in a node, only the words in the smallest cluster will be used in the communication. The currently available clustering methods are k-means and hierarchical bottom up clustering with k clusters. You can also define a maximum number of steps for k-means as an optional attribute. The definition of a clustering method is the following: `<clustering method="[k-means|bottom-up]" number="int" max-steps="int" />`

*Graph*
In the graph you must use the same ids as in the processor definitions. Using other ids will result in an error. For defining an edge you must use the `edge` tag with `v1` and `v2` attributes. Edges are bidirectional, so it is the same if you define `v1="1" v2="2"` or `v1="2" v2="1"`, therefore it is recommended to give the ids in alphabetical or numerical order. The format of an edge: `<edge v1="processor1Id" v2="processor2Id" />`

*Halting Conditions*
You can define multiple halting conditions for a simulation. The simulator will halt if any of them become true.

The simulation can stop
- after a given number of steps: `<condition type="MaximumNumberOfSteps" value="int" />`
- after two consecutive evolutionary/communication steps have the same configuration: `<condition type="ConsecutiveConfigurations" />`
- after a given node becomes non empty: `<condition type="NonEmptyNode" value="processorId" />` (you must use an id specified in the processor definitions).


If the XML file contains other valid XML elements that are not defined in this manual, they are ignored. This means that you can also use comments in the proper XML format.


The alphabet of your NEP is implicitly defined by your axioms and rules, therefore no illegal words can be given as input and no illegal words can be generated. If you use regular expression filter, don't use special characters as alphabet that are used in regular expressions.

An example description:
```
<?xml version="1.0"?>
<network>
	<halting-conditions>
		<condition type="MaximumNumberOfSteps" value="8"/>
		<condition type="ConsecutiveConfigurations"/>
		<condition type="NonEmptyNode" value="2"/>
	</halting-conditions>

	<processors word-separator=",">
		<node id="0" content="ab,cd">
			<rules type="insertion">
				<rule position="left" to="a" />
				<rule position="right" to="bb" /> 
			</rules>
			<inputfilter type="length" rule="<3" />
			<outputfilter type="regex" rule="a*..." />
		</node>
		<node id="1" content="a">
			<rules type="deletion">
				<rule position="right" from="a" />
			</rules>
			<inputfilter type="free" />
			<outputfilter type="free" />
		</node>
		<node id="2">
		</node>
		<node id="3">
			<rules type="substitution">
				<rule position="left" from="b" to="d" />
			</rules>
			<inputfilter type="free" />
			<outputfilter type="free" />
		</node>
	</processors>

	<graph>
		<edge v1="0" v2="1" />
		<edge v1="0" v2="2" />
	</graph>
</network>
```
## XML description of a configuration
The elements are defined between `<configuration><processors></processors></configuration>` tags. You do not have to describe the content of all nodes, the omitted ones will be empty.

The description of a node is similar to the NEP description: you have to use the same ids and the content must be separated by the word separator. You can change the default word separator (comma `,`) as an attribute of the configuration. You can omit the content tag if the node is empty. A node configuration description is the following: `<node id="processorId" content="words separated by word-separator" />`

You can also define if a configuration is initial, or is it after an evolutionary or communication step. This is also an attribute of the configuration:
`<configuration type="[initial|evolution|communication]" word-separator="string">...</configuration>`. If you do not specify it, the default configuration type is initial.

**The simulator does not investigate if a loaded configuration is reachable from the initial network.**

A file can have multiple configurations defined after each other (without a group tag), then in the simulation the last configuration will be used as starting point.

An example configuration file:
```
<configuration type="initial" word-separator=",">
	<processors>
		<node id="0" content="ab,cd" />
		<node id="1" />
		<node id="2" content="a" />
	</processors>
</configuration>
<configuration type="evolution" word-separator=",">
    <processors>
        <node id="0" content="aab,abbb,acd,cdbb"/>
        <node id="1" content=""/>
        <node id="2" content=""/>
        <node id="3" content=""/>
    </processors>
</configuration>
```