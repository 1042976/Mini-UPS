from django.db import connection
from collections import namedtuple


def namedtuplefetchall(cursor):
    """Return all rows from a cursor as a namedtuple"""
    desc = cursor.description
    nt_result = namedtuple('Result', [col[0] for col in desc])
    return [nt_result(*row) for row in cursor.fetchall()]


def get_shipment_status(package_id):
    with connection.cursor() as cursor:
        cursor.execute("SELECT STATUS FROM PACKAGE WHERE PACKAGE_ID = %s", [package_id])
        row = cursor.fetchone()
        if row is not None:
            return row[0]
    return None


def get_package_list(username):
    with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM PACKAGE WHERE USERNAME = %s", [username])
        results = namedtuplefetchall(cursor)
        if results is not None:
            return results
    return None


def get_package_id_list(username):
    with connection.cursor() as cursor:
        cursor.execute("SELECT PACKAGE_ID FROM PACKAGE WHERE USERNAME = %s", [username])
        row = cursor.fetchall()
        if row is not None:
            return [r[0] for r in row]
    return None


def get_item_list(package_id):
    with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM ITEM WHERE PACKAGE_ID = %s ORDER BY NAME ", [package_id])
        results = namedtuplefetchall(cursor)
        if results is not None:
            return results
    return None

def get_selected_package_list(username, package_id_list):
    with connection.cursor() as cursor:
        for package_id in package_id_list:
            cursor.execute("SELECT * FROM PACKAGE WHERE PACKAGE_ID = %s ", [package_id])
            row = cursor.fetchall()
            if row is not None:
                return [r[0] for r in row]
    return None

def get_selected_package_id_list(username, itemname):
    with connection.cursor() as cursor:
        cursor.execute("SELECT PACKAGE_ID FROM ITEM WHERE NAME = %s ", [itemname])
        row = cursor.fetchall()
        if row is not None:
            return [r[0] for r in row]
    return None
