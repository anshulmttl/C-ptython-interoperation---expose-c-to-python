import HelloExt
import struct

configDir = "C:\ProgramFiles"
holder = HelloExt.fcCarEngine_EngineCreatePy(configDir)
HelloExt.fcCarEngine_EngineDestroyPy(holder)
