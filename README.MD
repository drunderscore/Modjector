# Modjector
A base DLL injector, that has some not-so-important modding capabilities.

## How to use
Inject the built DLL into an application of your choice. It will open a console window, which has both output and input.

All mods have a `Main` and an `Think` virtual methods. A test mod is included in the build, which you can inject into whatever you want for testing.

## How should I inject it?
There is no one *undetectable* or *best* way to inject a DLL. Simply use whatever tool you prefer to inject the built DLL into an application of your choice.

## What to expect in the future
Some of the few things I would like to accomplish with this modbase:
* Console input
	* Concommands and *(maybe)* convars. Pretty much copy what Source Engine console is like.
* Better keyboard and mouse events for mods to use. (instead of using `GetAsyncKeyState` and mouse hooks)
* Ways to reload mods, and unload the DLL itself.