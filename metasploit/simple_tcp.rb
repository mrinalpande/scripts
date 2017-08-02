require 'msf/core'
class Metasploit3 < Msf::Auxiliary
    include Msf::Exploit::Remote::Tcp
    include Msf::Auxiliary::Scanner

    def initialize
        super(
            'Name'          => 'Custom TCP Port Sacnner'
            'Version'       => '$Revision: 1 $'
            'Description'   => %q(Quick Tcp scanner for port 4444 used by
                                  exploits commonly found on the internet.)
            'Author'        => 'Mrinal Pande'
            'License'       => MSF_LICENSE
        )
        regiester_options(
            [
                Opt::RPORT(4444)
            ]
        ),self.class)
    end
    
    def run_host(ip)
        connect()
        greeting = "HELLO Server"
        sock.puts(greeting)
        data = sock.recv(1024)
        print_status("Port Open:: Received : #{data} from {#ip}")
        disconnect()
    end
end