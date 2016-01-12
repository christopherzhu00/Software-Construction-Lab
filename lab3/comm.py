#!/usr/bin/python
import random, sys, locale
from optparse import OptionParser
class comm:
    def __init__(self, args, args2):
        f = open(args, 'r')
        self.lines = f.read().splitlines()
        f.close()
        f2 = open(args2, 'r')
        self.lines2 = f2.read().splitlines()
        f2.close()
    def readLines1(self):
        return self.lines
        
    def readLines2(self):
        return self.lines2
        
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Outputs Differences between FILE1 and FILE2."""
    
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1",
                    action="store_true", dest="column_1", 
                    default=False,
                    help="suppress column 1")
    parser.add_option("-2",
                    action="store_true", dest="column_2", 
                    default=False,
                    help="suppress column 2")
    parser.add_option("-3",
                    action="store_true", dest="column_3", 
                    default=False,
                    help="suppress column 3")
    parser.add_option("-u",
                    action="store_true", dest="unsorted", 
                    default=False,
                    help="compatible with unsorted")
    options, args = parser.parse_args(sys.argv[1:])
    if len(args) != 2:
        parser.error("wrong number of operands")
    lead1 = ""
    lead2 = ""
    if options.column_1 == False:
        lead1 += "\t"
    if options.column_2 == False:
        lead2 += "\t"
    
    input_file = args[0]
    input_file2 = args[1]
    try:
        generator = comm(input_file, input_file2)
    except IOError as err:
        parser.error("I/O error({0}): {1}". 
            format(err.errno, err.sterror))
    list1 = generator.readLines1()
    list2 = generator.readLines2()
    count1 = 0
    count2 = 0
    total = len(generator.readLines2()) + len(generator.readLines1())
    if options.unsorted == True:            #Brute force the search
        for cur in list1:                   #goes through first list
            if cur in list2:
                if options.column_3 == False:
                    sys.stdout.write(lead1)
                    sys.stdout.write(lead2)
                    sys.stdout.write(cur)
                    sys.stdout.write("\n")
                list2.remove(cur)
            else:
                if options.column_1 == False:
                    sys.stdout.write(cur)
                    sys.stdout.write("\n")
        for current in list2:
            if options.column_2 == False:
                sys.stdout.write(lead1)
                sys.stdout.write(current)
                sys.stdout.write("\n")
                    
    else:
        for index in range(total):
            if count1 < len(list1) and count2 < len(list2):
                if locale.strcoll(list1[count1],
                                  list2[count2]) < 0:
                    if options.column_1 == False:
                        sys.stdout.write(list1[count1])
                        sys.stdout.write("\n")
                    count1 += 1
                elif locale.strcoll(list1[count1], 
                    list2[count2]) > 0:
                    if options.column_1 == False and options.column_2 == False:
                        sys.stdout.write(lead1)
                    if options.column_2 == False:
                        sys.stdout.write(list2[count2])
                        sys.stdout.write("\n")
                    count2 += 1
                elif locale.strcoll(list1[count1], 
                    list2[count2]) == 0:
                    if options.column_3 == False:
                        sys.stdout.write(lead1)
                        sys.stdout.write(lead2)
                        sys.stdout.write(list1[count1])
                        sys.stdout.write("\n")
                    count1 += 1 
                    count2 += 1         
        while count1 < len(list1):
            sys.stdout.write(list1[count1] + "\n")
            count1 += 1
        if options.column_2 == False:
            while count2 < len(list2):
                if options.column_1 == False and options.column_2 == False:
                    sys.stdout.write("\t")
                sys.stdout.write(list2[count2] + "\n")
                count2 += 1
if __name__ == "__main__":
    main()