import os

qute = Browser()

class Browser:
    def __init__(self):
        self.commandQueue = os.getenv('QUTE_FIFO')
        self.url= os.getenv('QUTE_URL')

    def url(self):
        return self.url
    
    def executeCommand(self, command):
        with open(self.commandQueue) as fifo:
            fifo.write(command)


