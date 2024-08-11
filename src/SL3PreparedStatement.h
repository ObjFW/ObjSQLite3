/*
 * Copyright (c) 2020, 2024 Jonathan Schleifer <js@nil.im>
 *
 * https://fl.nil.im/objsqlite3
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#import <ObjFW/ObjFW.h>

#include <sqlite3.h>

OF_ASSUME_NONNULL_BEGIN

@class SL3Connection;

/**
 * @class SL3PreparedStatement SL3PreparedStatement.h ObjSQLite3/ObjSQLite3.h
 *
 * @brief A prepared statement.
 */
@interface SL3PreparedStatement: OFObject
{
#ifdef SL3_PUBLIC_IVARS
@public
#endif
	SL3Connection *_connection;
	sqlite3_stmt *_stmt;
}

/**
 * @brief The current row as an array.
 */
@property (readonly, nonatomic) OFArray *currentRowArray;

/**
 * @brief The current row as a dictionary.
 */
@property (readonly, nonatomic)
    OFDictionary OF_GENERIC(OFString *, id) *currentRowDictionary;

/**
 * @brief Binds the objects from the specified array.
 *
 * @param array An array of objects to bind
 * @throw OFOutOfRangeException The array has more objects than columns
 */
- (void)bindWithArray: (OFArray *)array;

/**
 * @brief Binds the objects from the specified dictionary that maps each column
 *	  name to a value.
 *
 * @param dictionary A map of column names to values
 * @throw OFUndefinedKeyException A column name which does not exist was
 *				  specified
 */
- (void)bindWithDictionary:
    (OFDictionary OF_GENERIC(OFString *, id) *)dictionary;

/**
 * @brief Clears all bindings.
 *
 * @throw SL3ClearBindingsFailedException The bindings could not be cleared
 */
- (void)clearBindings;

/**
 * @brief Steps the prepared statement, returning the next row, if any.
 *
 * @return Whether there was another row
 * @throw SL3ExecuteStatementFailedException Executing the prepared statement
 *					     failed
 */
- (bool)step;

/**
 * @brief Returns the object for the specified column of the current row.
 */
- (id)objectForCurrentRowAtColumn: (size_t)column;

/**
 * @brief The number of columns.
 */
- (size_t)columnCount;

/**
 * @brief Returns the name for the specified column.
 */
- (OFString *)nameForColumn: (size_t)column;

/**
 * @brief Resets the prepared statement.
 *
 * @throw SL3ResetStatementFailedException The prepared statement could not be
 *					   reset
 */
- (void)reset;
@end

OF_ASSUME_NONNULL_END
