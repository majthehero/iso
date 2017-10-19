# iso
## Goals of project
Finally learn cpp.
Design and implement a simple game engine.
Implement a game in said engine.
## Progress
Subsystems are:
  - InputSystem: listens for kbd and mouse events. Generates commands and drops unused events.
  - GameSystem: executes commands from InputSystem. Generates commands for RenderSystem.
  - RenderSystem: renders. Currently placeholder 2D grid environment.
  
Subsystems communicate via MessageBus, implemented as a vector.
MessageBus will periodically empty itself, keeping unread messages.
