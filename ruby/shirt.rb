#!/usr/bin/env ruby
require 'shellwords'

BUILTINS = {
	'cd' => lambda { |dir = '/home/nicolas'| Dir.chdir(dir) }, #hack
	'exit' => lambda { |code = 0| exit(code.to_i) },
	'exec' => lambda { |*command| exec *command },
	'set' => lambda {|args| 
		key, value = args.split('=')
		ENV[key] = value
	}
}


loop do
	$stdout.print '-> '
	line = $stdin.gets.strip 
	command, *arguments = Shellwords.shellsplit(line)

	if BUILTINS[command]
		BUILTINS[command].call(*arguments)
	else
		pid = fork {
			exec line
		}
		Process.wait pid
	end

end

