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

#import "SL3PreparedStatement.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3Connection SL3Connection.h ObjSQLite3/ObjSQLite3.h
 *
 * @brief A connection to a database.
 */
@interface SL3Connection: OFObject
{
#ifdef SL3_PUBLIC_IVARS
@public
#endif
	sqlite3 *_conn;
}

/**
 * @brief Creates a new connection to the database at the specified IRI.
 *
 * @param IRI The IRI to the database
 * @return A new database connection
 * @throw SL3OpenFailedException The database could not be opened
 */
+ (instancetype)connectionWithIRI: (OFIRI *)IRI;

/**
 * @brief Creates a new connection to the database at the specified IRI.
 *
 * @param IRI The IRI to the database
 * @param flags The flags to open the database with
 * @return A new database connection
 * @throw SL3OpenFailedException The database could not be opened
 */
+ (instancetype)connectionWithIRI: (OFIRI *)IRI flags: (int)flags;

/**
 * @brief Initializes an already allocated connection to connect to the
 *	  database at the specified IRI.
 *
 * @param IRI The IRI to the database
 * @return An initialized connection to the specified database
 * @throw SL3OpenFailedException The database could not be opened
 */
- (instancetype)initWithIRI: (OFIRI *)IRI;

/**
 * @brief Initializes an already allocated connection to connect to the
 *	  database at the specified IRI.
 *
 * @param IRI The IRI to the database
 * @param flags The flags to open the database with
 * @return An initialized connection to the specified database
 * @throw SL3OpenFailedException The database could not be opened
 */
- (instancetype)initWithIRI: (OFIRI *)IRI
		      flags: (int)flags OF_DESIGNATED_INITIALIZER;

/**
 * @brief Prepares the specified SQL statement for the connection and returns
 *	  it.
 *
 * @param SQLStatement An SQL statement to prepare
 * @return A prepared statement
 * @throw SL3PrepareStatementFailedException The statement could not be prepared
 */
- (SL3PreparedStatement *)prepareStatement: (OFConstantString *)SQLStatement;

/**
 * @brief Executes the specified statement without results.
 *
 * @param SQLStatement The SQL statement to execute
 * @throw SL3ExecuteStatementFailedException The statement could not be executed
 */
- (void)executeStatement: (OFConstantString *)SQLStatement;

#ifdef OF_HAVE_BLOCKS
/**
 * @brief Executes the specified block in an transaction.
 *
 * Before the block is executed, a transaction is started. If the block returns
 * true, the transaction is committed. If the block returns true or throws an
 * exception, the transaction is rolled back.
 *
 * @param block The block to execute in a transaction
 */
- (void)transactionWithBlock: (bool (^)(void))block;
#endif
@end

OF_ASSUME_NONNULL_END
