{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 6,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 40.0, 82.0, 1359.0, 639.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 222.5, 885.0, 45.0, 45.0 ]
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-58",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 380.0, 529.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-56",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 380.0, 439.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-54",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 461.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-46",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 523.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 221.0, 702.0, 48.0, 136.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"autosave" : 1,
					"id" : "obj-19",
					"inletInfo" : 					{
						"IOInfo" : [  ]
					}
,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "out1",
								"comment" : ""
							}
 ]
					}
,
					"outlettype" : [ "signal", "list" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 6,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "rnbo",
						"rect" : [ 34.0, 76.0, 973.0, 653.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Lato",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"assistshowspatchername" : 0,
						"title" : "untitled",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 763.0, 275.0, 212.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "thrusterspeed",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param thrusterspeed @min 1 @max 15",
									"varname" : "thrusterspeed"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 639.0, 400.0, 168.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "shields[1]",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param shields @min 1 @max 4",
									"varname" : "shields[1]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 6,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "rnbo",
										"rect" : [ 546.0, 146.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Lato",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"assistshowspatchername" : 0,
										"title" : "shields",
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-29",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 329.0, 359.0, 150.0, 21.0 ],
													"text" : "4 voices"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-27",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 487.0, 359.0, 150.0, 21.0 ],
													"text" : "3 voices"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-25",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 580.0, 382.0, 150.0, 21.0 ],
													"text" : "2 voices"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-23",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 469.0, 332.0, 31.0, 23.0 ],
													"rnbo_classname" : "/~",
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "/~_obj-23",
													"text" : "/~ 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-22",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 580.0, 346.0, 31.0, 23.0 ],
													"rnbo_classname" : "/~",
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "/~_obj-22",
													"text" : "/~ 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-20",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 90.0, 140.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 4,
													"rnbo_uniqueid" : "in_obj-20",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 3",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 3"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-19",
													"maxclass" : "newobj",
													"numinlets" : 5,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 138.0, 435.0, 67.0, 23.0 ],
													"rnbo_classname" : "selector~",
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "selector~_obj-19",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"onoff" : 															{
																"attrOrProp" : 1,
																"digest" : "Turns Input Off or Routes to Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "1"
															}
,
															"out" : 															{
																"attrOrProp" : 1,
																"digest" : "Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in2" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 2",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in3" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 3",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in4" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 4",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"choices" : 															{
																"attrOrProp" : 2,
																"digest" : "Number of inputs",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1"
															}

														}
,
														"inputs" : [ 															{
																"name" : "onoff",
																"type" : "auto",
																"digest" : "Turns Input Off or Routes to Output",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "Input 1",
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : "signal",
																"digest" : "Input 2",
																"docked" : 0
															}
, 															{
																"name" : "in3",
																"type" : "signal",
																"digest" : "Input 3",
																"docked" : 0
															}
, 															{
																"name" : "in4",
																"type" : "signal",
																"digest" : "Input 4",
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out",
																"type" : "signal",
																"digest" : "Output",
																"docked" : 0
															}
 ],
														"helpname" : "selector~",
														"aliasOf" : "selector~",
														"classname" : "selector~",
														"operator" : 0,
														"versionId" : -990475044,
														"changesPatcherIO" : 0
													}
,
													"text" : "selector~ 4"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-18",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 88.0, 322.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "generator",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 305.0, 70.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "in_obj-1",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 2",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 2"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-7",
																	"maxclass" : "newobj",
																	"numinlets" : 5,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 159.0, 214.0, 67.0, 23.0 ],
																	"rnbo_classname" : "selector~",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "selector~_obj-7",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"onoff" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Turns Input Off or Routes to Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "number",
																				"defaultValue" : "1"
																			}
,
																			"out" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in2" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 2",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in3" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 3",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in4" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 4",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"choices" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Number of inputs",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "1"
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "onoff",
																				"type" : "auto",
																				"digest" : "Turns Input Off or Routes to Output",
																				"hot" : 1,
																				"docked" : 0
																			}
, 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "Input 1",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in2",
																				"type" : "signal",
																				"digest" : "Input 2",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in3",
																				"type" : "signal",
																				"digest" : "Input 3",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in4",
																				"type" : "signal",
																				"digest" : "Input 4",
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out",
																				"type" : "signal",
																				"digest" : "Output",
																				"docked" : 0
																			}
 ],
																		"helpname" : "selector~",
																		"aliasOf" : "selector~",
																		"classname" : "selector~",
																		"operator" : 0,
																		"versionId" : -990475044,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "selector~ 4"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-5",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 380.0, 150.0, 786.0, 488.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "triangle",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 328.0, 235.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-4",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 326.0, 326.0, 55.0, 23.0 ],
																					"rnbo_classname" : "triangle~",
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "triangle~_obj-4",
																					"text" : "triangle~"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 336.0, 388.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 328.0, 282.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-4", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-4", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 275.0, 155.0, 58.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "triangle",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p triangle",
																	"varname" : "triangle"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-4",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 708.0, 183.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "phasor",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 334.0, 214.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 194.0, 155.0, 54.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 2,
																	"rnbo_uniqueid" : "phasor",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p phasor",
																	"varname" : "phasor"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-8",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 372.0, 200.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "sin",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 350.0, 177.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 2,
																					"outlettype" : [ "signal", "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 42.0, 23.0 ],
																					"rnbo_classname" : "cycle~",
																					"rnbo_extra_attributes" : 																					{
																						"buffername" : "RNBODefaultSinus",
																						"index" : "freq",
																						"interp" : "linear"
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "cycle~_obj-1",
																					"text" : "cycle~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 183.0, 124.0, 33.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 3,
																	"rnbo_uniqueid" : "sin",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p sin",
																	"varname" : "sin"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-45",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 159.0, 64.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 2,
																	"rnbo_uniqueid" : "in_obj-45",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-46",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 159.0, 297.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-46",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-4", 0 ],
																	"order" : 1,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-5", 0 ],
																	"order" : 0,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-8", 0 ],
																	"order" : 2,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 3 ],
																	"midpoints" : [ 203.5, 208.0, 204.5, 208.0 ],
																	"source" : [ "obj-4", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 0 ],
																	"source" : [ "obj-45", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 4 ],
																	"midpoints" : [ 284.5, 199.0, 216.5, 199.0 ],
																	"source" : [ "obj-5", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-46", 0 ],
																	"source" : [ "obj-7", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 2 ],
																	"midpoints" : [ 192.5, 148.0, 180.0, 148.0, 180.0, 199.0, 192.5, 199.0 ],
																	"source" : [ "obj-8", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 608.0, 243.0, 69.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 8,
													"rnbo_uniqueid" : "generator[2]",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in2",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p generator",
													"varname" : "generator[2]"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-17",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 88.0, 322.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "generator",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 305.0, 70.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "in_obj-1",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 2",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 2"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-7",
																	"maxclass" : "newobj",
																	"numinlets" : 5,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 159.0, 214.0, 67.0, 23.0 ],
																	"rnbo_classname" : "selector~",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "selector~_obj-7",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"onoff" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Turns Input Off or Routes to Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "number",
																				"defaultValue" : "1"
																			}
,
																			"out" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in2" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 2",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in3" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 3",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in4" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 4",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"choices" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Number of inputs",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "1"
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "onoff",
																				"type" : "auto",
																				"digest" : "Turns Input Off or Routes to Output",
																				"hot" : 1,
																				"docked" : 0
																			}
, 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "Input 1",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in2",
																				"type" : "signal",
																				"digest" : "Input 2",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in3",
																				"type" : "signal",
																				"digest" : "Input 3",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in4",
																				"type" : "signal",
																				"digest" : "Input 4",
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out",
																				"type" : "signal",
																				"digest" : "Output",
																				"docked" : 0
																			}
 ],
																		"helpname" : "selector~",
																		"aliasOf" : "selector~",
																		"classname" : "selector~",
																		"operator" : 0,
																		"versionId" : -990475044,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "selector~ 4"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-5",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 380.0, 150.0, 786.0, 488.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "triangle",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 328.0, 235.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-4",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 326.0, 326.0, 55.0, 23.0 ],
																					"rnbo_classname" : "triangle~",
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "triangle~_obj-4",
																					"text" : "triangle~"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 336.0, 388.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 328.0, 282.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-4", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-4", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 275.0, 155.0, 58.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "triangle",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p triangle",
																	"varname" : "triangle"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-4",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 708.0, 183.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "phasor",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 334.0, 214.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 194.0, 155.0, 54.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 2,
																	"rnbo_uniqueid" : "phasor",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p phasor",
																	"varname" : "phasor"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-8",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 372.0, 200.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "sin",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 350.0, 177.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 2,
																					"outlettype" : [ "signal", "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 42.0, 23.0 ],
																					"rnbo_classname" : "cycle~",
																					"rnbo_extra_attributes" : 																					{
																						"buffername" : "RNBODefaultSinus",
																						"index" : "freq",
																						"interp" : "linear"
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "cycle~_obj-1",
																					"text" : "cycle~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 183.0, 124.0, 33.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 3,
																	"rnbo_uniqueid" : "sin",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p sin",
																	"varname" : "sin"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-45",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 159.0, 64.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 2,
																	"rnbo_uniqueid" : "in_obj-45",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-46",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 159.0, 297.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-46",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-4", 0 ],
																	"order" : 1,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-5", 0 ],
																	"order" : 0,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-8", 0 ],
																	"order" : 2,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 3 ],
																	"midpoints" : [ 203.5, 208.0, 204.5, 208.0 ],
																	"source" : [ "obj-4", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 0 ],
																	"source" : [ "obj-45", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 4 ],
																	"midpoints" : [ 284.5, 199.0, 216.5, 199.0 ],
																	"source" : [ "obj-5", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-46", 0 ],
																	"source" : [ "obj-7", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 2 ],
																	"midpoints" : [ 192.5, 148.0, 180.0, 148.0, 180.0, 199.0, 192.5, 199.0 ],
																	"source" : [ "obj-8", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 496.0, 243.0, 69.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 7,
													"rnbo_uniqueid" : "generator[1]",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in2",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p generator",
													"varname" : "generator[1]"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-16",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 336.0, 327.0, 31.0, 23.0 ],
													"rnbo_classname" : "/~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "/~_obj-16",
													"text" : "/~ 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-13",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 598.0, 151.0, 29.5, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 5,
													"rnbo_uniqueid" : "*_obj-13",
													"text" : "* 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-12",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 532.0, 151.0, 33.0, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 4,
													"rnbo_uniqueid" : "*_obj-12",
													"text" : "* 1.5"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-11",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 450.0, 151.0, 40.0, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "*_obj-11",
													"text" : "* 1.25"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-10",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 449.0, 84.0, 42.0, 23.0 ],
													"rnbo_classname" : "r",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "r_obj-10",
													"text" : "r pitch"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-9",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 198.0, 12.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "in_obj-9",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 2",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-6",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 88.0, 322.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "generator",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 305.0, 70.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 4,
																	"rnbo_uniqueid" : "in_obj-1",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 2",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 2"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-7",
																	"maxclass" : "newobj",
																	"numinlets" : 5,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 159.0, 214.0, 67.0, 23.0 ],
																	"rnbo_classname" : "selector~",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "selector~_obj-7",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"onoff" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Turns Input Off or Routes to Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "number",
																				"defaultValue" : "1"
																			}
,
																			"out" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Output",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in2" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 2",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in3" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 3",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"in4" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "Input 4",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"choices" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Number of inputs",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "1"
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "onoff",
																				"type" : "auto",
																				"digest" : "Turns Input Off or Routes to Output",
																				"hot" : 1,
																				"docked" : 0
																			}
, 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "Input 1",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in2",
																				"type" : "signal",
																				"digest" : "Input 2",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in3",
																				"type" : "signal",
																				"digest" : "Input 3",
																				"docked" : 0
																			}
, 																			{
																				"name" : "in4",
																				"type" : "signal",
																				"digest" : "Input 4",
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out",
																				"type" : "signal",
																				"digest" : "Output",
																				"docked" : 0
																			}
 ],
																		"helpname" : "selector~",
																		"aliasOf" : "selector~",
																		"classname" : "selector~",
																		"operator" : 0,
																		"versionId" : -990475044,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "selector~ 4"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-5",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 380.0, 150.0, 786.0, 488.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "triangle",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 328.0, 235.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-4",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 326.0, 326.0, 55.0, 23.0 ],
																					"rnbo_classname" : "triangle~",
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "triangle~_obj-4",
																					"text" : "triangle~"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 336.0, 388.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 328.0, 282.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-4", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-4", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 275.0, 155.0, 58.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "triangle",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p triangle",
																	"varname" : "triangle"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-4",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 708.0, 183.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "phasor",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 334.0, 214.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 1,
																					"outlettype" : [ "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 51.0, 23.0 ],
																					"rnbo_classname" : "phasor~",
																					"rnbo_extra_attributes" : 																					{
																						"lock" : 0.0
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "phasor~_obj-1",
																					"text" : "phasor~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 194.0, 155.0, 54.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 2,
																	"rnbo_uniqueid" : "phasor",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p phasor",
																	"varname" : "phasor"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-8",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patcher" : 																	{
																		"fileversion" : 1,
																		"appversion" : 																		{
																			"major" : 8,
																			"minor" : 6,
																			"revision" : 4,
																			"architecture" : "x64",
																			"modernui" : 1
																		}
,
																		"classnamespace" : "rnbo",
																		"rect" : [ 372.0, 200.0, 640.0, 480.0 ],
																		"bglocked" : 0,
																		"openinpresentation" : 0,
																		"default_fontsize" : 12.0,
																		"default_fontface" : 0,
																		"default_fontname" : "Lato",
																		"gridonopen" : 1,
																		"gridsize" : [ 15.0, 15.0 ],
																		"gridsnaponopen" : 1,
																		"objectsnaponopen" : 1,
																		"statusbarvisible" : 2,
																		"toolbarvisible" : 1,
																		"lefttoolbarpinned" : 0,
																		"toptoolbarpinned" : 0,
																		"righttoolbarpinned" : 0,
																		"bottomtoolbarpinned" : 0,
																		"toolbars_unpinned_last_save" : 0,
																		"tallnewobj" : 0,
																		"boxanimatetime" : 200,
																		"enablehscroll" : 1,
																		"enablevscroll" : 1,
																		"devicewidth" : 0.0,
																		"description" : "",
																		"digest" : "",
																		"tags" : "",
																		"style" : "",
																		"subpatcher_template" : "",
																		"assistshowspatchername" : 0,
																		"title" : "sin",
																		"boxes" : [ 																			{
																				"box" : 																				{
																					"id" : "obj-3",
																					"maxclass" : "newobj",
																					"numinlets" : 0,
																					"numoutlets" : 1,
																					"outlettype" : [ "" ],
																					"patching_rect" : [ 350.0, 177.0, 28.0, 23.0 ],
																					"rnbo_classname" : "in",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "in_obj-3",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "inlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [  ],
																						"outputs" : [ 																							{
																								"name" : "out1",
																								"type" : [ "bang", "number", "list" ],
																								"digest" : "value from inlet with index 2",
																								"displayName" : "",
																								"docked" : 0
																							}
 ],
																						"helpname" : "in",
																						"aliasOf" : "in",
																						"classname" : "in",
																						"operator" : 0,
																						"versionId" : 1219109108,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "in 2"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-2",
																					"maxclass" : "newobj",
																					"numinlets" : 1,
																					"numoutlets" : 0,
																					"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																					"rnbo_classname" : "out~",
																					"rnbo_extra_attributes" : 																					{
																						"comment" : "",
																						"meta" : ""
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "out~_obj-2",
																					"rnboinfo" : 																					{
																						"needsInstanceInfo" : 1,
																						"argnames" : 																						{
																							"in1" : 																							{
																								"attrOrProp" : 1,
																								"digest" : "signal sent to outlet with index 1",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 0,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"inlet" : 1,
																								"type" : "signal"
																							}
,
																							"index" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "outlet number",
																								"defaultarg" : 1,
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "number",
																								"mandatory" : 1
																							}
,
																							"comment" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "mouse over comment",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol"
																							}
,
																							"meta" : 																							{
																								"attrOrProp" : 2,
																								"digest" : "A JSON formatted string containing metadata for use by the exported code",
																								"isalias" : 0,
																								"aliases" : [  ],
																								"settable" : 1,
																								"attachable" : 0,
																								"isparam" : 0,
																								"deprecated" : 0,
																								"type" : "symbol",
																								"defaultValue" : "",
																								"label" : "Metadata",
																								"displayorder" : 3
																							}

																						}
,
																						"inputs" : [ 																							{
																								"name" : "in1",
																								"type" : "signal",
																								"digest" : "signal sent to outlet with index 1",
																								"displayName" : "",
																								"hot" : 1,
																								"docked" : 0
																							}
 ],
																						"outputs" : [  ],
																						"helpname" : "out~",
																						"aliasOf" : "out~",
																						"classname" : "out~",
																						"operator" : 0,
																						"versionId" : 374499139,
																						"changesPatcherIO" : 1
																					}
,
																					"text" : "out~ 1"
																				}

																			}
, 																			{
																				"box" : 																				{
																					"id" : "obj-1",
																					"maxclass" : "newobj",
																					"numinlets" : 2,
																					"numoutlets" : 2,
																					"outlettype" : [ "signal", "signal" ],
																					"patching_rect" : [ 334.0, 261.0, 42.0, 23.0 ],
																					"rnbo_classname" : "cycle~",
																					"rnbo_extra_attributes" : 																					{
																						"buffername" : "RNBODefaultSinus",
																						"index" : "freq",
																						"interp" : "linear"
																					}
,
																					"rnbo_serial" : 1,
																					"rnbo_uniqueid" : "cycle~_obj-1",
																					"text" : "cycle~"
																				}

																			}
 ],
																		"lines" : [ 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-2", 0 ],
																					"source" : [ "obj-1", 0 ]
																				}

																			}
, 																			{
																				"patchline" : 																				{
																					"destination" : [ "obj-1", 0 ],
																					"source" : [ "obj-3", 0 ]
																				}

																			}
 ],
																		"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
																		"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
																		"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
																		"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
																		"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
																		"bgfillcolor_type" : "color",
																		"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
																		"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
																		"bgfillcolor_angle" : 270.0,
																		"bgfillcolor_proportion" : 0.39,
																		"bgfillcolor_autogradient" : 0.0
																	}
,
																	"patching_rect" : [ 183.0, 124.0, 33.0, 23.0 ],
																	"rnbo_classname" : "p",
																	"rnbo_extra_attributes" : 																	{
																		"receivemode" : "local",
																		"polyphony" : -1.0,
																		"args" : [  ],
																		"voicecontrol" : "simple",
																		"notecontroller" : 0,
																		"exposevoiceparams" : 0
																	}
,
																	"rnbo_serial" : 3,
																	"rnbo_uniqueid" : "sin",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"target" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "target",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "0"
																			}
,
																			"mute" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "mute",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"__probingout1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "__probingout1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "signal"
																			}
,
																			"out1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "out1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"outlet" : 1,
																				"type" : "signal"
																			}
,
																			"voicestatus" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "voicestatus",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "list"
																			}
,
																			"activevoices" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "activevoices",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 1,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number"
																			}
,
																			"polyphony" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Polyphony of the subpatcher.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"defaultValue" : "-1"
																			}
,
																			"exposevoiceparams" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "bool",
																				"defaultValue" : "false"
																			}
,
																			"title" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Title of the subpatcher",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"file" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "rnbo file to load",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"voicecontrol" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "simple", "user" ],
																				"type" : "enum",
																				"defaultValue" : "simple"
																			}
,
																			"notecontroller" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "DEPRECATED. Use voicecontrol instead.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}
,
																			"receivemode" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"enum" : [ "local", "compensated" ],
																				"type" : "enum",
																				"defaultValue" : "local"
																			}
,
																			"args" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"doNotShowInMaxInspector" : 1
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in2",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "in2",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : "signal",
																				"digest" : "out1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "patcher",
																		"aliasOf" : "rnbo",
																		"classname" : "p",
																		"operator" : 0,
																		"versionId" : 2039458657,
																		"changesPatcherIO" : 0
																	}
,
																	"text" : "p sin",
																	"varname" : "sin"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-45",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 159.0, 64.0, 28.0, 23.0 ],
																	"rnbo_classname" : "in",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 5,
																	"rnbo_uniqueid" : "in_obj-45",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "inlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [  ],
																		"outputs" : [ 																			{
																				"name" : "out1",
																				"type" : [ "bang", "number", "list" ],
																				"digest" : "value from inlet with index 1",
																				"displayName" : "",
																				"docked" : 0
																			}
 ],
																		"helpname" : "in",
																		"aliasOf" : "in",
																		"classname" : "in",
																		"operator" : 0,
																		"versionId" : 1219109108,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "in 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-46",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 159.0, 297.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-46",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-4", 0 ],
																	"order" : 1,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-5", 0 ],
																	"order" : 0,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-8", 0 ],
																	"order" : 2,
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 3 ],
																	"midpoints" : [ 203.5, 208.0, 204.5, 208.0 ],
																	"source" : [ "obj-4", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 0 ],
																	"source" : [ "obj-45", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 4 ],
																	"midpoints" : [ 284.5, 199.0, 216.5, 199.0 ],
																	"source" : [ "obj-5", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-46", 0 ],
																	"source" : [ "obj-7", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-7", 2 ],
																	"midpoints" : [ 192.5, 148.0, 180.0, 148.0, 180.0, 199.0, 192.5, 199.0 ],
																	"source" : [ "obj-8", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 401.0, 247.0, 69.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "generator",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : [ "bang", "number", "list" ],
																"digest" : "in2",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p generator",
													"varname" : "generator"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 131.0, 140.0, 35.0, 23.0 ],
													"rnbo_classname" : "in~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in~_obj-3",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal from inlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "signal from inlet with index 1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in~",
														"aliasOf" : "in~",
														"classname" : "in~",
														"operator" : 0,
														"versionId" : -176007711,
														"changesPatcherIO" : 1
													}
,
													"text" : "in~ 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 150.0, 497.0, 43.0, 23.0 ],
													"rnbo_classname" : "out~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "out~_obj-2",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal sent to outlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "signal sent to outlet with index 1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out~",
														"aliasOf" : "out~",
														"classname" : "out~",
														"operator" : 0,
														"versionId" : 374499139,
														"changesPatcherIO" : 1
													}
,
													"text" : "out~ 1"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-11", 0 ],
													"midpoints" : [ 458.5, 147.0, 459.5, 147.0 ],
													"order" : 2,
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-12", 0 ],
													"midpoints" : [ 458.5, 138.0, 541.5, 138.0 ],
													"order" : 1,
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-13", 0 ],
													"midpoints" : [ 458.5, 138.0, 607.5, 138.0 ],
													"order" : 0,
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 1 ],
													"midpoints" : [ 459.5, 177.0, 460.5, 177.0 ],
													"source" : [ "obj-11", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-17", 1 ],
													"midpoints" : [ 541.5, 228.0, 555.5, 228.0 ],
													"source" : [ "obj-12", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 1 ],
													"midpoints" : [ 607.5, 228.0, 667.5, 228.0 ],
													"source" : [ "obj-13", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 4 ],
													"midpoints" : [ 345.5, 351.0, 195.5, 351.0 ],
													"source" : [ "obj-16", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"midpoints" : [ 505.5, 312.0, 345.5, 312.0 ],
													"order" : 1,
													"source" : [ "obj-17", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-23", 0 ],
													"midpoints" : [ 505.5, 318.0, 478.5, 318.0 ],
													"order" : 0,
													"source" : [ "obj-17", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"midpoints" : [ 617.5, 312.0, 345.5, 312.0 ],
													"order" : 2,
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-22", 0 ],
													"midpoints" : [ 617.5, 333.0, 589.5, 333.0 ],
													"order" : 0,
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-23", 0 ],
													"midpoints" : [ 617.5, 318.0, 478.5, 318.0 ],
													"order" : 1,
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"midpoints" : [ 147.5, 484.0, 159.5, 484.0 ],
													"source" : [ "obj-19", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 0 ],
													"source" : [ "obj-20", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 2 ],
													"midpoints" : [ 589.5, 372.0, 576.0, 372.0, 576.0, 390.0, 171.5, 390.0 ],
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 3 ],
													"midpoints" : [ 478.5, 357.0, 480.0, 357.0, 480.0, 420.0, 183.5, 420.0 ],
													"source" : [ "obj-23", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"midpoints" : [ 140.5, 312.0, 345.5, 312.0 ],
													"order" : 2,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 1 ],
													"midpoints" : [ 140.5, 348.0, 159.5, 348.0 ],
													"order" : 3,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-22", 0 ],
													"midpoints" : [ 140.5, 312.0, 589.5, 312.0 ],
													"order" : 0,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-23", 0 ],
													"midpoints" : [ 140.5, 312.0, 478.5, 312.0 ],
													"order" : 1,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"midpoints" : [ 410.5, 312.0, 345.5, 312.0 ],
													"source" : [ "obj-6", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-17", 0 ],
													"midpoints" : [ 207.5, 228.0, 505.5, 228.0 ],
													"order" : 1,
													"source" : [ "obj-9", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 0 ],
													"midpoints" : [ 207.5, 228.0, 617.5, 228.0 ],
													"order" : 0,
													"source" : [ "obj-9", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 0 ],
													"midpoints" : [ 207.5, 234.0, 410.5, 234.0 ],
													"order" : 2,
													"source" : [ "obj-9", 0 ]
												}

											}
 ],
										"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
										"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
										"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
										"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
										"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
										"bgfillcolor_type" : "color",
										"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
										"bgfillcolor_angle" : 270.0,
										"bgfillcolor_proportion" : 0.39,
										"bgfillcolor_autogradient" : 0.0
									}
,
									"patching_rect" : [ 536.0, 452.0, 54.0, 23.0 ],
									"rnbo_classname" : "p",
									"rnbo_extra_attributes" : 									{
										"receivemode" : "local",
										"polyphony" : -1.0,
										"args" : [  ],
										"voicecontrol" : "simple",
										"notecontroller" : 0,
										"exposevoiceparams" : 0
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "shields",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"target_pitch_bang" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_bang",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"target_pitch_number" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_number",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"target_pitch_list" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_list",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"target" : 											{
												"attrOrProp" : 1,
												"digest" : "target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"mute" : 											{
												"attrOrProp" : 1,
												"digest" : "mute",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "in1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"__probingout1" : 											{
												"attrOrProp" : 1,
												"digest" : "__probingout1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "signal"
											}
,
											"out1" : 											{
												"attrOrProp" : 1,
												"digest" : "out1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"voicestatus" : 											{
												"attrOrProp" : 1,
												"digest" : "voicestatus",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"activevoices" : 											{
												"attrOrProp" : 1,
												"digest" : "activevoices",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"polyphony" : 											{
												"attrOrProp" : 2,
												"digest" : "Polyphony of the subpatcher.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"exposevoiceparams" : 											{
												"attrOrProp" : 2,
												"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"title" : 											{
												"attrOrProp" : 2,
												"digest" : "Title of the subpatcher",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "rnbo file to load",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"voicecontrol" : 											{
												"attrOrProp" : 2,
												"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "simple", "user" ],
												"type" : "enum",
												"defaultValue" : "simple"
											}
,
											"notecontroller" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED. Use voicecontrol instead.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"receivemode" : 											{
												"attrOrProp" : 2,
												"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "local", "compensated" ],
												"type" : "enum",
												"defaultValue" : "local"
											}
,
											"args" : 											{
												"attrOrProp" : 2,
												"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "in1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in2",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in2",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in3",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in3",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : "signal",
												"digest" : "out1",
												"displayName" : "",
												"docked" : 0
											}
 ],
										"helpname" : "patcher",
										"aliasOf" : "rnbo",
										"classname" : "p",
										"operator" : 0,
										"versionId" : 2039458657,
										"changesPatcherIO" : 0
									}
,
									"text" : "p shields",
									"varname" : "shields"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-51",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 6,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "rnbo",
										"rect" : [ 59.0, 107.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Lato",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"assistshowspatchername" : 0,
										"title" : "thruster",
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 332.0, 47.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "in_obj-1",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 3",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 3"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-18",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 115.0, 268.0, 29.5, 23.0 ],
													"rnbo_classname" : "*~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "*~_obj-18",
													"text" : "*~"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 278.0, 137.0, 29.5, 23.0 ],
													"rnbo_classname" : "+",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "+_obj-2",
													"text" : "+ 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-20",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 213.0, 100.0, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "number_obj-20"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-15",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 50.0, 326.0, 67.0, 23.0 ],
													"rnbo_classname" : "selector~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "selector~_obj-15",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"onoff" : 															{
																"attrOrProp" : 1,
																"digest" : "Turns Input Off or Routes to Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "1"
															}
,
															"out" : 															{
																"attrOrProp" : 1,
																"digest" : "Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in2" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 2",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"choices" : 															{
																"attrOrProp" : 2,
																"digest" : "Number of inputs",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1"
															}

														}
,
														"inputs" : [ 															{
																"name" : "onoff",
																"type" : "auto",
																"digest" : "Turns Input Off or Routes to Output",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "Input 1",
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : "signal",
																"digest" : "Input 2",
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out",
																"type" : "signal",
																"digest" : "Output",
																"docked" : 0
															}
 ],
														"helpname" : "selector~",
														"aliasOf" : "selector~",
														"classname" : "selector~",
														"operator" : 0,
														"versionId" : -990475044,
														"changesPatcherIO" : 0
													}
,
													"text" : "selector~ 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-11",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "signal", "signal" ],
													"patching_rect" : [ 323.0, 115.0, 46.0, 23.0 ],
													"rnbo_classname" : "saw~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "saw~_obj-11",
													"text" : "saw~ 8"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-48",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 76.5, 40.0, 35.0, 23.0 ],
													"rnbo_classname" : "in~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in~_obj-48",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal from inlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "signal from inlet with index 1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in~",
														"aliasOf" : "in~",
														"classname" : "in~",
														"operator" : 0,
														"versionId" : -176007711,
														"changesPatcherIO" : 1
													}
,
													"text" : "in~ 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-49",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 213.0, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in_obj-49",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 2",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-50",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 409.0, 43.0, 23.0 ],
													"rnbo_classname" : "out~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "out~_obj-50",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal sent to outlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "signal sent to outlet with index 1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out~",
														"aliasOf" : "out~",
														"classname" : "out~",
														"operator" : 0,
														"versionId" : 374499139,
														"changesPatcherIO" : 1
													}
,
													"text" : "out~ 1"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-11", 0 ],
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 1 ],
													"midpoints" : [ 332.5, 253.0, 135.0, 253.0 ],
													"source" : [ "obj-11", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-50", 0 ],
													"source" : [ "obj-15", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-15", 2 ],
													"midpoints" : [ 124.5, 313.0, 107.5, 313.0 ],
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-15", 0 ],
													"midpoints" : [ 287.5, 313.0, 59.5, 313.0 ],
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"midpoints" : [ 222.5, 133.0, 287.5, 133.0 ],
													"source" : [ "obj-20", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-15", 1 ],
													"order" : 1,
													"source" : [ "obj-48", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 0 ],
													"order" : 0,
													"source" : [ "obj-48", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-20", 0 ],
													"source" : [ "obj-49", 0 ]
												}

											}
 ],
										"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
										"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
										"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
										"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
										"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
										"bgfillcolor_type" : "color",
										"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
										"bgfillcolor_angle" : 270.0,
										"bgfillcolor_proportion" : 0.39,
										"bgfillcolor_autogradient" : 0.0
									}
,
									"patching_rect" : [ 536.0, 362.0, 61.0, 23.0 ],
									"rnbo_classname" : "p",
									"rnbo_extra_attributes" : 									{
										"receivemode" : "local",
										"polyphony" : -1.0,
										"args" : [  ],
										"voicecontrol" : "simple",
										"notecontroller" : 0,
										"exposevoiceparams" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "thruster",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"target" : 											{
												"attrOrProp" : 1,
												"digest" : "target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"mute" : 											{
												"attrOrProp" : 1,
												"digest" : "mute",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "in1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"__probingout1" : 											{
												"attrOrProp" : 1,
												"digest" : "__probingout1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "signal"
											}
,
											"out1" : 											{
												"attrOrProp" : 1,
												"digest" : "out1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"voicestatus" : 											{
												"attrOrProp" : 1,
												"digest" : "voicestatus",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"activevoices" : 											{
												"attrOrProp" : 1,
												"digest" : "activevoices",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"polyphony" : 											{
												"attrOrProp" : 2,
												"digest" : "Polyphony of the subpatcher.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"exposevoiceparams" : 											{
												"attrOrProp" : 2,
												"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"title" : 											{
												"attrOrProp" : 2,
												"digest" : "Title of the subpatcher",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "rnbo file to load",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"voicecontrol" : 											{
												"attrOrProp" : 2,
												"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "simple", "user" ],
												"type" : "enum",
												"defaultValue" : "simple"
											}
,
											"notecontroller" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED. Use voicecontrol instead.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"receivemode" : 											{
												"attrOrProp" : 2,
												"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "local", "compensated" ],
												"type" : "enum",
												"defaultValue" : "local"
											}
,
											"args" : 											{
												"attrOrProp" : 2,
												"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "in1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in2",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in2",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in3",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in3",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : "signal",
												"digest" : "out1",
												"displayName" : "",
												"docked" : 0
											}
 ],
										"helpname" : "patcher",
										"aliasOf" : "rnbo",
										"classname" : "p",
										"operator" : 0,
										"versionId" : 2039458657,
										"changesPatcherIO" : 0
									}
,
									"text" : "p thruster",
									"varname" : "thruster"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 6,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "rnbo",
										"rect" : [ 59.0, 107.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Lato",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"assistshowspatchername" : 0,
										"title" : "generator",
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-6",
													"maxclass" : "newobj",
													"numinlets" : 5,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 50.0, 190.0, 67.0, 23.0 ],
													"rnbo_classname" : "selector~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "selector~_obj-6",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"onoff" : 															{
																"attrOrProp" : 1,
																"digest" : "Turns Input Off or Routes to Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "1"
															}
,
															"out" : 															{
																"attrOrProp" : 1,
																"digest" : "Output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in2" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 2",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in3" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 3",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"in4" : 															{
																"attrOrProp" : 1,
																"digest" : "Input 4",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"choices" : 															{
																"attrOrProp" : 2,
																"digest" : "Number of inputs",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1"
															}

														}
,
														"inputs" : [ 															{
																"name" : "onoff",
																"type" : "auto",
																"digest" : "Turns Input Off or Routes to Output",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "Input 1",
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : "signal",
																"digest" : "Input 2",
																"docked" : 0
															}
, 															{
																"name" : "in3",
																"type" : "signal",
																"digest" : "Input 3",
																"docked" : 0
															}
, 															{
																"name" : "in4",
																"type" : "signal",
																"digest" : "Input 4",
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out",
																"type" : "signal",
																"digest" : "Output",
																"docked" : 0
															}
 ],
														"helpname" : "selector~",
														"aliasOf" : "selector~",
														"classname" : "selector~",
														"operator" : 0,
														"versionId" : -990475044,
														"changesPatcherIO" : 0
													}
,
													"text" : "selector~ 4"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-5",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 380.0, 150.0, 786.0, 488.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "triangle",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-3",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 332.5, 234.0, 42.0, 23.0 ],
																	"rnbo_classname" : "r",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "r_obj-3",
																	"text" : "r pitch"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-4",
																	"maxclass" : "newobj",
																	"numinlets" : 2,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 326.0, 326.0, 55.0, 23.0 ],
																	"rnbo_classname" : "triangle~",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "triangle~_obj-4",
																	"text" : "triangle~"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-2",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 336.0, 388.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-2",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 2,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 328.0, 282.0, 51.0, 23.0 ],
																	"rnbo_classname" : "phasor~",
																	"rnbo_extra_attributes" : 																	{
																		"lock" : 0.0
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "phasor~_obj-1",
																	"text" : "phasor~"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-4", 0 ],
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-1", 0 ],
																	"source" : [ "obj-3", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-2", 0 ],
																	"source" : [ "obj-4", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 166.0, 131.0, 58.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "triangle",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target_pitch_bang" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_bang",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bang"
															}
,
															"target_pitch_number" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_number",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"target_pitch_list" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_list",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"dummy" : 															{
																"attrOrProp" : 1,
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "dummy",
																"type" : "number",
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p triangle",
													"varname" : "triangle"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-4",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 708.0, 183.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "phasor",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-3",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 334.0, 214.0, 42.0, 23.0 ],
																	"rnbo_classname" : "r",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "r_obj-3",
																	"text" : "r pitch"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-2",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-2",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 2,
																	"numoutlets" : 1,
																	"outlettype" : [ "signal" ],
																	"patching_rect" : [ 334.0, 261.0, 51.0, 23.0 ],
																	"rnbo_classname" : "phasor~",
																	"rnbo_extra_attributes" : 																	{
																		"lock" : 0.0
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "phasor~_obj-1",
																	"text" : "phasor~"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-2", 0 ],
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-1", 0 ],
																	"source" : [ "obj-3", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 85.0, 131.0, 54.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "phasor",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target_pitch_bang" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_bang",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bang"
															}
,
															"target_pitch_number" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_number",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"target_pitch_list" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_list",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"dummy" : 															{
																"attrOrProp" : 1,
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "dummy",
																"type" : "number",
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p phasor",
													"varname" : "phasor"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 8,
															"minor" : 6,
															"revision" : 4,
															"architecture" : "x64",
															"modernui" : 1
														}
,
														"classnamespace" : "rnbo",
														"rect" : [ 704.0, 163.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"openinpresentation" : 0,
														"default_fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Lato",
														"gridonopen" : 1,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 1,
														"objectsnaponopen" : 1,
														"statusbarvisible" : 2,
														"toolbarvisible" : 1,
														"lefttoolbarpinned" : 0,
														"toptoolbarpinned" : 0,
														"righttoolbarpinned" : 0,
														"bottomtoolbarpinned" : 0,
														"toolbars_unpinned_last_save" : 0,
														"tallnewobj" : 0,
														"boxanimatetime" : 200,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"description" : "",
														"digest" : "",
														"tags" : "",
														"style" : "",
														"subpatcher_template" : "",
														"assistshowspatchername" : 0,
														"title" : "sin",
														"boxes" : [ 															{
																"box" : 																{
																	"id" : "obj-8",
																	"maxclass" : "newobj",
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"outlettype" : [ "" ],
																	"patching_rect" : [ 330.0, 163.0, 42.0, 23.0 ],
																	"rnbo_classname" : "r",
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "r_obj-8",
																	"text" : "r pitch"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-2",
																	"maxclass" : "newobj",
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"patching_rect" : [ 334.0, 304.0, 43.0, 23.0 ],
																	"rnbo_classname" : "out~",
																	"rnbo_extra_attributes" : 																	{
																		"comment" : "",
																		"meta" : ""
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "out~_obj-2",
																	"rnboinfo" : 																	{
																		"needsInstanceInfo" : 1,
																		"argnames" : 																		{
																			"in1" : 																			{
																				"attrOrProp" : 1,
																				"digest" : "signal sent to outlet with index 1",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 0,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"inlet" : 1,
																				"type" : "signal"
																			}
,
																			"index" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "outlet number",
																				"defaultarg" : 1,
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "number",
																				"mandatory" : 1
																			}
,
																			"comment" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "mouse over comment",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol"
																			}
,
																			"meta" : 																			{
																				"attrOrProp" : 2,
																				"digest" : "A JSON formatted string containing metadata for use by the exported code",
																				"isalias" : 0,
																				"aliases" : [  ],
																				"settable" : 1,
																				"attachable" : 0,
																				"isparam" : 0,
																				"deprecated" : 0,
																				"type" : "symbol",
																				"defaultValue" : "",
																				"label" : "Metadata",
																				"displayorder" : 3
																			}

																		}
,
																		"inputs" : [ 																			{
																				"name" : "in1",
																				"type" : "signal",
																				"digest" : "signal sent to outlet with index 1",
																				"displayName" : "",
																				"hot" : 1,
																				"docked" : 0
																			}
 ],
																		"outputs" : [  ],
																		"helpname" : "out~",
																		"aliasOf" : "out~",
																		"classname" : "out~",
																		"operator" : 0,
																		"versionId" : 374499139,
																		"changesPatcherIO" : 1
																	}
,
																	"text" : "out~ 1"
																}

															}
, 															{
																"box" : 																{
																	"id" : "obj-1",
																	"maxclass" : "newobj",
																	"numinlets" : 2,
																	"numoutlets" : 2,
																	"outlettype" : [ "signal", "signal" ],
																	"patching_rect" : [ 334.0, 261.0, 42.0, 23.0 ],
																	"rnbo_classname" : "cycle~",
																	"rnbo_extra_attributes" : 																	{
																		"buffername" : "RNBODefaultSinus",
																		"index" : "freq",
																		"interp" : "linear"
																	}
,
																	"rnbo_serial" : 1,
																	"rnbo_uniqueid" : "cycle~_obj-1",
																	"text" : "cycle~"
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"destination" : [ "obj-2", 0 ],
																	"source" : [ "obj-1", 0 ]
																}

															}
, 															{
																"patchline" : 																{
																	"destination" : [ "obj-1", 0 ],
																	"source" : [ "obj-8", 0 ]
																}

															}
 ],
														"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
														"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
														"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
														"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
														"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
														"bgfillcolor_type" : "color",
														"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
														"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
														"bgfillcolor_angle" : 270.0,
														"bgfillcolor_proportion" : 0.39,
														"bgfillcolor_autogradient" : 0.0
													}
,
													"patching_rect" : [ 74.0, 100.0, 33.0, 23.0 ],
													"rnbo_classname" : "p",
													"rnbo_extra_attributes" : 													{
														"receivemode" : "local",
														"polyphony" : -1.0,
														"args" : [  ],
														"voicecontrol" : "simple",
														"notecontroller" : 0,
														"exposevoiceparams" : 0
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "sin",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"target_pitch_bang" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_bang",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bang"
															}
,
															"target_pitch_number" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_number",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"target_pitch_list" : 															{
																"attrOrProp" : 1,
																"digest" : "target_pitch_list",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"target" : 															{
																"attrOrProp" : 1,
																"digest" : "target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"mute" : 															{
																"attrOrProp" : 1,
																"digest" : "mute",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"dummy" : 															{
																"attrOrProp" : 1,
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number"
															}
,
															"__probingout1" : 															{
																"attrOrProp" : 1,
																"digest" : "__probingout1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "signal"
															}
,
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "out1",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"voicestatus" : 															{
																"attrOrProp" : 1,
																"digest" : "voicestatus",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list"
															}
,
															"activevoices" : 															{
																"attrOrProp" : 1,
																"digest" : "activevoices",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number"
															}
,
															"polyphony" : 															{
																"attrOrProp" : 2,
																"digest" : "Polyphony of the subpatcher.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "-1"
															}
,
															"exposevoiceparams" : 															{
																"attrOrProp" : 2,
																"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"title" : 															{
																"attrOrProp" : 2,
																"digest" : "Title of the subpatcher",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"file" : 															{
																"attrOrProp" : 2,
																"digest" : "rnbo file to load",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"voicecontrol" : 															{
																"attrOrProp" : 2,
																"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "simple", "user" ],
																"type" : "enum",
																"defaultValue" : "simple"
															}
,
															"notecontroller" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED. Use voicecontrol instead.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}
,
															"receivemode" : 															{
																"attrOrProp" : 2,
																"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "local", "compensated" ],
																"type" : "enum",
																"defaultValue" : "local"
															}
,
															"args" : 															{
																"attrOrProp" : 2,
																"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"doNotShowInMaxInspector" : 1
															}

														}
,
														"inputs" : [ 															{
																"name" : "dummy",
																"type" : "number",
																"digest" : "Dummy inlet that lets you connect a set object to send mute messages.",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "out1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "patcher",
														"aliasOf" : "rnbo",
														"classname" : "p",
														"operator" : 0,
														"versionId" : 2039458657,
														"changesPatcherIO" : 0
													}
,
													"text" : "p sin",
													"varname" : "sin"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-45",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in_obj-45",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-46",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 273.0, 43.0, 23.0 ],
													"rnbo_classname" : "out~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "out~_obj-46",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal sent to outlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "signal sent to outlet with index 1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out~",
														"aliasOf" : "out~",
														"classname" : "out~",
														"operator" : 0,
														"versionId" : 374499139,
														"changesPatcherIO" : 1
													}
,
													"text" : "out~ 1"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 2 ],
													"midpoints" : [ 83.5, 124.0, 71.0, 124.0, 71.0, 175.0, 83.5, 175.0 ],
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 3 ],
													"midpoints" : [ 94.5, 184.0, 95.5, 184.0 ],
													"source" : [ "obj-4", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 0 ],
													"source" : [ "obj-45", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 4 ],
													"midpoints" : [ 175.5, 175.0, 107.5, 175.0 ],
													"source" : [ "obj-5", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-46", 0 ],
													"source" : [ "obj-6", 0 ]
												}

											}
 ],
										"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
										"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
										"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
										"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
										"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
										"bgfillcolor_type" : "color",
										"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
										"bgfillcolor_angle" : 270.0,
										"bgfillcolor_proportion" : 0.39,
										"bgfillcolor_autogradient" : 0.0
									}
,
									"patching_rect" : [ 536.0, 282.0, 69.0, 23.0 ],
									"rnbo_classname" : "p",
									"rnbo_extra_attributes" : 									{
										"receivemode" : "local",
										"polyphony" : -1.0,
										"args" : [  ],
										"voicecontrol" : "simple",
										"notecontroller" : 0,
										"exposevoiceparams" : 0
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "generator",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"target_pitch_bang" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_bang",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"target_pitch_number" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_number",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"target_pitch_list" : 											{
												"attrOrProp" : 1,
												"digest" : "target_pitch_list",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"target" : 											{
												"attrOrProp" : 1,
												"digest" : "target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"mute" : 											{
												"attrOrProp" : 1,
												"digest" : "mute",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"__probingout1" : 											{
												"attrOrProp" : 1,
												"digest" : "__probingout1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "signal"
											}
,
											"out1" : 											{
												"attrOrProp" : 1,
												"digest" : "out1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"voicestatus" : 											{
												"attrOrProp" : 1,
												"digest" : "voicestatus",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"activevoices" : 											{
												"attrOrProp" : 1,
												"digest" : "activevoices",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"polyphony" : 											{
												"attrOrProp" : 2,
												"digest" : "Polyphony of the subpatcher.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"exposevoiceparams" : 											{
												"attrOrProp" : 2,
												"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"title" : 											{
												"attrOrProp" : 2,
												"digest" : "Title of the subpatcher",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "rnbo file to load",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"voicecontrol" : 											{
												"attrOrProp" : 2,
												"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "simple", "user" ],
												"type" : "enum",
												"defaultValue" : "simple"
											}
,
											"notecontroller" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED. Use voicecontrol instead.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"receivemode" : 											{
												"attrOrProp" : 2,
												"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "local", "compensated" ],
												"type" : "enum",
												"defaultValue" : "local"
											}
,
											"args" : 											{
												"attrOrProp" : 2,
												"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : "signal",
												"digest" : "out1",
												"displayName" : "",
												"docked" : 0
											}
 ],
										"helpname" : "patcher",
										"aliasOf" : "rnbo",
										"classname" : "p",
										"operator" : 0,
										"versionId" : 2039458657,
										"changesPatcherIO" : 0
									}
,
									"text" : "p generator",
									"varname" : "generator"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 4,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 6,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "rnbo",
										"rect" : [ 59.0, 107.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Lato",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"assistshowspatchername" : 0,
										"title" : "arpeggiator",
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-21",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 162.0, 106.0, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "number_obj-21"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-12",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 337.0, 348.5, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "number_obj-12"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-7",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 336.0, 299.5, 29.5, 23.0 ],
													"rnbo_classname" : "+",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "+_obj-7",
													"text" : "+ 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-16",
													"maxclass" : "toggle",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 50.0, 105.5, 24.0, 24.0 ],
													"rnbo_classname" : "toggle",
													"rnbo_extra_attributes" : 													{
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "toggle_obj-16"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-123",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 572.0, 240.5, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "number_obj-123"
												}

											}
, 											{
												"box" : 												{
													"floatoutput" : 1,
													"id" : "obj-121",
													"maxclass" : "dial",
													"min" : 0.0,
													"mult" : 1.0,
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 523.0, 156.5, 40.0, 40.0 ],
													"rnbo_classname" : "dial",
													"rnbo_extra_attributes" : 													{
														"mult" : 1.0,
														"size" : 1.0,
														"floatoutput" : 1,
														"min" : 0.0,
														"preset" : 0,
														"order" : "",
														"value" : 0.0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "dial_obj-121",
													"size" : 1.0
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-118",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 335.5, 411.5, 53.0, 23.0 ],
													"rnbo_classname" : "switch",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "switch_obj-118",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"onoff" : 															{
																"attrOrProp" : 1,
																"digest" : "0 Turns switch Off, Non-zero Selects Input, Bang Reports Inlet.",
																"defaultarg" : 2,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"inputs" : 															{
																"attrOrProp" : 2,
																"digest" : "Number of inputs.",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "2"
															}

														}
,
														"inputs" : [ 															{
																"name" : "onoff",
																"type" : "number",
																"digest" : "0 Turns switch Off, Non-zero Selects Input, Bang Reports Inlet.",
																"defaultarg" : 2,
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 1",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 2",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Messages from selected input.",
																"docked" : 0
															}
 ],
														"helpname" : "switch",
														"aliasOf" : "switch",
														"classname" : "switch",
														"operator" : 0,
														"versionId" : 1043375357,
														"changesPatcherIO" : 0
													}
,
													"text" : "switch 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-102",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 264.0, 105.5, 24.0, 24.0 ],
													"rnbo_classname" : "button",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "button_obj-102"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-97",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 101.0, 216.5, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 4,
													"rnbo_uniqueid" : "number_obj-97"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-95",
													"maxclass" : "newobj",
													"numinlets" : 5,
													"numoutlets" : 4,
													"outlettype" : [ "", "", "", "" ],
													"patching_rect" : [ 84.0, 181.5, 79.0, 23.0 ],
													"rnbo_classname" : "counter",
													"rnbo_extra_attributes" : 													{
														"inc" : 1.0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "counter_obj-95",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"carryflag" : 															{
																"attrOrProp" : 1,
																"digest" : "Set underflow/overflow output type",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"enum" : [ "numeric", "bang" ],
																"type" : "enum",
																"defaultValue" : "numeric"
															}
,
															"input" : 															{
																"attrOrProp" : 1,
																"digest" : "numbers or bangs here are counted",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "bang"
															}
,
															"direction" : 															{
																"attrOrProp" : 1,
																"digest" : "Set Direction: 0 = Up, 1 = Down, 2 = UpDown",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"resetnext" : 															{
																"attrOrProp" : 1,
																"digest" : "Reset Counter to Number on Next Clock",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"resetnow" : 															{
																"attrOrProp" : 1,
																"digest" : "Reset Counter to Number Immediately",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"maximum" : 															{
																"attrOrProp" : 1,
																"digest" : "Set Maximum",
																"defaultarg" : 3,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "9999999"
															}
,
															"output" : 															{
																"attrOrProp" : 1,
																"digest" : "Current Count",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"underflow" : 															{
																"attrOrProp" : 1,
																"digest" : "Underflow (Counter Hit Minimum)",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "number"
															}
,
															"overflow" : 															{
																"attrOrProp" : 1,
																"digest" : "Overflow (Counter Hit Maximum)",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "number"
															}
,
															"carry" : 															{
																"attrOrProp" : 1,
																"digest" : "Carry Count",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"minimum" : 															{
																"attrOrProp" : 1,
																"digest" : "minimum",
																"defaultarg" : 2,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"inc" : 															{
																"attrOrProp" : 2,
																"digest" : "Increment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1"
															}

														}
,
														"inputs" : [ 															{
																"name" : "input",
																"type" : "bang",
																"digest" : "numbers or bangs here are counted",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "direction",
																"type" : "number",
																"digest" : "Set Direction: 0 = Up, 1 = Down, 2 = UpDown",
																"defaultarg" : 1,
																"docked" : 0
															}
, 															{
																"name" : "resetnext",
																"type" : [ "number", "bang" ],
																"digest" : "Reset Counter to Number on Next Clock",
																"docked" : 0
															}
, 															{
																"name" : "resetnow",
																"type" : [ "number", "bang" ],
																"digest" : "Reset Counter to Number Immediately",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "maximum",
																"type" : "number",
																"digest" : "Set Maximum",
																"defaultarg" : 3,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "output",
																"type" : "number",
																"digest" : "Current Count",
																"docked" : 0
															}
, 															{
																"name" : "underflow",
																"type" : [ "bang", "number" ],
																"digest" : "Underflow (Counter Hit Minimum)",
																"docked" : 0
															}
, 															{
																"name" : "overflow",
																"type" : [ "bang", "number" ],
																"digest" : "Overflow (Counter Hit Maximum)",
																"docked" : 0
															}
, 															{
																"name" : "carry",
																"type" : "number",
																"digest" : "Carry Count",
																"docked" : 0
															}
 ],
														"helpname" : "counter",
														"aliasOf" : "counter",
														"classname" : "counter",
														"operator" : 0,
														"versionId" : -1448073941,
														"changesPatcherIO" : 0
													}
,
													"text" : "counter 0 1 4"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-94",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 91.0, 147.5, 64.0, 23.0 ],
													"rnbo_classname" : "metro",
													"rnbo_extra_attributes" : 													{
														"lock" : 0.0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "metro_obj-94",
													"text" : "metro 200"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-93",
													"maxclass" : "newobj",
													"numinlets" : 5,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 227.0, 267.5, 61.0, 23.0 ],
													"rnbo_classname" : "switch",
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "switch_obj-93",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"onoff" : 															{
																"attrOrProp" : 1,
																"digest" : "0 Turns switch Off, Non-zero Selects Input, Bang Reports Inlet.",
																"defaultarg" : 2,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number",
																"defaultValue" : "0"
															}
,
															"inputs" : 															{
																"attrOrProp" : 2,
																"digest" : "Number of inputs.",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "2"
															}

														}
,
														"inputs" : [ 															{
																"name" : "onoff",
																"type" : "number",
																"digest" : "0 Turns switch Off, Non-zero Selects Input, Bang Reports Inlet.",
																"defaultarg" : 2,
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 1",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in2",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 2",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in3",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 3",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "in4",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Switch Input 4",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "out",
																"type" : [ "bang", "number", "list" ],
																"digest" : "Messages from selected input.",
																"docked" : 0
															}
 ],
														"helpname" : "switch",
														"aliasOf" : "switch",
														"classname" : "switch",
														"operator" : 0,
														"versionId" : 1043375357,
														"changesPatcherIO" : 0
													}
,
													"text" : "switch 4"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-92",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 307.0, 199.5, 29.5, 23.0 ],
													"rnbo_classname" : "/",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "/_obj-92",
													"text" : "/ 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-91",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 266.0, 199.5, 29.5, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "*_obj-91",
													"text" : "* 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-90",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 214.0, 199.5, 33.0, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "*_obj-90",
													"text" : "* 1.5"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-89",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 162.0, 195.5, 40.0, 23.0 ],
													"rnbo_classname" : "*",
													"rnbo_extra_attributes" : 													{
														"hot" : 0
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "*_obj-89",
													"text" : "* 1.25"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-64",
													"maxclass" : "flonum",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 303.0, 147.5, 50.0, 23.0 ],
													"rnbo_classname" : "number",
													"rnbo_extra_attributes" : 													{
														"minimum" : "<none>",
														"maximum" : "<none>",
														"initialFormat" : "float",
														"preset" : 0,
														"order" : ""
													}
,
													"rnbo_serial" : 5,
													"rnbo_uniqueid" : "number_obj-64"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-37",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in_obj-37",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-38",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 162.0, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "in_obj-38",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 2",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-39",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 313.25, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "in_obj-39",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 3",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 3"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-40",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 346.25, 40.0, 28.0, 23.0 ],
													"rnbo_classname" : "in",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 4,
													"rnbo_uniqueid" : "in_obj-40",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value from inlet with index 4",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in",
														"aliasOf" : "in",
														"classname" : "in",
														"operator" : 0,
														"versionId" : 1219109108,
														"changesPatcherIO" : 1
													}
,
													"text" : "in 4"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-41",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 264.0, 494.5, 36.0, 23.0 ],
													"rnbo_classname" : "out",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "out_obj-41",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value sent to outlet with index 1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out",
														"aliasOf" : "out",
														"classname" : "out",
														"operator" : 0,
														"versionId" : -735743983,
														"changesPatcherIO" : 1
													}
,
													"text" : "out 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-42",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 335.5, 494.5, 36.0, 23.0 ],
													"rnbo_classname" : "out",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 2,
													"rnbo_uniqueid" : "out_obj-42",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value sent to outlet with index 2",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out",
														"aliasOf" : "out",
														"classname" : "out",
														"operator" : 0,
														"versionId" : -735743983,
														"changesPatcherIO" : 1
													}
,
													"text" : "out 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-43",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 523.0, 494.5, 36.0, 23.0 ],
													"rnbo_classname" : "out",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 3,
													"rnbo_uniqueid" : "out_obj-43",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : [ "bang", "number", "list" ],
																"digest" : "value sent to outlet with index 3",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out",
														"aliasOf" : "out",
														"classname" : "out",
														"operator" : 0,
														"versionId" : -735743983,
														"changesPatcherIO" : 1
													}
,
													"text" : "out 3"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-41", 0 ],
													"source" : [ "obj-102", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-42", 0 ],
													"source" : [ "obj-118", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-118", 0 ],
													"midpoints" : [ 346.5, 395.5, 345.0, 395.5 ],
													"source" : [ "obj-12", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-123", 0 ],
													"midpoints" : [ 532.5, 227.5, 581.5, 227.5 ],
													"order" : 0,
													"source" : [ "obj-121", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-43", 0 ],
													"order" : 1,
													"source" : [ "obj-121", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-94", 0 ],
													"midpoints" : [ 59.5, 143.5, 100.5, 143.5 ],
													"source" : [ "obj-16", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-94", 1 ],
													"source" : [ "obj-21", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"source" : [ "obj-37", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-21", 0 ],
													"source" : [ "obj-38", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-118", 1 ],
													"order" : 0,
													"source" : [ "obj-39", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-64", 0 ],
													"order" : 1,
													"source" : [ "obj-39", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-7", 0 ],
													"source" : [ "obj-40", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-89", 0 ],
													"midpoints" : [ 312.5, 182.5, 171.5, 182.5 ],
													"order" : 3,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-90", 0 ],
													"midpoints" : [ 312.5, 185.5, 223.5, 185.5 ],
													"order" : 2,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-91", 0 ],
													"midpoints" : [ 312.5, 185.5, 275.5, 185.5 ],
													"order" : 1,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-92", 0 ],
													"midpoints" : [ 312.5, 185.5, 316.5, 185.5 ],
													"order" : 0,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-12", 0 ],
													"midpoints" : [ 345.5, 344.5, 346.5, 344.5 ],
													"source" : [ "obj-7", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-93", 1 ],
													"midpoints" : [ 171.5, 254.5, 247.0, 254.5 ],
													"source" : [ "obj-89", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-93", 2 ],
													"midpoints" : [ 223.5, 254.5, 257.5, 254.5 ],
													"source" : [ "obj-90", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-93", 3 ],
													"midpoints" : [ 275.5, 254.5, 268.0, 254.5 ],
													"source" : [ "obj-91", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-93", 4 ],
													"midpoints" : [ 316.5, 254.5, 278.5, 254.5 ],
													"source" : [ "obj-92", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-118", 2 ],
													"midpoints" : [ 236.5, 395.5, 379.0, 395.5 ],
													"source" : [ "obj-93", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-102", 0 ],
													"midpoints" : [ 100.5, 173.5, 250.0, 173.5, 250.0, 101.5, 273.5, 101.5 ],
													"order" : 0,
													"source" : [ "obj-94", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-95", 0 ],
													"midpoints" : [ 100.5, 173.5, 93.5, 173.5 ],
													"order" : 1,
													"source" : [ "obj-94", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-97", 0 ],
													"midpoints" : [ 93.5, 212.5, 110.5, 212.5 ],
													"source" : [ "obj-95", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-93", 0 ],
													"midpoints" : [ 110.5, 254.5, 236.5, 254.5 ],
													"source" : [ "obj-97", 0 ]
												}

											}
 ],
										"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
										"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
										"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
										"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
										"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
										"bgfillcolor_type" : "color",
										"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
										"bgfillcolor_angle" : 270.0,
										"bgfillcolor_proportion" : 0.39,
										"bgfillcolor_autogradient" : 0.0
									}
,
									"patching_rect" : [ 44.0, 336.0, 78.0, 23.0 ],
									"rnbo_classname" : "p",
									"rnbo_extra_attributes" : 									{
										"receivemode" : "local",
										"polyphony" : -1.0,
										"args" : [  ],
										"voicecontrol" : "simple",
										"notecontroller" : 0,
										"exposevoiceparams" : 0
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "arpeggiator",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"target" : 											{
												"attrOrProp" : 1,
												"digest" : "target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"mute" : 											{
												"attrOrProp" : 1,
												"digest" : "mute",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"__probingout1" : 											{
												"attrOrProp" : 1,
												"digest" : "__probingout1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "signal"
											}
,
											"voicestatus" : 											{
												"attrOrProp" : 1,
												"digest" : "voicestatus",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"activevoices" : 											{
												"attrOrProp" : 1,
												"digest" : "activevoices",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"polyphony" : 											{
												"attrOrProp" : 2,
												"digest" : "Polyphony of the subpatcher.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"exposevoiceparams" : 											{
												"attrOrProp" : 2,
												"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"title" : 											{
												"attrOrProp" : 2,
												"digest" : "Title of the subpatcher",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "rnbo file to load",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"voicecontrol" : 											{
												"attrOrProp" : 2,
												"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "simple", "user" ],
												"type" : "enum",
												"defaultValue" : "simple"
											}
,
											"notecontroller" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED. Use voicecontrol instead.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"receivemode" : 											{
												"attrOrProp" : 2,
												"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "local", "compensated" ],
												"type" : "enum",
												"defaultValue" : "local"
											}
,
											"args" : 											{
												"attrOrProp" : 2,
												"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in2",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in2",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in3",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in3",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "in4",
												"type" : [ "bang", "number", "list" ],
												"digest" : "in4",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : [ "bang", "number", "list" ],
												"digest" : "out1",
												"displayName" : "",
												"docked" : 0
											}
, 											{
												"name" : "out2",
												"type" : [ "bang", "number", "list" ],
												"digest" : "out2",
												"displayName" : "",
												"docked" : 0
											}
, 											{
												"name" : "out3",
												"type" : [ "bang", "number", "list" ],
												"digest" : "out3",
												"displayName" : "",
												"docked" : 0
											}
 ],
										"helpname" : "patcher",
										"aliasOf" : "rnbo",
										"classname" : "p",
										"operator" : 0,
										"versionId" : 2039458657,
										"changesPatcherIO" : 0
									}
,
									"text" : "p arpeggiator",
									"varname" : "arpeggiator"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 234.0, 251.0, 208.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "arpspeed",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param arpspeed @min 50 @max 2000",
									"varname" : "arpspeed"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 40.0, 255.0, 181.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"minimum" : 0.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "arpstart",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param arpstart @max 1 @steps 2",
									"varname" : "arpstart"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 604.0, 323.0, 174.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "thruster[1]",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param thruster @min 0 @max 1",
									"varname" : "thruster[1]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-119",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 169.0, 331.0, 149.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "arp",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param arp @min 0 @max 1",
									"varname" : "arp"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-87",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 79.0, 390.0, 43.0, 23.0 ],
									"rnbo_classname" : "s",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "s_obj-87",
									"text" : "s pitch"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-75",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 179.0, 292.0, 233.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "pitch",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param pitch @min 32.703 @max 2093.005",
									"varname" : "pitch"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 6,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "rnbo",
										"rect" : [ 1014.0, 82.0, 382.0, 384.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Lato",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"assistshowspatchername" : 0,
										"title" : "ringmod",
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-10",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 392.0, 89.0, 175.0, 23.0 ],
													"rnbo_classname" : "param",
													"rnbo_extra_attributes" : 													{
														"enum" : "",
														"steps" : 0.0,
														"displayorder" : "-",
														"unit" : "",
														"preset" : 1,
														"fromnormalized" : "",
														"order" : "0",
														"value" : 0.0,
														"meta" : "",
														"sendinit" : 1,
														"exponent" : 1.0,
														"ctlin" : 0.0,
														"tonormalized" : "",
														"displayname" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "ringmod",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"value" : 															{
																"attrOrProp" : 2,
																"digest" : "Set initial value",
																"defaultarg" : 2,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0",
																"label" : "Initial Value",
																"displayorder" : 3
															}
,
															"normalizedvalue" : 															{
																"attrOrProp" : 1,
																"digest" : "Set value normalized. ",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "number"
															}
,
															"reset" : 															{
																"attrOrProp" : 1,
																"digest" : "Reset param to initial value",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 1,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bang"
															}
,
															"normalized" : 															{
																"attrOrProp" : 1,
																"digest" : "Normalized parameter value.",
																"isalias" : 0,
																"aliases" : [  ],
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "number"
															}
,
															"name" : 															{
																"attrOrProp" : 2,
																"digest" : "Name of the parameter",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"label" : "Parameter Name",
																"mandatory" : 1
															}
,
															"enum" : 															{
																"attrOrProp" : 2,
																"digest" : "Use an enumerated output",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "list",
																"label" : "Enum Values",
																"displayorder" : 6
															}
,
															"minimum" : 															{
																"attrOrProp" : 2,
																"digest" : "Minimum value",
																"isalias" : 0,
																"aliases" : [ "min" ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0",
																"label" : "Minimum",
																"displayorder" : 1
															}
,
															"min" : 															{
																"attrOrProp" : 2,
																"digest" : "Minimum value",
																"isalias" : 1,
																"aliasOf" : "minimum",
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0",
																"label" : "Minimum",
																"displayorder" : 1
															}
,
															"maximum" : 															{
																"attrOrProp" : 2,
																"digest" : "Maximum value",
																"isalias" : 0,
																"aliases" : [ "max" ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1",
																"label" : "Maximum",
																"displayorder" : 2
															}
,
															"max" : 															{
																"attrOrProp" : 2,
																"digest" : "Maximum value",
																"isalias" : 1,
																"aliasOf" : "maximum",
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1",
																"label" : "Maximum",
																"displayorder" : 2
															}
,
															"exponent" : 															{
																"attrOrProp" : 2,
																"digest" : "Scale values exponentially",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "1",
																"label" : "Exponent",
																"displayorder" : 7
															}
,
															"steps" : 															{
																"attrOrProp" : 2,
																"digest" : "Divide the output into a number of discrete steps",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"defaultValue" : "0",
																"label" : "Steps",
																"displayorder" : 8
															}
,
															"displayName" : 															{
																"attrOrProp" : 2,
																"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 1,
																"type" : "symbol",
																"label" : "Display Name"
															}
,
															"displayname" : 															{
																"attrOrProp" : 2,
																"digest" : "A more readable name for the parameter in an external RNBO target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Display Name",
																"displayorder" : 14
															}
,
															"unit" : 															{
																"attrOrProp" : 2,
																"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Unit",
																"displayorder" : 15
															}
,
															"tonormalized" : 															{
																"attrOrProp" : 2,
																"digest" : "Converts a real parameter value to its normalized form.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"label" : "To Normalized Expression",
																"displayorder" : 10
															}
,
															"fromnormalized" : 															{
																"attrOrProp" : 2,
																"digest" : "Converts a normalized parameter into its actual parameter value.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"label" : "From Normalized Expression",
																"displayorder" : 9
															}
,
															"order" : 															{
																"attrOrProp" : 2,
																"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "0",
																"label" : "Restore Order",
																"displayorder" : 12
															}
,
															"displayorder" : 															{
																"attrOrProp" : 2,
																"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "-",
																"label" : "Display Order",
																"displayorder" : 13
															}
,
															"sendinit" : 															{
																"attrOrProp" : 2,
																"digest" : "Send initial value",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "true",
																"label" : "Send Init",
																"displayorder" : 4
															}
,
															"ctlin" : 															{
																"attrOrProp" : 2,
																"digest" : "MIDI controller number to control this parameter.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"label" : "MIDI Controller Number.",
																"displayorder" : 16
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 17
															}
,
															"nopreset" : 															{
																"attrOrProp" : 2,
																"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 1,
																"type" : "bool",
																"defaultValue" : "false"
															}
,
															"preset" : 															{
																"attrOrProp" : 2,
																"digest" : "Add this value to the preset.",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "bool",
																"defaultValue" : "true",
																"label" : "Include In Preset",
																"displayorder" : 11
															}

														}
,
														"inputs" : [ 															{
																"name" : "value",
																"type" : "number",
																"digest" : "Parameter value",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "normalizedvalue",
																"type" : "number",
																"digest" : "Set value normalized. ",
																"docked" : 0
															}
 ],
														"outputs" : [ 															{
																"name" : "value",
																"type" : "number",
																"digest" : "Parameter value",
																"hot" : 1,
																"docked" : 0
															}
, 															{
																"name" : "normalized",
																"type" : "number",
																"digest" : "Normalized parameter value.",
																"docked" : 0
															}
 ],
														"helpname" : "param",
														"aliasOf" : "param",
														"classname" : "param",
														"operator" : 0,
														"versionId" : -1940971094,
														"changesPatcherIO" : 0
													}
,
													"text" : "param ringmod @min 0 @max 1",
													"varname" : "ringmod"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-4",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 277.0, 301.0, 43.0, 23.0 ],
													"rnbo_classname" : "out~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "out~_obj-4",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"in1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal sent to outlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"inlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "outlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [ 															{
																"name" : "in1",
																"type" : "signal",
																"digest" : "signal sent to outlet with index 1",
																"displayName" : "",
																"hot" : 1,
																"docked" : 0
															}
 ],
														"outputs" : [  ],
														"helpname" : "out~",
														"aliasOf" : "out~",
														"classname" : "out~",
														"operator" : 0,
														"versionId" : 374499139,
														"changesPatcherIO" : 1
													}
,
													"text" : "out~ 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "signal", "signal" ],
													"patching_rect" : [ 353.0, 131.0, 52.0, 23.0 ],
													"rnbo_classname" : "cycle~",
													"rnbo_extra_attributes" : 													{
														"buffername" : "RNBODefaultSinus",
														"index" : "freq",
														"interp" : "linear"
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "cycle~_obj-3",
													"text" : "cycle~ 0"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 273.0, 218.0, 29.5, 23.0 ],
													"rnbo_classname" : "*~",
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "*~_obj-2",
													"text" : "*~"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 277.0, 131.0, 35.0, 23.0 ],
													"rnbo_classname" : "in~",
													"rnbo_extra_attributes" : 													{
														"comment" : "",
														"meta" : ""
													}
,
													"rnbo_serial" : 1,
													"rnbo_uniqueid" : "in~_obj-1",
													"rnboinfo" : 													{
														"needsInstanceInfo" : 1,
														"argnames" : 														{
															"out1" : 															{
																"attrOrProp" : 1,
																"digest" : "signal from inlet with index 1",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 0,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"outlet" : 1,
																"type" : "signal"
															}
,
															"index" : 															{
																"attrOrProp" : 2,
																"digest" : "inlet number",
																"defaultarg" : 1,
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "number",
																"mandatory" : 1
															}
,
															"comment" : 															{
																"attrOrProp" : 2,
																"digest" : "mouse over comment",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol"
															}
,
															"meta" : 															{
																"attrOrProp" : 2,
																"digest" : "A JSON formatted string containing metadata for use by the exported code",
																"isalias" : 0,
																"aliases" : [  ],
																"settable" : 1,
																"attachable" : 0,
																"isparam" : 0,
																"deprecated" : 0,
																"type" : "symbol",
																"defaultValue" : "",
																"label" : "Metadata",
																"displayorder" : 3
															}

														}
,
														"inputs" : [  ],
														"outputs" : [ 															{
																"name" : "out1",
																"type" : "signal",
																"digest" : "signal from inlet with index 1",
																"displayName" : "",
																"docked" : 0
															}
 ],
														"helpname" : "in~",
														"aliasOf" : "in~",
														"classname" : "in~",
														"operator" : 0,
														"versionId" : -176007711,
														"changesPatcherIO" : 1
													}
,
													"text" : "in~ 1"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-4", 0 ],
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 1 ],
													"source" : [ "obj-3", 0 ]
												}

											}
 ],
										"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
										"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
										"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
										"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
										"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
										"bgfillcolor_type" : "color",
										"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
										"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
										"bgfillcolor_angle" : 270.0,
										"bgfillcolor_proportion" : 0.39,
										"bgfillcolor_autogradient" : 0.0
									}
,
									"patching_rect" : [ 536.0, 323.0, 62.0, 23.0 ],
									"rnbo_classname" : "p",
									"rnbo_extra_attributes" : 									{
										"receivemode" : "local",
										"polyphony" : -1.0,
										"args" : [  ],
										"voicecontrol" : "simple",
										"notecontroller" : 0,
										"exposevoiceparams" : 0
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "ringmod",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"target" : 											{
												"attrOrProp" : 1,
												"digest" : "target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"mute" : 											{
												"attrOrProp" : 1,
												"digest" : "mute",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "in1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"__probingout1" : 											{
												"attrOrProp" : 1,
												"digest" : "__probingout1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "signal"
											}
,
											"out1" : 											{
												"attrOrProp" : 1,
												"digest" : "out1",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"voicestatus" : 											{
												"attrOrProp" : 1,
												"digest" : "voicestatus",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list"
											}
,
											"activevoices" : 											{
												"attrOrProp" : 1,
												"digest" : "activevoices",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number"
											}
,
											"polyphony" : 											{
												"attrOrProp" : 2,
												"digest" : "Polyphony of the subpatcher.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"exposevoiceparams" : 											{
												"attrOrProp" : 2,
												"digest" : "Expose per voice versions of the contained parameters (only valid in polyphonic subpatchers).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"title" : 											{
												"attrOrProp" : 2,
												"digest" : "Title of the subpatcher",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "rnbo file to load",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"voicecontrol" : 											{
												"attrOrProp" : 2,
												"digest" : "Chooses the way that polyphonic voices are controlled. 'simple' (or 'midi') will automatically allocate voices for \tincoming MIDI notes. Setting it to 'user' (or 'none') will switch off MIDI \tvoice allocation and start with all voices unmuted.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "simple", "user" ],
												"type" : "enum",
												"defaultValue" : "simple"
											}
,
											"notecontroller" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED. Use voicecontrol instead.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}
,
											"receivemode" : 											{
												"attrOrProp" : 2,
												"digest" : "Do receive~ objects get the signal from a send~ inside the patcher directly (without latency), or compensated (with latency, aligned with all other voices).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"enum" : [ "local", "compensated" ],
												"type" : "enum",
												"defaultValue" : "local"
											}
,
											"args" : 											{
												"attrOrProp" : 2,
												"digest" : "Replacement args for the subpatcher, everything named #1, #2 etc. will be replaced with the according argument.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"doNotShowInMaxInspector" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "in1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : "signal",
												"digest" : "out1",
												"displayName" : "",
												"docked" : 0
											}
 ],
										"helpname" : "patcher",
										"aliasOf" : "rnbo",
										"classname" : "p",
										"operator" : 0,
										"versionId" : 2039458657,
										"changesPatcherIO" : 0
									}
,
									"text" : "p ringmod",
									"varname" : "ringmod"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 526.0, 238.0, 167.0, 23.0 ],
									"rnbo_classname" : "param",
									"rnbo_extra_attributes" : 									{
										"enum" : "",
										"steps" : 0.0,
										"displayorder" : "-",
										"unit" : "",
										"preset" : 1,
										"fromnormalized" : "",
										"order" : "0",
										"value" : 0.0,
										"meta" : "",
										"sendinit" : 1,
										"exponent" : 1.0,
										"ctlin" : 0.0,
										"tonormalized" : "",
										"displayname" : ""
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "source",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"value" : 											{
												"attrOrProp" : 2,
												"digest" : "Set initial value",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Initial Value",
												"displayorder" : 3
											}
,
											"normalizedvalue" : 											{
												"attrOrProp" : 1,
												"digest" : "Set value normalized. ",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "number"
											}
,
											"reset" : 											{
												"attrOrProp" : 1,
												"digest" : "Reset param to initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bang"
											}
,
											"normalized" : 											{
												"attrOrProp" : 1,
												"digest" : "Normalized parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"outlet" : 1,
												"type" : "number"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the parameter",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "Parameter Name",
												"mandatory" : 1
											}
,
											"enum" : 											{
												"attrOrProp" : 2,
												"digest" : "Use an enumerated output",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "list",
												"label" : "Enum Values",
												"displayorder" : 6
											}
,
											"minimum" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 0,
												"aliases" : [ "min" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"min" : 											{
												"attrOrProp" : 2,
												"digest" : "Minimum value",
												"isalias" : 1,
												"aliasOf" : "minimum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Minimum",
												"displayorder" : 1
											}
,
											"maximum" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 0,
												"aliases" : [ "max" ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"max" : 											{
												"attrOrProp" : 2,
												"digest" : "Maximum value",
												"isalias" : 1,
												"aliasOf" : "maximum",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Maximum",
												"displayorder" : 2
											}
,
											"exponent" : 											{
												"attrOrProp" : 2,
												"digest" : "Scale values exponentially",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "1",
												"label" : "Exponent",
												"displayorder" : 7
											}
,
											"steps" : 											{
												"attrOrProp" : 2,
												"digest" : "Divide the output into a number of discrete steps",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"defaultValue" : "0",
												"label" : "Steps",
												"displayorder" : 8
											}
,
											"displayName" : 											{
												"attrOrProp" : 2,
												"digest" : "DEPRECATED: Use the lower case 'displayname' instead",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "symbol",
												"label" : "Display Name"
											}
,
											"displayname" : 											{
												"attrOrProp" : 2,
												"digest" : "A more readable name for the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Display Name",
												"displayorder" : 14
											}
,
											"unit" : 											{
												"attrOrProp" : 2,
												"digest" : "A symbol to describe the unit of the parameter in an external RNBO target",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Unit",
												"displayorder" : 15
											}
,
											"tonormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a real parameter value to its normalized form.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "To Normalized Expression",
												"displayorder" : 10
											}
,
											"fromnormalized" : 											{
												"attrOrProp" : 2,
												"digest" : "Converts a normalized parameter into its actual parameter value.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"label" : "From Normalized Expression",
												"displayorder" : 9
											}
,
											"order" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which initial parameter values will be sent out on patcher load. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "0",
												"label" : "Restore Order",
												"displayorder" : 12
											}
,
											"displayorder" : 											{
												"attrOrProp" : 2,
												"digest" : "Order in which parameters will show up in a list of all parameters. The order can be numeric or symbolic ('first' and 'last')",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "-",
												"label" : "Display Order",
												"displayorder" : 13
											}
,
											"sendinit" : 											{
												"attrOrProp" : 2,
												"digest" : "Send initial value",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Send Init",
												"displayorder" : 4
											}
,
											"ctlin" : 											{
												"attrOrProp" : 2,
												"digest" : "MIDI controller number to control this parameter.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"label" : "MIDI Controller Number.",
												"displayorder" : 16
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 17
											}
,
											"nopreset" : 											{
												"attrOrProp" : 2,
												"digest" : "Do not add this value to the preset [DEPRECATED - USE @preset 0 instead].",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 1,
												"type" : "bool",
												"defaultValue" : "false"
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "bool",
												"defaultValue" : "true",
												"label" : "Include In Preset",
												"displayorder" : 11
											}

										}
,
										"inputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalizedvalue",
												"type" : "number",
												"digest" : "Set value normalized. ",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "value",
												"type" : "number",
												"digest" : "Parameter value",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "normalized",
												"type" : "number",
												"digest" : "Normalized parameter value.",
												"docked" : 0
											}
 ],
										"helpname" : "param",
										"aliasOf" : "param",
										"classname" : "param",
										"operator" : 0,
										"versionId" : -1940971094,
										"changesPatcherIO" : 0
									}
,
									"text" : "param source @min 1 @max 4",
									"varname" : "source"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "flonum",
									"maximum" : 4.0,
									"minimum" : 1.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 519.0, 197.0, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"minimum" : 1.0,
										"maximum" : 4.0,
										"initialFormat" : "float",
										"preset" : 0,
										"order" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "number_obj-8"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 536.0, 580.0, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "out~_obj-1",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 1",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 374499139,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 1"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"midpoints" : [ 545.5, 349.0, 545.5, 349.0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 3 ],
									"midpoints" : [ 178.5, 357.0, 132.0, 357.0, 132.0, 330.0, 112.5, 330.0 ],
									"source" : [ "obj-119", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 1 ],
									"midpoints" : [ 243.5, 276.0, 222.0, 276.0, 222.0, 288.0, 73.166666666666671, 288.0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 1 ],
									"midpoints" : [ 613.5, 357.0, 566.5, 357.0 ],
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"midpoints" : [ 49.5, 330.0, 53.5, 330.0 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 2 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-119", 0 ],
									"midpoints" : [ 112.5, 360.0, 156.0, 360.0, 156.0, 327.0, 178.5, 327.0 ],
									"source" : [ "obj-44", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-75", 0 ],
									"midpoints" : [ 53.5, 369.0, 156.0, 369.0, 156.0, 288.0, 188.5, 288.0 ],
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-87", 0 ],
									"midpoints" : [ 83.0, 375.0, 88.5, 375.0 ],
									"source" : [ "obj-44", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"midpoints" : [ 545.5, 307.0, 545.5, 307.0 ],
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 2 ],
									"midpoints" : [ 772.5, 309.0, 789.0, 309.0, 789.0, 357.0, 587.5, 357.0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 2 ],
									"midpoints" : [ 188.5, 318.0, 92.833333333333343, 318.0 ],
									"source" : [ "obj-75", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"midpoints" : [ 528.5, 229.0, 535.5, 229.0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 1 ],
									"midpoints" : [ 535.5, 279.0, 522.0, 279.0, 522.0, 438.0, 563.0, 438.0 ],
									"order" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"midpoints" : [ 535.5, 274.0, 545.5, 274.0 ],
									"order" : 1,
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"default_bgcolor" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
						"color" : [ 0.929412, 0.929412, 0.352941, 1.0 ],
						"elementcolor" : [ 0.357540726661682, 0.515565991401672, 0.861786782741547, 1.0 ],
						"accentcolor" : [ 0.343034118413925, 0.506230533123016, 0.86220508813858, 1.0 ],
						"textcolor_inverse" : [ 0.968627, 0.968627, 0.968627, 1.0 ],
						"stripecolor" : [ 0.258338063955307, 0.352425158023834, 0.511919498443604, 1.0 ],
						"bgfillcolor_type" : "color",
						"bgfillcolor_color" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
						"bgfillcolor_color1" : [ 0.031372549019608, 0.125490196078431, 0.211764705882353, 1.0 ],
						"bgfillcolor_color2" : [ 0.263682, 0.004541, 0.038797, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39,
						"bgfillcolor_autogradient" : 0.0,
						"export_config" : 						{
							"cpp-export" : 							{
								"cpp-code-export" : 								{
									"export_name" : "shipbuilder_v4.cpp",
									"copy_dependencies" : 1,
									"write_binary_file" : 1,
									"exposevoiceparams" : 1,
									"openexportdirectory" : 1
								}

							}

						}

					}
,
					"patching_rect" : [ 215.0, 658.0, 232.0, 22.0 ],
					"rnboattrcache" : 					{
						"arpstart" : 						{
							"label" : "arpstart",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"arpspeed" : 						{
							"label" : "arpspeed",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"ringmod/ringmod" : 						{
							"label" : "ringmod",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"arp" : 						{
							"label" : "arp",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"pitch" : 						{
							"label" : "pitch",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"source" : 						{
							"label" : "source",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"thruster[1]" : 						{
							"label" : "thruster",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"shields[1]" : 						{
							"label" : "shields",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"thrusterspeed" : 						{
							"label" : "thrusterspeed",
							"isEnum" : 0,
							"parsestring" : ""
						}

					}
,
					"rnboversion" : "1.2.6",
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_annotation_name" : "source selector",
							"parameter_invisible" : 1,
							"parameter_longname" : "rnbo~",
							"parameter_modmode" : 0,
							"parameter_shortname" : "rnbo~",
							"parameter_type" : 3
						}

					}
,
					"saved_object_attributes" : 					{
						"annotation_name" : "source selector",
						"optimization" : "O1",
						"parameter_enable" : 1,
						"uuid" : "46a91b03-946d-11ef-9b03-a036bc5f97e6"
					}
,
					"snapshot" : 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "snapshotlist",
						"origin" : "rnbo~",
						"type" : "list",
						"subtype" : "Undefined",
						"embed" : 1,
						"snapshot" : 						{
							"shields" : 							{
								"value" : 4.0
							}
,
							"__presetid" : "46a91b03-946d-11ef-9b03-a036bc5f97e6",
							"source" : 							{
								"value" : 2.2
							}
,
							"arpstart" : 							{
								"value" : 1.0
							}
,
							"arp" : 							{
								"value" : 0.0
							}
,
							"arpspeed" : 							{
								"value" : 826.0
							}
,
							"pitch" : 							{
								"value" : 391.0
							}
,
							"thruster" : 							{
								"value" : 0.0
							}
,
							"thrusterspeed" : 							{
								"value" : 1.0
							}
,
							"__sps" : 							{
								"arpeggiator" : 								{

								}
,
								"ringmod" : 								{
									"ringmod" : 									{
										"value" : 0.0
									}

								}
,
								"shields" : 								{
									"__sps" : 									{
										"generator[2]" : 										{
											"__sps" : 											{
												"triangle" : 												{

												}
,
												"sin" : 												{

												}
,
												"phasor" : 												{

												}

											}

										}
,
										"generator" : 										{
											"__sps" : 											{
												"triangle" : 												{

												}
,
												"sin" : 												{

												}
,
												"phasor" : 												{

												}

											}

										}
,
										"generator[1]" : 										{
											"__sps" : 											{
												"triangle" : 												{

												}
,
												"sin" : 												{

												}
,
												"phasor" : 												{

												}

											}

										}

									}

								}
,
								"thruster" : 								{

								}
,
								"generator" : 								{
									"__sps" : 									{
										"triangle" : 										{

										}
,
										"sin" : 										{

										}
,
										"phasor" : 										{

										}

									}

								}

							}

						}
,
						"snapshotlist" : 						{
							"current_snapshot" : 0,
							"entries" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "untitled",
									"origin" : "46a91b03-946d-11ef-9b03-a036bc5f97e6",
									"type" : "rnbo",
									"subtype" : "",
									"embed" : 0,
									"snapshot" : 									{
										"shields" : 										{
											"value" : 4.0
										}
,
										"__presetid" : "46a91b03-946d-11ef-9b03-a036bc5f97e6",
										"source" : 										{
											"value" : 2.2
										}
,
										"arpstart" : 										{
											"value" : 1.0
										}
,
										"arp" : 										{
											"value" : 0.0
										}
,
										"arpspeed" : 										{
											"value" : 826.0
										}
,
										"pitch" : 										{
											"value" : 391.0
										}
,
										"thruster" : 										{
											"value" : 0.0
										}
,
										"thrusterspeed" : 										{
											"value" : 1.0
										}
,
										"__sps" : 										{
											"arpeggiator" : 											{

											}
,
											"ringmod" : 											{
												"ringmod" : 												{
													"value" : 0.0
												}

											}
,
											"shields" : 											{
												"__sps" : 												{
													"generator[2]" : 													{
														"__sps" : 														{
															"triangle" : 															{

															}
,
															"sin" : 															{

															}
,
															"phasor" : 															{

															}

														}

													}
,
													"generator" : 													{
														"__sps" : 														{
															"triangle" : 															{

															}
,
															"sin" : 															{

															}
,
															"phasor" : 															{

															}

														}

													}
,
													"generator[1]" : 													{
														"__sps" : 														{
															"triangle" : 															{

															}
,
															"sin" : 															{

															}
,
															"phasor" : 															{

															}

														}

													}

												}

											}
,
											"thruster" : 											{

											}
,
											"generator" : 											{
												"__sps" : 												{
													"triangle" : 													{

													}
,
													"sin" : 													{

													}
,
													"phasor" : 													{

													}

												}

											}

										}

									}
,
									"fileref" : 									{
										"name" : "untitled",
										"filename" : "untitled.maxsnap",
										"filepath" : "~/OneDrive/Documents/Max 8/Snapshots",
										"filepos" : -1,
										"snapshotfileid" : "e827e590ec7cb11104e66e6cebaca974"
									}

								}
 ]
						}

					}
,
					"text" : "rnbo~ @annotation_name source selector",
					"varname" : "rnbo~"
				}

			}
, 			{
				"box" : 				{
					"attr" : "source",
					"id" : "obj-7",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 494.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "ringmod/ringmod",
					"id" : "obj-8",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 380.0, 486.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "pitch",
					"id" : "obj-1",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 557.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "arp",
					"id" : "obj-3",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 380.0, 557.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "thruster[1]",
					"id" : "obj-6",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 588.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "arpstart",
					"id" : "obj-4",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 186.0, 425.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "arpspeed",
					"id" : "obj-5",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 417.0, 624.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "shields[1]",
					"id" : "obj-9",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 176.0, 383.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "thrusterspeed",
					"id" : "obj-10",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 201.0, 615.0, 150.0, 22.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 195.5, 582.0, 171.0, 582.0, 171.0, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 1 ],
					"midpoints" : [ 224.5, 693.0, 259.5, 693.0 ],
					"order" : 0,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"midpoints" : [ 224.5, 693.0, 230.5, 693.0 ],
					"order" : 1,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"source" : [ "obj-21", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 389.5, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 195.5, 450.0, 171.0, 450.0, 171.0, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 195.5, 546.0, 195.5, 546.0 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"midpoints" : [ 195.5, 486.0, 195.5, 486.0 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"midpoints" : [ 389.5, 462.0, 389.5, 462.0 ],
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"midpoints" : [ 389.5, 552.0, 389.5, 552.0 ],
					"source" : [ "obj-58", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 195.5, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 195.5, 519.0, 171.0, 519.0, 171.0, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 389.5, 510.0, 348.0, 510.0, 348.0, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 185.5, 411.0, 171.0, 411.0, 171.0, 645.0, 224.5, 645.0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-19" : [ "rnbo~", "rnbo~", 0 ],
			"obj-21" : [ "live.gain~", "live.gain~", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "untitled.maxsnap",
				"bootpath" : "~/OneDrive/Documents/Max 8/Snapshots",
				"patcherrelativepath" : "../../../../../../Max 8/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
