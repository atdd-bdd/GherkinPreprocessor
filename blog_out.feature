Given a transaction is authorised on 20-OCT-2020
And the transaction was not charged 
When the cancellation job runs for 19-NOV-2020
Then the authorisation should be cancelled

Given a transaction is authorised on 8 October 2020
And the transaction was not charged
When the cancellation job runs for 9 November 2020
Then the authorisation should be cancelled

Given a transaction was authorised more than a month ago 
And the transaction was not charged 
When the cancellation job runs
Then the authorisation should be cancelled

Given the current time is 2020-10-09T14:27:46.000Z
And a transaction is authorised
When the current time is 2020-11-09T14:27:46.001Z
And the transaction was not charged
And the cancellation job runs
Then the authorisation should be cancelled
