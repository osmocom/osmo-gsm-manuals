#!/usr/bin/env python3
# Rewrite the revhistory part of the document for vty reference (OS#4063)
import os
import shutil
import sys

xml_in = sys.argv[1]
xml_out = os.environ["TEMPFILE"]
git_date = os.environ["GIT_DATE"]
revnumber = os.environ["REVNUMBER"]


def get_author_initials(line):
    return line.split("<authorinitials>")[1].split("</authorinitials>")[0]


def write_revhistory_block(h_out, author_initials):
    h_out.write("<revhistory>\n")
    h_out.write("<revision>\n")
    h_out.write(f"<revnumber>{revnumber}</revnumber>\n")
    h_out.write(f"<date>{git_date}</date>\n")
    h_out.write(f"<authorinitials>{author_initials}</authorinitials>\n")
    h_out.write("<revremark>Automatically Generated VTY Reference</revremark>\n")
    h_out.write("</revision>\n")
    h_out.write("</revhistory>\n")


def set_revhistory():
    """
    Replace the part of the docbook that looks like the following, and copy
    all other lines. Just using python's xml library would be better, but it
    fails on docbook's custom DTDs.
    <revhistory>
        <revision>
            <revnumber>v1</revnumber>
            <date>18th September 2017</date>
            <authorinitials>nh</authorinitials>
            <revremark>Initial</revremark>
        </revision>
    </revhistory>
    """
    before = 0
    inside = 1
    after = 2

    pos = before
    author_initials = ""

    with open(xml_out, "w") as h_out:
        with open(xml_in, "r") as h_in:
            for line in h_in.readlines():
                if pos == before:
                    if "<revhistory>" in line:
                        h_out.write(line.split("<revhistory>")[0] + "\n")
                        pos = inside

                if pos in [before, after]:
                    h_out.write(line)

                if pos == inside:
                    if "<authorinitials>" in line:
                        author_initials = get_author_initials(line)
                    if "</revhistory>" in line:
                        write_revhistory_block(h_out, author_initials)
                        h_out.write(line.split("</revhistory>")[1])
                        pos = after


def main():
    if xml_in.endswith("-vty-reference.xml"):
        print(f"Changing revhistory to {revnumber}, {git_date}...")
        set_revhistory()
    else:
        print("Copying without change of revhistory...")
        shutil.copyfile(xml_in, xml_out)


main()
