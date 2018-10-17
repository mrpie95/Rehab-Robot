from ctypes import cdll

game = cdll.LoadLibrary('simonSays.dll')
game.python_entry_init('HandsOnHead,HandsOnHips,HandsOnShoulders,WaveLeftHand,WaveRightHand,StandOnOneLeg,Squat,HandsOutFront', '169.254.79.239')
