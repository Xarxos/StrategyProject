#pragma once

/*
TODO
----
- Make it so that you can enter that region from the world map.
- Implement specific tile data boxes for each of those tiles that can properly display their Bedrock data.

- Consider creating a separate WorldGenerator class or something. Or implement it as its own separate program altogether which writes to text files and then import those text files
	to the actual game.

- One of these days, sit down and really think about dat Asset Manager and how assets are loaded and shit.
	Like, should there be an unload function, and if so, when would it be used?
	Should assets always be loaded just before they're used or should they be pre-loaded in the GameLoadState or something? Maybe only sometimes? If so, when and when not?
- Actually, consider cleaning up a few classes here and there, like break out functions, restructure stuff, or something.

- Consider if input checks for the HUD should go before input checks for the substates in WorldMap.
- Maybe make a link-thing that can turn any sprite/shape/text into a button which takes you to some place or another... you know, opens a specific box or something.
*/