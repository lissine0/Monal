//
//  BlockedUsers.swift
//  Monal
//
//  Created by lissine on 5/9/2024.
//  Copyright © 2024 monal-im.org. All rights reserved.
//

struct BlockedUsers: View {
    let xmppAccount: xmpp
    var body: some View {
        let arr = DataLayer.sharedInstance().blockedJids(forAccount: xmppAccount.accountID)

        if arr.isEmpty {
            Text("No Blocked addresses found")
        }
        else {
            Text("yay")
        }
    }
}
