Networking Library

Design a library which can be used to build networked client/server applications. The intent of the library is to abstract out low-level details of socket I/O and allow users to focus on the application programming logic rather than the low-level networking details.
Assume we have standard OS capability for asynchronous send/receive - something like GetQueuedCompletion status.

Requirements from the library:
- Ability to write a server application as well client application.
- Managing client connections. (for a server application)
- Support for synchronous as well as asynchronous send and receive.
- Support for multiple protocols. The library should provide HTTP, but the user should be to provide his/her own protocol. Protocol is a higher level of abstraction than the networking library, but at a lower level relative to the Application. Hence the library can be thought of as having a networking layer and a protocol layer on top of it.
- Multi-OS support. Note that you don't have to solve how asynchronous IO will happen on different OSes, just that there are different ways to do it on different machines.
- Ability to handle streamed messages. Streamed messages are those which are very large, hence the entire message cannot be read before processing it. (Eg: transferring a 10 GB file over network).

As with last week, we will contrast different design approaches, viz, OO vs non OO.
