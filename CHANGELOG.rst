^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package plotjuggler
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1.8.4 (2018-09-17)
------------------
* add tooltip
* fix issue #109
* CMakeLists.txt add mac homebrew qt5 install directory (#111)
* Merge pull request #107 from v-lopez/master
* Fix dragging/deletion of hidden items
* Contributors: Andrew Hundt, Davide Faconti, Victor Lopez

1.8.3 (2018-08-24)
------------------
* bug fix (crash when detaching a _point_marker)
* more informative error messages
* cleanups
* more compact view and larger dummyData
* Contributors: Davide Faconti

1.8.2 (2018-08-19)
------------------
* bug fix (crash from zombie PlotMatrix)
* Contributors: Davide Faconti

1.8.1 (2018-08-18)
------------------
* message moved back to the ROS plugin
* More informative dialog (issue #100)
* many improvements related to  FilteredTableListWidget, issue #103
* Contributors: Davide Faconti

1.8.0 (2018-08-17)
------------------
* fixing splash time
* minor update
* fix issue #49
* README and splashscreen updates
* Update ISSUE_TEMPLATE.md
* F10 enhancement
* preparing release 1.8.0
* (speedup) skip _completer->addToCompletionTree altogether unless Prefix mode is active
* avoid data copying when loading a datafile
* fix issue #103
* workaround for issue #100
* trying to fix problem with time offset durinh streaming
* removed enableStreaming from StreamingPlugins
* several useless replot() calls removed
* more conservative implementation of setTimeOffset
* optimization
* reduced a lot the amount of computation related to addCurve()
* bug fix
* Update .appveyor.yml
* bug fix (_main_tabbed_widget is already included in TabbedPlotWidget::instances())
* remove bug (crash at deleteDataOfSingleCurve)
* make PlotData non-copyable
* change in sthe state publisher API
* shared_ptr removed. To be tested
* WIP: changed the way data is shared
* added suggestion from issue #105
* skip empty dataMaps in importPlotDataMap() . Issue #105
* fix issue #102 (grey background)
* Contributors: Davide Faconti

1.7.3 (2018-08-12)
------------------
* enhancement discussed in #104 Can clear buffer while streaming is active
* adding enhancements 4 and 5 from issue #105
* fixed bug reported in  #105
* fix critical error
* fix issue #101
* Contributors: Davide Faconti

1.7.2 (2018-08-10)
------------------
* Update .travis.yml
* fixed potential thread safety problem
* trying to apply changes discussed in issue #96
* add transport hint
* make hyperlinks clickable by allowing to open external links (#95)
* Contributors: Davide Faconti, Romain Reignier

* Update .travis.yml
* fixed potential thread safety problem
* trying to apply changes discussed in issue #96
* add transport hint
* make hyperlinks clickable by allowing to open external links (#95)
* Contributors: Davide Faconti, Romain Reignier

1.7.1 (2018-07-22)
------------------
* catch exceptions
* fix resize of PlotData size. Reported in issue #94
* Contributors: Davide Faconti

1.7.0 (2018-07-19)
------------------
* fixing issue #93 (thread safety in XYPlot and streaming)
* fix issue #92
* bug fix
* Issue #88 (#90)
* Reorder header files to fix conflicts with boost and QT (#86)
* Contributors: Davide Faconti, Enrique Fernández Perdomo

1.6.2 (2018-05-19)
------------------
* fixing issue introduced in bec2c74195d74969f9c017b9b718faf9be6c1687
* Contributors: Davide Faconti

1.6.1 (2018-05-15)
------------------
* allow the buffer size to be edited
* qDebug removed
* fixing right mouse drag&drop
* Contributors: Davide Faconti

1.6.0 (2018-05-01)
------------------
* fixed the most annoying bug ever (erroneus DragLeave). issue #80
* fine tuning the widget spacing
* added feature #83
* fix issue #82
* remove redundant code in CMakeLists.txt
* Qwt updated and background color change during drag&drop
* Contributors: Davide Faconti

1.5.2 (2018-04-24)
------------------
* bug fix #78
* Fix typo (#76)
* Fix QmessageBox
* fixed issue reported in #68
* Contributors: Davide Faconti, Victor Lopez

1.5.1 (2018-02-14)
------------------
* Ignore not initialized timestamps (#75)
* added a warning as suggested in issue #75
* Housekeeping of publishers in StatePublisher
* improved layout and visibility in StatePublisher selector
* Fix issue #73: bad_cast exception
* Update README.md
* added more control over the published topics
* save ALL message instances
* CSV  plugin: accept CSV files with empty cells
* fix issue #72: std::round not supported by older compilers
* add a prefix to the field name if required
* Fix issue #69
* bug fix in onActionSaveLayout + indentation
* A small plugin creating a websocket server (#64)
* bug fixes
* Contributors: Davide Faconti, Philippe Gauthier

1.5.0 (2017-11-28)
------------------
* using AsyncSpinner as it ought to be
* fixing the mutex problem in streaming
* Contributors: Davide Faconti

1.4.2 (2017-11-20)
------------------
* bug fix in getIndexFromX that affected the vertical axis range calculation
* fix issue #61
* Contributors: Davide Faconti

1.4.1 (2017-11-19)
------------------
* fixed some issue with reloading rosbags and addressing issue #54
* adding improvement #55
* Contributors: Davide Faconti

1.4.0 (2017-11-14)
------------------
* added the ability to set max_array_size in the GUI
* Contributors: Davide Faconti

1.3.1 (2017-11-14)
------------------
* warnings added
* License updated
* Fix build failures on Archlinux (#57)
* Update README.md
* Contributors: Davide Faconti, Kartik Mohta

1.3.0 (2017-10-12)
------------------
* added xmlLoadState and xmlSaveState to ALL plugins
* works with newer ros_type_introspection
* speed up
* fix potential confision with #include
* minor fix in timeSlider
* Contributors: Davide Faconti

1.2.1 (2017-08-30)
------------------
* better limits for timeSlider
* fix a potential issue with ranges
* set explicitly the max vector size
* avoid wasting time doing tableWidget->sortByColumn
* bug fix
* prevent a nasty error during construction
* Update README.md
* added ros_type_introspection to travis
* Contributors: Davide Faconti

1.2.0 (2017-08-29)
------------------
* Ros introspection updated (`#52 <https://github.com/facontidavide/PlotJuggler/issues/52>`_)
* Potential fix for precision issue when adding time_offset
* Update snap/snapcraft.yaml
* Contributors: Davide Faconti, Kartik Mohta

1.1.3 (2017-07-11)
------------------
* fixed few issues with DataStreamROS
* Update README.md
* improvement `#43 <https://github.com/facontidavide/PlotJuggler/issues/43>`_. Use F10 to hide/show controls
* Contributors: Davide Faconti

1.1.2 (2017-06-28)
------------------
* bug-fix in DataLoadROS (multi-selection from layout)
* Merge branch 'master' of github.com:facontidavide/PlotJuggler
* minor change
* Update README.md
* Contributors: Davide Faconti

1.1.1 (2017-06-26)
------------------
* store rosbag::MessageInstance to replay data with the publisher
* avoid allocation
* minor optimizations
* bug fix: checkbox to use renaming rules was not detected correctly
* fix for very large rosbags
* Contributors: Davide Faconti

1.1.0 (2017-06-20)
------------------
* fixing bug `#47 <https://github.com/facontidavide/PlotJuggler/issues/47>`_
* Contributors: Davide Faconti

1.0.8 (2017-06-20)
------------------
* update to be compatible with ros_type_introspection 0.6
* setting uninitialized variable (thanks valgrind)
* improvement `#48 <https://github.com/facontidavide/PlotJuggler/issues/48>`_
* fix for issue `#46 <https://github.com/facontidavide/PlotJuggler/issues/46>`_ (load csv files)
* more intuitive ordering of strings. Based on PR `#45 <https://github.com/facontidavide/PlotJuggler/issues/45>`_. Fixes `#27 <https://github.com/facontidavide/PlotJuggler/issues/27>`_
* Correct the string being searched for to find the header stamp field (`#44 <https://github.com/facontidavide/PlotJuggler/issues/44>`_)
* Contributors: Davide Faconti, Kartik Mohta

1.0.7 (2017-05-12)
------------------
* the list of topics in the Dialog will be automatically updated
* bug fix
* fixed some issues with the installation
* Contributors: Davide Faconti

1.0.5 (2017-05-07)
------------------
* fixed an issue with ROS during destruction
* allow timestamp injection
* Create ISSUE_TEMPLATE.md
* Contributors: Davide Faconti

1.0.4 (2017-04-30)
------------------
* save/restore the selected topics in the layout file
* Contributors: Davide Faconti

1.0.3 (2017-04-28)
------------------
* fixed window management
* Contributors: Davide Faconti

1.0.2 (2017-04-26)
------------------
* set axis Y limit is undoable now
* added the command line option "buffer_size"
* filter xml extension for save layout
* added axis limits (Y)
* Contributors: Davide Faconti

1.0.1 (2017-04-24)
------------------
* documentation fix
* color widget simplified
* Update README.md
* default extension fixed in layout.xml
* Contributors: Davide Faconti, Eduardo Caceres

1.0.0 (2017-4-22)
-----------------
* Total awesomeness

0.18.0 (2017-04-21)
-------------------
* added visualization policy to the TimeTracker
* bug fix in RosoutPublisher
* added try-catch guard to third party plugins method invokation
* improving documentation
* multiple fixes
* shall periodically update the list of curves from the streamer
* make the API of plugins more consistent and future proof
* removed double replot during streaming (and framerate limited to 25)
* Contributors: Davide Faconti

0.17.0 (2017-04-02)
-------------------
* more renaming rules and samples
* feature request #31
* fix QFileDialog (save)
* fixing a nasty bug in save plot to file
* Add dummy returns to function that required it (#36)
* trying to fix some issues with the streamer time offset
* fixing a crash in the plugin
* saving more application settings with QSettings
* cleanups
* new plugin: rosout
* several bugs fixed
* removed unused plugin
* Update README.md
* cleanups
* added data samples
* move wais to filter the listWidget
* visualization improvements
* Contributors: Davide Faconti, v-lopez

0.16.0 (2017-03-22)
-------------------
* removed the normalization of time in ROS plugins
* relative time seems to work properly
* Contributors: Davide Faconti

0.15.3 (2017-03-22)
-------------------
* multiple fixes
* update related to backtrace
* backward-cpp added
* show coordinates when the left mouse is clicked (but not moved)
* Contributors: Davide Faconti

0.15.1 (2017-03-20)
-------------------
* adding some deadband to the zoomer
* fixed a bug related to tabs and new windows
* Contributors: Davide Faconti

0.15.0 (2017-03-17)
-------------------
* Multiple problems fixed with streaming interface nd XY plots
* Contributors: Davide Faconti

0.14.2 (2017-03-16)
-------------------
* improve CurveColorPick
* bugs fixed
* crash fixed
* Prevent compiler warning if compiling under ROS (#29)
* Contributors: Davide Faconti, Tim Clephas

0.14.1 (2017-03-15)
-------------------
* improved the time slider
* bug fixes
* Contributors: Davide Faconti

0.14.0 (2017-03-15)
-------------------
* improved usability
* adding XY plots (#26)
* improving plot magnifier
* changed key combination
* file extension of saved images fixed
* bug fixes
* adding the ability to delete curves
* Contributors: Davide Faconti

0.13.1 (2017-03-14)
-------------------
* bug fix
* Contributors: Davide Faconti

0.13.0 (2017-03-12)
-------------------
* default range X for empty plots
* better formatting
* improving 2nd column visualization
* Contributors: Davide Faconti

0.12.2 (2017-03-10)
-------------------
* Left curve list will display current value from vertical tracker
* new splashscreen phrases
* Temporarily disabling Qt5Svg
* Contributors: Davide Faconti


0.12.0 (2017-03-06)
-------------------
* Create .appveyor.yml
* added the ability to save rosbags from streaming
* bug fixes
* might fix compilation problem in recent cmake (3.x)
* improvement of the horizontal slider
* save plots to file
* qwt updated to trunk
* catch the rosbag exception
* Contributors: Davide Faconti

0.11.0 (2017-02-23)
-------------------
* should fix the reloading issue
* Update README.md
* minor fixes of the help_dialog layout
* Contributors: Davide Faconti, MarcelSoler

0.10.3 (2017-02-21)
-------------------
* adding help dialog
* minor bug fix
* Contributors: Davide Faconti

0.10.2 (2017-02-14)
-------------------
* critical bug fixed in ROS streaming
* Contributors: Davide Faconti

0.10.1 (2017-02-14)
-------------------
* adding more command line functionality
* BUG-FIX: bad resizing when a matrix row or column is deleted
* simplifying how random colors are managed
* more streaming buffer
* remember selected topics
* improvements and bug fixes
* Contributors: Davide Faconti

0.10.0 (2017-02-12)
-------------------
* auto loading of streamer based on saved layout
* refactoring of the ROS plugins 
* REFACTORING to allow future improvements of drag&drop
* trying to fix a compilation problem
* Update README.md
* FIX: menu bar will stay where it is supposed to.
* Contributors: Davide Faconti

0.9.1 (2017-02-09)
------------------
* FIX: avoid the use of catkin when using plain cmake
* IMPROVEMENT: exit option in the file menu
* IMPROVEMENT: reduce the number of steps to launch a streamer
* SPEEDUP: use a cache to avoid repeated creation of std::string
* better way to stop streaming and reload the plugins
* fixed a compilation problem on windows
* fixed a problem with resizing
* help menu with About added
* qDebug commented
* default to RelWithDebInfo
* Contributors: Davide Faconti

0.9.0 (2017-02-07)
------------------
* bug fixes
* QWT submodule removed
* removed boost dependency
* Contributors: Davide Faconti

* remove submodule
* Contributors: Davide Faconti

0.8.1 (2017-01-24)
------------------
* removing the old name "SuperPlotter"
* bug fix that affected data streaming
* this explicit dependency might be needed by bloom

0.8.0 (2017-01-23)
------------------
* First official beta of PJ
* Contributors: Arturo Martin-de-Nicolas, Davide Faconti, Kartik Mohta, Mikael Arguedas
