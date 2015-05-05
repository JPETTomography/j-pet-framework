# J-PET SCOPE READER MANUAL

___Document produced on: 29.04.2015___

## Installation:

## Running:

## Preparing analysis:

I order to run analysis creating configuration file is required. Config is parsed using boost::property\_tree library, so it can be written in one of following formats:
+  `.info` dedicated for boost::property\_tree library, [more...](http://www.boost.org/doc/libs/1_58_0/doc/html/property_tree/parsers.html#property_tree.parsers.info_parser)
+  `.json` JavaScript Open Notation, [more...](http://www.boost.org/doc/libs/1_58_0/doc/html/property_tree/parsers.html#property_tree.parsers.json_parser)
+  `.xml`  Extensible Markup Language, [more...](http://www.boost.org/doc/libs/1_58_0/doc/html/property_tree/parsers.html#property_tree.parsers.xml_parser)

**Note!**
Due to configuration structure `.ini` files are not supported.

### Writing configuration file

#### .info format

Configuration structure in .info format:
~~~
config1_name
{ 
    bslot1
    {
        id bslot1_id(int)
        active bslot1_is_active(true/false)
        name bslot1_name(text)
        theta bslot1_theta(float)
        frame bslot1_frame(int)
    }
    bslot2
    {
        ...
    }
    pm1
    {
        id pm1_id(int)
	prefix pm1_prefix(text)
    }
    ...
    pm4
    {
       ... 
    }
    scin1
    {
        id scin1_id(int)
    }
    scin2
    {
        ...
    }
    location data_files_location(text)
    collimator
    {
        positions position(int)
        positions "position_begin(int) position_end(int)"
        positions "position_begin(int) position_end(int) step(int)"
	...
    }
}
config2_name
{
    ...
}
~~~
Exmaple configuration located at `workdir/ScopeReaderExample/cfg/example.info` .

#### .json format

Configuration structure in .json format:
~~~
{
    "config1_name":
    {
        "bslot1":
        {
            "id": "bslot1_id(int)",
            "active": "bslot1_is_active(true/false)",
            "name": "bslot1_name(text)",
            "theta": "bslot1_theta(float)",
            "frame": "bslot1_frame(int)"
        },
        "bslot2":
        {
            ...
        },
        "pm1":
        {
            "id": "pm1_id(int)",
            "prefix": "pm1_prefix(text)"
        },
        ...
        "pm4":
        {
            ...
        },
        "scin1":
        {
            "id": "scin1_id(int)"
        },
        "scin2":
        {
            ...
        },
        "location": "data_files_location(text)",
        "collimator":
        [
            {
                "positions": "position(int)"
            },
            {
                "positions": "position_begin(int) position_end(int)"
            },
            {
                "positions": "position_begin(int) position_end(int) step(int)"
            }
	    ...
        ]
    },
    "config2_name":
    {
        ...
    }
}
~~~
Exmaple configuration located at `workdir/ScopeReaderExample/cfg/example.json` .

#### .xml format

Configuration structure in .xml format:
~~~
<?xml version="1.0" encoding="utf-8"?>
<config1_name>
	<bslot1>
		<id>bslot1_id(int)</id>
		<active>bslot1_is_active(true/false)</active>
		<name>bslot1_name(text)</name>
		<theta>bslot1_theta(float)</theta>
		<frame>bslot1_frame(int)</frame>
	</bslot1>
	<bslot2>
		...
	</bslot2>
	<pm1>
		<id>pm1_id(int)</id>
		<prefix>pm1_prefix(text)</prefix>
	</pm1>
	...
	<pm4>
		...
	</pm4>
	<scin1>
		<id>scin1_id(int)</id>
	</scin1>
	<scin2>
		...
	</scin2>
	<location>data_files_location(text)</location>
	<collimator>
		<positions>position(int)</positions>
		<positions>position_begin(int) position_end(int)</positions>
		<positions>position_begin(int) position_end(int) step(int)</positions>
		...
	</collimator>
</config1_name>
<config2_name>
  ...
</config2_name>
~~~
Exmaple configuration located at `workdir/ScopeReaderExample/cfg/example.xml` .

