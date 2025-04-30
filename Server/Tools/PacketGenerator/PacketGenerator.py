import argparse
import jinja2

def main():

    arg_parser = argparse.ArgumentParser(description="Packet Generator")
    arg_parser.add_argument("--path", type=str, default="C:/Users/rkddl/Desktop/Study/study-cplus-tcp_server/Server/Common/Protobuf/bin/Protocol.proto", help="proto path")
    arg_parser.add_argument("--output", type=str, default="TestPacketHandler", help="output file")
    arg_parser.add_argument("--recv", type=str, default="C_", help="recv convention")
    arg_parser.add_argument("--send", type=str, default="S_", help="send convention")
    args = arg_parser.parse_args()


    return

if __name__ == "__main__":
    main()