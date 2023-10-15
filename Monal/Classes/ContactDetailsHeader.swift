//
//  ContactDetailsHeader.swift
//  ContactDetailsHeader
//
//  Created by Friedrich Altheide on 03.09.21.
//  Copyright © 2021 Monal.im. All rights reserved.
//

import MobileCoreServices
import UniformTypeIdentifiers
import SwiftUI
import monalxmpp

struct ContactDetailsHeader: View {
    var delegate: SheetDismisserProtocol
    @StateObject var contact: ObservableKVOWrapper<MLContact>
    @State private var navigationAction: String?

    var body: some View {
        VStack(alignment: .center) {
            HStack {
                Spacer()
                Image(uiImage: contact.avatar)
                    .resizable()
                    .frame(width: 150, height: 150, alignment: .center)
                    .scaledToFit()
                    .shadow(radius: 7)
                Spacer()
            }
            
            Spacer()
                .frame(height: 20)
            HStack {
                Text(contact.contactJid as String)
                //for ios >= 15.0
                //.textSelection(.enabled)
                Spacer().frame(width: 10)
                Button(action: {
                    UIPasteboard.general.setValue(contact.contactJid as String, forPasteboardType:UTType.utf8PlainText.identifier as String)
                }) {
                    Image(systemName: "doc.on.doc")
                        .foregroundColor(.primary)
                }
                .buttonStyle(BorderlessButtonStyle())
            }
            //only show account jid if more than one is configured
            if MLXMPPManager.sharedInstance().connectedXMPP.count > 1 && !contact.isSelfChat {
                Text("Account: \(MLXMPPManager.sharedInstance().getConnectedAccount(forID:contact.accountId)!.connectionProperties.identity.jid)")
            }
            
            if !contact.isSelfChat && !contact.isGroup {
                Spacer()
                    .frame(height: 20)
                if let lastInteractionTime = contact.lastInteractionTime as Date? {
                    if lastInteractionTime.timeIntervalSince1970 > 0 {
                        Text(String(format: NSLocalizedString("Last seen: %@", comment: ""),
                            DateFormatter.localizedString(from: lastInteractionTime, dateStyle: DateFormatter.Style.short, timeStyle: DateFormatter.Style.short)))
                    } else {
                        Text(String(format: NSLocalizedString("Last seen: %@", comment: ""), NSLocalizedString("now", comment: "")))
                    }
                } else {
                    Text(String(format: NSLocalizedString("Last seen: %@", comment: ""), NSLocalizedString("unknown", comment: "")))
                }
            }
            
            if(!contact.isGroup && (contact.statusMessage as String).count > 0) {
                Spacer()
                    .frame(height: 20)
                Text("Status message:")
                Text(contact.statusMessage as String)
                    .fixedSize(horizontal: false, vertical: true)
            }
            
            if(contact.isGroup && (contact.groupSubject as String).count > 0) {
                Spacer()
                    .frame(height: 20)
                if(contact.obj.mucType == "group") {
                    Text("Group subject:")
                } else {
                    Text("Channel subject:")
                }
                Text(contact.groupSubject as String)
                    .fixedSize(horizontal: false, vertical: true)
            }
        }
        .foregroundColor(.primary)
        .padding([.top, .bottom])
    }
}

struct ContactDetailsHeader_Previews: PreviewProvider {
    static var delegate = SheetDismisserProtocol()
    static var previews: some View {
        ContactDetailsHeader(delegate:delegate, contact:ObservableKVOWrapper<MLContact>(MLContact.makeDummyContact(0)))
        ContactDetailsHeader(delegate:delegate, contact:ObservableKVOWrapper<MLContact>(MLContact.makeDummyContact(1)))
        ContactDetailsHeader(delegate:delegate, contact:ObservableKVOWrapper<MLContact>(MLContact.makeDummyContact(2)))
        ContactDetailsHeader(delegate:delegate, contact:ObservableKVOWrapper<MLContact>(MLContact.makeDummyContact(3)))
        ContactDetailsHeader(delegate:delegate, contact:ObservableKVOWrapper<MLContact>(MLContact.makeDummyContact(4)))
    }
}
