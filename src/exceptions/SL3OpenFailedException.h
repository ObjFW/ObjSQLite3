/*
 * Copyright (c) 2020, 2024, 2025 Jonathan Schleifer <js@nil.im>
 *
 * https://git.nil.im/ObjFW/ObjSQLite3
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

#import "SL3Exception.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class SL3OpenFailedException SL3OpenFailedException.h
 *	  ObjSQLite3/ObjSQLite3.h
 *
 * @brief An exception indicating that a database could not be opened.
 */
@interface SL3OpenFailedException: SL3Exception
{
	OFIRI *_IRI;
	int _flags;
}

/**
 * @brief The IRI of the database that could not be opened.
 */
@property (readonly, nonatomic) OFIRI *IRI;

/**
 * @brief The flags with which the database could not be opened.
 */
@property (readonly, nonatomic) int flags;

+ (instancetype)exceptionWithConnection: (nullable SL3Connection *)connection
			      errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Creates a new open failed exception.
 *
 * @param IRI The IRI of the database that could not be opened
 * @param flags The flags with which the database could not be opened
 * @param errorCode The SQLite3 error code
 * @return A new, autoreleased open failed exception
 */
+ (instancetype)exceptionWithIRI: (OFIRI *)IFI
			   flags: (int)flags
		       errorCode: (int)errorCode;

- (instancetype)initWithConnection: (nullable SL3Connection *)connection
			 errorCode: (int)errorCode OF_UNAVAILABLE;

/**
 * @brief Initializes an already allocated open failed exception.
 *
 * @param IRI The IRI of the database that could not be opened
 * @param flags The flags with which the database could not be opened
 * @param errorCode The SQLite3 error code
 * @return An initialized open failed exception
 */
- (instancetype)initWithIRI: (OFIRI *)IRI
		      flags: (int)flags
		  errorCode: (int)errorCode OF_DESIGNATED_INITIALIZER;
@end

OF_ASSUME_NONNULL_END
