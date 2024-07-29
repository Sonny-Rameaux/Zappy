import sys

class errorParsing(Exception):
    pass

def parse_args():
    args = sys.argv
    if len(args) == 2:
        if args[1] == "-help":
            raise errorParsing("USAGE: ./zappy_ai -p port -n name [-h machine]")
        else:
            raise errorParsing("Error with number of arguments or type")
    
    if len(args) < 5:
        raise errorParsing("Error with number of arguments or type")
    if len(args) == 6:
        raise errorParsing("Error with number of arguments or type")
    if args[1] != '-p' or args[3] != '-n':
        raise errorParsing("Error with number of arguments or type")
    
    params = {
        'port': None,
        'name': None,
        'host': 'localhost'
    }

    if args[1] == '-p' and args[3] == '-n':
        if len(args) == 5 or len(args) == 7:
            if not args[2].isdigit():
                raise errorParsing("Error with number of arguments or type")
            params['port'] = int(args[2])
            params['name'] = args[4]
            if len(args) == 7:
                if args[5] == "-h":
                    params['host'] = args[6]
                else:
                    raise errorParsing("Error with number of arguments or type")
        else:
            raise errorParsing("Error with number of arguments or type")
    else:
        raise errorParsing("Error with number of arguments or type")
    
    return params