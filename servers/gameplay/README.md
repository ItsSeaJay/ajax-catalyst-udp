# AjaxCatalystGameplayServer
This is the primary server that the client connects to, and the only one that's
essential for gameplay. It's responsible for managing incoming and outgoing
connections, and synchronising the game state across all connected clients.

Primarily, this refers to movement positions and where each cat is on the map.