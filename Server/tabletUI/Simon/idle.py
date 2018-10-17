from ctypes import cdll

game = cdll.LoadLibrary('simonSays.dll')
game.idleTest('169.254.79.239')
